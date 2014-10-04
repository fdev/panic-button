#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>
#include "button.h"

int main()
{
	struct libusb_device_handle *dev = openButton();

	if (!dev) {
		exit(1);
	}

	/* Remember if the lid is open */
	int state = BUTTON_STATE_CLOSED;

	while (1) {
		int val = getButtonState(dev);

		if (val != state) {

			if (val == BUTTON_STATE_OPENED) {
				state = val;

				if (fork() == 0) {
					system("panicbutton-opened.sh");
					exit(0);
				}

				fprintf(stderr, "Opened.\n");
			}
			else if (val == BUTTON_STATE_PRESSED) {

				if (fork() == 0) {
					system("panicbutton-down.sh");
					exit(0);
				}

				fprintf(stderr, "Button down.\n");

				/* Wait until the button is up again */
				while (getButtonState(dev) == BUTTON_STATE_PRESSED) usleep(100000);

				if (fork() == 0) {
					system("panicbutton-up.sh");
					exit(0);
				}

				fprintf(stderr, "Button up.\n");

			}
			else if (val == BUTTON_STATE_CLOSED) {
				state = val;

				if (fork() == 0) {
					system("panicbutton-closed.sh");
					exit(0);
				}

				fprintf(stderr, "Closed.\n");
			}
			else if (val == 20) {
				fprintf(stderr, "Button pushed while the lid is closed?\n");
			}
			else {
				fprintf(stderr, "Unknown button status %d\n", val);
			}
		}

		usleep(100000);
	};

	if (libusb_release_interface(dev, 0) != 0) {
		printf("Cannot unclaim button\n");
	}

	libusb_close(dev);

	return 0;
}
