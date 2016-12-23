
/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

/* Set these to your desired credentials. */
const char *ssid = "ESP8266";
const char *password = "123456789";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
//  server.send(200, "text/html", "{ jsonTest : {success:true, name: oxford} }" );
//	server.send(200, "text/html", "<h1>You are connected</h1>");
Serial.println("new client connected");
  server.on( "/testJsonObj",testJsonObj );

}

void testJsonObj(){
  Serial.println("resive post method!");

  //ให้ฝั่ง android convert json obj to string before send on post method!
  String data = server.arg("testSendJsonObj");
  Serial.println("----->"+data);
  
  StaticJsonBuffer<500> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);
  String showData = jObject["showData"];
  String dataInt = jObject["dataInt"];
  Serial.println("dataInt > "+dataInt);
  Serial.println("showData > "+showData);

  server.send(200, "text/html", "{ jsonTest : {success:true, name: oxford} }" );
  
}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
