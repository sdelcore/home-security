#home-security
##Prepare for making in command line
```
sudo dnf install arduino-core pyserial rpmdevtools avrdude
git archive HEAD --prefix=arduino-mk-1.6.0/ -o ../arduino-mk-1.6.0.tar.gz
git clone https://github.com/sudar/Arduino-Makefile.git
cd Arduino-Makefile
git archive HEAD --prefix=arduino-mk-1.6.0/ -o ../arduino-mk-1.6.0.tar.gz
mkdir -p ~/rpmbuild/{SOURCES,SPECS}
cp ../arduino-mk-1.6.0.tar.gz ~/rpmbuild/SOURCES
cp packaging/fedora/arduino-mk.spec ~/rpmbuild/SPECS
cd ~/rpmbuild/SPECS
rpmbuild -ba arduino-mk.spec
PATH=$PATH:/usr/bin/avr-gcc/bin
sudo dnf install avr-gcc
export PATH
cd rpmbuild/BUILD/arduino-mk-1.6.0
mkdir /usr/share/arduino/Arduino-Makefile
sudo mkdir /usr/share/arduino/Arduino-Makefile
sudo cp -r * /usr/share/arduino/Arduino-Makefile
```

##Cross compile for ESP8266
```
git clone https://github.com/esp8266/Arduino.git esp8266
  344  cd esp8266
  345  git checkout tags/2.3.0
  346  cd tools
  347  python get.py
  348  cd ~
  349  git clone https://github.com/plerup/makeEspArduino.git
  350  cd makeEspArduino
  351  make -h
  352  make -f makeEspArduino.mk flash ESP_ROOT=~/esp8266
  353  vim ~/.zshrc
  354  alias espmake="make -f ~/makeEspArduino/makeEspArduino.mk ESP_ROOT=~/esp8266"
  374  cd ~
  376  git clone --recursive https://github.com/pfalcon/esp-open-sdk.git
  377  cd esp-open-sdk
  380  sudo dnf install autoconf gperf bison flex texinfo help2man libtool
  397  make PYTHON=python3
export PATH=/home/sdelcore/esp-open-sdk/xtensa-lx106-elf/bin:$PATH
```


##Flashing the ESP8266
ensure:
| UNO  | ESP8266 |
|:----:|:-------:|
| RX   | RX      |
| TX   | TX      |
| GND  | GND     |
| 3.3V | VCC     |
| 3.3V | CH_PD   |
| GND  | GPIO_0  |

##Running ESP8266 with Arduino
| UNO  | ESP8266 |
|:----:|:-------:|
| RX   | TX      |
| TX   | RX      |
| GND  | GND     |
| 3.3V | VCC     |
| 3.3V | CH_PD   |
| -    | GPIO_0  |
