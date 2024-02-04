#include "Arduino.h"

class ControllerSerial{
  public:
    static void setup();
    static void handleSerialMessage(String data);
  private:

};