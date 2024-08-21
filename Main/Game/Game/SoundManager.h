#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void playClickSound();
    void playMergeSound();

private:
    sf::SoundBuffer clickBuffer;
    sf::SoundBuffer mergeBuffer;
    sf::Sound clickSound;
    sf::Sound mergeSound;

    bool loadSoundBuffers();
};
