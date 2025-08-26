#ifndef PARAM_H
#define PARAM_H

#include "glass.h"
#include "math.h"

void glass_set_param_1f(GlassShader *shader, char *name, f32 param);
void glass_set_param_2f(GlassShader *shader, char *name, Vec2 param);
void glass_set_param_3f(GlassShader *shader, char *name, Vec3 param);
void glass_set_param_4f(GlassShader *shader, char *name, Vec4 param);

void glass_set_param_1i(GlassShader *shader, char *name, i32 param);
void glass_set_param_2i(GlassShader *shader, char *name, IVec2 param);
void glass_set_param_3i(GlassShader *shader, char *name, IVec3 param);
void glass_set_param_4i(GlassShader *shader, char *name, IVec4 param);

void glass_set_param_1u(GlassShader *shader, char *name, u32 param);
void glass_set_param_2u(GlassShader *shader, char *name, UVec2 param);
void glass_set_param_3u(GlassShader *shader, char *name, UVec3 param);
void glass_set_param_4u(GlassShader *shader, char *name, UVec4 param);

#endif // PARAM_H
