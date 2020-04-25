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
    char form [75];
    char temp[1500] = "<!DOCTYPE html>\
            <HTML lang=\"en-us\">\
            <HEAD>\
                <TITLE>\
                    Air Quality Setup\
                </TITLE>\
            </HEAD>\
            <BODY>\
                <form action=\"/formularPost\" method=\"POST\">\0";
    char temp1[1500];
    

    for(int i=0;i < KEY_AMOUNT;++i){
        Serial.print("In For: ");
        Serial.println(temp);
        snprintf(temp1,1500,"%s",temp);
        snprintf(temp,1500,"%s\n%s", temp1, config_mode.createHTMLForKey(config_mode.keys[i], form));
    }

    snprintf(temp1,1500,"%s",temp);
    snprintf(temp,1500,"%s\
                    <button type=\"submit\">Submit</button>\
                </form>\
            </BODY>\
            </HTML>"
    ,temp1);


    config_mode.server.send(200,"text/html",temp);
    return 0;
}

WebServer::THandlerFunction ConfigMode::formularPost() {
    return 0;
}

char * ConfigMode::createHTMLForKey(const char * key, char * htmlChar){
    CONFIG_TYPE keyType = configuration.getType(key);
    
    switch(keyType) {
        case CONFIG_TYPE::STRING:
            snprintf(htmlChar,100, 
            
            "<label for=\"%s\">%s:\
                <input id=\"%s\" name=\"%s\" value=\"%s\">\
            </label>"
            ,key,key,key,key,configuration.getString(key));
        break;

        case CONFIG_TYPE::BOOL:
            if(configuration.getBool(key)){
                snprintf(htmlChar,100, 
                
                "<label for=\"%s\">%s:\
                    <input type=\"checkbox\" id=\"%s\" name=\"%s\" checked>\
                </label>"
                ,key,key,key,key);
            }else{
                snprintf(htmlChar,100, 
                
                "<label for=\"%s\">%s:\
                    <input type=\"checkbox\" id=\"%s\" name=\"%s\">\
                </label>"
                ,key,key,key,key);
            }
            
        break;

        case CONFIG_TYPE::INT:
            snprintf(htmlChar,100, 
            
            "<label for=\"%s\">%s:\
                <input id=\"%s\" name=\"%s\" value=\"%d\">\
            </label>"
            ,key,key,key,key,configuration.getInt(key));
        break;

        case CONFIG_TYPE::FALSE:
        default:
            return " \0";
        break;

        Serial.print("HTMLGEN: ");
        Serial.println(htmlChar);
        return htmlChar;

    }
}