# speed_sign_converter
Speed sign converter NAC > Cirocco|Colour LCD

You need to enable speed limit signs in the dashboard/lcd/hud, and disable showing it from the camera in NAC. 
This code will work properly **only at the old cars**, like Peugeot 508 1 gen, which don't have same frames in the can comfort line. 

If you see blinking between what should be displayed and 0 grey sign, you have a **new car, with the new BSI.**

Blinking caused by difference between SAME frames sended by BSI and Arduino.

Example:
Bsi send frame: 0x001 00 00 00
Arduino frame: 0x001 00 FF 00

Result: accepting device is not understanding what happening and sometimes using first data, sometimes - second. 
