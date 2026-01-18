#version 460

//In
in vec2 pPixelCoords;

//Uniforms
uniform vec2 screenParams;
uniform vec3 viewParams; //planeWidth, planeHeight, focalLength;
uniform vec3 cameraPos;

uniform mat4 localToWorld;

//Out
out vec4 fragColor;

//Shader
struct Ray
{
    vec3 origin, dir;
};

struct HitInfo
{
    bool didHit;
    float dst;
    vec3 hitPos, normal;
};

//Thanks to: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html and https://www.youtube.com/watch?v=Qz0KTGYJtUk
HitInfo raySphere(Ray ray, vec3 position, float radius)
{
    HitInfo result;
    result.didHit = false;

    vec3 offsetRayOrigin = ray.origin - position;

    float a = dot(ray.dir, ray.dir);
    float b = 2 * dot(offsetRayOrigin, ray.dir);
    float c = dot(offsetRayOrigin, offsetRayOrigin) - radius * radius;

    float discreminant = b * b - 4 * a * c;

    if(discreminant >= 0)
    {
        float dst = (-b - sqrt(discreminant)) / (2 * a);

        if(dst >= 0)
        {
            result.didHit = true;
            result.dst = dst;
            result.hitPos = ray.origin + ray.dir * dst;
            result.normal = normalize(result.hitPos - position);
        }
    }

    return result;
}

void main()
{
    vec3 viewPointLocal = vec3(pPixelCoords - 0.5, 1) * viewParams;
    vec3 viewPoint = (localToWorld * vec4(viewPointLocal, 1)).xyz;

    Ray ray;
    ray.origin = cameraPos;
    ray.dir = normalize(viewPoint - ray.origin);

    HitInfo a = raySphere(ray, vec3(0, 0, 1), 1);

    fragColor = vec4(ray.dir * float(a.didHit), 1);
}
