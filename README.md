![image](https://github.com/user-attachments/assets/8701ac4c-9f6e-4676-9a31-b751b3f61b18)


**1. Prepare**

**Parts**
- 1 x QT Py RP2040 [Adafruit](https://www.adafruit.com/product/4900)
- 1 x ANO Directional Navigation and Scroll Wheel Rotary Encoder [Adafruit](https://www.adafruit.com/product/5001)
- 1 x Adafruit ANO Rotary Navigation Encoder to I2C Stemma QT Adapter [Adafruit](https://www.adafruit.com/product/5740)
- 1 x Trackball Breakout [Pimoroni](https://shop.pimoroni.com/products/trackball-breakout?variant=27672765038675)
- 2 x STEMMA QT / Qwiic JST SH 4-pin Cable - 100mm Long(or 50mm) [Adafruit](https://www.adafruit.com/product/4210)

**Hardware**
- M2.5 Socket Head Screws [Amazon](https://geni.us/S0KvnqZ)
     - 4 × 4mm
     - 4 × 5mm
     - 4 × 6mm

- 4 x 3M Bumpon Adhesive Rubber Cushions(8mm) [Amazon](https://www.amazon.co.jp/-/en/3M-Bumpon-Adhesive-Rubber-Cushions/dp/B00V5MQQIC/ref=sr_1_fkmr3_1?__mk_ja_JP=%E3%82%AB%E3%82%BF%E3%82%AB%E3%83%8A&crid=2QPRDAYAROAZ5&dib=eyJ2IjoiMSJ9.S3UGVLDoXMhmR3fm_h7kod5ZnHVsgZax7sXsWRPMaz19MzYfJKzJ0AzzPFWR_F7116YVshoMFda7HQPpi1X5_1HfbOeF3YuS8I8OC-xERzyu63efnA9qKrhQjOUah-0k.W2v3crykf5a5g-5oHiKS4X7neL4kGQ5ZKhzLRTb2-gY&dib_tag=se&keywords=mini%2Btype%2Bcushion%2Brubber&qid=1734697173&sprefix=mini%2Btype%2Bcushion%2Brubber%2Caps%2C230&sr=8-1-fkmr3&th=1)
- 12 x M2.5 Heat-Set Inserts [Amazon](https://www.amazon.co.jp/-/en/uxcell-M2-5x3mm-Printing-Threaded-Embedded/dp/B0CTTCW2LJ/ref=sr_1_3?crid=WL63MQ9F6896&dib=eyJ2IjoiMSJ9.yIRjErq9LKG6445j7WOAZU2Wd2hwkZ3V7JvBc-SvDHP8rjFx2BVmzGS5tQm2KH69X1QRbLpA7BRu-tWf4kgSlwM0WYFxpn11b0IzlVRiIIM1Eg4-O7IhZSmY_rzED5wpW67EHBS-X0EyyXr7UJClAzB-S--3gq_GSp1GclQgH7rgWNSULpWm2jlnVLQMm5n8MmUQfi6YV-LxNF2SfmNtD7gEC19I4r3d82Os342kyLkI6UvWk65Hm36_GBRw_gM5sZsr52LyjQdNCUN1KHxrxVnwBEc_l76kTMJxofc8ZHZOgHuAfDql1ylqaa6oPVEgUw2g5ko3EDBk0fXBfy0Iz6q7U2CYzmv28SCHAjWn1FIfEER5TW2HzxN1vgkaPYFmwBf6pqnb_m7cgz3ChTVZskNeR4npcp1lPEL-xxR7if-I-UI8rfy5xYsXDqcIopFq.kJMWToPjywflplyHwV6ASU2FZT8cKqEVf5FhLAfx9lk&dib_tag=se&keywords=heat+m2.5&qid=1734698362&sprefix=heat+m2.5%2Caps%2C311&sr=8-3)

**Tools**
- 3D Printer, PLA filament (For print the mouse's case)
- Soldering Station (For install heat-set inserts)
- Ginelson Mini Router (For cut heat-set inserts off) [Amazon](https://www.amazon.co.jp/Ginelson-Shifting-Rechargeable-Lightweight-Polishing/dp/B08FC9762H/ref=sr_1_1_sspa?crid=17F7X4LP9QO91&dib=eyJ2IjoiMSJ9.P5g0SVMCjUbQgdIDasTuWbOdcyvVcRopgU-jTdbBkOAxRY-FqnmSFfMdAuydM913gTgobaYLZ8QCrhro3fSM6Q.Q1e9ozeo3L1gy3jksuLM5ULijbE39Xr0I-uojx3EWME&dib_tag=se&keywords=ginelson&qid=1734702661&sprefix=ginel%2Caps%2C252&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1)


**2. 3D Printing & Assembly**

You can download .stp from Step folder on my [github](https://github.com/khoifrvn/Left-hand-trackball-with-Adafruit-ANO-Encoder/tree/main/Step)

Once you have completed the 3D printing, install the heat-set Inserts into the designated positions.

Note: In this design, **the wall on the Trackball side is quite thin**, so you need to shorten the heat-set before assembly it.

![image](https://github.com/user-attachments/assets/818af5db-e2fd-4de1-bcf3-99919578f686)

Then connect each parts as below diagram

![image](https://github.com/user-attachments/assets/1d8c63ba-37ec-4c2d-b0c9-9437591aba2d)


**3. Software**

First thing is to get the Adafruit QT Py RP2040 working in the Arduino IDE. You can follow [this guide](https://learn.adafruit.com/adafruit-qt-py-2040/arduino-ide-setup) if you never done this before.

Once the board is working properly you can open the Arduino sketch located [here](https://github.com/khoifrvn/Left-hand-trackball-with-Adafruit-ANO-Encoder/blob/main/Code/main.ino) and install the required libraries in your environment.

In order for the sketch to compile you will also need to change the USB stack to from Arduino to TinyUSB. You can read more on how to do that [here](https://learn.adafruit.com/mouse-and-keyboard-control-using-tinyusb-and-ble/tinyusb-mouse-and-keyboard-usage).

![image](https://github.com/user-attachments/assets/5c788811-429b-4404-9dfb-4354d00c79d5)

Once the board flashed successfully you can unplug, open the serial console and plug it back in.

**Functions**
- The functions on seesaw ANO module include:
     - Moving up, down, left, or right using the navigation buttons.
     - Selecting an option with the middle button.
     - Scrolling vertically or horizontally using the encoder(Switching between modes by holding the middle button for about 1 second).
- The same thing with Pimoroni trackball breakout module:
     - Moving mouse pointer.
     - Scrolling vertically or horizontally(Switching between modes by press trackball for about 1 second)

You can see my demo from [Youtube](https://youtu.be/a_s_giNTfWA)


Thank you for sticking around until the end!

This was a lot of fun to make and I enjoyed the process. There is certainly a lot of improvements to be made. I'd love to hear your suggestions.


*************************************************************************************************************************************

**4. FAQs**
- The "TinyUSB_Mouse_and_Keyboard.h" library might not be available in the Arduino IDE. You can download it from [here](https://learn.adafruit.com/mouse-and-keyboard-control-using-tinyusb-and-ble/installing-the-libraries)
- The "pimoroniTrackball.h" library can be downloaded from [here](https://github.com/ncmreynolds/pimoroniTrackball)
- The default address of the Seesaw is 0x49, and the Pimoroni Trackball Breakout is 0x0A.
If your board is not configured this way or you are not using a STEMMA QT Cable, you can check the I2C port using the following steps:
     - Install the "Adafruit_TestBed.h" library in your environment.
     - Open the I2C_scan.ino example from this library.
     - Upload the code to your board.
     - After uploading, open the Serial Monitor to check the address of each board.

- You can check the events from each board using the original code provided [here](https://github.com/khoifrvn/Left-hand-trackball-with-Adafruit-ANO-Encoder/blob/main/Code/HwTest.ino).
- The first time you compile the sketch, if the Arduino terminal displays something like the following issue, please check if your Arduino USB Stack is set to "Adafruit TinyUSB".

        #include <HID.h>
      ^~~~~~~
     compilation terminated.
     exit status 1
     Compilation error: exit status 1
  
