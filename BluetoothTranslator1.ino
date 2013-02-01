// test code for sending keystrokes from arduino
// to computer via HID bluetooth module

// specify which serial port to use 
//Leonardo specific using software serial


#include <avr/pgmspace.h>

#include <avrpins.h>
#include <max3421e.h>
#include <usbhost.h>
#include <usb_ch9.h>
#include <Usb.h>
#include <usbhub.h>
#include <address.h>
#include <hidboot.h>

#include <printhex.h>
#include <message.h>
#include <hexdump.h>
#include <parsetools.h>

#include <SoftwareSerial.h>


#define serialPort Serial1
//SoftwareSerial serialPort(11, 12); //RX, TX
#define debugSerial Serial

const bool DEBUG = 1;


class KbdRptParser : public KeyboardReportParser {
  protected:
    virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

void KbdRptParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  
  //testing
  debugSerial.print("Got a report, len= ");
  debugSerial.println(len); 
  
  if (buf[2] == 1) return;  //error
  //testing
  debugSerial.println("good report");
  
  // test bt functionality
  serialPort.write(" tested ");
}

USB Usb;
HIDBoot<HID_PROTOCOL_KEYBOARD>    ExtKeyboard(&Usb);
KbdRptParser Prs;



void setup() {
  delay(10000);
  serialPort.begin(115200);
  if (DEBUG) {
    debugSerial.begin(9600);
  }
//  while (!serialPort) {
//  }
  
  debugSerial.println("Initializing USB");
  int foo = Usb.Init();
  debugSerial.print("USB init returns ");
  debugSerial.println(foo);
  
  
  delay(5000);
  debugSerial.println("Setting Parser");
  
  
  ExtKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
  
  debugSerial.println("Parser assigned");
  serialPort.write(" starting ");
  delay(5000); //Just starting out
}

void loop() {
  Usb.Task();
}
