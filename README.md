# A Real time Qt Interface for Whisper.cpp 

A Qt application based on [whisper.cpp/examples/stream](https://github.com/ggml-org/whisper.cpp/tree/master/examples/stream).

Copyright (C) 2025  David Emmanuel Lopez

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

The goal of this application its to have a real time transcription (as subtitles) of audio output (any app, like youtube, video calls). Its essentially a accesibility tool. Its recommended to have CUDA and NVIDIA driver installed, for Real time performance. Other GPU+Vulkan its also supported by Whisper.cpp.

The project its at early stages. Its alpha version. Its tested on Linux+KDE. 

To allow the app to get focus, you must go:

System Settings -> Window Behavior-> Focus

* Disable: Click raises active window

In general terms, do you need to make capable that any application can obtain focus, without need of click.

For now the application get focus for every transcription, you cannot hold keyboard focus. This its
functional for a interview when not its need to use desktop actively.

### Example

The application looks like it. A semi-transparent text over the screen. You can see a video demo at [ https://www.youtube.com/watch?v=JTVPFc1cCBk](https://www.youtube.com/watch?v=JTVPFc1cCBk).

![example](img.png)


## Instructions

### Install Qt6-dev
On Debian based linux distributions:
* apt install qt6-base-dev

### Install dependencies
#### Install CUDA and NVIDIA driver
Follow the instructions in https://developer.nvidia.com/cuda-downloads. For integration in environment (for CUDA 12.9) i add to ~/.bashrc the next:

 export PATH="/usr/local/cuda-12.9/bin:$PATH"
 export LD_LIBRARY_PATH="/usr/local/cuda-12.9/lib64:$LD_LIBRARY_PATH"

You can also handle it a CMake build, only for the project.

#### Install SDL2

On Debian based linux distributions:
* sudo apt-get install libsdl2-dev

** Whisper.cpp its handled by git and the CMake project, as a submodule **
#### Install PulseAudio
On Debian based linux distributions:
* sudo apt-get install pulseaudio pavucontrol

Make the necessary to get it working, service enabling, check devices with pavucontrol.

### Build the CMake project and build the source.
Tested with gcc 14.12 and CUDA 12.9.

### Download models

For now, the default used model is medium.en.

* sh ./extern/whisper.cpp/models/download-ggml-model.sh medium.en
### Create virtual mic with pulse-audio

* pactl load-module module-remap-source     master=alsa_output.usb-Antelope_Audio_ZenGoSC_4501823000211-00.multichannel-output.monitor     source_name=virtmic     source_properties=device.description=Virtual_Microphone

replace master device with our device, use "pactl list short sinks" to know it. Put ".monitor" as suffix, like the example.

### Check available mics

use tool sdl_mics at project. Take the number of virtual microphone. 

### Start

run the application by "./QRTWhisper". A Small GUI allow us to select mic device.

### Roadmap

* Improve interfacing for avoid lost of keyboard focus.
* add mic managment at app, and other settings, to make it working out-fox-the-box.
* add other methods for show transcriptions, for example a Android app. 
* create builds for specific CUDA version and platforms (Linux, Windows, MacOS).

### Support it!

You can sponsor the project. Its helps the growth. 

USDT via TRC20:

TFPJT5d3aBoWcPDCGf241MZUen3E9htd23



