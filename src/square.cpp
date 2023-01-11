#include<square.hpp>
Square::Square(float x, float y, float length) {
	position = glm::vec3(x,y,0.0f);
	this->length = length;
}
void Square::SetDirection(Square::DIRECTION direction) {
	this->local_direction = direction;
}
void Square::move_square() {
	switch (local_direction) {
		case DIRECTION_RIGHT:
			position += glm::vec3(length, 0.0f, 0.0f);
			break;
		case DIRECTION_LEFT:
			position += glm::vec3(-length, 0.0f, 0.0f);
			break;
		case DIRECTION_UP:
			position += glm::vec3(0.0f, length, 0.0f);
			break;
		case DIRECTION_DOWN:
			position += glm::vec3(0.0f, -length, 0.0f);
			break;
	}
}
glm::vec3 Square::GetPosition() {
	return position;
}
glm::vec4 Square::GetColor() {
	return color;
}
Square::DIRECTION Square::getDirection() {
	return local_direction;
}
float Square::GetLength() {
	return length;
}
Square::Square(float x, float y, float length, glm::vec4 color, Square::DIRECTION DIR) {
	position = glm::vec3(x, y, 0.0f);
	this->length = length;
	this->color = color;
	local_direction = DIR;
}
void Square::Reset() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}
