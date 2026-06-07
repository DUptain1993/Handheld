//This program uses a web server webpage to control LED lights
//Directly enter the server IP address in the browser to access web pages

//pin usage as follow:
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL      VCC    GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27      5V     GND  

/***********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
#include <TFT_eSPI.h> 
#include <WiFi.h>

#define RED_PIN 22
#define GREEN_PIN 16
#define BLUE_PIN 17

#define LED_ON  LOW
#define LED_OFF HIGH

//Manually modifying parameters
const char *ssid = "yourssid";
const char *password = "yourpwd";

char t_buf[100] = {0};

// Set the web server port number to 80
WiFiServer server(80);
WiFiClient client;

// Variable to store the HTTP request
String header;

// Auxiliary variable for storing the current output state
String red_status = "off";
String green_status = "off";
String blue_status = "off";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define the timeout in milliseconds (eg: 2000ms = 2s)
const long timeoutTime = 2000;

TFT_eSPI my_lcd = TFT_eSPI();

void web_page(void)
{
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // Then the content-type, so the client knows what to expect, followed by the empty line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
            
  // turn gpio on and off
  if (header.indexOf("GET /red/on") >= 0) 
  {
    my_lcd.fillRect(10, 160, my_lcd.width()-1, 25,TFT_WHITE);
    my_lcd.drawString("RED LED ON", 10,160,2);
    red_status = "on";
    digitalWrite(RED_PIN, LED_ON);
  }
  else if (header.indexOf("GET /red/off") >= 0) 
  {
     my_lcd.fillRect(10, 160, my_lcd.width()-1, 25,TFT_WHITE);
     my_lcd.drawString("RED LED OFF", 10,160,2);
     red_status = "off";
     digitalWrite(RED_PIN, LED_OFF);
   } 
  else if (header.indexOf("GET /green/on") >= 0) 
  {
    my_lcd.fillRect(10, 185, my_lcd.width()-1, 25,TFT_WHITE);
    my_lcd.drawString("GREEN LED ON", 10,185,2);
    green_status = "on";
    digitalWrite(GREEN_PIN, LED_ON);
  }
  else if (header.indexOf("GET /green/off") >= 0) 
  {
     my_lcd.fillRect(10, 185, my_lcd.width()-1, 25,TFT_WHITE);
     my_lcd.drawString("GREEN LED OFF", 10,185,2);
     green_status = "off";
     digitalWrite(GREEN_PIN, LED_OFF);
   } 
   else if (header.indexOf("GET /blue/on") >= 0) 
   {
     my_lcd.fillRect(10, 210, my_lcd.width()-1, 25,TFT_WHITE);
     my_lcd.drawString("BLUE LED ON", 10,210,2);
     blue_status = "on";
     digitalWrite(BLUE_PIN, LED_ON);
   } 
   else if (header.indexOf("GET /blue/off") >= 0)
   {
     my_lcd.fillRect(10, 210, my_lcd.width()-1, 25,TFT_WHITE);
     my_lcd.drawString("BLUE LED OFF", 10,210,2);
     blue_status = "off";
     digitalWrite(BLUE_PIN, LED_OFF);
   }
   // Display HTML pages
   client.println("<!DOCTYPE html><html>");
   client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
   client.println("<link rel=\"icon\" href=\"data:,\">");
   // CSS to style the on/off button
   // Feel free to change the background color and font size properties to suit your preferences
   client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
   client.println(".button { background-color: #555555; border: none; color: white; padding: 16px 40px;");
   client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
   client.println(".button2 {background-color: #4CAF50;}</style></head>");
        
   // Page title
   client.println("<body><h1>ESP32 Web Server LED </h1>");

    // Display current status and ON/OFF button of red led
   client.println("<p>RED LED - State " + red_status + "</p>");
   // If red led status is off, show OFF button
   if (red_status=="off") 
   {
       client.println("<p><a href=\"/red/on\"><button class=\"button\">OFF</button></a></p>");
   }
   else
   {
       client.println("<p><a href=\"/red/off\"><button class=\"button button2\">ON</button></a></p>");
   } 
   
   // Display current status and ON/OFF button of green led
   client.println("<p>GREEN LED - State " + green_status + "</p>");
   // If green led  status is off, show OFF button
   if (green_status=="off") 
   {
       client.println("<p><a href=\"/green/on\"><button class=\"button\">OFF</button></a></p>");
   }
   else
   {
       client.println("<p><a href=\"/green/off\"><button class=\"button button2\">ON</button></a></p>");
   } 
               
   // Display current status and ON/OFF button of blue led
   client.println("<p> BLUE LED - State " + blue_status + "</p>");
   // If blue led status is off, show OFF button
   if (blue_status=="off") 
   {
      client.println("<p><a href=\"/blue/on\"><button class=\"button\">OFF</button></a></p>");
   } 
   else 
   {
      client.println("<p><a href=\"/blue/off\"><button class=\"button button2\">ON</button></a></p>");
   }
   client.println("</body></html>");
     
   // HTTP response ends with another blank line
   client.println();  
}


void setup() 
{
  Serial.begin(115200);
  // Initialize LED PIN
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  // Set LED PIN to HIGH
  digitalWrite(RED_PIN, LED_OFF);
  digitalWrite(GREEN_PIN, LED_OFF);
  digitalWrite(BLUE_PIN, LED_OFF);
  
  my_lcd.begin();
  my_lcd.setRotation(0);
  my_lcd.fillScreen(TFT_WHITE);
  my_lcd.setTextColor(TFT_RED);
  
  my_lcd.drawString("Start connecting to WiFi...", 10,55,2);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  my_lcd.fillRect(10, 55, my_lcd.width()-1, 25,TFT_WHITE);
  my_lcd.setTextColor(TFT_GREEN);
  my_lcd.drawString("Connection WIFI successful!!!", 10,55,2);
  my_lcd.setTextColor(TFT_BLUE);
  sprintf(t_buf, "SSID : %s", ssid);
  my_lcd.drawString(t_buf, 10,75,2);
  sprintf(t_buf, "  IP : %s", WiFi.localIP().toString().c_str());
  my_lcd.drawString(t_buf, 10,95,2);
  sprintf(t_buf, " MAC : %s", WiFi.macAddress().c_str());
  my_lcd.drawString(t_buf, 10,115,2);
  server.begin();
  my_lcd.drawString("Waiting for client connection", 10,135,2);
}

void loop()
{
  client = server.available();   // clients connect
  if (client) 
  {                  // If the current customer is available
    currentTime = millis();
    previousTime = currentTime;
    my_lcd.fillRect(10, 135, my_lcd.width()-1, 25,TFT_WHITE);
    my_lcd.drawString("Client connected.", 10,135,2);
    String currentLine = "";                // Create a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) // Loop while client connects
    {  
      currentTime = millis();
      if (client.available())   // If you want to read bytes from the client
      {            
        char c = client.read();             // Then read a byte
        Serial.write(c);                    // Print out on serial monitor
        header += c;
        if (c == '\n') 
        {                    // If the byte is a newline
          // If the current line is empty, there are two newlines on a line.
          // This is the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) 
          {
            web_page();
            // Out of the while loop
            break;
          } 
          else  // If you have a newline then clear currentLine
          { 
            currentLine = "";
          }
        } else if (c != '\r')  // If you get characters other than carriage return
        {  
          currentLine += c;      // Add it to the end of currentLine
        }
      }
    }
    // Clear header variable
    header = "";
    // Close the connection
    client.stop();
    my_lcd.fillRect(10, 135, my_lcd.width()-1, 25,TFT_WHITE);
    my_lcd.drawString("Client Disconnected.", 10,135,2);
  }
}
