#include<Timer.hpp>
Timer::Timer() {
	m = 0;
	s = 0;
}
std::string Timer::IncreaseTimer() {
	s = 0;
	s++;
	if (s>60)
	{
		s = 0;
		m++;
	}
	std::string data = m + ":" + s;
	return data;
}
