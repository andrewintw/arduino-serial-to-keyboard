# arduino-serial-to-keyboard

![](images/wiring-diagram.png)


## Pro Micro

* [Pro Micro & Fio V3 Hookup Guide](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/all)

![](images/ProMicro_Pinout.png)

![](images/ProMicro_Setup.png)


## Digispark

* [Connecting and Programming Your Digispark](http://digistump.com/wiki/digispark/tutorials/connecting)

![](images/DigiSpark_Pinout.png)

![](images/DigiSpark_Upload.png)

* [Debugging with the Digispark](https://digistump.com/wiki/digispark/tutorials/debugging)


### Library

clone the repos `git@github.com:andrewintw/Digispark_SoftSerial-INT0.git` to libraries/ folder.


## How To Test

1. Chech your new HID Keyboard Device

![](images/new-hid-keyboard-device.png)


2. Start a virtual machine on VirtualBox and attach the HID keyboard device to the virtual machine. 

note: Your host system will remove the HID keyboard.

![](images/attache-digikey-to-vm.png)


3. Connect to UART with 9600-8-n-1 and start typing.
