//This example is to create a Bluetooth cable server and then communicate with a mobile app

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
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#define SERVICE_UUID             "DFCD0001-36E1-4688-B7F5-EA07361B26A8"
#define CHARACTERISTIC1_UUID     "DFCD000A-36E1-4688-B7F5-EA07361B26A8"
bool deviceConnected = false;
BLEServer *pServer;
BLEService *pService;
BLECharacteristic* pCharacteristic;
int i = 0;


TFT_eSPI my_lcd = TFT_eSPI(); 

class MyServerCallbacks: public BLEServerCallbacks 
{
    void onConnect(BLEServer* pServer) 
    {
      my_lcd.fillRect(10, 0, my_lcd.width()-1, 20,TFT_WHITE);
      my_lcd.drawString("BLE device connected.", 10, 0); 
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) 
    {
      my_lcd.fillRect(10, 0, my_lcd.width()-1, 20,TFT_WHITE);
      my_lcd.drawString("BLE device disconnected.", 10, 0);
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks 
{
    void onWrite(BLECharacteristic *pCharacteristic) 
    {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) 
      {
        if(i>27)
        {
          i = 0;
          my_lcd.fillRect(0, 32, my_lcd.width()-1, my_lcd.height()-32,TFT_WHITE); 
        }
        my_lcd.drawString(value.c_str(),5,32+16*i);
        Serial.println(value.c_str());
        pCharacteristic->notify();
        i++;
      }
    } 
};
void setupBLE()
{
  BLEDevice::init("ESP32_BT_BLE");   //Create BLE device
  pServer = BLEDevice::createServer();   //Create BLE server
  pServer->setCallbacks(new MyServerCallbacks());   //Set the callback function for the server
  pService = pServer->createService(SERVICE_UUID); //Create BLE service
  pCharacteristic = pService->createCharacteristic(
                                                 CHARACTERISTIC1_UUID,
                                                 BLECharacteristic::PROPERTY_READ|
                                                 BLECharacteristic::PROPERTY_NOTIFY|
                                                 BLECharacteristic::PROPERTY_WRITE);   //Create characteristic values for services
  pCharacteristic->setCallbacks(new MyCallbacks());    //Callback function for setting eigenvalues
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setValue("ESP32 BT BLE");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}
void setup() 
{
  Serial.begin(115200);
  my_lcd.begin();
  my_lcd.setRotation(0);
  my_lcd.fillScreen(TFT_WHITE);
  my_lcd.setTextFont(2);
  my_lcd.setTextColor(TFT_RED);
  setupBLE();
  my_lcd.drawString("BLE server start.", 10, 0); 
  my_lcd.drawString("receive data :",10,16,2);
}

void loop() 
{
   delay(3000);
}
