#pragma once

/*
	Compute shaders can be used to perform computational operations parallely in gpu to speed up some processes.
	Compute shader must be written in glsl and must follow the rules.
	
	Functionalities:
		> dispatch (...dims...) : dispatches  the compute shader to gpu
		> waitUntilFinish(barriesBits) : wait until the barrier is crossed
		> use : activate the compute shader program
		> set... : sets the uniform values
		> getter functions  :work group count , work group size, max local work group invocations
*/

#include "utils.h"
#include "math/math.h"

namespace Physx2D {
	
	class PHYSX2D_API ComputeShader {
		public:
			ComputeShader(const char* path);
			~ComputeShader();

			inline void dispatch(uint32_t x, uint32_t y, uint32_t z = 1);
			inline void waitUntilFinish(GLbitfield barrier);
			inline void use();

			inline void setInt(const char* u_name, int value);
			inline void setFloat(const char* u_name, float value);

			inline tvec3<int> getWorkGrpCount();
			inline tvec3<int> getWorkGrpSize();
			inline int maxLocalWorkGrpInv();

		private:
			uint32_t m_ID;
	};
}