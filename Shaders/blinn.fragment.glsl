#version 460 core

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 UV;
};

struct LightSource {
    vec3 position;
    float reserved0;
    vec3 color;
    float attenuation;
};

in Vertex vertex;
in flat uint vertexMaterialId;
in flat uint vertexMeshId;

layout (std140, binding = 0) uniform CameraMatrices {
    mat4 world;
    mat4 view;
    mat4 projection;
    vec3 position;
} cameraMatrices;

layout (std430, binding = 0) buffer Lights {
    vec3 ambient;
    float reserved0;
    uint count;
    float reserved1;
    LightSource light[];
} lights;


layout (binding = 0) uniform sampler2D ambientTexture;
layout (binding = 1) uniform sampler2D diffuseTexture;
layout (binding = 2) uniform sampler2D specularTexture;
layout (binding = 3) uniform sampler2D bumpTexture;


out vec3 fragmentColor;

void main()
{
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    for (uint i = 0; i < lights.count; ++i)
    {
        vec3 lightingDirection = normalize(lights.light[i].position - vertex.position);
        float lightingDistance = length(lights.light[i].position - vertex.position);
        vec3 viewDirection = normalize(cameraMatrices.position - vertex.position);
        vec3 bisect = normalize(lightingDirection + viewDirection);

        vec3 dimmedColor = lights.light[i].color * pow(clamp((lights.light[i].attenuation - length(lightingDistance)) / lights.light[i].attenuation, 0.f, 1.f), 2);

        diffuse = diffuse + max(dot(normalize(vertex.normal), lightingDirection), 0.0) * dimmedColor;
        specular = specular + pow(max(dot(normalize(vertex.normal), bisect), 0.0), 64) * dimmedColor;
    }
    fragmentColor = 
        specular * texture(specularTexture, vertex.UV).rgb + (diffuse + lights.ambient * texture(ambientTexture, vertex.UV).rgb) * texture(diffuseTexture, vertex.UV).rgb; // Включить для текстурирования
    //fragmentColor = normalize(vertex.position).rgb; // Включить для обображения координат вершин
    //fragmentColor = normalize(vec3(vertex.UV.x, 0.0, vertex.UV.y)); // Включить для отображения текстурных координат
}
