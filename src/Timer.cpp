#include<Timer.hpp>

Timer::Timer() {
	m = 0;
	s = 0;
}
std::string Timer::IncreaseTimer() {
	s = 0;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	s++;
	if (s>60)
	{
		s = 0;
		m++;
	}
	std::string data = m + ":" + s;
	return data;
}
void Timer::setTitle(GLFWwindow* window,const char* title) {
	glfwSetWindowTitle(window, title +* IncreaseTimer().c_str());

}