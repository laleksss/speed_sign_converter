//  Speed converter by LAleksss  //
// No support No question please //

#include <EEPROM.h>
#include <SPI.h>
#include <Time.h>
#include <TimeLib.h>
#include <mcp2515.h> 

#define CS_PIN_CAN0 10
#define SERIAL_SPEED 115200
#define CAN_SPEED CAN_125KBPS // Entertainment CAN bus - Low speed
#define CAN_FREQ MCP_8MHZ // Switch to 8MHZ if you have a 8Mhz module

MCP2515 CAN0(CS_PIN_CAN0); // CAN-BUS Shield to read


// CAN-BUS Messages
struct can_frame canMsgSnd;
struct can_frame canMsgRcv;

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
        
      }
    }
   }
