#version 460 core
 
struct RayCastMat{
	vec4 color;
	vec4 e_cs;
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
vec3 traceRay(Ray ray, inout uint seed);

void main(){
	Camera camera;
	camera.position = vec3(0.f, 0.f, 600.f);
	camera.direction = vec3(0.f, 0.f, -1.f);

	ivec2 coords = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(img_output);

	Ray ray;
	ray.origin = camera.position;
	vec3 scrpos = vec3(float(coords.x  - size.x* .5f), float(coords.y  - size.y * .5f), 0.f);
	ray.direction = normalize(scrpos - camera.position);

	vec3 color = vec3(0.f);

	int raysPerPixel = 8;
	uint seed = coords.x + coords.y * size.x;
	for(int i=0; i<2; i++)
		color += traceRay(ray, seed);
	color /= float(raysPerPixel);

	imageStore(img_output, coords, vec4(color ,1.f));
}

vec3 traceRay(Ray ray, inout uint seed){
	vec3 ray_color = vec3(1.f);
	vec3 incoming = vec3(0.f);

	for(int i=0; i<4;i++){
		HitInfo info = calculateRayCollision(ray);

		if(info.hit){
			ray.origin = info.point;
			ray.direction = randomhemi(info.normal, seed);
			//ray.direction = reflect(ray.direction, info.normal);

			vec3 emitted =  info.material.e_cs.rgb * info.material.e_cs.a;
			incoming += ray_color * emitted;
			ray_color *= info.material.color.xyz;
			//incoming = info.normal;// * vec3(1.f, 1.f, -1.f);
		}else{
			incoming *= vec3(1.f, 1.f, 1.4f);
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
			hitInfo.normal = normalize(hitInfo.point - position);
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
	seed = seed * 747796405 + 2891336453;
	uint result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
	result = (result >> 22) ^ result;
	return float(result) / 4294967295.0f;
}
