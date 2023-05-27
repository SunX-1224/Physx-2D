#pragma once
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

			inline vec3<int> getWorkGrpCount();
			inline vec3<int> getWorkGrpSize();
			inline int maxLocalWorkGrpInv();

		private:
			uint32_t m_ID;
	};
}