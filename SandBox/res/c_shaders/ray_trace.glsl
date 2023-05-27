#version 460 core

layout(local_size_x = 10, local_size_y = 5, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D img_output;


struct Sphere{
	vec3 position;
	float radius;
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
};

HitInfo checkIntersect_sphere(Sphere sphere, Ray ray);

void main(){
	Camera camera;
	camera.position = vec3(0.f, 0.f, -5.f);
	camera.direction = vec3(0.f, 0.f, 1.f);

	Sphere sphere;
	sphere.position = vec3(500.f, 400.f, 50.f);
	sphere.radius = 50.f;

	vec4 value = vec4(0.f, 0.f, 0.f, 1.0f);
	ivec3 coords = ivec3(gl_GlobalInvocationID.xyz);

	Ray ray;
	ray.origin = camera.position;
	ray.direction = normalize(coords - camera.position);

	HitInfo info = checkIntersect_sphere(sphere, ray);

	if(info.hit)
		value.xyz = vec3(1.f, 0.3, 0.3f);

	imageStore(img_output, coords.xy, value);
}

HitInfo checkIntersect_sphere(Sphere sphere, Ray ray){
	HitInfo hitInfo;

	vec3 offsetRayOrigin = ray.origin - sphere.position;
	//vec3 offsetRayOrigin = vec3(0.f, 0.f, 0.f);
	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(offsetRayOrigin, ray.direction);
	float c = dot(offsetRayOrigin, offsetRayOrigin) - sphere.radius * sphere.radius;
	float discriminant = b * b - 4 * a * c; 

	if (discriminant >= 0) {
		float dst = (-b - sqrt(discriminant)) / (2 * a);

		if (dst >= 0) {
			hitInfo.hit = true;
			hitInfo.dist = dst;
			hitInfo.point = ray.origin + ray.direction * dst;
			hitInfo.normal = normalize(hitInfo.point - sphere.position);
		}
	}

	return hitInfo;
}
