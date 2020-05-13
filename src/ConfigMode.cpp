#include "ConfigMode.hpp"

ConfigMode::ConfigMode() {
    
}

void ConfigMode::init() {
    this->server.on("/", this->formular);
    this->server.on("/configuration", this->formularPost);
    this->server.begin(80);
    Serial.println("Config Mode enabled");
}

void ConfigMode::handle() {
    this->server.handleClient();
}

WebServer::THandlerFunction ConfigMode::formular() {
    Serial.println("GET /");
    char form [FORM_SIZE];
    char temp[FORM_SIZE*KEY_AMOUNT+1500] = "<!DOCTYPE html>\
            <HTML lang=\"en-us\">\
            <HEAD>\
                <TITLE>\
                    Air Quality Setup\
                </TITLE>\
            </HEAD>\
            <BODY>\
                <form action=\"/configuration\" method=\"POST\">\n\0";

    for(int i=0;i < KEY_AMOUNT;++i){
        //Serial.print("In For: ");
        //Serial.println(temp);
        strncat(temp,config_mode.createHTMLForKey(config_mode.keys[i], form),FORM_SIZE);
    }

    strncat(temp,"\
                    <button type=\"submit\">Submit</button>\
                </form>\
            </BODY>\
            </HTML>"
    ,FORM_SIZE);


    config_mode.server.send(200,"text/html",temp);
    return 0;
}

WebServer::THandlerFunction ConfigMode::formularPost() {
    Serial.println("GET /configuration");
    for(int i=0;i < KEY_AMOUNT;++i){
        if(config_mode.server.hasArg(config_mode.keys[i])){
            Serial.println(config_mode.server.arg(config_mode.keys[i]));
            CONFIG_TYPE keyType = configuration.getType(config_mode.keys[i]);

            switch(keyType) {
                case CONFIG_TYPE::STRING:
                    char charBuffer [50];
                    config_mode.server.arg(config_mode.keys[i]).toCharArray(charBuffer,50);
                    configuration.setString(config_mode.keys[i], charBuffer);
                break;

                case CONFIG_TYPE::BOOL:
                    configuration.setBool(config_mode.keys[i], config_mode.server.arg(config_mode.keys[i]));        
                break;

                case CONFIG_TYPE::INT:
                    configuration.setInt(config_mode.keys[i], config_mode.server.arg(config_mode.keys[i]).toInt());
                break;

                case CONFIG_TYPE::FALSE:
                default:
                    
                break;
            }
        }
    }
    config_mode.server.send(200,"text/html","<!DOCTYPE html>\
            <HTML lang=\"en-us\">\
            <HEAD>\
                <TITLE>\
                    Air Quality Setup\
                </TITLE>\
            </HEAD>\
            <BODY>\
            <div id=\"Success\">\
                Configured!\
            </div>\
            <form action=\"/\" method=\"POST\">\
                <button type=\"submit\">Go Back</button>\
            </form>\
            ");
    return 0;
}

char * ConfigMode::createHTMLForKey(const char * key, char * htmlChar){
    CONFIG_TYPE keyType = configuration.getType(key);
    
    switch(keyType) {
        case CONFIG_TYPE::STRING:
            char charBuffer [100];
            configuration.getString(key).toCharArray(charBuffer,100);

            snprintf(htmlChar,FORM_SIZE, 
            
            "<label for=\"%s\">%s:\
                <input id=\"%s\" name=\"%s\" value=\"%s\">\
            </label><br />\n"
            ,key,key,key,key,charBuffer);
        break;

        case CONFIG_TYPE::BOOL:
            if(configuration.getBool(key)){
                snprintf(htmlChar,FORM_SIZE, 
                
                "<label for=\"%s\">%s:\
                    <input type=\"checkbox\" id=\"%s\" name=\"%s\" checked>\
                </label><br />\n"
                ,key,key,key,key);
            }else{
                snprintf(htmlChar,FORM_SIZE, 
                
                "<label for=\"%s\">%s:\
                    <input type=\"checkbox\" id=\"%s\" name=\"%s\">\
                </label><br />\n"
                ,key,key,key,key);
            }
            
        break;

        case CONFIG_TYPE::INT:
            snprintf(htmlChar,FORM_SIZE, 
            
            "<label for=\"%s\">%s:\
                <input id=\"%s\" name=\"%s\" value=\"%d\">\
            </label><br />\n"
            ,key,key,key,key,configuration.getInt(key));
        break;

        case CONFIG_TYPE::FALSE:
        default:
            return '\0';
        break;
    }

    //Serial.print("HTMLGEN: ");
    //Serial.println(htmlChar);
    return htmlChar;
}