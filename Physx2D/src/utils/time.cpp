#include "time.h"

Physx2D::Time::Time() {
	current_time = 0.f;
	last_time = 0.f;
}

void Physx2D::Time::initTimer(){
	current_time = glfwGetTime();
	last_time = current_time;
}

double Physx2D::Time::get_time(){
	return glfwGetTime();
}

int Physx2D::Time::get_fps(){
	double del = current_time - last_time;
	return del == 0.0 ? 0 : (int)(1.0 / del);
}

double Physx2D ::Time::get_delta_time() {
	double del = current_time - last_time;
	return del < 0.0 ? 0.0 : del;
}

void Physx2D::Time::update(){
	last_time = current_time;
	current_time = glfwGetTime();
}
