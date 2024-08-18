#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() {
    if (!loadSoundBuffers()) {
        std::cerr << "Error loading sound files" << std::endl;
    }
    clickSound.setBuffer(clickBuffer);
    mergeSound.setBuffer(mergeBuffer);
}

SoundManager::~SoundManager() {
}

bool SoundManager::loadSoundBuffers() {
    if (!clickBuffer.loadFromFile("Sound/Tap.wav")) {
        std::cerr << "Error loading click sound" << std::endl;
        return false;
    }
    if (!mergeBuffer.loadFromFile("Sound/Merge.wav")) {
        std::cerr << "Error loading merge sound" << std::endl;
        return false;
    }
    return true;
}

void SoundManager::playClickSound() {
    clickSound.play();
}

void SoundManager::playMergeSound() {
    mergeSound.play();
}
