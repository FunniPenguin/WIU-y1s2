#include "SoundDevice.h"
#include <al.h>
#include <stdio.h>
#include <vector>
#include <iostream>

/// <summary>
/// Sets the master volume of our listeners. capped between 0 and 5 for now.
/// </summary>
/// <param name="val"></param>
void SoundDevice::SetGain(const float& val)
{
	//Either mute or unmute
	if ((val != 1) && (val != 0))
		return;
	alListenerf(AL_GAIN, val);
}

SoundDevice& SoundDevice::GetInstance()
{
	static SoundDevice instance; //Note that this will always be the same sound device that is returned
	return instance;
}

void SoundDevice::Init()
{
	p_ALCDevice = alcOpenDevice(nullptr); // nullptr = get default device
	if (!p_ALCDevice)
		std::cout << "Failed to get sound device\n";

	p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);  // create context
	if (!p_ALCContext)
		std::cout << "Failed to set sound context\n";

	if (!alcMakeContextCurrent(p_ALCContext))   // make context current
		std::cout << "Failed to make context current\n";

	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
		name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
	printf("Opened \"%s\"\n", name);
}

void SoundDevice::Exit()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(p_ALCContext);
	alcCloseDevice(p_ALCDevice);
}

float SoundDevice::GetGain()
{
	return AL_GAIN;
}
