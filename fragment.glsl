#version 460 core

in vec3 position;
in vec3 normal;
in vec3 color;

uniform mat4 MVP[3];
uniform vec3 cameraPosition;
uniform vec3 ambientColor;
uniform uint lightsCount;

struct lightSource {
    vec3 position;
    float reserved0;
    vec3 color;
    float attenuation;
};

layout (std430, binding = 0) buffer Lights {
    lightSource light[];
} lights;

out vec3 fragmentColor;

void main()
{
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    for (uint i = 0; i < lightsCount; ++i)
    {
        vec3 lightingDirection = normalize(lights.light[i].position - position);
        float lightingDistance = length(lights.light[i].position - position);
        vec3 viewDirection = normalize(cameraPosition - position);
        vec3 bisect = normalize(lightingDirection + viewDirection);

        //vec3 dimmedColor = lights.light[i].color;
        vec3 dimmedColor = lights.light[i].color * pow(clamp((lights.light[i].attenuation - length(lightingDistance)) / lights.light[i].attenuation, 0.f, 1.f), 2);

        diffuse = diffuse + max(dot(normalize(normal), lightingDirection), 0.0) * dimmedColor;
        specular = specular + pow(max(dot(normalize(normal), bisect), 0.0), 64) * dimmedColor;
    }
    fragmentColor = specular + diffuse + ambientColor;
}
