#include <stdio.h>
#include <stdlib.h>
#include "button.h"

int main() {
    struct libusb_device_handle *dev = openButton();
    int state = 0;
    do {
        int val = getButtonState(dev);
        if(val != state) {
            if(val == 1) {
                state = val;
                if(fork() == 0) {
                    system("panicbutton-opened.sh");
                    return 0;
                }
                else printf("Opened.\n");
            }
            else if(val == 2) {
                if(fork() == 0) {
                    system("panicbutton-pressed.sh");
                    return 0;
                }
                else printf("Pressed.\n");
                while(getButtonState(dev) == 2) usleep(100000);
            }
            else {
                state = val;
                if(fork() == 0) {
                    system("panicbutton-closed.sh");
                    return 0;
                }
                else printf("Closed.\n");
            }
        }
        usleep(100000);
    } while(1);
    if(libusb_release_interface(dev, 0) != 0) {
        printf("Cannot unclaim button\n");
    }

    libusb_close(dev);
    return 0;
}
