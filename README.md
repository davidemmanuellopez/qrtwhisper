# A Real time Qt Interface for Whisper.cpp 

A Qt application based on whisper.cpp/examples/stream. The goal its to have a real time transcription (as subtitles)
of audio output (any app, like youtube, video calls). 

Its recommended to have CUDA and nvidia driver installed, for Real time performance.
The project its at early stages. Its alpha version. Its tested on Linux+KDE. 

To allow the app to get focus, you must go:

System Settings -> Window Behavior-> Focus

* Disable: Click raises active window

In general terms, do you need to make capable that any application can obtain focus, without need of click.

For now the application get focus for every transcription, you cannot hold keyboard focus. This its
functional for a interview when not its need to use desktop actively.

### Example

The application looks like it. A semi-transparent text over the screen.

![example](img.png)


## Instructions

### Install dependencies
* Install CUDA and NVIDIA driver
* Install SDL2

Whisper.cpp its handled by the CMake project.

### Build the CMake project and build the source.
### Download model
sh ./extern/whisper.cpp/models/download-ggml-model.sh base.en
### create virtual mic with pulse-audio

* pactl load-module module-remap-source     master=alsa_output.usb-Antelope_Audio_ZenGoSC_4501823000211-00.multichannel-output.monitor     source_name=virtmic     source_properties=device.description=Virtual_Microphone

replace master device with our device, use "pactl list short sinks". Put .monitor as suffix.

### Check available mics

use tool sdl_mics at project. Take the number of virtual microphone. 

### Start

run the application by "./QRTWhisper [n]", where n its the virtual mic device.
for example "./QRTWhisper 1"


