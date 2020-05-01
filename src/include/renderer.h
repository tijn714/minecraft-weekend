#ifndef RENDERER_H
#define RENDERER_H

#include "blockatlas.h"
#include "gfx.h"
#include "util.h"
#include "shader.h"

#define SHADERS_LAST SHADER_BASIC_2D
enum ShaderType {
    SHADER_NONE = 0,
    SHADER_CHUNK,
    SHADER_BASIC_2D
};

#define CAMERA_STACK_MAX 256

enum RenderPass {
    PASS_2D, PASS_3D
};

struct Renderer {
    enum CameraType camera_type;
    struct {
        enum CameraType array[CAMERA_STACK_MAX];
        size_t size;
    } camera_stack;

    struct PerspectiveCamera perspective_camera;
    struct OrthoCamera ortho_camera;

    struct Shader shaders[SHADERS_LAST + 1];
    enum ShaderType current_shader;

    struct BlockAtlas block_atlas;

    vec4s clear_color;

    struct {
        bool wireframe: 1;
    } flags;
};

void renderer_init(struct Renderer *self);
void renderer_destroy(struct Renderer *self);
void renderer_update(struct Renderer *self);
void renderer_prepare(struct Renderer *self, enum RenderPass pass);
void renderer_set_camera(struct Renderer *self, enum CameraType type);
void renderer_push_camera(struct Renderer *self);
void renderer_pop_camera(struct Renderer *self);
void renderer_set_view_proj(struct Renderer *self);
void renderer_use_shader(struct Renderer *self, enum ShaderType shader);

#endif