#include "../stdafx.h"
#include "PrecisionTimer.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <ctime>
#endif

//=======================================================================================
// PrecisionTimer.cpp by Frank Luna (C) 2008 All Rights Reserved.
//=======================================================================================
PrecisionTimer::PrecisionTimer()
{
#ifdef _WIN32
	__int64 countsPerSec;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));
	m_SecondsPerCount = 1.0 / double(countsPerSec);
#endif
}

// Returns the total time elapsed since reset() was called, NOT counting any
// time when the clock is stopped.
double PrecisionTimer::GetGameTime()
{


	// If we are stopped, do not count the time that has passed since we stopped.
	//
	// ----*---------------*------------------------------*------> time
	//  mBaseTime       mStopTime                      mCurrTime

	if (m_bStopped)
	{
#ifdef _WIN32
		return static_cast<double>((m_StopTime - m_PausedTime - m_BaseTime) * m_SecondsPerCount);
#else
        return static_cast<double>((m_CurrTime - m_PausedTime - m_BaseTime) / CLOCKS_PER_SEC);
#endif
	}

	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from mCurrTime:  
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		//Bart: Get current time
#ifdef _WIN32
		QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrTime);
		return static_cast<double>((m_CurrTime - m_PausedTime - m_BaseTime) * m_SecondsPerCount);
#else
        m_CurrTime = std::clock();
        return static_cast<double>((m_CurrTime - m_PausedTime - m_BaseTime) / CLOCKS_PER_SEC);
#endif
	}
}

double PrecisionTimer::GetDeltaTime() const
{
	return double(m_DeltaTime);
}

void PrecisionTimer::Reset()
{
#ifdef _WIN32
	__int64 currTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
#else
    std::clock_t currTime { std::clock() };
#endif

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_PausedTime = 0;
	m_bStopped = false;
}

void PrecisionTimer::Start()
{
#ifdef _WIN32
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));
#else
    std::clock_t startTime { std::clock() };
#endif

	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime     

	if (m_bStopped)
	{
		m_PausedTime += (startTime - m_StopTime);
		m_StopTime = 0;
		m_bStopped = false;
	}
}

void PrecisionTimer::Stop()
{
	if (!m_bStopped)
	{
#ifdef _WIN32
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
#else
        std::clock_t currTime { std::clock() };
#endif

		m_StopTime = currTime;
		m_bStopped = true;
	}
}

void PrecisionTimer::Tick()
{
	if (m_bStopped)
	{
		m_DeltaTime = 0.0;
		return;
	}

#ifdef _WIN32
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
#else
    std::clock_t currTime { std::clock() };
#endif
	m_CurrTime = currTime;

	// Time difference between this frame and the previous.
#ifdef _WIN32
	m_DeltaTime = (m_CurrTime - m_PrevTime - m_PausedTime) * m_SecondsPerCount;
#else
    m_DeltaTime = (m_CurrTime - m_PausedTime - m_BaseTime) / CLOCKS_PER_SEC;
#endif

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}

	// Prepare for next frame.
	m_PrevTime = m_CurrTime;
	m_PausedTime = 0;

}

bool PrecisionTimer::IsStopped() const
{
	return m_bStopped;
}