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
            // TODO
            // if 0x9696 continue, nothing happened
            // if 0x40??04, ??-1 bytes with measurement results will follow
            // save them to this->data, and set measurement_available to true
        break;
        default:
        while(this->serialPort.available()) {
            uint8_t received = this->serialPort.read();
            Serial.println(received,HEX);
        }
    }
    // Poll for results
    if(this->command == HPMA_COMMAND::NONE) {
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
    // Start measurement
    byte start_mesurement[] = {0x68,0x01,0x01};
    this->sendChecksum(start_mesurement, sizeof(start_mesurement));
    this->measurement_available = false;
    this->command = HPMA_COMMAND::START_MEASUREMENT;
}
boolean HPMA115C0::measurementStatus() {
    return this->measurement_available;
}
void HPMA115C0::sendChecksum(byte data[], size_t len) {
    uint32_t checksum = 65536;
    for(int i=0;i<len;i++) {
        checksum-=data[i];
        this->serialPort.write(data[i]);
        Serial.printf("Sending %x\n",data[i]);
    }
    uint8_t checksum_mod = checksum % 256;
    Serial.printf("Sending checksum %x\n",checksum_mod);
    this->serialPort.write(checksum_mod);
}