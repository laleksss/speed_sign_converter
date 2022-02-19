/////////////////////
//    Libraries    //
/////////////////////

#include <EEPROM.h>
#include <SPI.h>
#include <Time.h>
#include <TimeLib.h>
#include <mcp2515.h> 

/////////////////////
//  Configuration  //
/////////////////////

#define CS_PIN_CAN0 10
#define SERIAL_SPEED 115200
#define CAN_SPEED CAN_125KBPS // Entertainment CAN bus - Low speed
#define CAN_FREQ MCP_8MHZ // Switch to 8MHZ if you have a 8Mhz module

////////////////////
// Initialization //
////////////////////

MCP2515 CAN0(CS_PIN_CAN0); // CAN-BUS Shield to read


// CAN-BUS Messages
struct can_frame canMsgSnd;
struct can_frame canMsgRcv;


  byte tmp0;
  byte tmp1;
  byte tmp2;
  byte tmp3;
  byte tmp4;
  byte tmp5;
  byte tmp6;
  byte tmp7;

void setup() {
  
  int tmpVal;

  CAN0.reset();
  CAN0.setBitrate(CAN_SPEED, CAN_FREQ);
  while (CAN0.setNormalMode() != MCP2515::ERROR_OK) {
    delay(100);
  }
}

void loop() {
  int tmpVal;
  byte MemVal;


 if (CAN0.readMessage( & canMsgRcv) == MCP2515::ERROR_OK ) {
    int id = canMsgRcv.can_id;
    int len = canMsgRcv.can_dlc;

  if (id == 489 && len == 6) { // SpeedLimit

        tmpVal = canMsgRcv.data[1];
        if (tmpVal == 00) { //NoSpeedData
          canMsgSnd.data[0] = 0xFF;
        } else {
          canMsgSnd.data[0] = canMsgRcv.data[1];
        }
        canMsgSnd.data[1] = 0x10;
        canMsgSnd.can_id = 0x268;
        canMsgSnd.can_dlc = 2;

        CAN0.sendMessage( & canMsgSnd);
        
  } else if (id == 148 && len == 8) { // TestCase
        
        tmp0 = canMsgRcv.data[0];
        tmp1 = canMsgRcv.data[1];
        tmp2 = canMsgRcv.data[2];
        tmp3 = canMsgRcv.data[3];
        tmp4 = canMsgRcv.data[4];
        tmp5 = canMsgRcv.data[5];
        tmp6 = canMsgRcv.data[6];
        tmp7 = canMsgRcv.data[7];

      } else if (id == 162 && len == 6) { // TestCase
        
        MemVal = canMsgRcv.data[1];
        
        if (MemVal == 04) {
        canMsgSnd.data[0] = tmp0;
        canMsgSnd.data[1] = tmp1;
        canMsgSnd.data[2] = tmp2;
        canMsgSnd.data[3] = 0xFF;
        canMsgSnd.data[4] = tmp4;
        canMsgSnd.data[5] = tmp5;
        canMsgSnd.data[6] = tmp6;
        canMsgSnd.data[7] = tmp7;
        canMsgSnd.can_id = 0x094;
        canMsgSnd.can_dlc = 8;
        CAN0.sendMessage( & canMsgSnd);
        }
       }
   }
  }
   
