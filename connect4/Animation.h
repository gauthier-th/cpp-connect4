#pragma once
#include <functional>

class Animation
{
private:
	int begin;
	int end;
	long long startTimestamp = 0;
	long long duration;
	int easingLinear(float percent);
	bool stopCalled = false;
	std::function<void()> endCallback = nullptr;
public:
	Animation(int _begin, int _end, long _duration);
	Animation(int _begin, int _end, long _duration, std::function<void()> _endCallback);
	void start();
	void stop();
	int state();
};