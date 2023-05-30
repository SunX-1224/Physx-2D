#version 460 core
 
struct RayCastMat{
	vec4 color;
	//vec4 e_color;
	//float e_strength;
};

struct Sphere{
	vec4 pos_rad;
	RayCastMat material;
};

struct Camera{
	vec3 position;
	vec3 direction;
};

struct Ray{
	vec3 origin;
	vec3 direction;
};

struct HitInfo{
	bool hit;
	float dist;
	vec3 point;
	vec3 normal;
	RayCastMat material;
};

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D img_output;

layout(std430, binding = 1) buffer spheredata{
	Sphere spheres[];
};

uniform int numSpheres;
//uniform float u_time;

HitInfo checkIntersect_sphere(vec3 position, float radius, Ray ray);
HitInfo calculateRayCollision(Ray ray);
float random(inout uint seed);
float randomnd(inout uint seed);
vec3 randomdir(inout uint seed);
vec3 randomhemi(vec3 normal, uint seed);
vec3 traceRay(Ray ray, uint seed);

void main(){
	Camera camera;
	camera.position = vec3(0.f, 0.f, -10000.f);
	camera.direction = vec3(0.f, 0.f, 1.f);

	ivec2 coords = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(img_output);

	Ray ray;
	ray.origin = camera.position;
	vec3 scrpos = vec3(float(coords.x * 2.f - size.x), float(coords.y * 2.f - size.y), 0.f);
	ray.direction = normalize(scrpos - camera.position);

	vec3 color = traceRay(ray, coords.x + coords.y * size.x);
	imageStore(img_output, coords, vec4(color ,1.f));
}

vec3 traceRay(Ray ray, uint seed){
	vec3 ray_color = vec3(1.f);
	vec3 incoming = vec3(0.f);

	for(int i=0; i<1;i++){
		HitInfo info = calculateRayCollision(ray);

		if(info.hit){
			ray.origin = info.point;
			ray.direction = randomhemi(info.normal, seed);

			//incoming += ray_color * info.material.color.xyz;
			ray_color *= info.material.color.xyz;
			incoming = info.normal;
		}else{
			break;
		}
	}
	return incoming;
}


HitInfo calculateRayCollision(Ray ray){
	
	HitInfo closest;
	closest.hit = false;
	closest.dist = 1.f/0.f;

	for(int i=0; i<numSpheres; i++){
		HitInfo info = checkIntersect_sphere(spheres[i].pos_rad.xyz, spheres[i].pos_rad.w, ray);

		if(info.hit && info.dist < closest.dist){
			closest = info;
			closest.material = spheres[i].material;
		}
	}

	return closest;
}

HitInfo checkIntersect_sphere(vec3 position, float radius, Ray ray){
	HitInfo hitInfo;

	vec3 off = ray.origin - position;

	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.direction, off);
	float c = dot(off, off) - radius * radius;

	float discr = b*b - 4*a*c;

	if(discr >= 0){
		float dist = (-b - sqrt(discr))/(2*a);

		if(dist >=0 ){
			hitInfo.hit = true;
			hitInfo.dist = dist;
			hitInfo.point = ray.origin + ray.direction * dist;
			hitInfo.normal = hitInfo.point - position;
		}
	}
	return hitInfo;
}

vec3 randomhemi(vec3 normal, uint seed){
	vec3 rn = randomdir(seed);
	return rn * sign(dot(rn, normal));
}

vec3 randomdir(inout uint seed){
	return vec3(randomnd(seed), randomnd(seed), randomnd(seed));
}

float randomnd(inout uint seed){
	float theta = 2*3.1415926*random(seed);
	float del = sqrt(-2 * log(random(seed)));
	return cos(theta) * del;
}

float random(inout uint seed){
	seed *= 45546654;
	seed *= seed * 32423 + 4535645;
	
	return float(seed)/4294967295.f;
}
