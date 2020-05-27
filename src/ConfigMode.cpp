#include "ConfigMode.hpp"

ConfigMode::ConfigMode() {
    
}

void ConfigMode::init() {
    this->server.on("/", this->formular);
    this->server.on("/configuration", this->formularPost);
    this->server.on("/stylesheet.css", this->sendCss);
    this->server.begin(80);
    Serial.println("Config Mode enabled");
}

void ConfigMode::handle() {
    this->server.handleClient();
}

WebServer::THandlerFunction ConfigMode::formular() {
    Serial.println("GET /");
    char form [FORM_SIZE];
    char temp[FORM_SIZE*KEY_AMOUNT+1250] = "<!DOCTYPE html>\n\
<HTML lang=\"en-us\">\n\
<HEAD>\n\
    <TITLE>\n\
        Air Quality Setup\n\
    </TITLE>\n\
    <link rel=\"stylesheet\" href=\"/stylesheet.css\" type=\"text/css\" />\n\
    <script>\n\
        function submitManually(){\n\
            const xhttp = new XMLHttpRequest();\n\
            const formData = new FormData(document.getElementById(\"settingsForm\"));\n\
            var q = new URLSearchParams();\n\
            for (const [key, val]  of formData.entries()) {\n\
                q.append( key, val );\n\
            }\n\
            xhttp.onreadystatechange = function() {\n\
                if (this.readyState == 4 && this.status == 200) {\n\
                    alert('hi');//document.getElementById(\"demo\").innerHTML = this.responseText;\n\
                }\n\
            };\n\
            xhttp.open(\"POST\", \"/configuration\", true);\n\
            xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n\
            xhttp.send(q);\n\
        }\n\
    </script>\n\
</HEAD>\n\
<BODY>\n\
    <form id=\"settingsForm\" onsubmit=\"submitManually();return false;\">\n\
    <table>\n\0";
    for(int i=0;i < KEY_AMOUNT;++i){
        strncat(temp,config_mode.createHTMLForKey(config_mode.keys[i], form),FORM_SIZE);
    }

    strncat(temp,"<\table>\n\
    <button type=\"submit\">Submit</button>\n\
    </form>\n\
</BODY>\n\
</HTML>"
            ,FORM_SIZE);


    config_mode.server.send(200,"text/html",temp);
    return 0;
}

WebServer::THandlerFunction ConfigMode::formularPost() {
    String boxName;
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
                    boxName = String(config_mode.keys[i]) + "Hidden";
                    if(config_mode.server.arg(boxName).compareTo(String("on"))){
                        Serial.println("Test 1");
                        if(config_mode.server.arg(config_mode.keys[i]).compareTo(String("on")) == 0){
                            configuration.setBool(config_mode.keys[i], true);
                        }else{
                        Serial.println("Test 2");
                        configuration.setBool(config_mode.keys[i], false);
                        }
                    }
                
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
<form action=\"/\" method=\"POST\">\
    <button type=\"submit\">Go to Settings</button>\
</form>");
    return 0;
}

WebServer::THandlerFunction ConfigMode::sendCss() {
    config_mode.server.send(200, "text/css", "\n");
    //to be filled out
    return 0;
}

char * ConfigMode::createHTMLForKey(const char * key, char * htmlChar){
    CONFIG_TYPE keyType = configuration.getType(key);
    String boxName;
    String stringConfig;
    
    switch(keyType) {
        case CONFIG_TYPE::STRING:
            char charBuffer [100];
            Serial.println(key);
            stringConfig = configuration.getString(key);
            Serial.println(stringConfig);
            if(stringConfig.length() >= 101){
                stringConfig.toCharArray(charBuffer,100);
            }else{
                stringConfig.toCharArray(charBuffer,stringConfig.length() + 1);
            }
                

            snprintf(htmlChar,FORM_SIZE,
            "<tr>\n\
<td> <label for=\"%s\" %s:> </label> </td>\n\
<td> <input id=\"%s\" name=\"%s\" type=\"text\" value=\"%s\"> </td>\n\
</tr>\n"
            ,key,key,key,key,charBuffer);
        break;

        case CONFIG_TYPE::BOOL:
            boxName = String(key) + "Hidden";
            char charBoxName [20];
            boxName.toCharArray(charBoxName,20);
            if(configuration.getBool(key)){
                snprintf(htmlChar,FORM_SIZE,
                "<tr> <td> <label for=\"%s\">%s: </label> </td>\n\
<td> <input type=\"checkbox\" id=\"%s\" name=\"%s\" checked>\n\
<input type=\"hidden\" id=\"%s\" name=\"%s\" checked> </td>\n\
</tr>\n"
                ,key,key,key,key,charBoxName,charBoxName);
            }else{
                snprintf(htmlChar,FORM_SIZE,                 
                "<tr> <td> <label for=\"%s\">%s: </label> </td>\n\
<td> <input type=\"checkbox\" id=\"%s\" name=\"%s\">\n\
<input type=\"hidden\" id=\"%s\" name=\"%s checked\"> </td>\n\
</tr>\n"
                ,key,key,key,key,charBoxName,charBoxName);
            }
            
        break;

        case CONFIG_TYPE::INT:
            snprintf(htmlChar,FORM_SIZE, 
            "<tr> <td> <label for=\"%s\" %s:> </label> </td>\n\
<td> <input id=\"%s\" name=\"%s\" type=\"text\" value=\"%d\"> </td>\n\
</tr>\n"
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