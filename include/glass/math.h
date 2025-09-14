#ifndef MATH_H
#define MATH_H

#include "../../src/shl_defs.h"

typedef struct {
  f32 x, y;
} Vec2;

typedef struct {
  f32 x, y, z;
} Vec3;

typedef struct {
  f32 x, y, z, w;
} Vec4;


typedef struct {
  i32 x, y;
} IVec2;

typedef struct {
  i32 x, y, z;
} IVec3;

typedef struct {
  i32 x, y, z, w;
} IVec4;


typedef struct {
  u32 x, y;
} UVec2;

typedef struct {
  u32 x, y, z;
} UVec3;

typedef struct {
  u32 x, y, z, w;
} UVec4;

Vec2 vec2(f32 x, f32 y);
Vec3 vec3(f32 x, f32 y, f32 z);
Vec4 vec4(f32 x, f32 y, f32 z, f32 w);

IVec2 ivec2(i32 x, i32 y);
IVec3 ivec3(i32 x, i32 y, i32 z);
IVec4 ivec4(i32 x, i32 y, i32 z, i32 w);

UVec2 uvec2(u32 x, u32 y);
UVec3 uvec3(u32 x, u32 y, u32 z);
UVec4 uvec4(u32 x, u32 y, u32 z, u32 w);

#endif // MATH_H
