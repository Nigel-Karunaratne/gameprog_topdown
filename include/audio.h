#pragma once

#include "raylib-cpp.hpp"
namespace rl = raylib;

#include <string>
#include <vector>
#include <deque>

class AudioManager
{
private:
    rl::AudioDevice audioDevice;
    std::deque<std::string> audioFileNames;
    std::vector<rl::Sound> loadedAudioFiles;
public:
    AudioManager();
    ~AudioManager(); //NOTE - raylib-cpp should handle audio unloading automatically

    void PlaySFX();
    void PlayMusic();
};
