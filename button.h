#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

static const int CONTROL_REQUEST_TYPE_IN = 0x21;
static const int HID_SET_REPORT = 0x09;
static const int HID_REPORT_TYPE_OUTPUT = 0x02;
static const char HID_CTRL_DATA[8] = {0,0,0,0,0,0,0,2};
static const int BUTTON_STATE_CLOSED = 0x15;
static const int BUTTON_STATE_OPENED = 0x17;
static const int BUTTON_STATE_PRESSED = 0x16;

struct libusb_device_handle *openButton();
unsigned char getButtonState(struct libusb_device_handle *dev);
