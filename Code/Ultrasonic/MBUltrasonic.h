/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef MBULTRASONIC_H_
#define MBULTRASONIC_H_

#define NUM_SAMPLES 9

#include "SensorBase.h"
#include "Task.h"
#include "PIDSource.h"

class Counter;
class DigitalInput;
class DigitalOutput;

/**
 * MBUltrasonic rangefinder class.
 * This class is a modified version of the WPILib Ultrasonic class.
 * It is specific to the Maxbotics LV-MaxSonar-EZ1, and omits the code to
 * coordinate multiple Ultrasonic sensors.
 * 
 * MBUltrasonic rangefinder measures absolute distance based on the round-trip time
 * of a ping generated by the controller. These sensors use two transducers, a speaker and
 * a microphone both tuned to the ultrasonic range.  By default, the EZ1 emits  pings repetitively.
 * Pings can be disabled by setting the EZ1's RCVR pin low, and re-enabled by setting RCVR high.
 * The EZ1 provides three different ways to report the echo delay, but this class only uses one of them,
 * the PW pin.  When a ping is sent, the PW pin is set high and when the echo is received
 * the PW pin is set low.  Thus the width of the high pulse on the PW pin is directly proportional
 * to the round trip distance (time of flight).
 * 
 * MBUltrasonic requires two digital channels.  The first is called m_pingChannel and is a digital
 * output connected to RCVR pin on the EZ1.  The second is called m_echoChannel and is a digital input
 * connected to the PW pin on the EZ1.
 */
class MBUltrasonic: public SensorBase, public PIDSource
{
public:
	typedef enum {
		kInches = 0,
		kMilliMeters = 1
	} DistanceUnit;
	
	MBUltrasonic(DigitalOutput *pingChannel, DigitalInput *echoChannel, DistanceUnit units = kInches);
	MBUltrasonic(DigitalOutput &pingChannel, DigitalInput &echoChannel, DistanceUnit units = kInches);
	MBUltrasonic(UINT32 pingChannel, UINT32 echoChannel, DistanceUnit units = kInches);
	MBUltrasonic(UINT8 pingModuleNumber, UINT32 pingChannel,
							UINT8 echoModuleNumber, UINT32 echoChannel, DistanceUnit units = kInches);
	virtual ~MBUltrasonic();

	void PingEnable(bool enable=1);
	bool IsPingEnabled() { return m_pingEnabled; }
	bool IsRangeValid();
	double GetRangeInches();
	double GetRangeMM();
	
	double PIDGet();
	void SetDistanceUnits(DistanceUnit units);
	DistanceUnit GetDistanceUnits();

private:
	void Initialize();

	double raw_range[10];
	int pos;
	
	static const double kPingTime = 10 * 1e-6;	///< Time (sec) for the ping trigger pulse.
	static const double kMaxUltrasonicTime = 0.1;	///< Max time (ms) between readings.
	static const double kSpeedOfSoundInchesPerSec = 1130.0 * 12.0;

	DigitalInput *m_echoChannel;
	DigitalOutput *m_pingChannel;
	bool m_allocatedChannels;
	bool m_pingEnabled;
	Counter *m_counter;
	
	DistanceUnit m_units;
};

#endif
