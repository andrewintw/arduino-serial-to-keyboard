# 共享筆電的螢幕鍵盤(滑鼠)給 Raspberry Pi

*使用 arduino-serial-to-keyboard*


## 前言

最近因為學習上的需求接觸了 `Headless installation`，所謂的 "Headless" 就是沒有 User Interface，即在沒有螢幕、鍵盤、滑鼠的狀況下安裝系統。

關於 Headless 的安裝方式不是這一篇要講的重點，如果你曾使用過 Pi Zero，應該會對這樣的安裝方式感到熟悉。

幾週前我看到了關於 `HDMI Input` 的資訊，以下這個影片示範得非常清楚。（點擊下圖觀看影片）

[![](https://img.youtube.com/vi/GkbmeYgTVlc/sddefault.jpg)](https://youtu.be/GkbmeYgTVlc)

你可以看到它整體的架構是這樣的:

![](images/hdmi-input.png)

USB HDMI 影像擷取插入筆電後，電腦端就會多一個 Video Input 的裝置。接著只要使用 "任何可以選擇 Video 輸入來源" 的軟體都可以看到 HDMI Input 的 Video 訊號。例如配合 [OBS Studio](https://obsproject.com/) 的軟體就可以看到畫面了（甚至可以錄下畫面）。此外如果你是 Windows 10 的使用者，使用 Windows Camera App 也可以從這個 HDMI Input 取得畫面。 


一般操作電腦時的使用者介面指的是 KVM，也就是鍵盤(Keyboard)、顯示器(Video)、滑鼠(Mous)的意思。既然現在 Video 已經可以透過一只 USB HDMI 影像擷取卡做到分享筆電的螢幕，那麼剩下的 KM（鍵盤和滑鼠）有沒有可能做到呢？

![](images/share-keyboard-and-mouse.png)


## 現有解決方案

關於共用 KVM 這件事情，市場上已經有一些解決方案，有些產品可以解決 KVM，有些只有 KM，但不是每一種方案都可以直接使用 host 端自帶的螢幕滑鼠鍵盤...

### 1. KVM switch

談到共用螢幕鍵盤滑鼠，就不得不提 KVM 切換器這種產品。KVM 的示意圖如下，你需要在一台 switch 上接上鍵盤螢幕滑鼠，然後透過 switch 上的切換按鈕，決定將這一組 KVM 給哪一台電腦使用。示意圖中的那三台電腦都不需要額外的 KVM。

![](images/kvm_switch.png)

但就算示意圖的那三台電腦都換成筆電，你還是需要一組 KVM 當作 source，筆電本身的 KVM 是無法共用給其它電腦的。


### 2. Synergy

[Synergy](https://zh.wikipedia.org/wiki/Synergy) 是一個很不錯的解決方案，只要你的 host（筆電）和 target（樹莓派）在同一個區網內，就可以透過網路共享筆電的滑鼠鍵盤（沒有螢幕，你需要在 target 端安裝螢幕）。

但 Synergy 仍需要在受控端先進行設定，並且啟動相關的應用程式，無法做到 "不設定就可以使用"。


### 3. Smart KM Link

另外市面上還有一種稱為 "Smart KM Link" 的傳輸線。標榜可以在兩台電腦之間共享滑鼠鍵盤，甚至複製檔案。（點擊下圖觀看影片）

[![](https://img.youtube.com/vi/eNn8RMQIJqE/sddefault.jpg)](https://www.youtube.com/watch?v=eNn8RMQIJqE)

看起來非常方便，但目前這類型的產品都只支援 Windows 系統，我不確定如果我另一端插入一台 Linux 主機（或是 pi），能不能做到共享 KVM？如果你知道的話請告訴我！


### 4. ATEN 攜帶型KVM控制器 CV211

[ATEN 攜帶型KVM控制器 CV211](https://www.aten.com/tw/zh/products/kvm%E5%A4%9A%E9%9B%BB%E8%85%A6%E5%88%87%E6%8F%9B%E5%99%A8/%E5%B8%B6%E7%B7%9A%E5%BC%8Fkvm%E5%A4%9A%E9%9B%BB%E8%85%A6%E5%88%87%E6%8F%9B%E5%99%A8/cv211/) 是目前我看到唯一能做到直接共享筆電螢幕、滑鼠、鍵盤的完整解決方案！（點擊下圖觀看影片）

[![](https://img.youtube.com/vi/eb2j-qtWTP0/sddefault.jpg)](https://www.youtube.com/watch?v=eb2j-qtWTP0)

在廠商開發的軟體上，你還可以直接錄製受控端的畫面。

但缺點就是 --- 超貴！XD [pchome 購物上](https://24h.pchome.com.tw/prod/DCAX4H-A9008WPCS)的售價是 9700！

對於一個不經常有這種需求的人來說不算是值得投資的東西。


## 自造想法

我突然想到某些版本的 Arduino 開發板可以將自己模擬成一台 HID keyboard。例如以前很熱門的 [Makey Makey](https://makeymakey.com/)，如果你去看它所公布的[電路圖](http://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/makey_makey-v12.pdf)，你會發現它之所以能跟電腦的遊戲互動，就是因為 Atmega32u4 可以模擬成 HID 鍵盤的關係。

Arduino 開發板系列中，使用 Atmega32u4 的開發板中，容易取得的有 [Leonardo](https://store.arduino.cc/usa/leonardo) 和 [Pro Micro](https://www.sparkfun.com/products/12640)。以體積來說，當然是 Pro Micro 比較方便。


### 實作想法

所以我的想法就是使用 Pro Micro 配合 Arduino 官方的 Keyboard library，將 Pro Micro 模擬成一台 USB HID Keyboard，所以當 Pro Mico 插入 Raspberry Pi 的時候，Pi 應該會認為有一台 USB 鍵盤接入。接著將 Pro Micro 的 UART 透過 USB-to-Serial 的模組接到我的控制筆電。

Pro Mico 的程式中，我只要簡單寫一段邏輯：


	只要從 UART 收到的字元，都透過 Keyboard library 提供的 write 輸出至 HID 介面 


最後，當我打開 serial port，對 COM port 輸入任何字元，應該就會轉送到 Raspberry Pi 了！架構圖如下：

![](images/wiring-diagram.png)


因此，關於筆電共用 KVM 的想法，便宜的解法就是：

* K（鍵盤）: 使用 Atmega32u4 模擬成 HID Keyboard
* V（螢幕）: 使用 USB HDMI 影像擷取卡 
* M（滑鼠）: 使用 Atmega32u4 模擬成 HID Mouse

ps: 關於滑鼠，事實上 Atmega32u4 也可以模擬成滑鼠，但是實作上有點麻煩，後面會說明。


## 神人的肩膀

在做任何實作之前，最好先找找有沒有人已經做過類似的事情了。以下是我找到的兩個作品。


### 1. Nehebkau by Frank Zhao

一開始我用關鍵字搜到了 raspberry pi forums 的這篇：[Using Laptop as keyboard and mouse](https://www.raspberrypi.org/forums/viewtopic.php?t=4762)

這個影片是那位大大做出來的成果展示：（點擊下圖觀看影片）

[![](https://img.youtube.com/vi/iXMBKlIrzQs/sddefault.jpg)](https://www.youtube.com/watch?v=iXMBKlIrzQs)

說明在作者的[部落格](https://eleccelerator.com/nehebkau-laptop-controlled-keyboard-and-mouse/)中。它使用兩個 ATmega32U4 對接：

![](https://i.imgur.com/2uz26.jpeg)

所以可以想像 Target 端（pi）不用處理，它就是接入了一個 HID 鍵盤。但是 Host 端（筆電）相當於接入了 "另一個" HID 裝置，所以它需要額外寫個應用程式擷取筆電原生的鍵盤訊號，然後轉發給那個接入的 HID 裝置，最後再透過作者所做的裝置傳給 Target 端。

這個對我來說太高級了，非常厲害。


#### Nehebkau 如何處理滑鼠

首先滑鼠的行為也是 Atmega32u4 可以模擬的，你需要在 host 端寫一個應用程式，擷取你的滑鼠行為（座標資訊），然後一樣透過 HID 介面送出去。如果你使用 Windows 平台，技術上你就必須要知道有哪些 Windows API 能協助你擷取滑鼠行為。但我認為更麻煩的是 -- host 端 和 target 端兩邊的螢幕解析度是不同的。

所以我在 survey 前人的神作時，看到的方式都是需要在應用程式中設定 target 螢幕的解析度，然後作比例的 mapping 調整。你可以 mapping 你整個螢幕，或是在應用程式畫面上產生一個小 pad，滑鼠移入這個 pad 範圍時，同步控制 target 端的滑鼠座標。


#### 關於神人 Frank Zhao

老實說我蠻欣賞這個案子的，但是它需要對 USB 技術非常熟悉才做得出來。Frank Zhao 是 Sony 的硬體工程師，之前也曾在 [Adafruit](https://blog.adafruit.com/author/frank/) 工作過。如果你對自造議題感興趣的話，我敢打賭你肯定曾看過它的 USB Business Card 作品：（點擊下圖觀看影片）

[![](https://img.youtube.com/vi/vX1tDk_iwOo/hqdefault.jpg)](https://www.youtube.com/watch?v=vX1tDk_iwOo)


### 2. KeyMouSerial by Peter Burkimsher

[KeyMouSerial](http://peterburk.github.io/programs/) 比較接近我的原始想法，就只是把鍵盤的按鍵和滑鼠的移動事件透過 Atmega32u4 轉送到另一端的裝置。跟上面的 Nehebkau 一樣，你只要要處理滑鼠的事件，你就需要在 host 端撰寫應用程式。這個作者一定非常有熱情，他同時替 Windows/Mac/Linux 寫了對應的應用程式。

所有的程式都公布在作者的 [GitHub: keyMouSerial](https://github.com/peterburk/keyMouSerial)。打開 Arduino 的程式 [keyMouSerial.ino](https://github.com/peterburk/keyMouSerial/blob/master/Arduino/keyMouSerial.ino)，跟我預期的一樣，其實沒有很複雜，如果你不想處理滑鼠的話（我不想 XD）其實你最關鍵的只有這兩行：


	char inChar = (char)Serial1.read();
	Keyboard.write(inChar);


另外，作者正在努力讓 keyMouSerial 支援 [Rockbox](https://www.rockbox.org/) 有興趣的人可以研究。


#### 關於神人 Peter Burkimsher

Peter Burkimsher 來自紐西蘭，我蠻驚訝地發現，2014~2018 之間他曾在台灣的高雄工作過！


## 我的實作

一開始我先在 Pro Micro 實作，後來我發現使用 Attiny85 為主晶片的 [Digispark](http://digistump.com/products/1) 也可以做到 HID keyboard 的模擬，所以我在我的 [GitHub repo](https://github.com/andrewintw/arduino-serial-to-keyboard) 中提供了這兩者的實作程式碼。

* [ProMicro](https://github.com/andrewintw/arduino-serial-to-keyboard/tree/main/ProMicro) 目錄放的就是 Pro Micro 的版本。
	* [ProMicro_SerialToKeyboard](https://github.com/andrewintw/arduino-serial-to-keyboard/blob/main/ProMicro/ProMicro_SerialToKeyboard/ProMicro_SerialToKeyboard.ino) 是最終的運作版本，其餘 "Test_ProMicro_" 開頭的程式都只是測試程式。
* [DigiSpark](https://github.com/andrewintw/arduino-serial-to-keyboard/tree/main/DigiSpark) 目錄放的就是 DigiSpark 的版本。
	* [DigiSpark_SoftSerial_to_Keyboard](https://github.com/andrewintw/arduino-serial-to-keyboard/blob/main/DigiSpark/DigiSpark_SoftSerial_to_Keyboard/DigiSpark_SoftSerial_to_Keyboard.ino) 是最終的運作版本，其餘 "Test_DigiSpark_" 開頭的程式都只是測試程式。


我的測試環境是 Windows 7。

另外，因為我不會 Windows 的程式設計，所以我目前不打算處理滑鼠的部份了。有想過用 Python 寫，但是需要更長的學習時間，所以目前先擱置這個計劃。


## ProMicro_SerialToKeyboard

你在市面上能買到便宜的 Pro Micro 相容板通常長這樣：

![](images/arduino-pro-micro.jpg)

這個相容板在 Arduino IDE 上能使用 Leonardo 的 Board setting 燒錄。但如果你想要使用 sparkfun 官方的 BSP，你需要先按照 [Pro Micro & Fio V3 Hookup Guide](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/all) 的說明增加 Arduino IDE 對 Pro Micro 的支援。接著拿一台 Arduino UNO，替這個相容板燒錄真正 Pro Micro 的 Bootloader。之後你就可以在 IDE 上直接選用 Pro Micro 了。

當然，或許你也可以不用這麼 "折騰自己"，直接使用 Leonardo 的設定即可 :p


## DigiSpark_SoftSerial_to_Keyboard

![](images/digispark.png)

後來我又做了 DigiSpark 的版本，我比較喜歡 DigiSpark，因為它自帶 USB 接頭，體積又比 Pro Mico 小。

使用 DigiSpark 時，你需要參考官網的文件 [Connecting and Programming Your Digispark](http://digistump.com/wiki/digispark/tutorials/connecting)。

比較需要注意的是燒錄步驟。你將 DigiSpark 接上電腦時，Arduino IDE 不會出現 COM port。事實上燒錄的方式是先移除 DigiSpark，在 Arduino IDE 上點 Upload 後，待訊息列出現 `"Plug in device now... (will timeout in 60 seconds)"` 之後，在 60 秒內再將 DigiSpark 插入電腦即可。 

![](images/DigiSpark_Upload.png)


### DigiSpark Library

DigiSpark/ 的 [libraries/](https://github.com/andrewintw/arduino-serial-to-keyboard/tree/main/DigiSpark/libraries) 目錄下有引入一個 [Digispark_SoftSerial-INT0](https://github.com/andrewintw/digispark_softserial-int0) 函示庫。

原始的作者 Repo 是 [J-Rios/Digispark_SoftSerial-INT0](https://github.com/J-Rios/Digispark_SoftSerial-INT0)。我 Fork 到我的 repo 後只有依照 Arduino 的 Library 規範做了一些設定，以便讓你在 IDE 上能夠出現 Example 選單。


#### 如何下載程式


所以如果你想要使用 DigiSpark，clone 時請使用下面的指令一併 clone submodule

	git clone git@github.com:andrewintw/arduino-serial-to-keyboard.git --recurse-submodules

或是拆成兩個指令（通常適用於忘記加 --recurse-submodules 的人 XD）

	git clone git@github.com:andrewintw/arduino-serial-to-keyboard.git
	git submodule update --init --recursive

當然你也可以進入 DigiSpark/libraries/ 然後手動 clone

	cd DigiSpark/libraries/
	git clone git@github.com:andrewintw/Digispark_SoftSerial-INT0.git


## 如何測試


### 1. 連接 UART

不要忘了我們的架構是這樣。所以你需要準備一片 USB-to-Serial 的 USB 模組（ex: FTDI FT232R、CP2102、PL2303、CH340...排序是價格的高低 XD）。然後將 TX、RX、GND 三個 pins 接到 Pro Micro/DigiSpark 的 UART pins。

![](images/wiring-diagram.png)

你需要對照 Pro Micro/DigiSpar 的 pinout 圖：


Pro Micro 是 pin1（TX）、pin0（RX）。

![](ProMicro/ProMicro_Pinout.png)

DigiSpark 使用 SoftSerial，程式碼中定義的是 P1（TX）、P2（RX）。 

![](DigiSpark/DigiSpark_Pinout.png) 


### 2. 檢查你的 HID 新裝置

假如你有成功，當你插入 Pro Micro/DigiSpark 到 host 筆電時，你的裝置管理員應該會多一個 "HID Keyboard Device"。

![](images/new-hid-keyboard-device.png)


### 3. 使用 VM 測試

事實上你可以直接拿一台 Raspberry Pi 測試。但如果你想要應急測試的話，你可以使用虛擬機器。VM 的軟體都會偵測 host 端的 USB 裝置，你可以選擇將 Pro Micro/DigiSpark 所模擬的 HID 裝置掛入 (attaching) VM 環境中。例如下圖的 "digistump.com DigiKey" 就是 DigiSpark 所模擬的 HID Keyboard Device

![](images/attache-digikey-to-vm.png)

當你成功將 DigiSpark 所模擬的 HID 裝置掛入 VM 環境時，host 端的裝置管理員上的對應清單就會消失（很合理）。


## 4. 打開 serial port 開始測試

使用 serial 的軟體（ex: putty），以 9600-8-n-1 打開對應的 COM port，然後開始打字。你應該會發現在 serial 軟體中所輸入的字元，會即時地出現在 target 端的畫面中。


## 真實 Demo 影片

(coming soon...XD)

## 參考資料

* [Debugging with the Digispark](https://digistump.com/wiki/digispark/tutorials/debugging)
* [Example programs for the DigiUSB library](https://github.com/digistump/DigisparkExamplePrograms)

~ END ~