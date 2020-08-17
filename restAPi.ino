#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#define HTTP_REST_PORT 80
#define WIFI_RETRY_DELAY 500
#define MAX_WIFI_INIT_RETRY 50

struct Led { 
    byte id;
    byte ida;
    byte idb;
    byte idc;
    byte idd;
    byte ide;
    byte idf;
    byte idg;
    byte idh;
    byte idi;
    byte idj;
    byte idk;
    byte idl;
    byte idm;
    byte idn;
} led_resource;

const char* wifi_ssid = "gaya_SLT";
const char* wifi_passwd = "gaya1993";

ESP8266WebServer http_rest_server(HTTP_REST_PORT);

void init_led_resource()
{    
    led_resource.id = 1;
//    led_resource.ida = 10;
    led_resource.idb= 20;
    led_resource.idc = 30;
    led_resource.idd = 40;
    led_resource.ide = 50;
    led_resource.idf = 60;
    led_resource.idg = 70;
    led_resource.idh = 80;
    led_resource.idi = 90;
    led_resource.idj = 100;
    led_resource.idk = 110;
    led_resource.idl = 120;
    led_resource.idm = 130;
    led_resource.idn = 140;
}

int init_wifi() {
    int retries = 0;

    Serial.println("Connecting to WiFi AP..........");

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_passwd);
    // check the status of WiFi connection to be WL_CONNECTED
    while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY)) {
        retries++;
        delay(WIFI_RETRY_DELAY);
        Serial.print("#");
    }
    return WiFi.status(); // return the WiFi connection status
}

void get_leds() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[200];

    if (led_resource.id == 0)
        http_rest_server.send(204);
    else {
//        jsonObj["ida"] = led_resource.ida;
        jsonObj["idb"] = led_resource.idb;
        jsonObj["idc"] = led_resource.idc;
        jsonObj["idd"] = led_resource.idd;
        jsonObj["ide"] = led_resource.ide;
        jsonObj["idf"] = led_resource.idf;
        jsonObj["idg"] = led_resource.idg;
        jsonObj["idh"] = led_resource.idh;
        jsonObj["idi"] = led_resource.idi;
        jsonObj["idj"] = led_resource.idj;
        jsonObj["idk"] = led_resource.idk;
        jsonObj["idl"] = led_resource.idl;
        jsonObj["idm"] = led_resource.idm;
        jsonObj["idn"] = led_resource.idn;
        jsonObj.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
        http_rest_server.send(200, "application/json", JSONmessageBuffer);
    }
}

void json_to_resource(JsonObject& jsonBody) {
    int ida, idb, idc, idd, ide, idf, idg, idh, idi, idj, idk, idl, idm, idn;
   
    ida = jsonBody["ida"];
    idb = jsonBody["idb"];
    idc = jsonBody["idc"];
    idd = jsonBody["idd"];
    ide = jsonBody["ide"];
    idf = jsonBody["idf"];
    idg = jsonBody["idg"];
    idh = jsonBody["idh"];
    idi = jsonBody["idi"];
    idj = jsonBody["idj"];
    idk = jsonBody["idk"];
    idl = jsonBody["idl"];
    idm = jsonBody["idm"];
    idn = jsonBody["idn"];
   
    
 

//    Serial.println(id);
//    Serial.println(gpio);
//    Serial.println(abc);

    led_resource.ida = ida;
    led_resource.idb = idb;
    led_resource.idc = idc;
    led_resource.idd = idd;
    led_resource.ide = ide;
    led_resource.idf = idf;
    led_resource.idg = idg;
    led_resource.idh = idh;
    led_resource.idi = idi;
    led_resource.idj = idj;
    led_resource.idk = idk;
    led_resource.idl = idl;
    led_resource.idm = idm;
    led_resource.idn = idn;
   
}

//void post_put_leds() {
//    StaticJsonBuffer<500> jsonBuffer;
//    String post_body = http_rest_server.arg("plain");
//    Serial.println(post_body);
//
//    JsonObject& jsonBody = jsonBuffer.parseObject(http_rest_server.arg("plain"));
//
//    Serial.print("HTTP Method: ");
//    Serial.println(http_rest_server.method());
//    
//    if (!jsonBody.success()) {
//        Serial.println("error in parsin json body");
//        http_rest_server.send(400);
//    }
//    else {   
//        if (http_rest_server.method() == HTTP_POST) {
//            if ((jsonBody["id"] != 0) && (jsonBody["id"] != led_resource.id)) {
//                json_to_resource(jsonBody);
//                http_rest_server.sendHeader("Location", "/leds/" + String(led_resource.id));
//                http_rest_server.send(201);
//                pinMode(led_resource.gpio, OUTPUT);
//            }
//            else if (jsonBody["id"] == 0)
//              http_rest_server.send(404);
//            else if (jsonBody["id"] == led_resource.id)
//              http_rest_server.send(409);
//        }
//        else if (http_rest_server.method() == HTTP_PUT) {
//            if (jsonBody["id"] == led_resource.id) {
//                json_to_resource(jsonBody);
//                http_rest_server.sendHeader("Location", "/leds/" + String(led_resource.id));
//                http_rest_server.send(200);
//                digitalWrite(led_resource.gpio, led_resource.status);
//            }
//            else
//              http_rest_server.send(404);
//        }
//    }
//}

void config_rest_server_routing() {
    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.send(200, "text/html",
            "Welcome to the ESP8266 REST Web Server");
    });
    http_rest_server.on("/sens", HTTP_GET, get_leds);
//    http_rest_server.on("/leds", HTTP_POST, post_put_leds);
//    http_rest_server.on("/leds", HTTP_PUT, post_put_leds);
}

void setup(void) {
    Serial.begin(115200);

    init_led_resource();
    if (init_wifi() == WL_CONNECTED) {
        Serial.print("Connetted to ");
        Serial.print(wifi_ssid);
        Serial.print("--- IP: ");
        Serial.println(WiFi.localIP());
    }
    else {
        Serial.print("Error connecting to: ");
        Serial.println(wifi_ssid);
    }

    config_rest_server_routing();

    http_rest_server.begin();
    Serial.println("HTTP REST Server Started");
}

void loop(void) {
    http_rest_server.handleClient();
}
