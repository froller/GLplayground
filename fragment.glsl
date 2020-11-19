#version 460 core

in vec3 position;
in vec3 normal;
in vec3 color;

uniform mat4 MVP[3];
uniform vec3 cameraPosition;
uniform vec3 ambientColor;
uniform uint lightsCount;

layout (std430, binding = 0) buffer Lights {
    vec3 position;
    vec3 color;
    float attenuation;
} lights[4];

out vec3 fragmentColor;

void main()
{
    vec3 diffuse;
    vec3 specular;
    for (uint i = 0; i < lightsCount; ++i)
    {
        vec3 lightingDirection = normalize(lights[i].position - position);
        float lightingDistance = length(lights[i].position - position);
        vec3 viewDirection = normalize(cameraPosition - position);
        vec3 bisect = normalize(lightingDirection + viewDirection);

        //vec3 dimmedColor = lights[i].color;
        vec3 dimmedColor = lights[i].color * pow(clamp((lights[i].attenuation - length(lightingDistance)) / lights[i].attenuation, 0.f, 1.f), 2);

        diffuse = diffuse + dot(normalize(normal), lightingDirection) * dimmedColor;
        specular = specular + 0.5 * pow(max(dot(normalize(normal), bisect), 0.0), 64) * dimmedColor;
    }
    fragmentColor = specular + diffuse + ambientColor;
}
