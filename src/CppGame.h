#pragma once
#include "CppGameCore.h"
#include <float.h>
#include <math.h>

constexpr float PI = 3.1415926535f;
constexpr float PI_INVERSE = 1.0f / PI;
constexpr float TAU = PI / 2;
constexpr float REAL_EPSILON = FLT_EPSILON;
constexpr float REAL_MAX = FLT_MAX;
constexpr float REAL_MIN = FLT_MIN;
constexpr float REAL_INFINITY = INFINITY;

union Vec2 {
	struct {
		float x, y;
	};
	float m[2];
	Vec2() { }
	Vec2(float a): x(a), y(a) { }
	Vec2(float a, float b): x(a), y(b) { }
	float &operator()(uint32_t index) {
		Assert(index < 2);
		return ((float *)this)[index];
	}
};

union Vec3 {
	struct {
		float x, y, z;
	};
	struct {
		Vec2  xy;
		float _z;
	};
	struct {
		float _x;
		Vec2  yz;
	};
	float m[3];
	Vec3() { }
	Vec3(float a): x(a), y(a), z(a) { }
	Vec3(float a, float b, float c): x(a), y(b), z(c) { }
	Vec3(Vec2 ab, float c): xy(ab), _z(c) { }
	Vec3(float a, Vec2 cd): _x(a), yz(cd) { }
	float &operator()(uint32_t index) {
		Assert(index < 3);
		return ((float *)this)[index];
	}
};

union Vec4 {
	struct {
		float x, y, z, w;
	};
	struct {
		Vec2 xy, zw;
	};
	struct {
		Vec3  xyz;
		float _w;
	};
	struct {
		float _x;
		Vec3  yzw;
	};
	float m[4];
	Vec4() { }
	Vec4(float a): x(a), y(a), z(a), w(a) { }
	Vec4(float a, float b, float c, float d): x(a), y(b), z(c), w(d) { }
	Vec4(Vec2 ab, Vec2 cd): xy(ab), zw(cd) { }
	Vec4(Vec3 abc, float d): xyz(abc), _w(d) { }
	Vec4(float a, Vec3 bcd): _x(a), yzw(bcd) { }
	float &operator()(uint32_t index) {
		Assert(index < 4);
		return ((float *)this)[index];
	}
};

union Mat2 {
	Vec2  rows[2];
	float m[4];
	float m2[2][2];
	Mat2() { }
	float &operator()(uint32_t i, uint32_t j) {
		Assert(i < 2 && j < 2);
		return m2[i][j];
	}
};

union Mat3 {
	Vec3  rows[3];
	float m[9];
	float m2[3][3];
	Mat3() { }
	float &operator()(uint32_t i, uint32_t j) {
		Assert(i < 3 && j < 3);
		return m2[i][j];
	}
};

union Mat4 {
	Vec4  rows[4];
	float m[16];
	float m2[4][4];
	inline Mat4() { }
	inline float &operator()(uint32_t i, uint32_t j) {
		Assert(i < 4 && j < 4);
		return m2[i][j];
	}
};

union Quat {
	float m[4];
	struct {
		float x, y, z, w;
	};
	struct {
		float i, j, k, real;
	};
	struct {
		Vec4 v4;
	};
	Quat() { }
	Quat(Vec4 v): v4(v) { }
	Quat(float b, float c, float d, float a) {
		m[0] = b;
		m[1] = c;
		m[2] = d;
		m[3] = a;
	}
	float &operator()(uint32_t index) {
		Assert(index < 4);
		return ((float *)this)[index];
	}
};

#define ExpandVec2(v) (v).x, (v).y
#define ExpandVec3(v) (v).x, (v).y, (v).z
#define ExpandVec4(v) (v).x, (v).y, (v).z, (v).w

#define DegreesToRadians(deg) ((deg) * (PI / 180))
#define RadiansToDegrees(rad) ((rad) * (180 / PI))

#define Absolute(x)    fabsf(x)
#define Sin(x)         sinf(x)
#define Cos(x)         cosf(x)
#define Tan(x)         tanf(x)
#define ArcSin(x)      asinf(x)
#define ArcCos(x)      acosf(x)
#define ArcTan2(y, x)  atan2f(y, x)
#define SquareRoot(x)  sqrtf(x)
#define Pow(x, y)      powf(x, y)
#define CopySign(x, y) copysignf(x, y)
#define Mod(x, y)      fmodf(x, y)
#define Square(x)      ((x) * (x))

inline Vec2 Arm(float angle) { return Vec2(Cos(angle), Sin(angle)); }
inline Vec2 ArmInverse(float angle) { return Vec2(Sin(angle), Cos(angle)); }

inline Vec2 MinimumVec(Vec2 a, Vec2 b) { return Vec2{ Minimum(a.x, b.x), Minimum(a.y, b.y) }; }
inline Vec2 MaximumVec(Vec2 a, Vec2 b) { return Vec2{ Maximum(a.x, b.x), Maximum(a.y, b.y) }; }
inline Vec3 MinimumVec(Vec3 a, Vec3 b) { return Vec3{ Minimum(a.x, b.x), Minimum(a.y, b.y), Minimum(a.z, b.z) }; }
inline Vec3 MaximumVec(Vec3 a, Vec3 b) { return Vec3{ Maximum(a.x, b.x), Maximum(a.y, b.y), Maximum(a.z, b.z) }; }
inline Vec4 MinimumVec(Vec4 a, Vec4 b) { return Vec4{ Minimum(a.x, b.x), Minimum(a.y, b.y), Minimum(a.z, b.z), Minimum(a.w, b.w) }; }
inline Vec4 MaximumVec(Vec4 a, Vec4 b) { return Vec4{ Maximum(a.x, b.x), Maximum(a.y, b.y), Maximum(a.z, b.z), Maximum(a.w, b.w) }; }

inline bool IsNull(Vec2 a) { return Absolute(a.x) < REAL_EPSILON && Absolute(a.y) < REAL_EPSILON; }
inline bool IsNull(Vec3 a) { return Absolute(a.x) < REAL_EPSILON && Absolute(a.y) < REAL_EPSILON && Absolute(a.z) < REAL_EPSILON; }
inline bool IsNull(Vec4 a) { return Absolute(a.x) < REAL_EPSILON && Absolute(a.y) < REAL_EPSILON && Absolute(a.z) < REAL_EPSILON && Absolute(a.w) < REAL_EPSILON; }

inline Vec2 operator+(Vec2 a, Vec2 b) { return Vec2(a.x + b.x, a.y + b.y); }
inline Vec3 operator+(Vec3 a, Vec3 b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vec4 operator+(Vec4 a, Vec4 b) { return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline Vec2 operator-(Vec2 a, Vec2 b) { return Vec2(a.x - b.x, a.y - b.y); }
inline Vec3 operator-(Vec3 a, Vec3 b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec4 operator-(Vec4 a, Vec4 b) { return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline Vec2 operator*(float s, Vec2 v) { return Vec2(s * v.x, s * v.y); }
inline Vec2 operator*(Vec2 v, float s) { return s * v; }
inline Vec3 operator*(float s, Vec3 v) { return Vec3(s * v.x, s * v.y, s * v.z); }
inline Vec3 operator*(Vec3 v, float s) { return s * v; }
inline Vec4 operator*(float s, Vec4 v) { return Vec4(s * v.x, s * v.y, s * v.z, s * v.w); }
inline Vec4 operator*(Vec4 v, float s) { return s * v; }
inline Vec2 operator/(Vec2 v, float s) {
	s = 1.0f / s;
	return Vec2(v.x * s, v.y * s);
}
inline Vec3 operator/(Vec3 v, float s) {
	s = 1.0f / s;
	return Vec3(v.x * s, v.y * s, v.z * s);
}
inline Vec4 operator/(Vec4 v, float s) { return v * 1.0f / s; }
inline Vec2 operator*(Vec2 l, Vec2 r) { return Vec2(l.x * r.x, l.y * r.y); }
inline Vec3 operator*(Vec3 l, Vec3 r) { return Vec3(l.x * r.x, l.y * r.y, l.z * r.z); }
inline Vec4 operator*(Vec4 l, Vec4 r) { return Vec4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w); }
inline Vec2 operator/(Vec2 l, Vec2 r) { return Vec2(l.x / r.x, l.y / r.y); }
inline Vec3 operator/(Vec3 l, Vec3 r) { return Vec3(l.x / r.x, l.y / r.y, l.z / r.z); }
inline Vec4 operator/(Vec4 l, Vec4 r) { return Vec4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w); }

inline Vec2  operator-(const Vec2 &v) { return Vec2(-v.x, -v.y); }
inline Vec3  operator-(const Vec3 &v) { return Vec3(-v.x, -v.y, -v.z); }
inline Vec4  operator-(const Vec4 &v) { return Vec4(-v.x, -v.y, -v.z, -v.w); }
inline Vec2 &operator+=(Vec2 &a, Vec2 b) {
	a = a + b;
	return a;
}
inline Vec3 &operator+=(Vec3 &a, Vec3 b) {
	a = a + b;
	return a;
}
inline Vec4 &operator+=(Vec4 &a, Vec4 b) {
	a = a + b;
	return a;
}
inline Vec2 &operator-=(Vec2 &a, Vec2 b) {
	a = a - b;
	return a;
}
inline Vec3 &operator-=(Vec3 &a, Vec3 b) {
	a = a - b;
	return a;
}
inline Vec4 &operator-=(Vec4 &a, Vec4 b) {
	a = a - b;
	return a;
}
inline Vec2 &operator*=(Vec2 &t, float s) {
	t = t * s;
	return t;
}
inline Vec3 &operator*=(Vec3 &t, float s) {
	t = t * s;
	return t;
}
inline Vec4 &operator*=(Vec4 &t, float s) {
	t = t * s;
	return t;
}
inline Vec2 &operator/=(Vec2 &t, float s) {
	t = t / s;
	return t;
}
inline Vec3 &operator/=(Vec3 &t, float s) {
	t = t / s;
	return t;
}
inline Vec4 &operator/=(Vec4 &t, float s) {
	t = t / s;
	return t;
}
inline Vec2 &operator*=(Vec2 &t, Vec2 s) {
	t = t * s;
	return t;
}
inline Vec3 &operator*=(Vec3 &t, Vec3 s) {
	t = t * s;
	return t;
}
inline Vec4 &operator*=(Vec4 &t, Vec4 s) {
	t = t * s;
	return t;
}
inline Vec2 &operator/=(Vec2 &t, Vec2 s) {
	t = t / s;
	return t;
}
inline Vec3 &operator/=(Vec3 &t, Vec3 s) {
	t = t / s;
	return t;
}
inline Vec4 &operator/=(Vec4 &t, Vec4 s) {
	t = t / s;
	return t;
}

inline float DotProduct(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }
inline float DotProduct(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float DotProduct(Vec4 a, Vec4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
inline float Determinant(Vec2 a, Vec2 b) { return (a.x * b.y) - (a.y * b.x); }
inline Vec3  CrossProduct(Vec2 a, Vec2 b) {
	Vec3 res;
	res.x = 0;
	res.y = 0;
	res.z = (a.x * b.y) - (a.y * b.x);
	return res;
}
inline Vec3 CrossProduct(Vec3 a, Vec3 b) {
	Vec3 res;
	res.x = (a.y * b.z) - (a.z * b.y);
	res.y = (a.z * b.x) - (a.x * b.z);
	res.z = (a.x * b.y) - (a.y * b.x);
	return res;
}
inline Vec2 TripleProduct(Vec2 a, Vec2 b, Vec2 c) {
	float det = Determinant(a, b);
	Vec2  res;
	res.x = -c.y * det;
	res.y = c.x * det;
	return res;
}
inline Vec3 TripleProduct(Vec3 a, Vec3 b, Vec3 c) { return CrossProduct(CrossProduct(a, b), c); }

inline float LengthSq(Vec2 v) { return DotProduct(v, v); }
inline float LengthSq(Vec3 v) { return DotProduct(v, v); }
inline float LengthSq(Vec4 v) { return DotProduct(v, v); }
inline float Length(Vec2 v) { return SquareRoot(DotProduct(v, v)); }
inline float Length(Vec3 v) { return SquareRoot(DotProduct(v, v)); }
inline float Length(Vec4 v) { return SquareRoot(DotProduct(v, v)); }
inline float Distance(float a, float b) { return b - a; }
inline float Distance(Vec2 a, Vec2 b) { return Length(b - a); }
inline float Distance(Vec3 a, Vec3 b) { return Length(b - a); }
inline float Distance(Vec4 a, Vec4 b) { return Length(b - a); }

inline Vec2 NormalizeChecked(Vec2 v) {
	Vec2  res = {};
	float len = Length(v);
	if (len != 0) res = v / len;
	return res;
}
inline Vec3 NormalizeChecked(Vec3 v) {
	Vec3  res = {};
	float len = Length(v);
	if (len != 0) res = v / len;
	return res;
}
inline Vec4 NormalizeChecked(Vec4 v) {
	Vec4  res = {};
	float len = Length(v);
	if (len != 0) res = v * (1.0f / len);
	return res;
}
inline Vec2 Normalize(Vec2 v) {
	Vec2  res = {};
	float len = Length(v);
	Assert(len != 0);
	res = v / len;
	return res;
}
inline Vec3 Normalize(Vec3 v) {
	Vec3  res = {};
	float len = Length(v);
	Assert(len != 0);
	res = v / len;
	return res;
}
inline Vec4 Normalize(Vec4 v) {
	Vec4  res = {};
	float len = Length(v);
	Assert(len != 0);
	res = v * (1.0f / len);
	return res;
}

inline float AngleBetween(Vec2 a, Vec2 b) {
	float dot = Clamp(-1.0f, 1.0f, DotProduct(a, b));
	return Cos(dot);
}
inline float AngleBetween(Vec3 a, Vec3 b) {
	float dot = Clamp(-1.0f, 1.0f, DotProduct(a, b));
	return Cos(dot);
}
inline float AngleBetweenNormalized(Vec2 a, Vec2 b) {
	a = Normalize(a);
	b = Normalize(b);
	return AngleBetween(a, b);
}
inline float AngleBetweenNormalized(Vec3 a, Vec3 b) {
	a = Normalize(a);
	b = Normalize(b);
	return AngleBetween(a, b);
}
inline float SignedAngleBetween(Vec2 a, Vec2 b) {
	float dot = Clamp(-1.0f, 1.0f, DotProduct(a, b));
	float angle = Cos(dot);
	float cross = a.x * b.y - a.y * b.x;
	if (cross < 0) {
		angle = -angle;
	}
	return angle;
}
inline float SignedAngleBetween(Vec3 a, Vec3 b, Vec3 n) {
	float dot = Clamp(-1.0f, 1.0f, DotProduct(a, b));
	float angle = Cos(dot);
	Vec3  cross = CrossProduct(a, b);
	if (DotProduct(n, cross) < 0) {
		angle = -angle;
	}
	return angle;
}
inline float SignedAngleBetweenNormalized(Vec2 a, Vec2 b) {
	a = Normalize(a);
	b = Normalize(b);
	return SignedAngleBetween(a, b);
}
inline float SignedAngleBetweenNormalized(Vec3 a, Vec3 b, Vec3 n) {
	a = Normalize(a);
	b = Normalize(b);
	n = Normalize(n);
	return SignedAngleBetween(a, b, n);
}

inline Vec2 ClampVec(Vec2 min, Vec2 max, Vec2 v) {
	v.x = Clamp(min.x, max.x, v.x);
	v.y = Clamp(min.y, max.y, v.y);
	return v;
}
inline Vec3 ClampVec(Vec3 min, Vec3 max, Vec3 v) {
	v.x = Clamp(min.x, max.x, v.x);
	v.y = Clamp(min.y, max.y, v.y);
	v.z = Clamp(min.z, max.z, v.z);
	return v;
}
inline Vec4 ClampVec(Vec4 min, Vec4 max, Vec4 v) {
	v.x = Clamp(min.x, max.x, v.x);
	v.y = Clamp(min.y, max.y, v.y);
	v.z = Clamp(min.z, max.z, v.z);
	v.w = Clamp(min.w, max.w, v.w);
	return v;
}

Mat2  IdentityMat2();
float Determinant(const Mat2 &mat);
Mat2  Inverse(const Mat2 &mat);
Mat2  Transpose(const Mat2 &m);
Mat3  IdentityMat3();
float Determinant(const Mat3 &mat);
Mat3  Inverse(const Mat3 &mat);
Mat3  Transpose(const Mat3 &m);
Mat4  IdentityMat4();
float Determinant(const Mat4 &mat);
Mat4  Inverse(const Mat4 &mat);
Mat4  Transpose(const Mat4 &m);

Mat2 operator*(const Mat2 &left, const Mat2 &right);
Vec2 operator*(const Mat2 &mat, Vec2 vec);
Vec2 operator*(Vec2 vec, const Mat2 &mat);
Mat3 operator*(const Mat3 &left, const Mat3 &right);
Vec3 operator*(const Mat3 &mat, Vec3 vec);
Mat4 operator*(const Mat4 &left, const Mat4 &right);
Vec4 operator*(const Mat4 &mat, Vec4 vec);

inline Mat2 &operator*=(Mat2 &t, Mat2 &o) {
	t = t * o;
	return t;
}
inline Mat3 &operator*=(Mat3 &t, Mat3 &o) {
	t = t * o;
	return t;
}
inline Mat4 &operator*=(Mat4 &t, Mat4 &o) {
	t = t * o;
	return t;
}

//
//
//

Mat2 ScalarMat2(float x, float y);
Mat2 ScalarMat2(Vec2 s);
Mat2 RotationMat2(float angle);
Mat3 ScalarMat3(float S_1, float S_2);
Mat3 ScalarMat3(Vec2 s);
Mat3 TranslationMat3(float T_x, float T_y);
Mat3 TranslationMat3(Vec2 t);
Mat3 RotationMat3(float angle);
Mat3 LookAt(Vec2 from, Vec2 to, Vec2 forward);
Mat4 LookAtDirection(Vec3 dir, Vec3 world_up);
Mat4 ScalarMat4(float S_1, float S_2, float S_3);
Mat4 ScalarMat4(Vec3 s);
Mat4 TranslationMat4(float T_x, float T_y, float T_z);
Mat4 TranslationMat4(Vec3 t);
Mat4 RotationX(float angle);
Mat4 RotationY(float angle);
Mat4 RotationZ(float angle);
Mat4 RotationMat4(float x, float y, float z, float angle);
Mat4 RotationMat4(Vec3 axis, float angle);
Mat4 LookAt(Vec3 from, Vec3 to, Vec3 world_up);
Mat4 OrthographicProjection(float l, float r, float t, float b, float n, float f);
Mat4 PerspectiveProjection(float fov, float aspect_ratio, float n, float f);
Vec3 GetRight(const Mat4 &m);
Vec3 GetUp(const Mat4 &m);
Vec3 GetForward(const Mat4 &m);
Mat2 ToMat2(const Mat3 &mat);
Mat3 ToMat3(const Mat2 &mat);
Mat3 ToMat3(const Mat4 &mat);
Mat4 ToMat4(const Mat3 &mat);

inline Quat operator-(Quat &q) { return Quat(-q.v4); }
inline Quat operator-(Quat r1, Quat r2) { return Quat(r1.v4 - r2.v4); }
inline Quat operator+(Quat r1, Quat r2) { return Quat(r1.v4 + r2.v4); }
inline Quat operator*(Quat q, float s) { return Quat(q.v4 * s); }
inline Quat operator*(float s, Quat q) { return Quat(q.v4 * s); }

Quat        IdentityQuat();
float       DotProduct(Quat q1, Quat q2);
float       Length(Quat q);
Quat        Normalize(Quat q);
Quat        Conjugate(Quat q);
Quat        operator*(Quat q1, Quat q2);
Vec3        Rotate(Quat q, Vec3 v);
inline Vec3 operator*(Quat q, Vec3 v) { Rotate(q, v); }
Quat        QuatFromAngleAxis(Vec3 axis, float angle);
Quat        QuatFromAngleAxisNormalized(Vec3 axis, float angle);
void        GetAngleAxis(Quat q, float *angle, Vec3 *axis);
Vec3        GetAxis(Quat q);
float       GetAngle(Quat q);
Quat        QuatFromMat4(const Mat4 &m);
Quat        QuatFromMat4Nomalized(const Mat4 &m);
Mat4        GetMat4(Quat q);
Vec3        GetForward(Quat q);
Vec3        GetRight(Quat q);
Vec3        GetUp(Quat q);
Quat        QuatFromEulerAngles(float pitch, float yaw, float roll);
Quat        QuatFromEulerAngles(Vec3 euler);
Vec3        GetEulerAngles(Quat q);
Quat        QuatBetween(Vec3 from, Vec3 to);
Quat        QuatBetween(Quat a, Quat b);
Quat        QuatLookAt(Vec3 from, Vec3 to, Vec3 world_forward);

Vec3 LinearToSrgb(Vec3 color);
Vec4 LinearToSrgb(Vec4 color);
Vec3 LinearToSrgb(Vec3 color, float gamma);
Vec4 LinearToSrgb(Vec4 color, float gamma);
Vec3 SrgbToLinear(Vec3 color);
Vec4 SrgbToLinear(Vec4 color);
Vec3 SrgbToLinear(Vec3 color, float gamma);
Vec4 SrgbToLinear(Vec4 color, float gamma);

Vec3 HsvToRgb(Vec3 c);
Vec3 RgbToHsv(Vec3 c);
Vec4 HsvToRgb(Vec4 c);
Vec4 RgbToHsv(Vec4 c);

template <typename Type>
Type Lerp(Type from, Type to, float t) {
	return (1 - t) * from + t * to;
}

template <typename Type>
Type BezierQuadratic(Type a, Type b, Type c, float t) {
	float mt = 1 - t;
	float w1 = mt * mt;
	float w2 = 2 * mt * t;
	float w3 = t * t;
	return w1 * a + w2 * b + w3 * c;
}

template <typename Type>
Type BezeriCubic(Type a, Type b, Type c, Type d, float t) {
	float mt = 1.0f - t;
	float w1 = mt * mt * mt;
	float w2 = 3 * mt * mt * t;
	float w3 = 3 * mt * t * t;
	float w4 = t * t * t;
	return w1 * a + w2 * b + w3 * c + w4 * d;
}

template <typename Type>
Type Slerp(Type from, Type to, float angle, float t) {
	float s = Sin(angle);
	float ts = Sin(angle * t);
	float mts = Sin(angle * (1 - t));
	return (mts * from + ts * to) * (1.0f / s);
}

Mat2  Lerp(const Mat2 &from, const Mat2 &to, float t);
Mat3  Lerp(const Mat3 &from, const Mat3 &to, float t);
Mat4  Lerp(const Mat4 &from, const Mat4 &to, float t);
Vec2  Slerp(Vec2 from, Vec2 to, float t);
Vec3  Slerp(Vec3 from, Vec3 to, float t);
Quat  Slerp(Quat from, Quat to, float t);
float Step(float edge, float val);
Vec2  Step(Vec2 edge, Vec2 val);
Vec3  Step(Vec3 edge, Vec3 val);
Vec4  Step(Vec4 edge, Vec4 val);
Quat  Step(Quat edge, Quat val);

template <typename T>
float SmoothStepZeroChecked(T a, T b, T v) {
	float div_distance = Distance(a, b);
	if (div_distance) {
		auto x = Clamp(0.0f, 1.0f, Distance(a, v) / div_distance);
		return x * x * (3 - 2 * x);
	}
	return 1;
}

template <typename T>
float SmoothStep(T a, T b, T v) {
	auto x = Clamp(0.0f, 1.0f, Distance(a, v) / Distance(a, b));
	return x * x * (3 - 2 * x);
}

float InverseSmoothStep(float x);

template <typename T>
T MapRange(T in_a, T in_b, T out_a, T out_b, T v) {
	return (out_b - out_a) / (in_b - in_a) * (v - in_a) + out_a;
}
template <typename T>
T Map01(T in_a, T in_b, T v) {
	return MapRange(in_a, in_b, T(0), T(1), v);
}

Vec2 MoveTowards(Vec2 from, Vec2 to, float factor);
Vec3 MoveTowards(Vec3 from, Vec3 to, float factor);
Vec4 MoveTowards(Vec4 from, Vec4 to, float factor);
Vec2 RotateAround(Vec2 point, Vec2 center, float angle);
Quat RotateTowards(Quat from, Quat to, float max_angle);
Vec2 Reflect(Vec2 d, Vec2 n);

union UintColor {
	struct {
		uint8_t r, g, b, a;
	};
	uint8_t channels[4];

	UintColor() { }
	UintColor(uint8_t x, uint8_t y, uint8_t z, uint8_t w): r(x), g(y), b(z), a(w) { }
};

UintColor Vec4ToUintColor(Vec4 v);
UintColor Vec3ToUintColor(Vec3 v);
Vec4      UintColorToVec4(UintColor c);
Vec3      UintColorToVec3(UintColor c);

struct Rect {
	Vec2 Min;
	Vec2 Max;

	Rect() { }
	Rect(Vec2 min, Vec2 max): Min(min), Max(max) { }
	Rect(float min_x, float min_y, float max_x, float max_y): Min(min_x, min_y), Max(max_x, max_y) { }
};

//
//
//

#pragma once

#define KiloBytes(n) ((n)*1024u)
#define MegaBytes(n) (KiloBytes(n) * 1024u)
#define GigaBytes(n) (MegaBytes(n) * 1024u)

struct Arena {
	uint8_t *Current;
	uint8_t *Memory;
	uint8_t *Max;
};

Arena CreateArena(uint8_t *ptr, size_t size);
void  ResetArena(Arena *arena);

size_t AllocatedMemory(Arena *arena);
size_t UsedMemory(Arena *arena);
size_t LeftMemory(Arena *arena);

void *BeginTemporaryMemory(Arena *arena);
void  EndTemporaryMemory(Arena *arena, void *ptr);

uint8_t *Align(uint8_t *location, size_t alignment);
size_t   Align(size_t location, size_t alignment);

void *PushSize(Arena *arena, size_t size);
void *PushSizeAligned(Arena *arena, size_t size, uint32_t alignment);

#define PushType(arena, type)                           (type *)PushSize(arena, sizeof(type))
#define PushArray(arena, type, count)                   (type *)PushSize(arena, sizeof(type) * count)
#define PushArrayAligned(arena, type, count, alignment) (type *)PushSizeAligned(arena, sizeof(type) * count, alignment)

void *operator new(size_t size, Arena *arena) noexcept;

//
//
//

static constexpr int DEFAULT_CIRCLE_SEGMENTS = 48;
static constexpr int DEFAULT_BEZIER_SEGMENTS = 48;

void  SetDefaultTexture(uint32_t texture);
uint32_t GetDefaultTexture();

void SetClearColor(float r, float g, float b, float a);
void SetClearColor(Vec4 color);
Vec4 GetClearColor();
void  SetThickness(float thickness);
void  SetTexture(uint32_t texture);
uint32_t PushTexture(uint32_t texture);
void  PopTexture(uint32_t texture);

void SetClipRect(Rect clip_rect);
Rect PushClipRect(Rect clip_rect);
void PopClipRect(Rect clip_rect);
void BeginScene2D(const Mat4 &view);
void BeginScene2D(float left, float right, float bottom, float top);
void EndScene2D();

void DrawTriangle(Vec2 va, Vec2 vb, Vec2 vc, Vec2 ta, Vec2 tb, Vec2 tc, Vec4 ca, Vec4 cb, Vec4 cc);
void DrawTriangle(Vec2 a, Vec2 b, Vec2 c, Vec2 ta, Vec2 tb, Vec2 tc, Vec4 col);
void DrawTriangle(Vec2 a, Vec2 b, Vec2 c, Vec4 color);

void DrawQuad(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color);
void DrawQuad(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec4 color);
void DrawQuad(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Rect rect, Vec4 color);

void DrawRect(Vec2 pos, Vec2 dim, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color);
void DrawRect(Vec2 pos, Vec2 dim, Vec4 color);
void DrawRect(Vec2 pos, Vec2 dim, Rect rect, Vec4 color);

void DrawRectRotated(Vec2 pos, Vec2 dim, float angle, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color);
void DrawRectRotated(Vec2 pos, Vec2 dim, float angle, Vec4 color);
void DrawRectRotated(Vec2 pos, Vec2 dim, float angle, Rect rect, Vec4 color);

void DrawRectCentered(Vec2 pos, Vec2 dim, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color);
void DrawRectCentered(Vec2 pos, Vec2 dim, Vec4 color);
void DrawRectCentered(Vec2 pos, Vec2 dim, Rect rect, Vec4 color);

void DrawRectCenteredRotated(Vec2 pos, Vec2 dim, float angle, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color);
void DrawRectCenteredRotated(Vec2 pos, Vec2 dim, float angle, Vec4 color);
void DrawRectCenteredRotated(Vec2 pos, Vec2 dim, float angle, Rect rect, Vec4 color);

void DrawEllipse(Vec2 pos, float radius_a, float radius_b, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);

void DrawCircle(Vec2 pos, float radius, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);

void DrawPie(Vec2 pos, float radius_a, float radius_b, float theta_a, float theta_b, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);
void DrawPie(Vec2 pos, float radius, float theta_a, float theta_b, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);

void DrawPiePart(Vec2 pos, float radius_a_min, float radius_b_min, float radius_a_max, float radius_b_max, float theta_a, float theta_b, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);
void DrawPiePart(Vec2 pos, float radius_min, float radius_max, float theta_a, float theta_b, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);

void DrawLine(Vec2 a, Vec2 b, Vec4 color);

void DrawBezierQuadratic(Vec2 a, Vec2 b, Vec2 c, Vec4 color, int segments = DEFAULT_BEZIER_SEGMENTS);
void DrawBezierCubic(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec4 color, int segments = DEFAULT_BEZIER_SEGMENTS);

void DrawPolygon(const Vec2 *vertices, uint32_t count, Vec4 color);

void DrawTriangleOutline(Vec2 a, Vec2 b, Vec2 c, Vec4 color);

void DrawQuadOutline(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec4 color);

void DrawRectOutline(Vec2 pos, Vec2 dim, Vec4 color);

void DrawRectCenteredOutline(Vec2 pos, Vec2 dim, Vec4 color);

void DrawEllipseOutline(Vec2 position, float radius_a, float radius_b, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);

void DrawCircleOutline(Vec2 position, float radius, Vec4 color, int segments = DEFAULT_CIRCLE_SEGMENTS);

void DrawArcOutline(Vec2 position, float radius_a, float radius_b, float theta_a, float theta_b, Vec4 color, bool closed = true, int segments = DEFAULT_CIRCLE_SEGMENTS);
void DrawArcOutline(Vec2 position, float radius, float theta_a, float theta_b, Vec4 color, bool closed = true, int segments = DEFAULT_CIRCLE_SEGMENTS);

void DrawPolygonOutline(const Vec2 *vertices, uint32_t count, Vec4 color);

uint8_t* LoadPNGFile(struct Platform* p, const char* img_path, unsigned* width, unsigned* height, unsigned* no_of_channels, unsigned* bit_depth);

uint32_t CreateTexture(uint8_t *pixels, uint32_t width, uint32_t height, uint32_t channels);
uint32_t CreateTextureFromFile(Platform *platform, const char *file, uint32_t *w, uint32_t *h, uint32_t *channels);
void DestroyTexture(uint32_t tex);

//
//
//

enum Key : uint32_t {
	Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H, Key_I, Key_J, Key_K, Key_L, Key_M,
	Key_N, Key_O, Key_P, Key_Q, Key_R, Key_S, Key_T, Key_U, Key_V, Key_W, Key_X, Key_Y, Key_Z,
	Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,
	Key_Return, Key_Escape, Key_BackSpace, Key_Tab, Key_Space, Key_Shift, Key_Ctrl,
	Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_F11, Key_F12,
	Key_PrintScreen, Key_Insert, Key_Home, Key_PageUp, Key_PageDown, Key_Delete, Key_End,
	Key_Right, Key_Left, Key_Down, Key_Up,
	Key_Divide, Key_Multiply, Key_Minus, Key_Plus, Key_Period, Key_BackTick,
	Key_Pad0, Key_Pad1, Key_Pad2, Key_Pad3, Key_Pad4,
	Key_Pad5, Key_Pad6, Key_Pad7, Key_Pad8, Key_Pad9,

	_Key_Count
};

enum Button {
	Button_Left,
	Button_Middle,
	Button_Right,

	_Button_Count
};

struct MouseState {
	Vec2     Position;
	Vec2     Delta;
	Vec2	 Scroll;
	bool     IsDown[_Button_Count];
	bool	 EndedDown[_Key_Count];
	bool	 EndedUp[_Key_Count];
	uint32_t Transitions[_Button_Count];
	uint32_t DoubleClick[_Button_Count];
};

struct KeyboardState {
	bool     IsDown[_Key_Count];
	bool	 EndedDown[_Key_Count];
	bool	 EndedUp[_Key_Count];
	uint32_t Repeat[_Key_Count];
	uint32_t Transitions[_Key_Count];
};

struct Timestep {
	float FixedDeltaTime;
	float Time;
	float DeltaTime;
	float RealTime;
	float RealDeltaTime;
	float SimulationSpeedFactor;
};

typedef void *(*PlatformAlloc)(size_t size);
typedef void *(*PlatformRealloc)(void *ptr, size_t size);
typedef void (*PlatformFree)(void *ptr);
typedef void (*PlatformOnWindowResize)(struct Platform *, uint32_t w, uint32_t h);
typedef bool (*PlatformOnLoad)(struct Platform *);
typedef void (*PlatformOnQuit)(struct Platform *);
typedef void (*PlatformFixedUpdate)(struct Platform *, float dt);
typedef void (*PlatformUpdateAndRender)(struct Platform *, float dt, float alpha);
typedef void (*PlatformLog)(const char *fmt, ...);
typedef void (*PlatformLogError)(const char *fmt, ...);
typedef void (*PlatformFatalError)(const char *messge);

struct Platform {
	Arena Scratch;

	PlatformAlloc Alloc;
	PlatformRealloc Realloc;
	PlatformFree Free;
	void *UserPointer;

	KeyboardState Keyboard;
	MouseState Mouse;

	PlatformLog Log;
	PlatformLogError LogError;
	PlatformFatalError FatalError;
	
	float RenderTargetWidth;
	float RenderTargetHeight;
	float AspectRatio;

	Timestep Time;
	PlatformOnLoad OnLoad;
	PlatformOnQuit OnQuit;
	PlatformFixedUpdate FixedUpdate;
	PlatformUpdateAndRender UpdateAndRender;
	PlatformOnWindowResize OnWindowResize;

	const char *Name;
	bool Running;
};

inline void PlatformQuit(Platform *p) { p->Running = false; }

inline bool KeyIsDown(Platform *p, Key k) { return p->Keyboard.IsDown[k]; }
inline bool KeyIsPressed(Platform *p, Key k) { return p->Keyboard.EndedDown[k]; }
inline bool KeyIsReleased(Platform *p, Key k) { return !p->Keyboard.EndedUp[k]; }
inline bool ButtonIsDown(Platform *p, Button b) { return p->Mouse.IsDown[b]; }
inline bool ButtonIsPressed(Platform *p, Button b) { return p->Mouse.EndedDown[b]; }
inline bool ButtonIsReleased(Platform *p, Button b) { return p->Mouse.EndedUp[b]; }

#if !defined(CppGameCall)
#define CppGameCall extern "C"
#endif

CppGameCall void CppGameInitialize(Platform * platform, int argc, char **argv);
