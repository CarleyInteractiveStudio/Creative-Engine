#pragma once

// This is a placeholder for the engine's math library.
// A full implementation would be extensive and highly optimized, likely using SIMD instructions
// for vector and matrix operations. It would include classes for Vec2, Vec3, Vec4, Mat3, Mat4,
// Quaternions, and a wide range of mathematical functions (e.g., Lerp, Clamp, Radians).

namespace Creative {

// Basic Vector structs
struct Vec2 { float x = 0.0f, y = 0.0f; };
struct Vec3 { float x = 0.0f, y = 0.0f, z = 0.0f; };
struct Vec4 { float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f; };

// Placeholder for a 4x4 Matrix
// In a real engine, this would have a full suite of operations:
// translation, rotation, scale, perspective, look-at, etc.
struct Mat4
{
    // Stored in column-major order for compatibility with graphics APIs like OpenGL.
    float elements[4][4];
};

} // namespace Creative
