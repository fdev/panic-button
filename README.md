Panic Button
============

Allows to use the "Big Red Button" from DreamCheeky on Linux.

By default it calls /usr/bin/panicbutton-{opened,closed,pressed}.sh. 
That file should contain all the instructions that should run when the button is pressed.

Make sure to run the tool as root, because you need write-access to the device.

Dependencies
============

Ubuntu or debian with the libusb library renamed to libusb-1.0.

	apt-get install build-essential libusb-1.0.0-dev

A DreamCheeky Big Red Button.
