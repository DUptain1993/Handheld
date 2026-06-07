//This example function is how to search for Bluetooth cable devices

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
#include <BLEDevice.h>            //Bluetooth BLE device library
#include <BLEUtils.h>
#include <BLEScan.h>              //Scan function library for Bluetooth BLE devices
#include <BLEAdvertisedDevice.h>  //Scanned Bluetooth devices (broadcast status)


int scanTime = 5;       //Bluetooth scanning time
BLEScan* pBLEScan;      //Scanning objects
uint8_t show_index = 0;

char t_buf[100] = {0};

TFT_eSPI my_lcd = TFT_eSPI();

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks  //BLE broadcast callback function (called every time a broadcast device is scanned)
{
    void onResult(BLEAdvertisedDevice advertisedDevice) 
    {
        my_lcd.setTextColor(TFT_BLUE);
        my_lcd.drawString("Nr  |                   BLE_DEV_Name                   |  RSSI", 10, 20);

        if (advertisedDevice.haveName())
        {
            my_lcd.fillRect(10, 40+show_index * 16, my_lcd.width()-1, 16,TFT_WHITE);
            my_lcd.drawNumber(show_index + 1, 10, 40 + show_index * 16); 
            my_lcd.drawString(advertisedDevice.getName().c_str(), 50, 40+show_index * 16); //Display BLE device name
            if (advertisedDevice.haveRSSI()) 
            {
                sprintf(t_buf, "%4d", advertisedDevice.getRSSI());
                my_lcd.drawString(t_buf, my_lcd.width()-110, 40+show_index * 16);   //Display BLE device strength
            }
            show_index++;
            if (show_index == 17)    //Display up to 17 ble devices
            {
              show_index = 0;
            }
        }
    }
};

void setup() 
{
    Serial.begin(115200);
    my_lcd.begin();
    my_lcd.setRotation(1);
    my_lcd.fillScreen(TFT_WHITE);
    my_lcd.setTextColor(TFT_RED);
    my_lcd.setFreeFont(&FreeSans18pt7b);
    my_lcd.drawString("BLE Scan Start", 105, 148);
    BLEDevice::init("ESP BLEDevice");   //Create a BLE device
    pBLEScan = BLEDevice::getScan();    //Create a new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());  //Initialize callback function
    pBLEScan->setActiveScan(true);      //Active scanning consumes more energy but yields results faster
    pBLEScan->setInterval(100);         //Set scan interval
    pBLEScan->setWindow(99);            //Set window size
    my_lcd.fillScreen(TFT_WHITE);
    my_lcd.setTextFont(2);
}

void loop() 
{
    my_lcd.setTextColor(TFT_RED);
    my_lcd.fillRect(10, 0, my_lcd.width()-1, 20,TFT_WHITE);
    my_lcd.drawString("BLE scanning ...", 10, 0); 
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);   //Start BLE scan and call callback function when scanning broadcast devices
    sprintf(t_buf, "BLE Scan done! %d Devices found.",foundDevices.getCount());
    my_lcd.fillRect(10, 0, my_lcd.width()-1, 20,TFT_WHITE);
    my_lcd.drawString(t_buf, 10, 0); 
    pBLEScan->clearResults();   //Delete results from BLEScan buffer to free up memory 
    delay(2000);
}
