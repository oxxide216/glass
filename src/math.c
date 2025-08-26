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
