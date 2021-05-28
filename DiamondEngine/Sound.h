#ifndef _sound_
#define _sound_
#pragma once
#include <Windows.h>
#include <stdio.h>
#include <mmeapi.h>
#include <mmsystem.h>
#include <amstream.h>


class Sound {
	WAVEFORMATEX wf;
	HWAVEOUT hwo;

public:

	HWAVEOUT getHWO();

	void SetLocalVolume(DWORD dwVolume);
};
#endif