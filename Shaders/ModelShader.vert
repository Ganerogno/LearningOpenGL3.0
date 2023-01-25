#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in ivec4 boneIDs;
layout (location = 4) in vec4 weights;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragNorm;
out vec3 fragPos;
out vec2 TexCoords;

void main()
{
    fragNorm = mat3(model) * normals;
    fragPos = vec3(model * vec4(position, 1.0f));
    TexCoords = texCoords;

    mat4 BoneTransform = gBones[boneIDs[0]] * weights[0];
    BoneTransform += gBones[boneIDs[1]] * weights[1];
    BoneTransform += gBones[boneIDs[2]] * weights[2];
    BoneTransform += gBones[boneIDs[3]] * weights[3];   

    vec4 PosL = BoneTransform * vec4(position, 1.0);
    gl_Position = projection * view * model * PosL;
}