# A Real time Qt Interface for Whisper.cpp 

A Qt application based on whisper.cpp/examples/stream.

Its recommended to have CUDA and nvidia driver installed.

## Instructions

### Build the project.
### Download model: sh ./extern/whisper.cpp/models/download-ggml-model.sh base.en
#### create virtual mic with pulse-audio

pactl load-module module-remap-source     master=alsa_output.usb-Antelope_Audio_ZenGoSC_4501823000211-00.multichannel-output.monitor     source_name=virtmic     source_properties=device.description=Virtual_Microphone

replace master device with our device, use "pactl list short sinks". Put .monitor as suffix.
