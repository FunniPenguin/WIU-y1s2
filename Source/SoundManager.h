#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

//Audio class headers
#include "SoundDevice.h"
#include "SoundManager.h"
#include "SoundEffectsPlayer.h"
#include "MusicBuffer.h"

#include <iostream>
#include <vector>

enum BGM {
	//Dylan's bgm
	BGM1 = 0,
	BGM2,
	BGM3,
	BGM4,
	BGM_START,
	//Other ppl bgms (Note please put the other bgms under here so its easier to integrate)
	NUM_BGMS
};

enum SFX {
	//Dylan's sfx
	METAL_PIPE = 0,
	//Other ppl sfx (Note please put the other sfx under here so its easier to integrate)
	NUM_SFX
};

class SoundManager {
private:
	SoundEffectsPlayer sfxPlayer;
	MusicBuffer* bgms[NUM_BGMS]; //Maybe remove this and create new music buffers to switch and reset tracks?
	MusicBuffer* currBgm;
	uint32_t sfx[NUM_SFX];
	double delayedUpdate;
	int currentVolume;
	std::vector<ALuint> p_SoundEffectBuffers;
public:
	SoundManager() = default;
	~SoundManager() {};
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	void Init();
	void updateSounds(double dt);
	void setBGM(BGM bgm);
	void pauseBGM();
	void resumeBGM();
	void stopBGM();
	void switchBGM(BGM bgm);
	void playSound(SFX Sfx);
	ALuint Load(const char* filename); //for sfx
	void Exit();
	//void Exit();

	static SoundManager& GetInstance();
	void UpdateBgmMusicBuffer(double dt);
};

#endif

