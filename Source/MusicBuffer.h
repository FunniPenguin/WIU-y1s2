#ifndef MUSIC_BUFFER_H
#define MUSIC_BUFFER_H
#include <al.h>
#include <sndfile.h>

//Note: Class is not singleton because you may want to load different audio tracks for different scenes.
//To create different audio tracks, make another MusicBuffer.
class MusicBuffer
{
public:
	void Play();
	void Pause();
	void Stop();
	void Resume();

	void UpdateBufferStream();

	ALint getSource();

	bool isPlaying();

	MusicBuffer(const char* filename);
	~MusicBuffer();
private:
	ALuint p_Source;
	static const int BUFFER_SAMPLES = 8192;
	static const int NUM_BUFFERS = 4;
	ALuint p_Buffers[NUM_BUFFERS];
	SNDFILE* p_SndFile;
	SF_INFO p_Sfinfo;
	short* p_Membuf;
	ALenum p_Format;

	MusicBuffer() = delete;
};

#endif