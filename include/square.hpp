#ifndef SQUARE_HPP
#define SQUARE_HPP
#include<iostream>
#include<Shader.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class Square {
public:
	enum DIRECTION
	{
		DIRECTION_LEFT	= -1,
		DIRECTION_RIGHT =  1,
		DIRECTION_UP	=  2,
		DIRECTION_DOWN	= -2
	}; 
	Square(float x,float y,float length);
	Square(float x,float y,float length,glm::vec4 color,Square::DIRECTION DIR);
	void SetDirection(Square::DIRECTION direction);
	Square::DIRECTION getDirection();
	void move_square();
	glm::vec3 GetPosition();
	glm::vec4 GetColor();
	float GetLength();
	void Reset();
private:
	Square::DIRECTION local_direction = DIRECTION_RIGHT;
	float length=0.1f;
	glm::vec3 position=glm::vec3(0.0f,0.0f,0.0f);
	glm::vec4 color=glm::vec4(0.5f,0.5f,0.0f,1.0f);
};










#endif 