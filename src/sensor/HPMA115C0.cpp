#include "HPMA115C0.hpp"

HPMA115C0::HPMA115C0() : Sensor()
{
    this->serialPort.begin(9600,SERIAL_8N1,RX2,TX2);
    this->data.pm10 = INVAL;
    this->data.pm4 = INVAL;
    this->data.pm25 = INVAL;
    this->data.pm1 = INVAL;
    // Disable auto send
    byte disable_auto_send[] = {0x68,0x01,0x20};
    this->sendChecksum(disable_auto_send, sizeof(disable_auto_send));
    this->command = HPMA_COMMAND::STOP_AUTO_SEND;
}

HPMA115C0::~HPMA115C0()
{
}

void HPMA115C0::handle()
{
    // Read out logic
    switch(this->command) {
        case HPMA_COMMAND::STOP_AUTO_SEND:
            // Auto send command answer
            if(this->serialPort.available()>=2) {
                if((this->serialPort.read()==0xA5) && (this->serialPort.read()==0xA5)) {
                    Serial.println("HPMA Auto send stopped");
                } else {
                    Serial.println("Error stopping HPMA auto send");
                }
                this->command = HPMA_COMMAND::NONE;
            }
        break;
        case HPMA_COMMAND::START_MEASUREMENT:
            // process command answer
            if(this->serialPort.available()>=2) {
                if((this->serialPort.read()==0xA5) && (this->serialPort.read()==0xA5)) {
                    Serial.println("HPMA measurement started");
                } else {
                    Serial.println("Error starting HPMA measurement");
                }
                this->command = HPMA_COMMAND::NONE;
            }
        break;
        case HPMA_COMMAND::READ_RESULTS:
            if(this->serialPort.available()>=2) {
                this->data.status = SENSOR_STATUS::ERROR;
                byte cmdbuffer[2];
                cmdbuffer[0] = this->serialPort.read();
                cmdbuffer[1] = this->serialPort.read();
                if(cmdbuffer[0] == 0x96 && cmdbuffer[1] == 0x96) {
                    // if 0x9696 continue, nothing happened
                    Serial.println("HPMA Measurement Results: Not available");
                } else if(cmdbuffer[0] == 0x40 && cmdbuffer[1] == 0x0D) {
                    Serial.println("HPMA Measurement Results: Found data available header");
                    // 0x0D bytes with results will follow
                    // ToDo: Do not block here.
                    while(this->serialPort.available()<0x0E);
                    byte databuffer[0x0D];
                    for(int i=0;i<0x0D;i++) {
                        databuffer[i] = this->serialPort.read();
                    }
                    if(databuffer[0]!=0x04) {
                        // Byte must be 0x04
                        Serial.println("HPMA Measurement Results: Invalid first data byte");                         
                        return;
                    }
                    // PM1=[1]*256+[2] usw.
                    this->data.pm1=(databuffer[1]*256+databuffer[2])*1000;
                    this->data.pm25=(databuffer[3]*256+databuffer[4])*1000;
                    this->data.pm4=(databuffer[5]*256+databuffer[6])*1000;
                    this->data.pm10=(databuffer[7]*256+databuffer[8])*1000;
                    this->data.status = SENSOR_STATUS::OK_MASS; 
                    // Update flags
                    this->measurement_running = false;
                    this->measurement_available = true;
                    // Ignore Checksum for now
                    this->serialPort.read();
                }
                this->command = HPMA_COMMAND::NONE;
            }
        break;
        default:
        while(this->serialPort.available()) {
            uint8_t received = this->serialPort.read();
            Serial.println(received,HEX);
        }
    }
    // Poll for results
    if(this->command == HPMA_COMMAND::NONE && this->measurement_running) {
        // Query status
        byte mesurement_read[] = {0x68,0x01,0x04};
        this->sendChecksum(mesurement_read, sizeof(mesurement_read));
        this->command = HPMA_COMMAND::READ_RESULTS;
    };
}

sensorData HPMA115C0::getData()
{
    this->measurement_available = false;
    return data;
}

void HPMA115C0::startMeasurement() {
    if(this->command == HPMA_COMMAND::NONE) {
        // Start measurement
        byte start_mesurement[] = {0x68,0x01,0x01};
        this->sendChecksum(start_mesurement, sizeof(start_mesurement));
        this->measurement_available = false;
        this->measurement_running = true;
        this->command = HPMA_COMMAND::START_MEASUREMENT;
    }
}
boolean HPMA115C0::measurementStatus() {
    return this->measurement_available;
}
void HPMA115C0::sendChecksum(byte data[], size_t len) {
    uint32_t checksum = 65536;
    for(int i=0;i<len;i++) {
        checksum-=data[i];
        this->serialPort.write(data[i]);
        // Serial.printf("Sending %x\n",data[i]);
    }
    uint8_t checksum_mod = checksum % 256;
    // Serial.printf("Sending checksum %x\n",checksum_mod);
    this->serialPort.write(checksum_mod);
}