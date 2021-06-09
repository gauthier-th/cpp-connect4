#include "Animation.h"
#include <iostream>
#include <chrono>

Animation::Animation(int _begin, int _end, long _duration): begin(_begin), end(_end), duration(_duration)
{
}
Animation::Animation(int _begin, int _end, long _duration, std::function<void()> _endCallback) : begin(_begin), end(_end), duration(_duration), endCallback(_endCallback)
{
}

void Animation::start()
{
	this->startTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
void Animation::stop()
{
	if (this->endCallback != nullptr && !this->stopCalled)
	{
		this->stopCalled = true;
		this->endCallback();
		//this->startTimestamp = 0.f;
	}
}

int Animation::state()
{
	if (this->startTimestamp == 0)
		throw "Animation not started!";
	const auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (this->startTimestamp + this->duration <= timestamp)
	{
		this->stop();
		return this->end;
	}
	const float percent = (timestamp - this->startTimestamp) / (float)this->duration;
	return this->easingLinear(percent);
}

int Animation::easingLinear(float percent)
{
	return ((float)(this->end - this->begin)) * percent + (float)this->begin;
}