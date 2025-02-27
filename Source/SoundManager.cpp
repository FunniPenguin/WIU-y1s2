#include "SoundManager.h"
#include <fstream>

#include "KeyboardController.h"

//Include GLFW
#include <GLFW/glfw3.h>

#include <sndfile.h>
#include <inttypes.h>
#include <alext.h>
#include <al.h>

void SoundManager::Init()
{
	delayedUpdate = 0;
	currBgm = nullptr;
	currentVolume = 5.f;
	sfxPlayer.SetLooping(true); //set to not loop sound effects
	SoundDevice::GetInstance().Init();
	//Load music
	bgms[BGM1] = new MusicBuffer("Audio//bgms//bgm1.wav");
	bgms[BGM2] = new MusicBuffer("Audio//bgms//bgm2.wav");
	bgms[BGM3] = new MusicBuffer("Audio//bgms//bgm3.wav");
	bgms[BGM4] = new MusicBuffer("Audio//bgms//bgm4.wav");
	bgms[BGM_START] = new MusicBuffer("Audio//bgms//startingost.wav");
	//Load sfx
	sfx[METAL_PIPE] = Load("Audio//sfx//MetalPipe.ogg");
	SoundDevice::GetInstance().SetGain(currentVolume);
}

void SoundManager::updateSounds(double dt)
{
	delayedUpdate -= dt;
	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_9))
		SoundDevice::GetInstance().SetGain(0.f);
	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_0))
		SoundDevice::GetInstance().SetGain(1.f);
	if (currBgm != nullptr) {
		if (!(currBgm->isPlaying()))
		{
			currBgm->Play();
		}
		if ((currBgm->isPlaying()) && (delayedUpdate <= 0))
		{
			currBgm->UpdateBufferStream();
			delayedUpdate = 0.1f;
		}
	} //TODO: fix the songs such that they will loop
	/*if (!(sfxPlayer.isPlaying()))*/
	if (KeyboardController::GetInstance()->IsKeyDown('T'))
		sfxPlayer.Play(sfx[METAL_PIPE]);
}

void SoundManager::setBGM(BGM bgm)
{
	if (currBgm == nullptr) {
		currBgm = bgms[bgm];
	}
	else { std::cout << "Error: Another track is playing atm.\n"; }
}

void SoundManager::pauseBGM()
{
	if (currBgm != nullptr) {
		if (currBgm->isPlaying()) {
			currBgm->Pause();
		}
	}
	else { std::cout << "Error: current track is nullptr.\n"; }
}

void SoundManager::resumeBGM()
{
	if (currBgm != nullptr) {
		if (!(currBgm->isPlaying())) {
			currBgm->Play();
		}
	}
	else { std::cout << "Error: current track is nullptr.\n"; }
}

void SoundManager::stopBGM()
{
	if (currBgm != nullptr) {
		if (currBgm->isPlaying()) {
			currBgm->Stop();
		}
	}
	currBgm = nullptr;
}

void SoundManager::switchBGM(BGM bgm)
{
	if (currBgm != nullptr) {
		if (currBgm->isPlaying()) {
			currBgm->Stop();
		}
	}
	currBgm = bgms[bgm];
}

void SoundManager::playSound(SFX Sfx)
{
	if (sfxPlayer.isPlaying()) {
		return;
	}
	sfxPlayer.SetBufferToPlay(sfx[Sfx]);
	sfxPlayer.Play(sfx[Sfx]);
}

ALuint SoundManager::Load(const char* filename)
{
	ALenum err, format;
	ALuint buffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t num_frames;
	ALsizei num_bytes;

	/* Open the audio file and check that it's usable. */
	sndfile = sf_open(filename, SFM_READ, &sfinfo);
	if (!sndfile)
	{
		fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
		return 0;
	}
	if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
	{
		fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
		sf_close(sndfile);
		return 0;
	}

	/* Get the sound format, and figure out the OpenAL format */
	format = AL_NONE;
	if (sfinfo.channels == 1)
		format = AL_FORMAT_MONO16;
	else if (sfinfo.channels == 2)
		format = AL_FORMAT_STEREO16;
	else if (sfinfo.channels == 3)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT2D_16;
	}
	else if (sfinfo.channels == 4)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT3D_16;
	}
	if (!format)
	{
		fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
		sf_close(sndfile);
		return 0;
	}

	/* Decode the whole audio file to a buffer. */
	membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

	num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	if (num_frames < 1)
	{
		free(membuf);
		sf_close(sndfile);
		fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
		return 0;
	}
	num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

	/* Buffer the audio data into a new buffer object, then free the data and
	 * close the file.
	 */
	buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

	free(membuf);
	sf_close(sndfile);

	/* Check if an error occured, and clean up if so. */
	err = alGetError();
	if (err != AL_NO_ERROR)
	{
		fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
		if (buffer && alIsBuffer(buffer))
			alDeleteBuffers(1, &buffer);
		return 0;
	}
	int index = p_SoundEffectBuffers.size();
	p_SoundEffectBuffers.push_back(buffer);  // add to the list of known buffers
	return p_SoundEffectBuffers[index];
}

void SoundManager::Exit()
{
	for (int i = 0; i < static_cast<int>(NUM_BGMS); i++) {
		if (bgms[i] != nullptr) {
			delete bgms[i];
		}
	}
	alDeleteBuffers(p_SoundEffectBuffers.size(), p_SoundEffectBuffers.data());
	p_SoundEffectBuffers.clear();
	SoundDevice::GetInstance().Exit();
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance; //Note that this will always be the same Sound Effects Library that is returned
	return instance;
}

void SoundManager::UpdateBgmMusicBuffer(double dt)
{
	if (currBgm != nullptr) {
		if ((currBgm->isPlaying()) && (delayedUpdate <= 0))
		{
			currBgm->UpdateBufferStream();
			delayedUpdate = 0.1f;
		}
	}
}
