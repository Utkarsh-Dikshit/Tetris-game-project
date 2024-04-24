#include "sounds.h"

sounds:: sounds(){
    InitAudioDevice();
    // clearRowSound = LoadSound (" ");
    // rotateSound = LoadSound (" ");
    // music = LoadMusicStream (" ");

}

sounds:: ~sounds(){
    CloseAudioDevice();
    UnloadSound(clearRowSound);
    UnloadSound(rotateSound);
    UnloadMusicStream(music);
}