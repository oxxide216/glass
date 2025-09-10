#include <GL/glew.h>

#include "params.h"

void glass_set_param_texture(GlassShader *shader, char *name,
                             GlassTextures *textures, u32 index) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform1i(location, textures->items[index].id);
}

void glass_set_param_1f(GlassShader *shader, char *name, f32 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform1f(location, param);
}

void glass_set_param_2f(GlassShader *shader, char *name, Vec2 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform2f(location, param.x, param.y);
}

void glass_set_param_3f(GlassShader *shader, char *name, Vec3 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform3f(location, param.x, param.y, param.z);
}

void glass_set_param_4f(GlassShader *shader, char *name, Vec4 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform4f(location, param.x, param.y, param.z, param.w);
}


void glass_set_param_1i(GlassShader *shader, char *name, i32 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform1i(location, param);
}

void glass_set_param_2i(GlassShader *shader, char *name, IVec2 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform2i(location, param.x, param.y);
}

void glass_set_param_3i(GlassShader *shader, char *name, IVec3 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform3i(location, param.x, param.y, param.z);
}

void glass_set_param_4i(GlassShader *shader, char *name, IVec4 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform4i(location, param.x, param.y, param.z, param.w);
}


void glass_set_param_1u(GlassShader *shader, char *name, u32 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform1ui(location, param);
}

void glass_set_param_2u(GlassShader *shader, char *name, UVec2 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform2ui(location, param.x, param.y);
}

void glass_set_param_3u(GlassShader *shader, char *name, UVec3 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform3ui(location, param.x, param.y, param.z);
}

void glass_set_param_4u(GlassShader *shader, char *name, UVec4 param) {
  glUseProgram(shader->id);
  GLint location = glGetUniformLocation(shader->id, name);
  glUniform4ui(location, param.x, param.y, param.z, param.w);
}
