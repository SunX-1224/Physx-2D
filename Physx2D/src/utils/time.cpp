#include "pch.h"
#include "time.h"

Physx2D::Time::Time() {
	current_time = 0.f;
	last_time = 0.f;
}

void Physx2D::Time::initTimer(){
	current_time = last_time = 0;
	glfwSetTime(0.0);
}

double Physx2D::Time::get_time(){
	return glfwGetTime();
}

int Physx2D::Time::get_fps(){
	return current_time < last_time ? 0 : (1.f / (current_time - last_time));
}

double Physx2D ::Time::get_delta_time() {
	return current_time < last_time ? 0.0 :(current_time - last_time);
}

void Physx2D::Time::update(){
	last_time = current_time, current_time = glfwGetTime();
}
