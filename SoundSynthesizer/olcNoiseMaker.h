#pragma once //makes sure the header file is included only once

#pragma comment(lib, "winmm.lib") //searches for winmm.lib at link time

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic> //support for atomic operations (performed in their entirety or not at all)	
#include <condition_variable> //suport for blocking operations (wait for an event when i have a mutex)

using namespace std;

#include <Windows.h>

#ifndef FTYPE
#define FTYPE double
#endif // !FTYPE

const double PI = 2.0 * acos(0.0);

template<class T>
class olcNoiseMaker
{
public:
	//Constructor
	olcNoiseMaker(wstring sOutputDevice, unsigned int nSampleRate = 44100, unsigned int nChannels = 1, unsigned int nBlocks = 8, unsigned int nBlockSamples = 512)
	{
		Create(sOutputDevice, nSampleRate, nChannels, nBlocks, nBlockSamples);
	}

	//Destructor
	~olcNoiseMaker()
	{
		Destroy();
	}



public:
	static vector<wstring> Enumerate()
	{
		int nDeviceCount = waveOutGetNumDevs(); //gets the number of WAV output devices
		vector<wstring> sDevices;
		WAVEOUTCAPS woc; //data structure that describes the properties of a WAV output device

		for (int i = 0; i < nDeviceCount; i++)
		{
			if (waveOutGetDevCaps(n, &woc, sizeof(WAVEOUTCAPS)) == S_OK) // gets the information about the WAV device in the woc obj
			{
				sDevices.push_back(woc.szPname); //pushes to the array the name of the WAV output device
			}
		}

		return sDevices;
	}

	void SetUserFunction(FTYPE(*func)(int, FTYPE))
	{
		m_userFunction = func;
	}

	FTYPE clip(FTYPE dSample, FTYPE dMax)
	{
		if (dSample >= 0.0)
			return fmin(dSample, dMax);
		else
			return fmax(dSample, -dMax);
	}


private:

};























