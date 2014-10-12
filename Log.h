#pragma once

#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include "Area.h"

enum LogLevel {
	Debug,
	Info,
	Warn,
	Error
};

class Log
{
private:
	Log();

	static LogLevel threshold;

	class LogSignal
	{
	public:
		LogSignal() {}
	};

	class LogStream
	{
	public:
		LogStream(const LogLevel threshold)
			: threshold(threshold)
		{

		}

		template <class T>
		LogStream& operator<<(const T& message)
		{
			if (this->threshold <= Log::threshold)
			{
				std::cerr << message;
			}
			return *this;
		}

		template<>
		LogStream& operator<<(const LogSignal& signal)
		{

			if (this->threshold <= Log::threshold)
			{
				std::cerr << std::endl;
			}
			return *this;
		}
	private:
		const LogLevel threshold;
	};

public:
	static void SetThreshold(const LogLevel threshold);
	static void SetThreshold(const char* thresholdName);
	static void PrintPixels(const char* message, const Area* area, const GLubyte* content, const int channels);

	static LogStream Debug;
	static LogStream Info;
	static LogStream Warn;
	static LogStream Error;

	static const LogSignal end;
};
