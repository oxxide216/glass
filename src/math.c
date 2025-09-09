#include "math.h"

Vec2 vec2(f32 x, f32 y) {
  return (Vec2) { x, y };
}

Vec3 vec3(f32 x, f32 y, f32 z) {
  return (Vec3) { x, y, z };
}

Vec4 vec4(f32 x, f32 y, f32 z, f32 w) {
  return (Vec4) { x, y, z, w };
}

IVec2 ivec2(i32 x, i32 y) {
  return (IVec2) { x, y };
}

IVec3 ivec3(i32 x, i32 y, i32 z) {
  return (IVec3) { x, y, z };
}

IVec4 ivec4(i32 x, i32 y, i32 z, i32 w) {
  return (IVec4) { x, y, z, w };
}

UVec2 uvec2(u32 x, u32 y) {
  return (UVec2) { x, y };
}

UVec3 uvec3(u32 x, u32 y, u32 z) {
  return (UVec3) { x, y, z };
}

UVec4 uvec4(u32 x, u32 y, u32 z, u32 w) {
  return (UVec4) { x, y, z, w };
}
