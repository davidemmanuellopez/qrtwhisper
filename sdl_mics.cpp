#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    SDL_Init(SDL_INIT_AUDIO);

    int num_devices = SDL_GetNumAudioDevices(SDL_TRUE); // SDL_TRUE = captura
    for (int i = 0; i < num_devices; i++) {
        printf("Dispositivo %d: %s\n", i, SDL_GetAudioDeviceName(i, SDL_TRUE));
    }

    SDL_Quit();
    return 0;
}
