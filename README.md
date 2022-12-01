# ExtFriend

ExtFriend is a USB adapter for the WonderSwan's EXT port based on the RP2040 chip and the Raspberry Pi Pico board, providing the following features at a low cost:

* A USB serial port communicating with the WonderSwan at 9600 and 38400 baud,
* A USB audio device allowing digital stereo audio capture from the WonderSwan.

Both features can be active simultaneously - for example, this could allow one to control a WonderSwan as an audio synthesizer.

Special thanks to [BluRaf](https://mastodon.sdf.org/@BluRaf) for providing support and advice through my first journey into TinyUSB lands.

## Tips

* If you mute the USB audio device, the WonderSwan will consider the headphones as disconnected, re-enabling the internal speaker.

## Build Instructions

* Copy `pico_sdk_import.cmake` from your Pico-SDK installation to the repository's root.
* Run `mkdir build`, `cd build`, `cmake ..`, `make`.

## Installation Instructions (Raspberry Pi Pico)

![ExtFriend plugged into a SwanCrystal using a soldered header.](https://img.asie.pl/PTC3.jpg)

* Flash the program to the Pico: for example, `picotool load -v -x extfriend.uf2`
* Connect the Raspberry Pi Pico to [the WonderSwan's EXT port](http://daifukkat.su/docs/wsman/#pinout_extport) as follows:
  * EXT GND - Pico GND (for example pin 3)
  * EXT SER_MOSI - Pico pin 2 (GP1)
  * EXT SER_MISO - Pico pin 1 (GP0)
  * If you want to use digital audio capture:
    * EXT HDPN_BCLK - Pico pin 7 (GP5)
    * EXT HDPN_LRCK - Pico pin 6 (GP4)
    * EXT HDPN_SDAT - Pico pin 4 (GP3)
    * EXT /HDPN_DETECT - Pico pin 3 (GP2)

As the HDMI connector is *sort of* compatible with an EXT port, it would be interesting to see if an HDMI breakout board could be used to faciliate a
solderless DIY connection - unfortunately, as my SwanCrystal already has a breakout header (and I prefer it that way), I wasn't able to test this.

## License

GPLv3+.
