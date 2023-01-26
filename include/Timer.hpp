#ifndef TIMER_HPP
#define TIMER_HPP
#include<iostream>
#include<GLFW/glfw3.h>
#include<thread>
#include<chrono>
class Timer
{
public:
	Timer();
	void setTitle(GLFWwindow* window,const char* title);
	std::string IncreaseTimer();
private:
	
	int s, m;
};

#endif