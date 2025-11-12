#ifndef PARAM_H
#define PARAM_H

#include "glass.h"
#include "math.h"

void glass_set_param_texture(GlassShader *shader, char *name, GlassTexture *param);

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

void glass_set_param_1f_array(GlassShader *shader, char *name,
                              f32 *params, u32 len);
void glass_set_param_2f_array(GlassShader *shader, char *name,
                              Vec2 *params, u32 len);
void glass_set_param_3f_array(GlassShader *shader, char *name,
                              Vec3 *params, u32 len);
void glass_set_param_4f_array(GlassShader *shader, char *name,
                              Vec4 *params, u32 len);

void glass_set_param_1i_array(GlassShader *shader, char *name,
                              i32 *params, u32 len);
void glass_set_param_2i_array(GlassShader *shader, char *name,
                              IVec2 *params, u32 len);
void glass_set_param_3i_array(GlassShader *shader, char *name,
                              IVec3 *params, u32 len);
void glass_set_param_4i_array(GlassShader *shader, char *name,
                              IVec4 *params, u32 len);

void glass_set_param_1u_array(GlassShader *shader, char *name,
                             u32 *params, u32 len);
void glass_set_param_2u_array(GlassShader *shader, char *name,
                              UVec2 *params, u32 len);
void glass_set_param_3u_array(GlassShader *shader, char *name,
                              UVec3 *params, u32 len);
void glass_set_param_4u_array(GlassShader *shader, char *name,
                              UVec4 *params, u32 len);

#endif // PARAM_H
