#include "CppGame.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

//
// Begin Section
//

/*
* Math
* Arena
* Renderer
* Platform: OpenGL
* Platform: OpenGL Renderer
* Platform: Windows
* Platform: Linux?? (Not Imeplemented)
* BMP Loader
* PNG Loader
*/

//
// End Section
//

//
// Begin Math
//

Mat2 IdentityMat2() {
	Mat2 m;
	m.rows[0] = Vec2(1.0f, 0.0f);
	m.rows[1] = Vec2(0.0f, 1.0f);
	return m;
}

float Determinant(const Mat2 &mat) {
	return mat.m2[0][0] * mat.m2[1][1] - mat.m2[0][1] * mat.m2[1][0];
}

Mat2 Inverse(const Mat2 &mat) {
	float det = mat.m2[0][0] * mat.m2[1][1] - mat.m2[0][1] * mat.m2[1][0];
	det /= det;
	Mat2 res;
	res.m2[0][0] = mat.m2[1][1];
	res.m2[0][1] = -mat.m2[0][1];
	res.m2[1][0] = -mat.m2[1][0];
	res.m2[1][1] = mat.m2[0][0];
	res.m[0] *= det;
	res.m[1] *= det;
	res.m[2] *= det;
	res.m[3] *= det;
	return res;
}

Mat2 Transpose(const Mat2 &m) {
	Mat2 t;
	t.m2[0][0] = m.m2[0][0];
	t.m2[0][1] = m.m2[1][0];
	t.m2[1][0] = m.m2[0][1];
	t.m2[1][1] = m.m2[1][1];
	return t;
}

Mat3 IdentityMat3() {
	Mat3 m;
	m.rows[0] = Vec3(1.0f, 0.0f, 0.0f);
	m.rows[1] = Vec3(0.0f, 1.0f, 0.0f);
	m.rows[2] = Vec3(0.0f, 0.0f, 1.0f);
	return m;
}

float Determinant(const Mat3 &mat) {
	float det = mat.m2[0][0] * (mat.m2[1][1] * mat.m2[2][2] - mat.m2[2][1] * mat.m2[1][2]) +
		mat.m2[0][1] * (mat.m2[1][2] * mat.m2[2][0] - mat.m2[1][0] * mat.m2[2][2]) +
		mat.m2[0][2] * (mat.m2[1][0] * mat.m2[2][1] - mat.m2[2][0] * mat.m2[1][1]);
	return det;
}

Mat3 Inverse(const Mat3 &mat) {
	Mat3 result;
	result.m2[0][0] = mat.m2[1][1] * mat.m2[2][2] - mat.m2[2][1] * mat.m2[1][2];
	result.m2[0][1] = mat.m2[0][2] * mat.m2[2][1] - mat.m2[0][1] * mat.m2[2][2];
	result.m2[0][2] = mat.m2[0][1] * mat.m2[1][2] - mat.m2[0][2] * mat.m2[1][1];
	result.m2[1][0] = mat.m2[1][2] * mat.m2[2][0] - mat.m2[1][0] * mat.m2[2][2];
	result.m2[1][1] = mat.m2[0][0] * mat.m2[2][2] - mat.m2[0][2] * mat.m2[2][0];
	result.m2[1][2] = mat.m2[1][0] * mat.m2[0][2] - mat.m2[0][0] * mat.m2[1][2];
	result.m2[2][0] = mat.m2[1][0] * mat.m2[2][1] - mat.m2[2][0] * mat.m2[1][1];
	result.m2[2][1] = mat.m2[2][0] * mat.m2[0][1] - mat.m2[0][0] * mat.m2[2][1];
	result.m2[2][2] = mat.m2[0][0] * mat.m2[1][1] - mat.m2[1][0] * mat.m2[0][1];

	float det = mat.m2[0][0] * result.m2[0][0] + mat.m2[0][1] * result.m2[1][0] + mat.m2[0][2] * result.m2[2][0];
	det /= det;
	for (int i = 0; i < 3; i++)
		result.rows[i] = result.rows[i] * det;
	return result;
}

Mat3 Transpose(const Mat3 &m) {
	Mat3 res;
	res.rows[0] = Vec3(m.m2[0][0], m.m2[1][0], m.m2[2][0]);
	res.rows[1] = Vec3(m.m2[0][1], m.m2[1][1], m.m2[2][1]);
	res.rows[2] = Vec3(m.m2[0][2], m.m2[1][2], m.m2[2][2]);
	return res;
}

Mat4 IdentityMat4() {
	Mat4 m;
	m.rows[0] = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
	m.rows[1] = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
	m.rows[2] = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

float Determinant(const Mat4 &mat) {
	float m0 = mat.m[5] * mat.m[10] * mat.m[15] -
		mat.m[5] * mat.m[11] * mat.m[14] -
		mat.m[9] * mat.m[6] * mat.m[15] +
		mat.m[9] * mat.m[7] * mat.m[14] +
		mat.m[13] * mat.m[6] * mat.m[11] -
		mat.m[13] * mat.m[7] * mat.m[10];

	float m4 = -mat.m[4] * mat.m[10] * mat.m[15] +
		mat.m[4] * mat.m[11] * mat.m[14] +
		mat.m[8] * mat.m[6] * mat.m[15] -
		mat.m[8] * mat.m[7] * mat.m[14] -
		mat.m[12] * mat.m[6] * mat.m[11] +
		mat.m[12] * mat.m[7] * mat.m[10];

	float m8 = mat.m[4] * mat.m[9] * mat.m[15] -
		mat.m[4] * mat.m[11] * mat.m[13] -
		mat.m[8] * mat.m[5] * mat.m[15] +
		mat.m[8] * mat.m[7] * mat.m[13] +
		mat.m[12] * mat.m[5] * mat.m[11] -
		mat.m[12] * mat.m[7] * mat.m[9];

	float m12 = -mat.m[4] * mat.m[9] * mat.m[14] +
		mat.m[4] * mat.m[10] * mat.m[13] +
		mat.m[8] * mat.m[5] * mat.m[14] -
		mat.m[8] * mat.m[6] * mat.m[13] -
		mat.m[12] * mat.m[5] * mat.m[10] +
		mat.m[12] * mat.m[6] * mat.m[9];

	float det = mat.m[0] * m0 + mat.m[1] * m4 + mat.m[2] * m8 + mat.m[3] * m12;
	return det;
}

Mat4 Inverse(const Mat4 &mat) {
	Mat4 result;

	result.m[0] = mat.m[5] * mat.m[10] * mat.m[15] -
		mat.m[5] * mat.m[11] * mat.m[14] -
		mat.m[9] * mat.m[6] * mat.m[15] +
		mat.m[9] * mat.m[7] * mat.m[14] +
		mat.m[13] * mat.m[6] * mat.m[11] -
		mat.m[13] * mat.m[7] * mat.m[10];

	result.m[4] = -mat.m[4] * mat.m[10] * mat.m[15] +
		mat.m[4] * mat.m[11] * mat.m[14] +
		mat.m[8] * mat.m[6] * mat.m[15] -
		mat.m[8] * mat.m[7] * mat.m[14] -
		mat.m[12] * mat.m[6] * mat.m[11] +
		mat.m[12] * mat.m[7] * mat.m[10];

	result.m[8] = mat.m[4] * mat.m[9] * mat.m[15] -
		mat.m[4] * mat.m[11] * mat.m[13] -
		mat.m[8] * mat.m[5] * mat.m[15] +
		mat.m[8] * mat.m[7] * mat.m[13] +
		mat.m[12] * mat.m[5] * mat.m[11] -
		mat.m[12] * mat.m[7] * mat.m[9];

	result.m[12] = -mat.m[4] * mat.m[9] * mat.m[14] +
		mat.m[4] * mat.m[10] * mat.m[13] +
		mat.m[8] * mat.m[5] * mat.m[14] -
		mat.m[8] * mat.m[6] * mat.m[13] -
		mat.m[12] * mat.m[5] * mat.m[10] +
		mat.m[12] * mat.m[6] * mat.m[9];

	result.m[1] = -mat.m[1] * mat.m[10] * mat.m[15] +
		mat.m[1] * mat.m[11] * mat.m[14] +
		mat.m[9] * mat.m[2] * mat.m[15] -
		mat.m[9] * mat.m[3] * mat.m[14] -
		mat.m[13] * mat.m[2] * mat.m[11] +
		mat.m[13] * mat.m[3] * mat.m[10];

	result.m[5] = mat.m[0] * mat.m[10] * mat.m[15] -
		mat.m[0] * mat.m[11] * mat.m[14] -
		mat.m[8] * mat.m[2] * mat.m[15] +
		mat.m[8] * mat.m[3] * mat.m[14] +
		mat.m[12] * mat.m[2] * mat.m[11] -
		mat.m[12] * mat.m[3] * mat.m[10];

	result.m[9] = -mat.m[0] * mat.m[9] * mat.m[15] +
		mat.m[0] * mat.m[11] * mat.m[13] +
		mat.m[8] * mat.m[1] * mat.m[15] -
		mat.m[8] * mat.m[3] * mat.m[13] -
		mat.m[12] * mat.m[1] * mat.m[11] +
		mat.m[12] * mat.m[3] * mat.m[9];

	result.m[13] = mat.m[0] * mat.m[9] * mat.m[14] -
		mat.m[0] * mat.m[10] * mat.m[13] -
		mat.m[8] * mat.m[1] * mat.m[14] +
		mat.m[8] * mat.m[2] * mat.m[13] +
		mat.m[12] * mat.m[1] * mat.m[10] -
		mat.m[12] * mat.m[2] * mat.m[9];

	result.m[2] = mat.m[1] * mat.m[6] * mat.m[15] -
		mat.m[1] * mat.m[7] * mat.m[14] -
		mat.m[5] * mat.m[2] * mat.m[15] +
		mat.m[5] * mat.m[3] * mat.m[14] +
		mat.m[13] * mat.m[2] * mat.m[7] -
		mat.m[13] * mat.m[3] * mat.m[6];

	result.m[6] = -mat.m[0] * mat.m[6] * mat.m[15] +
		mat.m[0] * mat.m[7] * mat.m[14] +
		mat.m[4] * mat.m[2] * mat.m[15] -
		mat.m[4] * mat.m[3] * mat.m[14] -
		mat.m[12] * mat.m[2] * mat.m[7] +
		mat.m[12] * mat.m[3] * mat.m[6];

	result.m[10] = mat.m[0] * mat.m[5] * mat.m[15] -
		mat.m[0] * mat.m[7] * mat.m[13] -
		mat.m[4] * mat.m[1] * mat.m[15] +
		mat.m[4] * mat.m[3] * mat.m[13] +
		mat.m[12] * mat.m[1] * mat.m[7] -
		mat.m[12] * mat.m[3] * mat.m[5];

	result.m[14] = -mat.m[0] * mat.m[5] * mat.m[14] +
		mat.m[0] * mat.m[6] * mat.m[13] +
		mat.m[4] * mat.m[1] * mat.m[14] -
		mat.m[4] * mat.m[2] * mat.m[13] -
		mat.m[12] * mat.m[1] * mat.m[6] +
		mat.m[12] * mat.m[2] * mat.m[5];

	result.m[3] = -mat.m[1] * mat.m[6] * mat.m[11] +
		mat.m[1] * mat.m[7] * mat.m[10] +
		mat.m[5] * mat.m[2] * mat.m[11] -
		mat.m[5] * mat.m[3] * mat.m[10] -
		mat.m[9] * mat.m[2] * mat.m[7] +
		mat.m[9] * mat.m[3] * mat.m[6];

	result.m[7] = mat.m[0] * mat.m[6] * mat.m[11] -
		mat.m[0] * mat.m[7] * mat.m[10] -
		mat.m[4] * mat.m[2] * mat.m[11] +
		mat.m[4] * mat.m[3] * mat.m[10] +
		mat.m[8] * mat.m[2] * mat.m[7] -
		mat.m[8] * mat.m[3] * mat.m[6];

	result.m[11] = -mat.m[0] * mat.m[5] * mat.m[11] +
		mat.m[0] * mat.m[7] * mat.m[9] +
		mat.m[4] * mat.m[1] * mat.m[11] -
		mat.m[4] * mat.m[3] * mat.m[9] -
		mat.m[8] * mat.m[1] * mat.m[7] +
		mat.m[8] * mat.m[3] * mat.m[5];

	result.m[15] = mat.m[0] * mat.m[5] * mat.m[10] -
		mat.m[0] * mat.m[6] * mat.m[9] -
		mat.m[4] * mat.m[1] * mat.m[10] +
		mat.m[4] * mat.m[2] * mat.m[9] +
		mat.m[8] * mat.m[1] * mat.m[6] -
		mat.m[8] * mat.m[2] * mat.m[5];

	float det = mat.m[0] * result.m[0] + mat.m[1] * result.m[4] + mat.m[2] * result.m[8] + mat.m[3] * result.m[12];
	det = 1.0f / det;
	for (int i = 0; i < 4; i++)
		result.rows[i] = result.rows[i] * det;
	return result;
}

Mat4 Transpose(const Mat4 &m) {
	Mat4 res;
	res.rows[0] = Vec4(m.m2[0][0], m.m2[1][0], m.m2[2][0], m.m2[3][0]);
	res.rows[1] = Vec4(m.m2[0][1], m.m2[1][1], m.m2[2][1], m.m2[3][1]);
	res.rows[2] = Vec4(m.m2[0][2], m.m2[1][2], m.m2[2][2], m.m2[3][2]);
	res.rows[3] = Vec4(m.m2[0][3], m.m2[1][3], m.m2[2][3], m.m2[3][3]);
	return res;
}

//
//
//

Mat2 operator*(const Mat2 &left, const Mat2 &right) {
	Mat2 res;
	Mat2 tras = Transpose(right);

	res.m2[0][0] = DotProduct(left.rows[0], tras.rows[0]);
	res.m2[0][1] = DotProduct(left.rows[0], tras.rows[1]);
	res.m2[1][0] = DotProduct(left.rows[1], tras.rows[0]);
	res.m2[1][1] = DotProduct(left.rows[1], tras.rows[1]);

	return res;
}

Vec2 operator*(const Mat2 &mat, Vec2 vec) {
	Vec2 res;
	res.m[0] = DotProduct(vec, mat.rows[0]);
	res.m[1] = DotProduct(vec, mat.rows[1]);
	return res;
}

Vec2 operator*(Vec2 vec, const Mat2 &mat) {
	Vec2 res;
	res.m[0] = DotProduct(vec, Vec2(mat.m2[0][0], mat.m2[1][0]));
	res.m[1] = DotProduct(vec, Vec2(mat.m2[0][1], mat.m2[1][1]));
	return res;
}

Mat3 operator*(const Mat3 &left, const Mat3 &right) {
	Mat3 res;
	Mat3 tras = Transpose(right);

	res.m2[0][0] = DotProduct(left.rows[0], tras.rows[0]);
	res.m2[0][1] = DotProduct(left.rows[0], tras.rows[1]);
	res.m2[0][2] = DotProduct(left.rows[0], tras.rows[2]);

	res.m2[1][0] = DotProduct(left.rows[1], tras.rows[0]);
	res.m2[1][1] = DotProduct(left.rows[1], tras.rows[1]);
	res.m2[1][2] = DotProduct(left.rows[1], tras.rows[2]);

	res.m2[2][0] = DotProduct(left.rows[2], tras.rows[0]);
	res.m2[2][1] = DotProduct(left.rows[2], tras.rows[1]);
	res.m2[2][2] = DotProduct(left.rows[2], tras.rows[2]);

	return res;
}

Vec3 operator*(const Mat3 &mat, Vec3 vec) {
	Vec3 res;
	res.m[0] = DotProduct(vec, mat.rows[0]);
	res.m[1] = DotProduct(vec, mat.rows[1]);
	res.m[2] = DotProduct(vec, mat.rows[2]);
	return res;
}

Mat4 operator*(const Mat4 &left, const Mat4 &right) {
	Mat4 res;
	Mat4 tras = Transpose(right);

	res.m2[0][0] = DotProduct(left.rows[0], tras.rows[0]);
	res.m2[0][1] = DotProduct(left.rows[0], tras.rows[1]);
	res.m2[0][2] = DotProduct(left.rows[0], tras.rows[2]);
	res.m2[0][3] = DotProduct(left.rows[0], tras.rows[3]);

	res.m2[1][0] = DotProduct(left.rows[1], tras.rows[0]);
	res.m2[1][1] = DotProduct(left.rows[1], tras.rows[1]);
	res.m2[1][2] = DotProduct(left.rows[1], tras.rows[2]);
	res.m2[1][3] = DotProduct(left.rows[1], tras.rows[3]);

	res.m2[2][0] = DotProduct(left.rows[2], tras.rows[0]);
	res.m2[2][1] = DotProduct(left.rows[2], tras.rows[1]);
	res.m2[2][2] = DotProduct(left.rows[2], tras.rows[2]);
	res.m2[2][3] = DotProduct(left.rows[2], tras.rows[3]);

	res.m2[3][0] = DotProduct(left.rows[3], tras.rows[0]);
	res.m2[3][1] = DotProduct(left.rows[3], tras.rows[1]);
	res.m2[3][2] = DotProduct(left.rows[3], tras.rows[2]);
	res.m2[3][3] = DotProduct(left.rows[3], tras.rows[3]);

	return res;
}

Vec4 operator*(const Mat4 &mat, Vec4 vec) {
	Vec4 res;
	res.m[0] = DotProduct(vec, mat.rows[0]);
	res.m[1] = DotProduct(vec, mat.rows[1]);
	res.m[2] = DotProduct(vec, mat.rows[2]);
	res.m[3] = DotProduct(vec, mat.rows[3]);
	return res;
}

//
//
//

Mat2 ScalarMat2(float x, float y) {
	Mat2 m;
	m.rows[0] = Vec2(x, 0.0f);
	m.rows[1] = Vec2(0.0f, y);
	return m;
}

Mat2 ScalarMat2(Vec2 s) {
	Mat2 m;
	m.rows[0] = Vec2(s.x, 0.0f);
	m.rows[1] = Vec2(0.0f, s.y);
	return m;
}

Mat2 RotationMat2(float angle) {
	float c = Cos(angle);
	float s = Sin(angle);

	Mat2 mat;
	mat.rows[0] = Vec2(c, -s);
	mat.rows[1] = Vec2(s, c);
	return mat;
}

Mat3 ScalarMat3(float S_1, float S_2) {
	Mat3 m;
	m.rows[0] = Vec3(S_1, 0.0f, 0.0f);
	m.rows[1] = Vec3(0.0f, S_2, 0.0f);
	m.rows[2] = Vec3(0.0f, 0.0f, 1.0f);
	return m;
}

Mat3 ScalarMat3(Vec2 s) {
	return ScalarMat3(s.x, s.y);
}

Mat3 TranslationMat3(float T_x, float T_y) {
	Mat3 m;
	m.rows[0] = Vec3(1.0f, 0.0f, T_x);
	m.rows[1] = Vec3(0.0f, 1.0f, T_y);
	m.rows[2] = Vec3(0.0f, 0.0f, 1.0f);
	return m;
}

Mat3 TranslationMat3(Vec2 t) {
	return TranslationMat3(t.x, t.y);
}

Mat3 RotationMat3(float angle) {
	Mat3  m;
	float c = Cos(angle);
	float s = Sin(angle);
	m.rows[0] = Vec3(c, -s, 0.0f);
	m.rows[1] = Vec3(s, c, 0.0f);
	m.rows[2] = Vec3(0.0f, 0.0f, 1.0f);
	return m;
}

Mat3 LookAt(Vec2 from, Vec2 to, Vec2 forward) {
	Vec2  dir = Normalize(to - from);
	float cos_theta = DotProduct(dir, forward);
	float sin_theta = SquareRoot(1.0f - cos_theta * cos_theta);

	Mat3 m;
	m.rows[0] = Vec3(cos_theta, -sin_theta, from.x);
	m.rows[1] = Vec3(sin_theta, cos_theta, from.y);
	m.rows[2] = Vec3(0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 ScalarMat4(float S_1, float S_2, float S_3) {
	Mat4 m;
	m.rows[0] = Vec4(S_1, 0.0f, 0.0f, 0.0f);
	m.rows[1] = Vec4(0.0f, S_2, 0.0f, 0.0f);
	m.rows[2] = Vec4(0.0f, 0.0f, S_3, 0.0f);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 ScalarMat4(Vec3 s) {
	return ScalarMat4(s.x, s.y, s.z);
}

Mat4 TranslationMat4(float T_x, float T_y, float T_z) {
	Mat4 m;
	m.rows[0] = Vec4(1.0f, 0.0f, 0.0f, T_x);
	m.rows[1] = Vec4(0.0f, 1.0f, 0.0f, T_y);
	m.rows[2] = Vec4(0.0f, 0.0f, 1.0f, T_z);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 TranslationMat4(Vec3 t) {
	return TranslationMat4(t.x, t.y, t.z);
}

Mat4 RotationX(float angle) {
	Mat4 m;
	m.rows[0] = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
	m.rows[1] = Vec4(0.0f, Cos(angle), -Sin(angle), 0.0f);
	m.rows[2] = Vec4(0.0f, Sin(angle), Cos(angle), 0.0f);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 RotationY(float angle) {
	Mat4 m;
	m.rows[0] = Vec4(Cos(angle), 0.0f, -Sin(angle), 0.0f);
	m.rows[1] = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
	m.rows[2] = Vec4(Sin(angle), 0.0f, Cos(angle), 0.0f);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 RotationZ(float angle) {
	Mat4 m;
	m.rows[0] = Vec4(Cos(angle), -Sin(angle), 0.0f, 0.0f);
	m.rows[1] = Vec4(Sin(angle), Cos(angle), 0.0f, 0.0f);
	m.rows[2] = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 RotationMat4(float x, float y, float z, float angle) {
	float c = Cos(angle);
	float s = Sin(angle);

	float x2 = x * x;
	float xy = x * y;
	float zx = x * z;
	float y2 = y * y;
	float yz = y * z;
	float z2 = z * z;

	Mat4 m;
	m.rows[0] = Vec4(c + x2 * (1 - c), xy * (1 - c) - z * s, zx * (1 - c) + y * s, 0.0f);
	m.rows[1] = Vec4(xy * (1 - c) + z * s, c + y2 * (1 - c), yz * (1 - c) - x * s, 0.0f);
	m.rows[2] = Vec4(zx * (1 - c) - y * s, yz * (1 - c) + x * s, c + z2 * (1 - c), 0.0f);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 RotationMat4(Vec3 axis, float angle) {
	return RotationMat4(axis.x, axis.y, axis.z, angle);
}

Mat4 LookAt(Vec3 from, Vec3 to, Vec3 world_up) {
	Vec3 forward = Normalize(from - to);
	Vec3 right = Normalize(CrossProduct(world_up, forward));
	Vec3 up = CrossProduct(right, forward);

	Mat4 lookat;
	lookat.rows[0] = Vec4(right.x, up.x, forward.x, -from.x);
	lookat.rows[1] = Vec4(right.y, up.y, forward.y, -from.y);
	lookat.rows[2] = Vec4(right.z, up.z, forward.z, -from.z);
	lookat.rows[3] = Vec4(0, 0, 0, 1);

	return lookat;
}

Mat4 LookAtDirection(Vec3 dir, Vec3 world_up) {
	Assert(!IsNull(dir));

	Vec3 forward = dir;
	Vec3 right = Normalize(CrossProduct(world_up, forward));
	Vec3 up = CrossProduct(right, forward);

	Mat4 lookat;
	lookat.rows[0] = Vec4(right.x, up.x, forward.x, 0);
	lookat.rows[1] = Vec4(right.y, up.y, forward.y, 0);
	lookat.rows[2] = Vec4(right.z, up.z, forward.z, 0);
	lookat.rows[3] = Vec4(0, 0, 0, 1);

	return lookat;
}

Mat4 OrthographicProjection(float l, float r, float t, float b, float n, float f) {
	float iwidth = 1 / (r - l);
	float iheight = 1 / (t - b);
	float range = 1 / (f - n);

	Mat4 m;
	m.rows[0] = Vec4(2 * iwidth, 0.0f, 0.0f, -(l + r) * iwidth);
	m.rows[1] = Vec4(0.0f, 2 * iheight, 0.0f, -(t + b) * iheight);
	m.rows[2] = Vec4(0.0f, 0.0f, -2 * range, -(f + n) * range);
	m.rows[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}

Mat4 PerspectiveProjection(float fov, float aspect_ratio, float n, float f) {
	float height = 1.0f / Tan(fov * 0.5f);
	float width = height / aspect_ratio;
	float range = 1 / (f - n);

	Mat4 m;
	m.rows[0] = Vec4(width, 0.0f, 0.0f, 0.0f);
	m.rows[1] = Vec4(0.0f, height, 0.0f, 0.0f);
	m.rows[2] = Vec4(0.0f, 0.0f, -(f + n) * range, -2.0f * f * n * range);
	m.rows[3] = Vec4(0.0f, 0.0f, -1.0f, 0.0f);
	return m;
}

Vec3 GetRight(const Mat4 &m) {
	Vec3 v;
	v.x = m.m2[0][0];
	v.y = m.m2[1][0];
	v.z = m.m2[2][0];
	return v;
}

Vec3 GetUp(const Mat4 &m) {
	Vec3 v;
	v.x = m.m2[0][2];
	v.y = m.m2[1][2];
	v.z = m.m2[2][2];
	return v;
}

Vec3 GetForward(const Mat4 &m) {
	Vec3 v;
	v.x = m.m2[0][1];
	v.y = m.m2[1][1];
	v.z = m.m2[2][1];
	return v;
}

Mat2 ToMat2(const Mat3 &mat) {
	Mat2 result;
	result.rows[0] = mat.rows[0].xy;
	result.rows[1] = mat.rows[1].xy;
	return result;
}

Mat3 ToMat3(const Mat2 &mat) {
	Mat3 result;
	result.rows[0] = Vec3(mat.rows[0], 0);
	result.rows[1] = Vec3(mat.rows[1], 0);
	result.rows[2] = Vec3(0, 0, 1);
	return result;
}

Mat3 ToMat3(const Mat4 &mat) {
	Mat3 result;
	result.rows[0] = mat.rows[0].xyz;
	result.rows[1] = mat.rows[1].xyz;
	result.rows[2] = mat.rows[2].xyz;
	return result;
}

Mat4 ToMat4(const Mat3 &mat) {
	Mat4 result;
	result.rows[0] = Vec4(mat.rows[0], 0);
	result.rows[1] = Vec4(mat.rows[1], 0);
	result.rows[2] = Vec4(mat.rows[2], 0);
	result.rows[3] = Vec4(0, 0, 0, 1);
	return result;
}

//
//
//

Quat IdentityQuat() {
	return Quat(0, 0, 0, 1);
}

float DotProduct(Quat q1, Quat q2) {
	return q1.real * q2.real + q1.i * q2.i + q1.j * q2.j + q1.k * q2.k;
}

float Length(Quat q) {
	return SquareRoot(DotProduct(q, q));
}

Quat Normalize(Quat q) {
	float len = Length(q);
	Assert(len != 0);
	return q * (1.0f / len);
}

Quat Conjugate(Quat q) {
	return Quat(-q.i, -q.j, -q.k, q.real);
}

Quat operator*(Quat q1, Quat q2) {
	float a = q1.w;
	float b = q1.x;
	float c = q1.y;
	float d = q1.z;

	float e = q2.w;
	float f = q2.x;
	float g = q2.y;
	float h = q2.z;

	Quat res;
	res.w = a * e - b * f - c * g - d * h;
	res.x = a * f + b * e + c * h - d * g;
	res.y = a * g - b * h + c * e + d * f;
	res.z = a * h + b * g - c * f + d * e;
	return res;
}

Vec3 Rotate(Quat q, Vec3 v) {
	Quat p = Quat(v.x, v.y, v.z, 0);
	Quat qc = Conjugate(q);
	Quat res = (q * p * qc);
	return Vec3(res.x, res.y, res.z);
}

Quat QuatFromAngleAxis(Vec3 axis, float angle) {
	float r = Cos(angle * 0.5f);
	float s = Sin(angle * 0.5f);
	float i = s * axis.x;
	float j = s * axis.y;
	float k = s * axis.z;
	return Quat(i, j, k, r);
}

Quat QuatFromAngleAxisNormalized(Vec3 axis, float angle) {
	return QuatFromAngleAxis(Normalize(axis), angle);
}

void GetAngleAxis(Quat q, float *angle, Vec3 *axis) {
	float len = SquareRoot(q.i * q.i + q.j * q.j + q.k * q.k);
	if (len) {
		*angle = 2.0f * ArcTan2(len, q.real);
		len = 1.0f / len;
		axis->x = q.i * len;
		axis->y = q.j * len;
		axis->z = q.k * len;
	} else {
		// degenerate case, unit quaternion
		*angle = 0;
		*axis = Vec3(0, 0, 1);
	}
}

Vec3 GetAxis(Quat q) {
	Vec3  axis;
	float angle;
	GetAngleAxis(q, &angle, &axis);
	return axis;
}

float GetAngle(Quat q) {
	Vec3  axis;
	float angle;
	GetAngleAxis(q, &angle, &axis);
	return angle;
}

Quat QuatFromMat4(const Mat4 &m) {
	Quat  q;
	float trace = m.m2[0][0] + m.m2[1][1] + m.m2[2][2];
	if (trace > 0.0f) {
		float s = 0.5f / SquareRoot(trace + 1.0f);
		q.w = 0.25f / s;
		q.x = (m.m2[2][1] - m.m2[1][2]) * s;
		q.y = (m.m2[0][2] - m.m2[2][0]) * s;
		q.z = (m.m2[1][0] - m.m2[0][1]) * s;
	} else {
		if (m.m2[0][0] > m.m2[1][1] && m.m2[0][0] > m.m2[2][2]) {
			float s = 2.0f * SquareRoot(1.0f + m.m2[0][0] - m.m2[1][1] - m.m2[2][2]);
			q.w = (m.m2[2][1] - m.m2[1][2]) / s;
			q.x = 0.25f * s;
			q.y = (m.m2[0][1] + m.m2[1][0]) / s;
			q.z = (m.m2[0][2] + m.m2[2][0]) / s;
		} else if (m.m2[1][1] > m.m2[2][2]) {
			float s = 2.0f * SquareRoot(1.0f + m.m2[1][1] - m.m2[0][0] - m.m2[2][2]);
			q.w = (m.m2[0][2] - m.m2[2][0]) / s;
			q.x = (m.m2[0][1] + m.m2[1][0]) / s;
			q.y = 0.25f * s;
			q.z = (m.m2[1][2] + m.m2[2][1]) / s;
		} else {
			float s = 2.0f * SquareRoot(1.0f + m.m2[2][2] - m.m2[0][0] - m.m2[1][1]);
			q.w = (m.m2[1][0] - m.m2[0][1]) / s;
			q.x = (m.m2[0][2] + m.m2[2][0]) / s;
			q.y = (m.m2[1][2] + m.m2[2][1]) / s;
			q.z = 0.25f * s;
		}
	}
	return Normalize(q);
}

Quat QuatFromMat4Nomalized(const Mat4 &m) {
	Mat4 nm;
	nm.rows[0] = Vec4(Normalize(m.rows[0].xyz), m.rows[0].w);
	nm.rows[1] = Vec4(Normalize(m.rows[1].xyz), m.rows[1].w);
	nm.rows[2] = Vec4(Normalize(m.rows[2].xyz), m.rows[2].w);
	nm.rows[3] = Vec4(Normalize(m.rows[3].xyz), m.rows[3].w);
	return QuatFromMat4(nm);
}

Mat4 GetMat4(Quat q) {
	float i = q.i;
	float j = q.j;
	float k = q.k;
	float r = q.real;

	float ii = i * i;
	float jj = j * j;
	float kk = k * k;

	float ij = i * j;
	float jk = j * k;
	float kr = k * r;
	float jr = j * r;
	float ir = i * r;
	float ik = i * k;

	Mat4 m;

	m.m2[0][0] = 1 - 2 * (jj + kk);
	m.m2[0][1] = 2 * (ij - kr);
	m.m2[0][2] = 2 * (ik + jr);
	m.m2[0][3] = 0;

	m.m2[1][0] = 2 * (ij + kr);
	m.m2[1][1] = 1 - 2 * (ii + kk);
	m.m2[1][2] = 2 * (jk - ir);
	m.m2[1][3] = 0;

	m.m2[2][0] = 2 * (ik - jr);
	m.m2[2][1] = 2 * (jk + ir);
	m.m2[2][2] = 1 - 2 * (ii + jj);
	m.m2[2][3] = 0;

	m.m2[3][0] = 0;
	m.m2[3][1] = 0;
	m.m2[3][2] = 0;
	m.m2[3][3] = 1;

	return m;
}

Vec3 GetForward(Quat q) {
	Vec3 up;
	up.x = 2 * (q.i * q.k + q.j * q.real);
	up.y = 2 * (q.j * q.k - q.i * q.real);
	up.z = 1 - 2 * (q.i * q.i + q.j * q.j);
	return Normalize(up);
}

Vec3 GetRight(Quat q) {
	Vec3 right;
	right.x = 1 - 2 * (q.j * q.j + q.k * q.k);
	right.y = 2 * (q.i * q.j + q.k * q.real);
	right.z = 2 * (q.i * q.k - q.j * q.real);
	return Normalize(right);
}

Vec3 GetUp(Quat q) {
	Vec3 forward;
	forward.x = 2 * (q.i * q.j - q.k * q.real);
	forward.y = 1 - 2 * (q.i * q.i + q.k * q.k);
	forward.z = 2 * (q.j * q.k + q.i * q.real);
	return Normalize(forward);
}

Quat QuatFromEulerAngles(float pitch, float yaw, float roll) {
	float cy = Cos(roll * 0.5f);
	float sy = Sin(roll * 0.5f);
	float cp = Cos(yaw * 0.5f);
	float sp = Sin(yaw * 0.5f);
	float cr = Cos(pitch * 0.5f);
	float sr = Sin(pitch * 0.5f);

	Quat q;
	q.w = cy * cp * cr + sy * sp * sr;
	q.x = cy * cp * sr - sy * sp * cr;
	q.y = sy * cp * sr + cy * sp * cr;
	q.z = sy * cp * cr - cy * sp * sr;
	return q;
}

Quat QuatFromEulerAngles(Vec3 euler) {
	return QuatFromEulerAngles(euler.x, euler.y, euler.z);
}

Vec3 GetEulerAngles(Quat q) {
	Vec3 angles;

	float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
	float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
	angles.z = ArcTan2(sinr_cosp, cosr_cosp);

	float sinp = 2.0f * (q.w * q.y - q.z * q.x);
	if (Absolute(sinp) >= 1.0f) {
		// use 90 degrees if out of range
		angles.x = CopySign(PI / 2, sinp);
	} else {
		angles.x = ArcSin(sinp);
	}

	float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
	float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	angles.y = ArcTan2(siny_cosp, cosy_cosp);

	return angles;
}

Quat QuatBetween(Vec3 from, Vec3 to) {
	Quat q;
	q.v4.w = 1.0f + DotProduct(from, to);

	if (q.real) {
		q.v4.xyz = CrossProduct(from, to);
	} else {
		q.v4.xyz = Absolute(from.x) > Absolute(from.z) ? Vec3(-from.y, from.x, 0.f) : Vec3(0.f, -from.z, from.y);
	}

	return Normalize(q);
}

Quat QuatBetween(Quat a, Quat b) {
	Quat t = Conjugate(a);
	t = t * (1.0f / DotProduct(t, t));
	return t * b;
}

Quat QuatLookAt(Vec3 from, Vec3 to, Vec3 world_forward) {
	Vec3 dir = to - from;
	return QuatBetween(world_forward, dir);
}

//
//
//

Vec3 LinearToSrgb(Vec3 color) {
	Vec3 res;
	res.x = SquareRoot(color.x);
	res.y = SquareRoot(color.y);
	res.z = SquareRoot(color.z);
	return res;
}

Vec4 LinearToSrgb(Vec4 color) {
	Vec4 res;
	res.xyz = LinearToSrgb(color.xyz);
	res.w = color.w;
	return res;
}

Vec3 LinearToSrgb(Vec3 color, float gamma) {
	float igamma = 1.0f / gamma;
	Vec3  res;
	res.x = Pow(color.x, igamma);
	res.y = Pow(color.y, igamma);
	res.z = Pow(color.z, igamma);
	return res;
}

Vec4 LinearToSrgb(Vec4 color, float gamma) {
	Vec4 res;
	res.xyz = LinearToSrgb(color.xyz, gamma);
	res.w = color.w;
	return res;
}

Vec3 SrgbToLinear(Vec3 color) {
	Vec3 res;
	res.x = color.x * color.x;
	res.y = color.y * color.y;
	res.z = color.z * color.z;
	return res;
}

Vec4 SrgbToLinear(Vec4 color) {
	Vec4 res;
	res.xyz = SrgbToLinear(color.xyz);
	res.w = color.w;
	return res;
}

Vec3 SrgbToLinear(Vec3 color, float gamma) {
	Vec3 res;
	res.x = Pow(color.x, gamma);
	res.y = Pow(color.y, gamma);
	res.z = Pow(color.z, gamma);
	return res;
}

Vec4 SrgbToLinear(Vec4 color, float gamma) {
	Vec4 res;
	res.xyz = SrgbToLinear(color.xyz, gamma);
	res.w = color.w;
	return res;
}

// http://en.wikipedia.org/wiki/HSL_and_HSV
Vec3 HsvToRgb(Vec3 col) {
	Vec3 res;

	float h = col.x;
	float s = col.y;
	float v = col.z;

	if (s == 0.0f) {
		// gray
		res.x = res.y = res.z = v;
		return res;
	}

	h = Mod(h, 1.0f) / (60.0f / 360.0f);
	int   i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i) {
		case 0:
		res = Vec3(v, t, p);
		break;
		case 1:
		res = Vec3(q, v, p);
		break;
		case 2:
		res = Vec3(p, v, t);
		break;
		case 3:
		res = Vec3(p, q, v);
		break;
		case 4:
		res = Vec3(t, p, v);
		break;
		case 5:
		default:
		res = Vec3(v, p, q);
		break;
	}

	return res;
}

// http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
Vec3 RgbToHsv(Vec3 c) {
	float r = c.x;
	float g = c.y;
	float b = c.z;

	float k = 0.f;
	if (g < b) {
		auto t = b;
		b = g;
		g = t;
		k = -1.f;
	}
	if (r < g) {
		auto t = g;
		g = r;
		r = t;
		k = -2.f / 6.f - k;
	}

	Vec3  res;
	float chroma = r - (g < b ? g : b);
	res.x = Absolute(k + (g - b) / (6.f * chroma + 1e-20f));
	res.y = chroma / (r + 1e-20f);
	res.z = r;
	return res;
}

Vec4 HsvToRgb(Vec4 c) {
	return Vec4(HsvToRgb(c.xyz), c.w);
}

Vec4 RgbToHsv(Vec4 c) {
	return Vec4(RgbToHsv(c.xyz), c.w);
}

//
//
//

Mat2 Lerp(const Mat2 &from, const Mat2 &to, float t) {
	Mat2 res;
	res.rows[0] = Lerp(from.rows[0], to.rows[0], t);
	res.rows[1] = Lerp(from.rows[1], to.rows[1], t);
	return res;
}

Mat3 Lerp(const Mat3 &from, const Mat3 &to, float t) {
	Mat3 res;
	res.rows[0] = Lerp(from.rows[0], to.rows[0], t);
	res.rows[1] = Lerp(from.rows[1], to.rows[1], t);
	res.rows[2] = Lerp(from.rows[2], to.rows[2], t);
	return res;
}

Mat4 Lerp(const Mat4 &from, const Mat4 &to, float t) {
	Mat4 res;
	res.rows[0] = Lerp(from.rows[0], to.rows[0], t);
	res.rows[1] = Lerp(from.rows[1], to.rows[1], t);
	res.rows[2] = Lerp(from.rows[2], to.rows[2], t);
	res.rows[3] = Lerp(from.rows[3], to.rows[3], t);
	return res;
}

Vec2 Slerp(Vec2 from, Vec2 to, float t) {
	return Slerp(from, to, AngleBetween(from, to), t);
}

Vec3 Slerp(Vec3 from, Vec3 to, float t) {
	return Slerp(from, to, AngleBetween(from, to), t);
}

Quat Slerp(Quat from, Quat to, float t) {
	float dot = Clamp(-1.0f, 1.0f, DotProduct(from, to));

	// use shorter path
	if (dot < 0.0f) {
		to = -to;
		dot = -dot;
	}

	if (dot > 0.9999f) {
		Quat result = Lerp(from, to, t);
		return Normalize(result);
	}

	float theta_0 = ArcCos(dot);
	float theta = theta_0 * t;
	float sin_theta = Sin(theta);
	float sin_theta_0 = Sin(theta_0);

	float s0 = Cos(theta) - dot * sin_theta / sin_theta_0;
	float s1 = sin_theta / sin_theta_0;

	return (s0 * from) + (s1 * to);
}

float Step(float edge, float val) {
	return val < edge ? 0.0f : 1.0f;
}

Vec2 Step(Vec2 edge, Vec2 val) {
	Vec2 res;
	res.x = Step(edge.x, val.x);
	res.y = Step(edge.y, val.y);
	return res;
}

Vec3 Step(Vec3 edge, Vec3 val) {
	Vec3 res;
	res.x = Step(edge.x, val.x);
	res.y = Step(edge.y, val.y);
	res.z = Step(edge.z, val.z);
	return res;
}

Vec4 Step(Vec4 edge, Vec4 val) {
	Vec4 res;
	res.x = Step(edge.x, val.x);
	res.y = Step(edge.y, val.y);
	res.z = Step(edge.z, val.z);
	res.w = Step(edge.w, val.w);
	return res;
}

Quat Step(Quat edge, Quat val) {
	Quat res;
	res.v4 = Step(edge.v4, val.v4);
	return res;
}

float InverseSmoothStep(float x) {
	return 0.5f - Sin(ArcSin(1.0f - 2.0f * x) / 3.0f);
}

Vec2 MoveTowards(Vec2 from, Vec2 to, float factor) {
	if (factor) {
		Vec2  direction = to - from;
		float distance = Length(direction);

		if (distance < factor) {
			return to;
		}

		float t = factor / distance;

		return Lerp(to, from, t);
	}

	return from;
}

Vec3 MoveTowards(Vec3 from, Vec3 to, float factor) {
	if (factor) {
		Vec3  direction = to - from;
		float distance = Length(direction);

		if (distance < factor) {
			return to;
		}

		float t = factor / distance;

		return Lerp(from, to, t);
	}

	return from;
}

Vec4 MoveTowards(Vec4 from, Vec4 to, float factor) {
	if (factor) {
		Vec4  direction = to - from;
		float distance = Length(direction);

		if (distance < factor) {
			return to;
		}

		float t = factor / distance;

		return Lerp(to, from, t);
	}

	return from;
}

//
//
//

Vec2 RotateAround(Vec2 point, Vec2 center, float angle) {
	float c = Cos(angle);
	float s = Sin(angle);
	Vec2  res;
	Vec2  p = point - center;
	res.x = p.x * c - p.y * s;
	res.y = p.x * s + p.y * c;
	res += center;
	return res;
}

Quat RotateTowards(Quat from, Quat to, float max_angle) {
	if (max_angle) {
		float dot = Clamp(-1.0f, 1.0f, DotProduct(from, to));

		// use shorter path
		if (dot < 0.0f) {
			to = -to;
			dot = -dot;
		}

		float theta_0 = ArcCos(dot);

		if (theta_0 < max_angle) {
			return to;
		}

		float t = max_angle / theta_0;

		theta_0 = max_angle;
		float theta = theta_0 * t;
		float sin_theta = Sin(theta);
		float sin_theta_0 = Sin(theta_0);

		float s0 = Cos(theta) - dot * sin_theta / sin_theta_0;
		float s1 = sin_theta / sin_theta_0;

		return (s0 * from) + (s1 * to);
	} else {
		return from;
	}
}

Vec2 Reflect(Vec2 d, Vec2 n) {
	float c = DotProduct(NormalizeChecked(d), n);
	float s = SquareRoot(10.f - Square(c));
	Vec2  r;
	r.x = d.x * c - d.y * s;
	r.y = d.x * s + d.y * c;
	return r;
}

UintColor Vec4ToUintColor(Vec4 v) {
	uint8_t r = static_cast<uint8_t>(255.0f * v.x);
	uint8_t g = static_cast<uint8_t>(255.0f * v.y);
	uint8_t b = static_cast<uint8_t>(255.0f * v.z);
	uint8_t a = static_cast<uint8_t>(255.0f * v.w);
	return UintColor(r, g, b, a);
}

UintColor Vec3ToUintColor(Vec3 v) {
	uint8_t r = static_cast<uint8_t>(255.0f * v.x);
	uint8_t g = static_cast<uint8_t>(255.0f * v.y);
	uint8_t b = static_cast<uint8_t>(255.0f * v.z);
	uint8_t a = 255;
	return UintColor(r, g, b, a);
}

Vec4 UintColorToVec4(UintColor c) {
	float div = 1.0f / 255.0f;
	float r = static_cast<float>(c.r) * div;
	float g = static_cast<float>(c.g) * div;
	float b = static_cast<float>(c.b) * div;
	float a = static_cast<float>(c.a) * div;
	return Vec4(r, g, b, a);
}

Vec3 UintColorToVec3(UintColor c) {
	float div = 1.0f / 255.0f;
	float r = static_cast<float>(c.r) * div;
	float g = static_cast<float>(c.g) * div;
	float b = static_cast<float>(c.b) * div;
	return Vec3(r, g, b);
}

//
// End Math
//

//
// Begin Arena
//

static constexpr size_t DEFAULT_MEMORY_ALIGNMENT = sizeof(size_t);

Arena CreateArena(uint8_t *ptr, size_t size) {
	Arena arena;
	arena.Current = ptr;
	arena.Memory = ptr;
	arena.Max = ptr + size;
	return arena;
}

void ResetArena(Arena *arena) {
	arena->Current = arena->Memory;
}

size_t AllocatedMemory(Arena *arena) {
	return arena->Max - arena->Memory;
}

size_t UsedMemory(Arena *arena) {
	return arena->Current - arena->Memory;
}

size_t LeftMemory(Arena *arena) {
	return arena->Max - arena->Current;
}

void *BeginTemporaryMemory(Arena *arena) {
	return arena->Current;
}

void EndTemporaryMemory(Arena *arena, void *ptr) {
	Assert(ptr >= arena->Memory && ptr <= arena->Max);
	arena->Current = (uint8_t *)ptr;
}

uint8_t *Align(uint8_t *location, size_t alignment) {
	return reinterpret_cast<uint8_t *>(reinterpret_cast<size_t>(location + (alignment - 1)) & ~(alignment - 1));
}

size_t Align(size_t location, size_t alignment) {
	return ((location + (alignment - 1)) & ~(alignment - 1));
}

void *PushSize(Arena *arena, size_t size) {
	uint8_t *next = Align(arena->Current, DEFAULT_MEMORY_ALIGNMENT) + size;

	if (next < arena->Max) {
		void *ptr = arena->Current;
		arena->Current = next;
		return ptr;
	}

	return NULL;
}

void *PushSizeAligned(Arena *arena, size_t size, uint32_t alignment) {
	uint8_t *next = Align(arena->Current, alignment) + size;

	if (next < arena->Max) {
		void *ptr = arena->Current;
		arena->Current = next;
		return ptr;
	}
	return NULL;
}

void *operator new(size_t size, Arena *arena) noexcept {
	return PushSize(arena, size);
}

//
// End Arena
//

//
// Renderer
//

static constexpr uint32_t MAX_VERTICES = 200000;
static constexpr uint32_t MAX_INDICES = MAX_VERTICES * 6;
static constexpr uint32_t MAX_DRAW_CMDS = 5000;
static constexpr uint32_t MAX_DRAW_CMD_LISTS = 500;

static constexpr int MIN_CIRCLE_SEGMENTS = 12;
static constexpr int MAX_CIRCLE_SEGMENTS = 512;

struct Vertex2D {
	Vec2 Position;
	Vec2 TexCoord;
	Vec4 Color;
};

typedef uint32_t Index2D;

struct DrawCmd2D {
	Rect     ClipRect;
	uint32_t Texture;
	uint32_t VertexOffset;
	uint32_t IndexOffset;
	uint32_t IndexCount;
};

struct DrawCmd2DList {
	Mat4 ViewTransform;

	DrawCmd2D *Cmds;
	uint32_t   CmdCount;
};

struct DrawCmd2DListQueue {
	DrawCmd2DList *First;
	DrawCmd2DList *Last;

	inline DrawCmd2DList *begin() { return First; }
	inline DrawCmd2DList *end() { return Last; }
};

struct Draw2DBufferView {
	Vertex2D *VertexBufferPtr;
	size_t    VertexBufferSize;
	Index2D *IndexBufferPtr;
	size_t    IndexBufferSize;
};

template <typename T>
struct Buffer {
	T *Current;
	T *Pointer;
	T *Last;
};

using VertexBuffer = Buffer<Vertex2D>;

constexpr uint32_t VERTEX_STUB_COUNT = 4;
constexpr uint32_t INDEX_STUB_COUNT = 6;
constexpr uint32_t DRAW_CMD_STUB_COUNT = 1;
constexpr uint32_t DRAW_CMD_LIST_STUB_COUNT = 1;

struct Renderer2D {
	Buffer<DrawCmd2DList> DrawCmdList;
	Buffer<DrawCmd2D>     DrawCmd;
	Buffer<Vertex2D>      Vertex;
	Buffer<Index2D>       Index;

	DrawCmd2D *CurrentDrawCmd;
	Index2D    NextIndex;

	Rect  ClipRect;
	uint32_t Texture;
	uint32_t DefaultTexture;
	float Thickness;
	Vec4 ClearColor;

	void *AllocatedMemory;
};

static float g_UnitCircleCosValues[MAX_CIRCLE_SEGMENTS];
static float g_UnitcircleSinValues[MAX_CIRCLE_SEGMENTS];

static Renderer2D g_RendererContext;

static Draw2DBufferView GetDraw2DBufferView() {
	Draw2DBufferView data;
	data.VertexBufferPtr = g_RendererContext.Vertex.Pointer;
	data.VertexBufferSize = (char *)g_RendererContext.Vertex.Current - (char *)g_RendererContext.Vertex.Pointer;
	data.IndexBufferPtr = g_RendererContext.Index.Pointer;
	data.IndexBufferSize = (char *)g_RendererContext.Index.Current - (char *)g_RendererContext.Index.Pointer;
	return data;
}

static DrawCmd2DListQueue GetDraw2DListQueue() {
	DrawCmd2DListQueue queue;
	queue.First = g_RendererContext.DrawCmdList.Pointer;
	queue.Last = g_RendererContext.DrawCmdList.Current;
	return queue;
}

bool InitializeRenderer2D(Platform *platform) {
	for (int i = 0; i < MAX_CIRCLE_SEGMENTS; ++i) {
		float theta = ((float)i / (float)MAX_CIRCLE_SEGMENTS) * PI * 2;
		g_UnitCircleCosValues[i] = cosf(theta);
		g_UnitcircleSinValues[i] = sinf(theta);
	}

	g_UnitCircleCosValues[MAX_CIRCLE_SEGMENTS - 1] = 1;
	g_UnitcircleSinValues[MAX_CIRCLE_SEGMENTS - 1] = 0;

	// Sizes including stubs
	uint32_t size = 0;
	size += sizeof(Vertex2D) * (MAX_VERTICES + VERTEX_STUB_COUNT);
	size += sizeof(Index2D) * (MAX_INDICES + INDEX_STUB_COUNT);
	size += sizeof(DrawCmd2D) * (MAX_DRAW_CMDS + DRAW_CMD_STUB_COUNT);
	size += sizeof(DrawCmd2DList) * (MAX_DRAW_CMD_LISTS + DRAW_CMD_LIST_STUB_COUNT);

	g_RendererContext.AllocatedMemory = platform->Alloc(size);
	if (g_RendererContext.AllocatedMemory == NULL) return false;

	g_RendererContext.Vertex.Pointer = (Vertex2D *)g_RendererContext.AllocatedMemory;
	g_RendererContext.Vertex.Last = g_RendererContext.Vertex.Pointer + MAX_VERTICES;
	g_RendererContext.Vertex.Current = g_RendererContext.Vertex.Pointer;

	g_RendererContext.Index.Pointer = (Index2D *)(g_RendererContext.Vertex.Last);
	g_RendererContext.Index.Last = g_RendererContext.Index.Pointer + MAX_INDICES;
	g_RendererContext.Index.Current = g_RendererContext.Index.Pointer;

	g_RendererContext.DrawCmd.Pointer = (DrawCmd2D *)(g_RendererContext.Index.Last);
	g_RendererContext.DrawCmd.Last = g_RendererContext.DrawCmd.Pointer + MAX_DRAW_CMDS;
	g_RendererContext.DrawCmd.Current = g_RendererContext.DrawCmd.Pointer;

	g_RendererContext.DrawCmdList.Pointer = (DrawCmd2DList *)(g_RendererContext.DrawCmd.Last);
	g_RendererContext.DrawCmdList.Last = g_RendererContext.DrawCmdList.Pointer + MAX_DRAW_CMD_LISTS;
	g_RendererContext.DrawCmdList.Current = g_RendererContext.DrawCmdList.Pointer;

	g_RendererContext.Thickness = 1;

	g_RendererContext.ClearColor = Vec4(.2f, .3f, .4f, 1);

	return true;
}

void FrameRenderer2D(Rect region) {
	g_RendererContext.DrawCmdList.Current = g_RendererContext.DrawCmdList.Pointer;
	g_RendererContext.DrawCmd.Current = g_RendererContext.DrawCmd.Pointer;
	g_RendererContext.Index.Current = g_RendererContext.Index.Pointer;
	g_RendererContext.Vertex.Current = g_RendererContext.Vertex.Pointer;

	g_RendererContext.Texture = g_RendererContext.DefaultTexture;
	g_RendererContext.ClipRect = region;

	g_RendererContext.CurrentDrawCmd = g_RendererContext.DrawCmd.Current;
	g_RendererContext.NextIndex = 0;

	auto cmd = g_RendererContext.CurrentDrawCmd;
	cmd->VertexOffset = 0;
	cmd->IndexOffset = 0;
	cmd->Texture = g_RendererContext.Texture;
	cmd->ClipRect = g_RendererContext.ClipRect;
	cmd->IndexCount = 0;
}

void BeginScene2D(const Mat4 &view) {
	auto cmd_list = g_RendererContext.DrawCmdList.Current;
	cmd_list->ViewTransform = view;
	cmd_list->Cmds = g_RendererContext.DrawCmd.Current;
	cmd_list->CmdCount = 0;

	// Setting default clip rect as entire render region
	g_RendererContext.DrawCmd.Current->ClipRect = g_RendererContext.ClipRect;
	// Set the default texture for new scene
	g_RendererContext.Texture = g_RendererContext.DefaultTexture;
	g_RendererContext.DrawCmd.Current->Texture = g_RendererContext.Texture;
}

void BeginScene2D(float left, float right, float bottom, float top) {
	BeginScene2D(OrthographicProjection(left, right, bottom, top, -1, 1));
}

static inline void PushDrawCmd() {
	if (g_RendererContext.DrawCmd.Current < g_RendererContext.DrawCmd.Last) {
		g_RendererContext.DrawCmd.Current += 1;
		g_RendererContext.DrawCmdList.Current->CmdCount += 1;
	} else {
		Unreachable();  // DrawCmd buffer full
	}

	g_RendererContext.NextIndex = 0;
	g_RendererContext.CurrentDrawCmd = g_RendererContext.DrawCmd.Current;

	auto cmd = g_RendererContext.CurrentDrawCmd;
	cmd->VertexOffset = (uint32_t)(g_RendererContext.Vertex.Current - g_RendererContext.Vertex.Pointer);
	cmd->IndexOffset = (uint32_t)(g_RendererContext.Index.Current - g_RendererContext.Index.Pointer);
	cmd->ClipRect = g_RendererContext.ClipRect;
	cmd->Texture = g_RendererContext.Texture;
	cmd->IndexCount = 0;
}

void EndScene2D() {
	if (g_RendererContext.CurrentDrawCmd->IndexCount) {
		PushDrawCmd();
	}
	if (g_RendererContext.DrawCmdList.Current < g_RendererContext.DrawCmdList.Last) {
		g_RendererContext.DrawCmdList.Current += 1;
	} else {
		Unreachable();  // DrawCmdList buffer full
	}
}

void SetDefaultTexture(uint32_t texture) {
	g_RendererContext.DefaultTexture = texture;
}

uint32_t GetDefaultTexture() {
	return g_RendererContext.DefaultTexture;
}

void SetClearColor(float r, float g, float b, float a) {
	g_RendererContext.ClearColor = Vec4(r, g, b, a);
}

void SetClearColor(Vec4 color) {
	g_RendererContext.ClearColor = color;
}

Vec4 GetClearColor() {
	return g_RendererContext.ClearColor;
}

void SetThickness(float thickness) {
	g_RendererContext.Thickness = thickness;
}

void SetTexture(uint32_t texture) {
	if (texture != g_RendererContext.Texture && g_RendererContext.CurrentDrawCmd->IndexCount)
		PushDrawCmd();

	g_RendererContext.Texture = texture ? texture : g_RendererContext.DefaultTexture;
	g_RendererContext.CurrentDrawCmd->Texture = g_RendererContext.Texture;
}

uint32_t PushTexture(uint32_t texture) {
	uint32_t result = g_RendererContext.Texture;
	SetTexture(texture);
	return result;
}

void PopTexture(uint32_t texture) {
	SetTexture(texture);
}

void SetClipRect(Rect clip_rect) {
	if (memcmp(&clip_rect, &g_RendererContext.ClipRect, sizeof(clip_rect)) != 0 && g_RendererContext.CurrentDrawCmd->IndexCount)
		PushDrawCmd();

	g_RendererContext.ClipRect = clip_rect;
	g_RendererContext.CurrentDrawCmd->ClipRect = clip_rect;
}

Rect PushClipRect(Rect clip_rect) {
	Rect result = g_RendererContext.ClipRect;
	SetClipRect(clip_rect);
	return result;
}

void PopClipRect(Rect clip_rect) {
	SetClipRect(clip_rect);
}

inline Vertex2D *EnsureVertex(uint32_t count) {
	Assert(count <= VERTEX_STUB_COUNT);

	if (g_RendererContext.Vertex.Current + count < g_RendererContext.Vertex.Last) {
		auto r = g_RendererContext.Vertex.Current;
		g_RendererContext.Vertex.Current += count;
		return r;
	} else {
		Unreachable();  // Vertex buffer full
		g_RendererContext.Vertex.Current = g_RendererContext.Vertex.Last;
		return g_RendererContext.Vertex.Last;
	}
}

inline Index2D *EnsureIndex(uint32_t count) {
	Assert(count <= INDEX_STUB_COUNT);

	if (g_RendererContext.Index.Current + count < g_RendererContext.Index.Last) {
		auto r = g_RendererContext.Index.Current;
		g_RendererContext.Index.Current += count;
		return r;
	} else {
		Unreachable();  // Index buffer full
		g_RendererContext.Index.Current = g_RendererContext.Index.Last;
		return g_RendererContext.Index.Last;
	}
}

void DrawTriangle(Vec2 va, Vec2 vb, Vec2 vc, Vec2 ta, Vec2 tb, Vec2 tc, Vec4 ca, Vec4 cb, Vec4 cc) {
	Vertex2D *vtx = EnsureVertex(3);
	Index2D *idx = EnsureIndex(3);

	vtx[0].Position = va;
	vtx[0].TexCoord = ta;
	vtx[0].Color = ca;
	vtx[1].Position = vb;
	vtx[1].TexCoord = tb;
	vtx[1].Color = cb;
	vtx[2].Position = vc;
	vtx[2].TexCoord = tc;
	vtx[2].Color = cc;

	Index2D index = g_RendererContext.NextIndex;
	idx[0] = index + 0;
	idx[1] = index + 1;
	idx[2] = index + 2;

	g_RendererContext.CurrentDrawCmd->IndexCount += 3;
	g_RendererContext.NextIndex += 3;
}

void DrawTriangle(Vec2 a, Vec2 b, Vec2 c, Vec2 ta, Vec2 tb, Vec2 tc, Vec4 col) {
	DrawTriangle(a, b, c, ta, tb, tc, col, col, col);
}

void DrawTriangle(Vec2 a, Vec2 b, Vec2 c, Vec4 color) {
	DrawTriangle(a, b, c, Vec2(0), Vec2(0), Vec2(0), color, color, color);
}

void DrawQuad(Vec2 va, Vec2 vb, Vec2 vc, Vec2 vd, Vec2 ta, Vec2 tb, Vec2 tc, Vec2 td, Vec4 color) {
	Vertex2D *vtx = EnsureVertex(4);
	Index2D *idx = EnsureIndex(6);

	vtx[0].Position = va;
	vtx[0].TexCoord = ta;
	vtx[0].Color = color;
	vtx[1].Position = vb;
	vtx[1].TexCoord = tb;
	vtx[1].Color = color;
	vtx[2].Position = vc;
	vtx[2].TexCoord = tc;
	vtx[2].Color = color;
	vtx[3].Position = vd;
	vtx[3].TexCoord = td;
	vtx[3].Color = color;

	Index2D index = g_RendererContext.NextIndex;
	idx[0] = index + 0;
	idx[1] = index + 1;
	idx[2] = index + 2;
	idx[3] = index + 0;
	idx[4] = index + 2;
	idx[5] = index + 3;

	g_RendererContext.CurrentDrawCmd->IndexCount += 6;
	g_RendererContext.NextIndex += 4;
}

void DrawQuad(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec4 color) {
	DrawQuad(a, b, c, d, Vec2(0), Vec2(0), Vec2(0), Vec2(0), color);
}

void DrawQuad(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Rect rect, Vec4 color) {
	auto uv_a = rect.Min;
	auto uv_b = Vec2(rect.Min.x, rect.Max.y);
	auto uv_c = rect.Max;
	auto uv_d = Vec2(rect.Max.x, rect.Min.y);
	DrawQuad(a, b, c, d, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRect(Vec2 pos, Vec2 dim, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color) {
	Vec2 a = pos;
	Vec2 b = Vec2(pos.x, pos.y + dim.y);
	Vec2 c = Vec2(pos + dim);
	Vec2 d = Vec2(pos.x + dim.x, pos.y);
	DrawQuad(a, b, c, d, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRect(Vec2 pos, Vec2 dim, Vec4 color) {
	DrawRect(pos, dim, Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0), color);
}

void DrawRect(Vec2 pos, Vec2 dim, Rect rect, Vec4 color) {
	auto uv_a = rect.Min;
	auto uv_b = Vec2(rect.Min.x, rect.Max.y);
	auto uv_c = rect.Max;
	auto uv_d = Vec2(rect.Max.x, rect.Min.y);
	DrawRect(pos, dim, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRectRotated(Vec2 pos, Vec2 dim, float angle, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color) {
	Vec2 center = 0.5f * (2 * pos + dim);

	Vec2 a = pos;
	Vec2 b = Vec2(pos.x, pos.y + dim.y);
	Vec2 c = pos + dim;
	Vec2 d = Vec2(pos.x + dim.x, pos.y);

	auto r0 = a - center;
	auto r1 = b - center;
	auto r2 = c - center;
	auto r3 = d - center;

	float cv = Cos(angle);
	float sv = Sin(angle);

	a.x = r0.x * cv - r0.y * sv;
	a.y = r0.x * sv + r0.y * cv;
	b.x = r1.x * cv - r1.y * sv;
	b.y = r1.x * sv + r1.y * cv;
	c.x = r2.x * cv - r2.y * sv;
	c.y = r2.x * sv + r2.y * cv;
	d.x = r3.x * cv - r3.y * sv;
	d.y = r3.x * sv + r3.y * cv;

	a += center;
	b += center;
	c += center;
	d += center;

	DrawQuad(a, b, c, d, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRectRotated(Vec2 pos, Vec2 dim, float angle, Vec4 color) {
	DrawRectRotated(pos, dim, angle, Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0), color);
}

void DrawRectRotated(Vec2 pos, Vec2 dim, float angle, Rect rect, Vec4 color) {
	auto uv_a = rect.Min;
	auto uv_b = Vec2(rect.Min.x, rect.Max.y);
	auto uv_c = rect.Max;
	auto uv_d = Vec2(rect.Max.x, rect.Min.y);
	DrawRectRotated(pos, dim, angle, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRectCentered(Vec2 pos, Vec2 dim, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color) {
	Vec2 half_dim = 0.5f * dim;

	Vec2 a, b, c, d;
	a = pos - half_dim;
	b = Vec2(pos.x - half_dim.x, pos.y + half_dim.y);
	c = pos + half_dim;
	d = Vec2(pos.x + half_dim.x, pos.y - half_dim.y);

	DrawQuad(a, b, c, d, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRectCentered(Vec2 pos, Vec2 dim, Vec4 color) {
	DrawRectCentered(pos, dim, Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0), color);
}

void DrawRectCentered(Vec2 pos, Vec2 dim, Rect rect, Vec4 color) {
	auto uv_a = rect.Min;
	auto uv_b = Vec2(rect.Min.x, rect.Max.y);
	auto uv_c = rect.Max;
	auto uv_d = Vec2(rect.Max.x, rect.Min.y);
	DrawRectCentered(pos, dim, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRectCenteredRotated(Vec2 pos, Vec2 dim, float angle, Vec2 uv_a, Vec2 uv_b, Vec2 uv_c, Vec2 uv_d, Vec4 color) {
	Vec2 center = pos;

	Vec2 half_dim = 0.5f * dim;
	Vec2 a, b, c, d;
	a = pos - half_dim;
	b = Vec2(pos.x - half_dim.x, pos.y + half_dim.y);
	c = pos + half_dim;
	d = Vec2(pos.x + half_dim.x, pos.y - half_dim.y);

	auto r0 = a - center;
	auto r1 = b - center;
	auto r2 = c - center;
	auto r3 = d - center;

	float cv = cosf(angle);
	float sv = sinf(angle);

	a.x = r0.x * cv - r0.y * sv;
	a.y = r0.x * sv + r0.y * cv;
	b.x = r1.x * cv - r1.y * sv;
	b.y = r1.x * sv + r1.y * cv;
	c.x = r2.x * cv - r2.y * sv;
	c.y = r2.x * sv + r2.y * cv;
	d.x = r3.x * cv - r3.y * sv;
	d.y = r3.x * sv + r3.y * cv;

	a += center;
	b += center;
	c += center;
	d += center;

	DrawQuad(a, b, c, d, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawRectCenteredRotated(Vec2 pos, Vec2 dim, float angle, Vec4 color) {
	DrawRectCenteredRotated(pos, dim, angle, Vec2(0, 0), Vec2(0, 1), Vec2(1, 1), Vec2(1, 0), color);
}

void DrawRectCenteredRotated(Vec2 pos, Vec2 dim, float angle, Rect rect, Vec4 color) {
	auto uv_a = rect.Min;
	auto uv_b = Vec2(rect.Min.x, rect.Max.y);
	auto uv_c = rect.Max;
	auto uv_d = Vec2(rect.Max.x, rect.Min.y);
	DrawRectCenteredRotated(pos, dim, angle, uv_a, uv_b, uv_c, uv_d, color);
}

void DrawEllipse(Vec2 pos, float radius_a, float radius_b, Vec4 color, int segments) {
	segments = Clamp(MIN_CIRCLE_SEGMENTS, MAX_CIRCLE_SEGMENTS - 1, segments);

	float px = g_UnitCircleCosValues[0] * radius_a;
	float py = g_UnitcircleSinValues[0] * radius_b;

	float npx, npy;
	for (int index = 1; index <= segments; ++index) {
		int lookup = (int)(((float)index / (float)segments) * (MAX_CIRCLE_SEGMENTS - 1) + 0.5f);

		npx = g_UnitCircleCosValues[lookup] * radius_a;
		npy = g_UnitcircleSinValues[lookup] * radius_b;

		DrawTriangle(pos, pos + Vec2(npx, npy), pos + Vec2(px, py), color);

		px = npx;
		py = npy;
	}
}

void DrawCircle(Vec2 pos, float radius, Vec4 color, int segments) {
	DrawEllipse(pos, radius, radius, color, segments);
}

void DrawPie(Vec2 pos, float radius_a, float radius_b, float theta_a, float theta_b, Vec4 color, int segments) {
	Assert(theta_a >= 0 && theta_a <= PI * 2 && theta_b >= 0 && theta_b <= PI * 2);

	int first_index = (int)((0.5f * theta_a * PI_INVERSE) * (float)(MAX_CIRCLE_SEGMENTS)+0.5f);
	int last_index = (int)((0.5f * theta_b * PI_INVERSE) * (float)(MAX_CIRCLE_SEGMENTS)+0.5f);

	while (first_index >= last_index)
		last_index += MAX_CIRCLE_SEGMENTS;

	auto value_count = last_index - first_index;
	segments = Minimum(segments, value_count);

	float px = g_UnitCircleCosValues[first_index] * radius_a;
	float py = g_UnitcircleSinValues[first_index] * radius_b;

	float npx, npy;
	for (int index = 1; index <= segments; ++index) {
		auto lookup = first_index + (int)((float)index / (float)segments * (float)value_count + 0.5f);
		lookup = lookup % MAX_CIRCLE_SEGMENTS;

		npx = g_UnitCircleCosValues[lookup] * radius_a;
		npy = g_UnitcircleSinValues[lookup] * radius_b;

		DrawTriangle(pos, pos + Vec2(npx, npy), pos + Vec2(px, py), color);

		px = npx;
		py = npy;
	}
}

void DrawPie(Vec2 pos, float radius, float theta_a, float theta_b, Vec4 color, int segments) {
	DrawPie(pos, radius, radius, theta_a, theta_b, color, segments);
}

void DrawPiePart(Vec2 pos, float radius_a_min, float radius_b_min, float radius_a_max, float radius_b_max, float theta_a, float theta_b, Vec4 color, int segments) {
	Assert(theta_a >= 0 && theta_a <= PI * 2 && theta_b >= 0 && theta_b <= PI * 2);

	int first_index = (int)((0.5f * theta_a * PI_INVERSE) * (float)(MAX_CIRCLE_SEGMENTS)+0.5f);
	int last_index = (int)((0.5f * theta_b * PI_INVERSE) * (float)(MAX_CIRCLE_SEGMENTS)+0.5f);

	while (first_index >= last_index)
		last_index += MAX_CIRCLE_SEGMENTS;

	auto value_count = last_index - first_index;
	segments = Minimum(segments, value_count);

	float min_px = g_UnitCircleCosValues[first_index] * radius_a_min;
	float min_py = g_UnitcircleSinValues[first_index] * radius_b_min;
	float max_px = g_UnitCircleCosValues[first_index] * radius_a_max;
	float max_py = g_UnitcircleSinValues[first_index] * radius_b_max;

	float min_npx, min_npy;
	float max_npx, max_npy;
	for (int index = 1; index <= segments; ++index) {
		auto lookup = first_index + (int)((float)index / (float)segments * (float)value_count + 0.5f);
		lookup = lookup % MAX_CIRCLE_SEGMENTS;

		min_npx = g_UnitCircleCosValues[lookup] * radius_a_min;
		min_npy = g_UnitcircleSinValues[lookup] * radius_b_min;
		max_npx = g_UnitCircleCosValues[lookup] * radius_a_max;
		max_npy = g_UnitcircleSinValues[lookup] * radius_b_max;

		DrawQuad(pos + Vec2(min_npx, min_npy),
				 pos + Vec2(max_npx, max_npy),
				 pos + Vec2(max_px, max_py),
				 pos + Vec2(min_px, min_py),
				 color);

		min_px = min_npx;
		min_py = min_npy;
		max_px = max_npx;
		max_py = max_npy;
	}
}

void DrawPiePart(Vec2 pos, float radius_min, float radius_max, float theta_a, float theta_b, Vec4 color, int segments) {
	DrawPiePart(pos, radius_min, radius_min, radius_max, radius_max, theta_a, theta_b, color, segments);
}

void DrawLine(Vec2 a, Vec2 b, Vec4 color) {
	if (IsNull(b - a)) return;

	Vertex2D *vtx = EnsureVertex(4);
	Index2D *idx = EnsureIndex(6);

	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float ilen = 1.0f / sqrtf(dx * dx + dy * dy);
	dx *= (g_RendererContext.Thickness * ilen);
	dy *= (g_RendererContext.Thickness * ilen);

	vtx[0].Position = Vec2(a.x - dy, a.y + dx);
	vtx[0].TexCoord = Vec2(0, 0);
	vtx[0].Color = color;
	vtx[1].Position = Vec2(b.x - dy, b.y + dx);
	vtx[1].TexCoord = Vec2(0, 1);
	vtx[1].Color = color;
	vtx[2].Position = Vec2(b.x + dy, b.y - dx);
	vtx[2].TexCoord = Vec2(1, 1);
	vtx[2].Color = color;
	vtx[3].Position = Vec2(a.x + dy, a.y - dx);
	vtx[3].TexCoord = Vec2(1, 0);
	vtx[3].Color = color;

	Index2D index = g_RendererContext.NextIndex;
	idx[0] = index + 0;
	idx[1] = index + 1;
	idx[2] = index + 2;
	idx[3] = index + 0;
	idx[4] = index + 2;
	idx[5] = index + 3;

	g_RendererContext.CurrentDrawCmd->IndexCount += 6;
	g_RendererContext.NextIndex += 4;
}

void DrawBezierQuadratic(Vec2 a, Vec2 b, Vec2 c, Vec4 color, int segments) {
	Vec2 p = a, np;
	for (int seg_index = 0; seg_index <= segments; ++seg_index) {
		float t = (float)seg_index / (float)segments;
		np = BezierQuadratic(a, b, c, t);
		DrawLine(p, np, color);
		p = np;
	}
}

void DrawBezierCubic(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec4 color, int segments) {
	Vec2 p = a, np;
	for (int seg_index = 0; seg_index <= segments; ++seg_index) {
		float t = (float)seg_index / (float)segments;
		np = BezeriCubic(a, b, c, d, t);
		DrawLine(p, np, color);
		p = np;
	}
}

void DrawPolygon(const Vec2 *vertices, uint32_t count, Vec4 color) {
	Assert(count >= 3);
	uint32_t triangle_count = count - 2;
	for (uint32_t triangle_index = 0; triangle_index < triangle_count; ++triangle_index) {
		DrawTriangle(Vec2(vertices[0]),
					 Vec2(vertices[triangle_index + 1]),
					 Vec2(vertices[triangle_index + 2]), color);
	}
}

void DrawTriangleOutline(Vec2 a, Vec2 b, Vec2 c, Vec4 color) {
	DrawLine(a, b, color);
	DrawLine(b, c, color);
	DrawLine(c, a, color);
}

void DrawQuadOutline(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Vec4 color) {
	DrawLine(a, b, color);
	DrawLine(b, c, color);
	DrawLine(c, d, color);
	DrawLine(a, d, color);
}

void DrawRectOutline(Vec2 pos, Vec2 dim, Vec4 color) {
	Vec2 a = pos;
	Vec2 b = pos + Vec2(0, dim.y);
	Vec2 c = pos + dim;
	Vec2 d = pos + Vec2(dim.x, 0);
	DrawQuadOutline(a, b, c, d, color);
}

void DrawRectCenteredOutline(Vec2 pos, Vec2 dim, Vec4 color) {
	Vec2 half_dim = 0.5f * dim;

	Vec2 a, b, c, d;
	a = pos - half_dim;
	b = Vec2(pos.x - half_dim.x, pos.y + half_dim.y);
	c = pos + half_dim;
	d = Vec2(pos.x + half_dim.x, pos.y - half_dim.y);

	DrawQuadOutline(a, b, c, d, color);
}

void DrawEllipseOutline(Vec2 position, float radius_a, float radius_b, Vec4 color, int segments) {
	segments = Clamp(MIN_CIRCLE_SEGMENTS, MAX_CIRCLE_SEGMENTS - 1, segments);

	float px = g_UnitCircleCosValues[0] * radius_a;
	float py = g_UnitcircleSinValues[0] * radius_b;

	float npx, npy;
	for (int index = 1; index <= segments; ++index) {
		int lookup = (int)(((float)index / (float)segments) * (MAX_CIRCLE_SEGMENTS - 1) + 0.5f);

		npx = g_UnitCircleCosValues[lookup] * radius_a;
		npy = g_UnitcircleSinValues[lookup] * radius_b;

		DrawLine(position + Vec2(px, py), position + Vec2(npx, npy), color);

		px = npx;
		py = npy;
	}
}

void DrawCircleOutline(Vec2 position, float radius, Vec4 color, int segments) {
	DrawEllipseOutline(position, radius, radius, color, segments);
}

void DrawArcOutline(Vec2 position, float radius_a, float radius_b, float theta_a, float theta_b, Vec4 color, bool closed, int segments) {
	Assert(theta_a >= 0 && theta_a <= PI * 2 && theta_b >= 0 && theta_b <= PI * 2);

	int first_index = (int)((0.5f * theta_a * PI_INVERSE) * (float)(MAX_CIRCLE_SEGMENTS)+0.5f);
	int last_index = (int)((0.5f * theta_b * PI_INVERSE) * (float)(MAX_CIRCLE_SEGMENTS)+0.5f);

	while (first_index >= last_index)
		last_index += MAX_CIRCLE_SEGMENTS;

	auto value_count = last_index - first_index;
	segments = Minimum(segments, value_count);

	float px = g_UnitCircleCosValues[first_index] * radius_a;
	float py = g_UnitcircleSinValues[first_index] * radius_b;

	if (closed) {
		DrawLine(position, position + Vec2(px, py), color);
	}

	float npx, npy;
	for (int index = 1; index <= segments; ++index) {
		auto lookup = first_index + (int)((float)index / (float)segments * (float)value_count + 0.5f);
		lookup = lookup % MAX_CIRCLE_SEGMENTS;

		npx = g_UnitCircleCosValues[lookup] * radius_a;
		npy = g_UnitcircleSinValues[lookup] * radius_b;

		DrawLine(position + Vec2(px, py), position + Vec2(npx, npy), color);

		px = npx;
		py = npy;
	}

	if (closed) {
		DrawLine(position, position + Vec2(px, py), color);
	}
}

void DrawArcOutline(Vec2 position, float radius, float theta_a, float theta_b, Vec4 color, bool closed, int segments) {
	DrawArcOutline(position, radius, radius, theta_a, theta_b, color, closed, segments);
}

void DrawPolygonOutline(const Vec2 *vertices, uint32_t count, Vec4 color) {
	const Vec2 *p, *q;
	p = vertices;
	for (uint32_t index = 0; index < count - 1; ++index) {
		q = p + 1;
		DrawLine(*p, *q, color);
		p = q;
	}
	DrawLine(*vertices, *p, color);
}

//
// End Renderer
//

//
// Utils
//

uint32_t FindLeastSignificantSetBit(uint32_t value) {
	for (uint32_t test = 0; test < 32; ++test) {
		if (value & (1 << test)) {
			return test;
			break;
		}
	}
	return 0;
}

uint8_t *LoadBMPFromFile(Platform *p, const char *file, int *w, int *h) {
#if OS_WINDOWS
	FILE *fp = NULL;
	fopen_s(&fp, file, "rb");
#else
	FILE *fp = fopen(file, "rb");
#endif
	if (!fp) return NULL;

	uint16_t file_type; uint32_t file_size; uint16_t reserved1; uint16_t reserved2; uint32_t bitmap_offset;
	if (fread(&file_type, sizeof(file_type), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&file_size, sizeof(file_size), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&reserved1, sizeof(reserved1), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&reserved2, sizeof(reserved2), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&bitmap_offset, sizeof(bitmap_offset), 1, fp) != 1) { fclose(fp); return NULL; }

	uint32_t size; int32_t width; int32_t height; uint16_t planes; uint16_t bits_per_pixel; uint32_t compression;
	if (fread(&size, sizeof(size), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&width, sizeof(width), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&height, sizeof(height), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&planes, sizeof(planes), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&bits_per_pixel, sizeof(bits_per_pixel), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&compression, sizeof(compression), 1, fp) != 1) { fclose(fp); return NULL; }

	uint32_t bitmap_size; int32_t h_res; int32_t v_res; uint32_t color_used; uint32_t colors_important;
	if (fread(&bitmap_size, sizeof(bitmap_size), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&h_res, sizeof(h_res), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&v_res, sizeof(v_res), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&color_used, sizeof(color_used), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&colors_important, sizeof(colors_important), 1, fp) != 1) { fclose(fp); return NULL; }

	uint32_t red_mask; uint32_t green_mask; uint32_t blue_mask;
	if (fread(&red_mask, sizeof(red_mask), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&green_mask, sizeof(green_mask), 1, fp) != 1) { fclose(fp); return NULL; }
	if (fread(&blue_mask, sizeof(blue_mask), 1, fp) != 1) { fclose(fp); return NULL; }

	uint32_t alpha_mask = ~(red_mask | green_mask | blue_mask);
	if (red_mask == 0 || green_mask == 0 || blue_mask == 0 || alpha_mask == 0) {
		fprintf(stderr, "Failed to load BMP(%s). Color format must be RGBA", file);
		fclose(fp);
		return NULL;
	}

	if (compression != 3) {
		fprintf(stderr, "Failed to load BMP(%s). Compression is not supported", file);
		fclose(fp);
		return NULL;
	}

	if (bits_per_pixel != 32) {
		fprintf(stderr, "Failed to load BMP(%s). Bits per pixel must be 32", file);
		fclose(fp);
		return NULL;
	}

	size_t pixels_size = sizeof(uint32_t) * width * height;
	uint8_t *pixels = (uint8_t *)p->Alloc(pixels_size);
	if (fread(pixels, pixels_size, 1, fp) != 1) {
		fprintf(stderr, "Invalid BMP file");
		p->Free(pixels);
		fclose(fp);
		return NULL;
	}

	fclose(fp);

	uint32_t red_shift = FindLeastSignificantSetBit(red_mask);
	uint32_t green_shift = FindLeastSignificantSetBit(green_mask);
	uint32_t blue_shift = FindLeastSignificantSetBit(blue_mask);
	uint32_t alpha_shift = FindLeastSignificantSetBit(alpha_mask);

	uint32_t *dest = (uint32_t *)pixels;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			uint32_t c = *dest;
			*dest = ((((c >> alpha_shift) & 0xff) << 24) | (((c >> blue_shift) & 0xff) << 16) |
					 (((c >> green_shift) & 0xff) << 8) | (((c >> red_shift) & 0xff) << 0));
			dest += 1;
		}
	}

	*w = width;
	*h = height;
	return pixels;
}


// Start of the PNG decoder
typedef void (*handle_ptr)(unsigned char*, int);

struct handler
{
	const char* type;
	handle_ptr func;
};

typedef struct pngInfo
{
	unsigned char* image_data;
	unsigned count;
	unsigned image_width;
	unsigned image_height;
	enum { RGB, RGBA } color_channel;
	unsigned color_type;
	unsigned image_bit_depth;
} pngInfo;

// Forward declaration
static int deflate(unsigned char*, unsigned, unsigned char*, unsigned*);

// helper functions defined here
unsigned char average(unsigned char a, unsigned char b)
{
	int c = a + b;
	return c / 2;
}

// uses upcoming 4 bytes to form it into 32 bit integer with network order
unsigned int getBigEndian(const unsigned char* lenbuf)
{
	unsigned int v = 0, temp = 0;
	unsigned char ch;
	int k = 24;
	for (int i = 0; i < 4; ++i)
	{
		ch = lenbuf[i];
		temp = ch << k;
		k = k - 8;
		v = v | temp;
	}
	return v;
}

// png chunk handler.. doesn't do anything much but will be required
void header_handler(unsigned char* buffer, int len, pngInfo* image_info)
{
	image_info->image_width = getBigEndian(buffer);
	image_info->image_height = getBigEndian(buffer + 4);
	image_info->image_bit_depth = buffer[8];
	image_info->color_type = buffer[9];
}

void background_handler(unsigned char* buffer, int len)
{
	printf("Background Color info :  \n");
	int r = 0, g = 0, b = 0;
	r |= (buffer[0] << 8);
	r |= buffer[1];
	g |= buffer[2] << 8;
	g |= buffer[3];
	b |= buffer[4] << 8;
	b |= buffer[5];
	printf("\tRed color is : %02x.\n", r);
	printf("\tGreen color is : %02x.\n", g);
	printf("\tBlue color is %02x.\n", b);
}

void pixelXY_handler(unsigned char* buffer, int len)
{
	printf("\tPixel per unit, X axis : %u.\n", getBigEndian(buffer));
	printf("\tPixel per unit, Y axis : %u.\n", getBigEndian(buffer + 4));
	printf("\tUnit specifier : %u.\n", (unsigned char)*(buffer + 8));
}

void palette_generator(unsigned char* buffer, int len)
{
	for (int i = 0; i < len; i += 3)
	{
		printf("%02x %02x %02x   ", (unsigned char)buffer[i], (unsigned char)buffer[i + 1], (unsigned char)buffer[i + 2]);
	}
}


// utility functions
bool validate_header(const unsigned char* buf)
{
	// Validate first 4 bytes of the header.
	return buf[0] == 0x89 && buf[1] == 'P' && buf[2] == 'N' && buf[3] == 'G';
}




uint32_t CRC_check(unsigned char* buf, int len)
{
	const uint32_t POLY = 0xEDB88320; // Straight copied
	const unsigned char* buffer = (const unsigned char*)buf;
	uint32_t crc = -1;

	while (len--)
	{
		crc = crc ^ *buffer++;
		for (int bit = 0; bit < 8; bit++)
		{
			if (crc & 1)
				crc = (crc >> 1) ^ POLY;
			else
				crc = (crc >> 1);
		}
	}
	return ~crc;
}

uint32_t adler32_checksum(const unsigned char* buffer, int len)
{
	const uint32_t adler_mod = 65521; // smallest prime less than 2^16-1
	uint16_t a = 1;
	uint16_t b = 0;
	for (int i = 0; i < len; ++i)
	{
		a = (a + *(buffer + i)) % adler_mod;
		b = (b + a) % adler_mod;
	}
	return (b << 16) | a;
}

unsigned char paethPredictor(unsigned char a, unsigned char b, unsigned char c)
{
	int p = a + b - c;
	int pa = abs(p - a);
	int pb = abs(p - b);
	int pc = abs(p - c);
	char pr;

	if (pa <= pb && pa <= pc)
		pr = a;
	else if (pb <= pc)
		pr = b;
	else
		pr = c;
	return pr;
}

void reverse_filter(Platform* p, const unsigned char* data, unsigned len, pngInfo* image_info)
{
	// Demo for only color_type 6 i.e true color with alpha channel
	if (!(image_info->color_type == 2 || image_info->color_type == 6))
	{
		image_info->count = 0;
		image_info->image_data = NULL;
		return;
	}

	int byteDepth; // For true color with alpha channel

	// Only these two types are implemented now. Some types need palette or bit manipulation. Will consider them a bit later
	if (image_info->color_type == 2)
		byteDepth = 3;
	else
		byteDepth = 4;

	unsigned char* prev_scanline = (unsigned char*)p->Alloc(sizeof(unsigned char) * image_info->image_width * byteDepth);
	for (unsigned int i = 0; i < image_info->image_width; ++i)
		prev_scanline[i] = 0;

	unsigned char* final_data = (unsigned char*)p->Alloc(sizeof(char) * image_info->image_width * image_info->image_height * byteDepth);
	unsigned char* original_data = final_data;

	const unsigned char* filter_data = data;

	unsigned char a = 0, b = 0, c = 0, x;
	int pos = 0;
	int line_byte = image_info->image_width * byteDepth;
	unsigned char ch;

	int count = 0;

	for (unsigned int height = 0; height < image_info->image_height; ++height)
	{
		ch = *filter_data;
		pos = 1;
		a = b = c = x = 0;
		for (int seek = 0; seek < line_byte; ++seek)
		{
			count++;
			if (pos <= byteDepth)
			{
				c = 0;
				a = 0;
			}
			else
			{
				c = prev_scanline[pos - byteDepth - 1];
				a = *(original_data - byteDepth);
			}
			b = prev_scanline[pos - 1];
			x = filter_data[pos];
			if (ch == 0)
				x = x;
			else if (ch == 1)
				x = x + a;
			else if (ch == 2)
				x = x + b;
			else if (ch == 3)
				x = x + average(a, b);
			else if (ch == 4)
				x = x + paethPredictor(a, b, c);
			else
			{
				fprintf(stderr, "Invalid filter type");
				image_info->image_data = NULL;
				image_info->count = 0;
				return;
			}
			pos++;
			*(original_data++) = x;
		}
		memcpy(prev_scanline, original_data - line_byte, line_byte);
		filter_data += line_byte + 1;
	}

	image_info->count = count;
	image_info->image_data = final_data;
	fprintf(stderr, "Total count here is %u.", count);
	p->Free(prev_scanline);
}


#define MAX_SIZE (10 * 1024 * 1024)
unsigned char* LoadPNGFile(Platform* p, const char* img_path, unsigned* width, unsigned* height, unsigned* no_of_channels, unsigned* bit_depth)
{
	FILE* image_file = NULL;

	// might review it later
#ifdef OS_WINDOWS
	int err = fopen_s(&image_file, img_path, "rb"); // This below double check seems redundant.
	if (err || !image_file)
		return NULL;
#else
	if (!(image_file = fopen(img_path, "rb")))
	{
		fprintf(stderr, "\nFailed to open %s.. Exiting..", img_path);
		return NULL;
	}
#endif 

	const struct handler handlers[] = {
		{"bKGD", background_handler},
		{"pHYs", pixelXY_handler},
		{"PLTE", palette_generator},
		{NULL, NULL} };

	// Allocate space and read from file
	unsigned char* buf = (unsigned char*)p->Alloc(sizeof(char) * MAX_SIZE);
	unsigned size = fread(buf, 1, MAX_SIZE, image_file);
	if (size == MAX_SIZE)
	{
		// Memory leak here
		fprintf(stderr, "Not enough memory allocated...");
		p->Free(buf);
		return NULL;
	}
	// Allocate buffer for deflate stream
	// This stream is formed by concatenating chunk of IDAT in a sequential manner
	unsigned char* deflate_stream = (unsigned char*)p->Alloc(sizeof(unsigned char) * MAX_SIZE);
	unsigned deflate_len = 0;

	validate_header(buf);
	pngInfo image_info;

	// Read the 4 byte length -> PNG use big-endian ordering while our system is little-endian

	int i = 0;
	// Advance stream to the 8th bit where header finished
	int pos = 8;
	unsigned int len = 0;

	while (1)
	{
		unsigned char lengthbuf[4];
		memcpy(lengthbuf, buf + pos, 4);

		char chunkbuf[5] = { '\0' };
		len = getBigEndian(lengthbuf);
		memcpy(chunkbuf, buf + pos + 4, 4);

		if (!strcmp(chunkbuf, "IHDR"))
		{
			header_handler(buf + pos + 8, len, &image_info);
		}
		else if (!strcmp(chunkbuf, "IDAT"))
		{
			memcpy(deflate_stream + deflate_len, (buf + pos + 8), len);
			deflate_len += len;
		}
		else
			for (int i = 0; handlers[i].type != NULL; ++i)
			{
				if (!strcmp(handlers[i].type, chunkbuf))
				{
					handlers[i].func(buf + pos + 8, len);
					break;
				}
			}

		if (!(CRC_check(buf + pos + 4, len + 4) == getBigEndian(buf + pos + 8 + len)))
		{
			fprintf(stderr, "Failed to verify CRC check...\n");
			return NULL;
		}

		pos += len + 12;
		if (!strcmp(chunkbuf, "IEND"))
			break;
	}

	// Time to decompress the deflate stream
	// skip first and second bytes and pass it to the deflate decompressor

	// Allocate space that will be used by the output uncompressed stream with max size SIZE
	unsigned char* decomp_data = (unsigned char*)p->Alloc(sizeof(unsigned char) * MAX_SIZE);
	unsigned decomp_len = MAX_SIZE;

	//// It decompresses the deflate stream, writes it into decomp_data and writes total length of output stram in decomp_len integer
	if (deflate(deflate_stream + 2, deflate_len, decomp_data, &decomp_len))
	{
		fprintf(stderr, "Failed the deflate decompression..");
		return NULL;
	}
	fprintf(stderr, "\nDecomped len is : %d.", decomp_len);
	// Apply adler32 checksum on the decomp_data and vertify it
	unsigned char* at_last = deflate_stream + deflate_len;
	uint32_t stored_adler32 = at_last[-4] << 24 | at_last[-3] << 16 | at_last[-2] << 8 | at_last[-1]; // :D :D
	uint32_t calc_adler32 = adler32_checksum(decomp_data, decomp_len);

	if (stored_adler32 != calc_adler32)
	{
		fprintf(stderr, "Adler32 check not passed i.e failed.\n");
		return NULL;
	}
	// Time to rewrite filter function
	// Its not a good function. It allocates memory hiddenly. And stores that memory in image_info->image_data
	reverse_filter(p, decomp_data, decomp_len, &image_info);

	// image_info have everything that is needed by other programs

	fclose(image_file);
	p->Free(buf);
	p->Free(deflate_stream);
	p->Free(decomp_data);

	// Fill in the parameters required values
	*width = image_info.image_width;
	*height = image_info.image_height;

	if (image_info.color_type == 2)
		*no_of_channels = 3;
	else if (image_info.color_type == 6)
		*no_of_channels = 4;
	else  // Not implemented other channels filtering
		*no_of_channels = 0;

	*bit_depth = image_info.image_bit_depth;
	return image_info.image_data;
}


// Lastly deflate algo .. This is quite large though

#define MAXBITS 15
#define MAXLCODES 286
#define MAXDCODES 30
#define MAXCODES 316
#define FIXLCODES 288

struct state
{
	unsigned char* input;
	unsigned curinput;
	unsigned totinput;
	unsigned char* output;
	unsigned curoutput;
	unsigned totoutput;
	unsigned bitbuf;
	unsigned bitcount;
};

static int uncompressed(struct state*);
static int dynamic(struct state*);
static int fixed(struct state*);
static int bits(struct state*, unsigned int);

struct huffman
{
	short* count; // number of symbols of each length
	short* symbol;
};

int codes(struct state* s, struct huffman*, struct huffman*);
// Used to create huffman table
int construct(struct huffman*, short*, int);

// decode binary code using generated huffman table
int decode(struct state*, struct huffman*);

int deflate(unsigned char* buffer, unsigned int inlen, unsigned char* out, unsigned* outlen)
{
	struct state s;
	s.input = buffer;
	s.totinput = inlen;
	s.curinput = 0;
	s.curoutput = 0;
	s.output = out;
	s.totoutput = *outlen;
	s.bitbuf = 0;
	s.bitcount = 0;
	int error_code = 0;
	int last_block;
	int compressed_type;
	do
	{
		last_block = bits(&s, 1);
		compressed_type = bits(&s, 2);

		if (compressed_type == 0)
			error_code = uncompressed(&s);
		else if (compressed_type == 1)
			error_code = fixed(&s); //
		else if (compressed_type == 2)
			error_code = dynamic(&s);
		else
		{
			error_code = -1;
			break;
		}

	} while (!last_block);

	if (error_code == 0)
		*outlen = s.curoutput;
	else
		*outlen = 0;
	return error_code;
}

int bits(struct state* s, unsigned int required)
{
	unsigned val;
	val = s->bitbuf;
	while (s->bitcount < required)
	{
		if (s->curinput >= s->totinput)
			return -1;
		val |= s->input[s->curinput++] << s->bitcount;
		s->bitcount += 8;
	}
	if (s->bitcount >= required)
	{
		s->bitbuf = val >> required;
	}
	else
	{
		return -2;
	}
	s->bitcount -= required;
	// printf("Curent bitcount is : %d.", s->bitcount);
	return val & ((1 << required) - 1);
}

int dynamic(struct state* s)
{
	int hlit, hdist, hclen;
	hlit = bits(s, 5) + 257;
	hdist = bits(s, 5) + 1;
	hclen = bits(s, 4) + 4;
	int index;
	short lengths[MAXCODES];
	short lencnt[MAXBITS + 1], lensym[MAXLCODES];
	short distcnt[MAXBITS + 1], distsym[MAXDCODES];

	struct huffman lencode, distcode;

	lencode.count = lencnt;
	lencode.symbol = lensym;
	distcode.count = distcnt;
	distcode.symbol = distsym;

	static const short order[19] =
	{ 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

	if (hlit > MAXLCODES || hdist > MAXDCODES)
		return -3; // bad counting

	for (index = 0; index < hclen; index++)
	{
		lengths[order[index]] = bits(s, 3);
	}
	for (; index < 19; index++)
	{
		lengths[order[index]] = 0;
	}
	// Run length codes
	// build huffman table for code lengths codes (use lencode temporarily)
	int err = construct(&lencode, lengths, 19);
	if (err)
		return -5;

	index = 0;
	while (index < hlit + hdist)
	{
		int symbol;
		symbol = decode(s, &lencode);
		if (symbol < 0)
			return symbol;
		if (symbol < 16)
			lengths[index++] = symbol;
		else
		{
			int len = 0;
			if (symbol == 16)
			{
				if (index == 0)
				{
					printf("NO previous code length .. .error...");
					return -11;
				}
				len = lengths[index - 1];
				symbol = 3 + bits(s, 2);
			}
			else if (symbol == 17)
			{
				symbol = 3 + bits(s, 3);
			}
			else if (symbol == 18)
			{
				symbol = 11 + bits(s, 7);
			}
			if (index + symbol > hdist + hlit)
			{
				return -6;
			}
			while (symbol--)
				lengths[index++] = len;
		}
	}

	err = construct(&lencode, lengths, hlit);
	if (err && (err < 0 || hlit != lencode.count[0] + lencode.count[1]))
	{
		printf("\nError -7.");
		return -7;
	}

	err = construct(&distcode, lengths + hlit, hdist);
	if (err && (err < 0 || hdist != distcode.count[0] + distcode.count[1]))
	{
		printf("\nErrorr -8..");
		return -8;
	}

	return codes(s, &lencode, &distcode);
}

int construct(struct huffman* h, short* length, int n)
{
	// Counter each number of symbol
	int left;
	for (int i = 0; i <= MAXBITS; ++i)
		h->count[i] = 0;

	for (int i = 0; i < n; ++i)
		h->count[length[i]]++;

	// Something like integiry check with huffman coded data
	left = 1;
	for (int i = 1; i <= MAXBITS; ++i)
	{
		left <<= 1;
		left -= h->count[i];
		if (left < 0)
			return left;
	}

	// if (!left)
	//    printf("Integrity passed.\n");

	short offs[MAXBITS + 1];
	offs[1] = 0;

	for (int i = 1; i < MAXBITS; ++i)
		offs[i + 1] = offs[i] + h->count[i];

	for (int i = 0; i < n; ++i)
		h->symbol[i] = -1;

	for (int symbol = 0; symbol < n; ++symbol)
		if (length[symbol])
			h->symbol[offs[length[symbol]]++] = symbol;

	// This function keeps the length in cannonical (or deflate stated form.);
	return 0;
}

// Since we are going to read huffman code, we have to read in bit reversed method

int decode(struct state* s, struct huffman* h)
{
	int count;
	int index;
	int code;
	int first;
	count = index = code = first = 0;

	for (int len = 1; len <= MAXBITS; ++len)
	{
		code |= bits(s, 1);
		count = h->count[len];
		if (code - count < first)
			return h->symbol[index + (code - first)];
		first += count; // Count the total number of smaller code lengths
		index += count;
		first <<= 1;
		code <<= 1;
	}
	return -2;
}

int codes(struct state* s, struct huffman* lencode, struct huffman* distcode)
{
	const short lenadd[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35,
							43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258 };
	const short extrabit[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
							  4, 4, 4, 4, 5, 5, 5, 5, 0 };

	const short distadd[] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769,
							 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577 };

	const short distextra[] = { 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8,
							   9, 9, 10, 10, 11, 11, 12, 12, 13, 13 };

	int symbol, len;
	int dist;
	do
	{
		symbol = decode(s, lencode);
		if (symbol < 0)
			return symbol;
		if (symbol < 256)
		{
			if (s->output != NULL)
			{
				if (s->curoutput > s->totoutput)
					return 1;
				s->output[s->curoutput] = symbol;
			}
			s->curoutput++;
		}
		else if (symbol > 256)
		{
			int extra = symbol - 257;
			if (extra >= 29)
				return -10;
			len = lenadd[extra] + bits(s, extrabit[extra]);
			if (len > 258)
			{
				printf("Error in back traversing length...");
				return -23;
			}
			// check distance
			symbol = decode(s, distcode);
			if (symbol < 0)
				return symbol;
			if (symbol > 29)
				return -22;
			int k;
			k = bits(s, distextra[symbol]);
			dist = distadd[symbol] + k;

			if (s->output != NULL)
			{
				if (s->curinput + len > s->totoutput)
					return 1;
				while (len--)
				{
					s->output[s->curoutput] = s->output[s->curoutput - dist];
					s->curoutput++;
				}
			}
			else
			{
				s->curoutput += len;
			}
		}
	} while (symbol != 256);

	// done with valid dynamic block
	return 0;
}

int uncompressed(struct state* s)
{
	s->bitcount = 0;
	s->bitbuf = 0;
	/** |       |       |                       |
	 *  |len    | nlen  |   uncompressed data   |
	 *  |       |       |                       |
	 **/
	if (s->curinput + 4 > s->totinput)
		return 2;

	int len = s->input[s->curinput++];
	len |= s->input[s->curinput++] << 8;

	int nlen = s->input[s->curinput++];
	nlen |= s->input[s->curinput++] << 8;

	if ((len & 0xFFFF) == (~nlen & 0xFFFF))
		printf("Uncompressed data verified.\n");
	else
	{
		printf("Unverified uncompressed data.\n");
	}
	while (len--)
	{
		s->output[s->curoutput++] = s->input[s->curinput++];
	}

	return 0;
}

int fixed(struct state* s)
{
	static int first = 1;
	short lengths[MAXCODES];
	struct huffman lencode, distcode;
	short lencnt[MAXBITS + 1], lensym[FIXLCODES];
	short distcnt[MAXBITS + 1], distsym[MAXDCODES];
	lencode.count = lencnt;
	lencode.symbol = lensym;
	distcode.count = distcnt;
	distcode.symbol = distsym;
	if (1)
	{
		for (int i = 0; i <= 143; ++i)
			lengths[i] = 8;
		for (int i = 144; i <= 255; ++i)
			lengths[i] = 9;
		for (int i = 256; i <= 279; ++i)
			lengths[i] = 7;
		for (int i = 280; i <= 287; ++i)
			lengths[i] = 8;
		first = 0;
	}
	construct(&lencode, lengths, FIXLCODES);

	for (int i = 0; i < MAXDCODES; ++i)
		lengths[i] = 5;

	construct(&distcode, lengths, MAXDCODES);
	return codes(s, &lencode, &distcode);
}

//
// End Utils
//


//
// Platform
//

bool PlatformOnLoadStub(Platform *) {
	return true;
}

void PlatformFixedUpdateStub(Platform *, float dt) {

}

void PlatformUpdateAndRenderStub(Platform *, float dt, float alpha) {

}

void PlatformOnWindowResizeStub(Platform *, uint32_t w, uint32_t h) {

}

//
// Begin Platform: OpenGL
//

#ifndef __khrplatform_h_
#define __khrplatform_h_

/*
** Copyright (c) 2008-2018 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Khronos platform-specific types and definitions.
 *
 * The master copy of khrplatform.h is maintained in the Khronos EGL
 * Registry repository at https://github.com/KhronosGroup/EGL-Registry
 * The last semantic modification to khrplatform.h was at commit ID:
 *      67a3e0864c2d75ea5287b9f3d2eb74a745936692
 *
 * Adopters may modify this file to suit their platform. Adopters are
 * encouraged to submit platform specific modifications to the Khronos
 * group so that they can be included in future versions of this file.
 * Please submit changes by filing pull requests or issues on
 * the EGL Registry repository linked above.
 *
 *
 * See the Implementer's Guidelines for information about where this file
 * should be located on your system and for more details of its use:
 *    http://www.khronos.org/registry/implementers_guide.pdf
 *
 * This file should be included as
 *        #include <KHR/khrplatform.h>
 * by Khronos client API header files that use its types and defines.
 *
 * The types in khrplatform.h should only be used to define API-specific types.
 *
 * Types defined in khrplatform.h:
 *    khronos_int8_t              signed   8  bit
 *    khronos_uint8_t             unsigned 8  bit
 *    khronos_int16_t             signed   16 bit
 *    khronos_uint16_t            unsigned 16 bit
 *    khronos_int32_t             signed   32 bit
 *    khronos_uint32_t            unsigned 32 bit
 *    khronos_int64_t             signed   64 bit
 *    khronos_uint64_t            unsigned 64 bit
 *    khronos_intptr_t            signed   same number of bits as a pointer
 *    khronos_uintptr_t           unsigned same number of bits as a pointer
 *    khronos_ssize_t             signed   size
 *    khronos_usize_t             unsigned size
 *    khronos_float_t             signed   32 bit floating point
 *    khronos_time_ns_t           unsigned 64 bit time in nanoseconds
 *    khronos_utime_nanoseconds_t unsigned time interval or absolute time in
 *                                         nanoseconds
 *    khronos_stime_nanoseconds_t signed time interval in nanoseconds
 *    khronos_boolean_enum_t      enumerated boolean type. This should
 *      only be used as a base type when a client API's boolean type is
 *      an enum. Client APIs which use an integer or other type for
 *      booleans cannot use this as the base type for their boolean.
 *
 * Tokens defined in khrplatform.h:
 *
 *    KHRONOS_FALSE, KHRONOS_TRUE Enumerated boolean false/true values.
 *
 *    KHRONOS_SUPPORT_INT64 is 1 if 64 bit integers are supported; otherwise 0.
 *    KHRONOS_SUPPORT_FLOAT is 1 if floats are supported; otherwise 0.
 *
 * Calling convention macros defined in this file:
 *    KHRONOS_APICALL
 *    KHRONOS_APIENTRY
 *    KHRONOS_APIATTRIBUTES
 *
 * These may be used in function prototypes as:
 *
 *      KHRONOS_APICALL void KHRONOS_APIENTRY funcname(
 *                                  int arg1,
 *                                  int arg2) KHRONOS_APIATTRIBUTES;
 */

#if defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#endif

 /*-------------------------------------------------------------------------
  * Definition of KHRONOS_APICALL
  *-------------------------------------------------------------------------
  * This precedes the return type of the function in the function prototype.
  */
#if defined(KHRONOS_STATIC)
  /* If the preprocessor constant KHRONOS_STATIC is defined, make the
   * header compatible with static linking. */
#   define KHRONOS_APICALL
#elif defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#elif defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#else
#   define KHRONOS_APICALL
#endif

  /*-------------------------------------------------------------------------
   * Definition of KHRONOS_APIENTRY
   *-------------------------------------------------------------------------
   * This follows the return type of the function  and precedes the function
   * name in the function prototype.
   */
#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
   /* Win32 but not WinCE */
#   define KHRONOS_APIENTRY __stdcall
#else
#   define KHRONOS_APIENTRY
#endif

   /*-------------------------------------------------------------------------
	* Definition of KHRONOS_APIATTRIBUTES
	*-------------------------------------------------------------------------
	* This follows the closing parenthesis of the function prototype arguments.
	*/
#if defined (__ARMCC_2__)
#define KHRONOS_APIATTRIBUTES __softfp
#else
#define KHRONOS_APIATTRIBUTES
#endif

	/*-------------------------------------------------------------------------
	 * basic type definitions
	 *-----------------------------------------------------------------------*/
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


	 /*
	  * Using <stdint.h>
	  */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__VMS ) || defined(__sgi)

	 /*
	  * Using <inttypes.h>
	  */
#include <inttypes.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)

	 /*
	  * Win32
	  */
typedef __int32                 khronos_int32_t;
typedef unsigned __int32        khronos_uint32_t;
typedef __int64                 khronos_int64_t;
typedef unsigned __int64        khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__sun__) || defined(__digital__)

	 /*
	  * Sun or Digital
	  */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#if defined(__arch64__) || defined(_LP64)
typedef long int                khronos_int64_t;
typedef unsigned long int       khronos_uint64_t;
#else
typedef long long int           khronos_int64_t;
typedef unsigned long long int  khronos_uint64_t;
#endif /* __arch64__ */
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif 0

	 /*
	  * Hypothetical platform with no float or int64 support
	  */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#define KHRONOS_SUPPORT_INT64   0
#define KHRONOS_SUPPORT_FLOAT   0

#else

	 /*
	  * Generic fallback
	  */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#endif


/*
 * Types that are (so far) the same on all platforms
 */
typedef signed   char          khronos_int8_t;
typedef unsigned char          khronos_uint8_t;
typedef signed   short int     khronos_int16_t;
typedef unsigned short int     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#ifdef _WIN64
typedef signed   long long int khronos_intptr_t;
typedef unsigned long long int khronos_uintptr_t;
typedef signed   long long int khronos_ssize_t;
typedef unsigned long long int khronos_usize_t;
#else
typedef signed   long  int     khronos_intptr_t;
typedef unsigned long  int     khronos_uintptr_t;
typedef signed   long  int     khronos_ssize_t;
typedef unsigned long  int     khronos_usize_t;
#endif

#if KHRONOS_SUPPORT_FLOAT
/*
 * Float type
 */
typedef          float         khronos_float_t;
#endif

#if KHRONOS_SUPPORT_INT64
/* Time types
 *
 * These types can be used to represent a time interval in nanoseconds or
 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
 * of nanoseconds since some arbitrary system event (e.g. since the last
 * time the system booted).  The Unadjusted System Time is an unsigned
 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
 * may be either signed or unsigned.
 */
typedef khronos_uint64_t       khronos_utime_nanoseconds_t;
typedef khronos_int64_t        khronos_stime_nanoseconds_t;
#endif

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

 /*
  * Enumerated boolean type
  *
  * Values other than zero should be considered to be true.  Therefore
  * comparisons should not be made against KHRONOS_TRUE.
  */
typedef enum {
	KHRONOS_FALSE = 0,
	KHRONOS_TRUE = 1,
	KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

#endif /* __khrplatform_h_ */

#ifndef __gl_glcorearb_h_
#define __gl_glcorearb_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

	/*
	** Copyright 2013-2020 The Khronos Group Inc.
	** SPDX-License-Identifier: MIT
	**
	** This header is generated from the Khronos OpenGL / OpenGL ES XML
	** API Registry. The current version of the Registry, generator scripts
	** used to make the header, and the header can be found at
	**   https://github.com/KhronosGroup/OpenGL-Registry
	*/

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

	/* glcorearb.h is for use with OpenGL core profile implementations.
	** It should should be placed in the same directory as gl.h and
	** included as <GL/glcorearb.h>.
	**
	** glcorearb.h includes only APIs in the latest OpenGL core profile
	** implementation together with APIs in newer ARB extensions which
	** can be supported by the core profile. It does not, and never will
	** include functionality removed from the core profile, such as
	** fixed-function vertex and fragment processing.
	**
	** Do not #include both <GL/glcorearb.h> and either of <GL/gl.h> or
	** <GL/glext.h> in the same source file.
	*/

	/* Generated C header for:
	 * API: gl
	 * Profile: core
	 * Versions considered: .*
	 * Versions emitted: .*
	 * Default extensions included: glcore
	 * Additional extensions included: _nomatch_^
	 * Extensions removed: _nomatch_^
	 */

	typedef void GLvoid;
	typedef unsigned int GLenum;
	typedef khronos_float_t GLfloat;
	typedef int GLint;
	typedef int GLsizei;
	typedef unsigned int GLbitfield;
	typedef double GLdouble;
	typedef unsigned int GLuint;
	typedef unsigned char GLboolean;
	typedef khronos_uint8_t GLubyte;
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_VIEWPORT                       0x0BA2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F
#define GL_TEXTURE                        0x1702
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_REPEAT                         0x2901

#ifndef GL_VERSION_1_5
#define GL_VERSION_1_5 1
	typedef khronos_ssize_t GLsizeiptr;
	typedef khronos_intptr_t GLintptr;
#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765
#define GL_QUERY_COUNTER_BITS             0x8864
#define GL_CURRENT_QUERY                  0x8865
#define GL_QUERY_RESULT                   0x8866
#define GL_QUERY_RESULT_AVAILABLE         0x8867
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_BUFFER_ACCESS                  0x88BB
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_SAMPLES_PASSED                 0x8914
#define GL_SRC1_ALPHA                     0x8589
#endif

#ifndef GL_VERSION_2_0
#define GL_VERSION_2_0 1
	typedef char GLchar;
	typedef khronos_int16_t GLshort;
	typedef khronos_int8_t GLbyte;
	typedef khronos_uint16_t GLushort;
#define GL_BLEND_EQUATION_RGB             0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_MAX_VARYING_FLOATS             0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE                    0x8B4F
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_SAMPLER_1D_SHADOW              0x8B61
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_DELETE_STATUS                  0x8B80
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN      0x8CA0
#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
#endif

#ifndef GL_VERSION_1_3
#define GL_VERSION_1_3 1
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_CLAMP_TO_BORDER                0x812D
#endif

	typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
	typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
	typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
	typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
	typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
	typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
	typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
	typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
	typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
	typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
	typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
	typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
	typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
	typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
	typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
	typedef GLuint(APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
	typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
	typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
	typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
	typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
	typedef GLuint(APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
	typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
	typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
	typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
	typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
	typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
	typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
	typedef GLint(APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
	typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
	typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
	typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum cap);
	typedef void (APIENTRYP PFNGLGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
	typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
	typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
	typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
	typedef GLenum(APIENTRYP PFNGLGETERRORPROC) (void);

#ifdef __cplusplus
}
#endif

#endif

typedef void *(*GLLoader)(const char *name);

static PFNGLCLEARCOLORPROC glClearColor;
static PFNGLCLEARPROC glClear;
static PFNGLVIEWPORTPROC glViewport;
static PFNGLSCISSORPROC glScissor;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
static PFNGLBINDBUFFERPROC glBindBuffer;
static PFNGLBUFFERDATAPROC glBufferData;
static PFNGLGENTEXTURESPROC glGenTextures;
static PFNGLBINDTEXTUREPROC glBindTexture;
static PFNGLDELETETEXTURESPROC glDeleteTextures;
static PFNGLTEXIMAGE2DPROC glTexImage2D;
static PFNGLTEXPARAMETERIPROC glTexParameteri;
static PFNGLCREATESHADERPROC glCreateShader;
static PFNGLSHADERSOURCEPROC glShaderSource;
static PFNGLCOMPILESHADERPROC glCompileShader;
static PFNGLGETSHADERIVPROC glGetShaderiv;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
static PFNGLCREATEPROGRAMPROC glCreateProgram;
static PFNGLATTACHSHADERPROC glAttachShader;
static PFNGLLINKPROGRAMPROC glLinkProgram;
static PFNGLDELETEPROGRAMPROC glDeleteProgram;
static PFNGLDELETESHADERPROC glDeleteShader;
static PFNGLGETPROGRAMIVPROC glGetProgramiv;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
static PFNGLBUFFERSUBDATAPROC glBufferSubData;
static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLENABLEPROC glEnable;
static PFNGLGLBLENDFUNCPROC glBlendFunc;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
static PFNGLUNIFORM1IPROC glUniform1i;
static PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;
static PFNGLGETERRORPROC glGetError;
static PFNGLACTIVETEXTUREPROC glActiveTexture;

bool LoadOpenGLFunctions(GLLoader load) {
#define GL_LOAD_FUNC(name, type)	name  = (type)load(#name); if (!name) return false

	GL_LOAD_FUNC(glClearColor, PFNGLCLEARCOLORPROC);
	GL_LOAD_FUNC(glClear, PFNGLCLEARPROC);
	GL_LOAD_FUNC(glViewport, PFNGLVIEWPORTPROC);
	GL_LOAD_FUNC(glScissor, PFNGLSCISSORPROC);
	GL_LOAD_FUNC(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC);
	GL_LOAD_FUNC(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC);
	GL_LOAD_FUNC(glGenBuffers, PFNGLGENBUFFERSPROC);
	GL_LOAD_FUNC(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
	GL_LOAD_FUNC(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC);
	GL_LOAD_FUNC(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC);
	GL_LOAD_FUNC(glBindBuffer, PFNGLBINDBUFFERPROC);
	GL_LOAD_FUNC(glBufferData, PFNGLBUFFERDATAPROC);
	GL_LOAD_FUNC(glGenTextures, PFNGLGENTEXTURESPROC);
	GL_LOAD_FUNC(glBindTexture, PFNGLBINDTEXTUREPROC);
	GL_LOAD_FUNC(glDeleteTextures, PFNGLDELETETEXTURESPROC);
	GL_LOAD_FUNC(glTexImage2D, PFNGLTEXIMAGE2DPROC);
	GL_LOAD_FUNC(glTexParameteri, PFNGLTEXPARAMETERIPROC);
	GL_LOAD_FUNC(glCreateShader, PFNGLCREATESHADERPROC);
	GL_LOAD_FUNC(glShaderSource, PFNGLSHADERSOURCEPROC);
	GL_LOAD_FUNC(glCompileShader, PFNGLCOMPILESHADERPROC);
	GL_LOAD_FUNC(glGetShaderiv, PFNGLGETSHADERIVPROC);
	GL_LOAD_FUNC(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
	GL_LOAD_FUNC(glCreateProgram, PFNGLCREATEPROGRAMPROC);
	GL_LOAD_FUNC(glAttachShader, PFNGLATTACHSHADERPROC);
	GL_LOAD_FUNC(glLinkProgram, PFNGLLINKPROGRAMPROC);
	GL_LOAD_FUNC(glDeleteProgram, PFNGLDELETEPROGRAMPROC);
	GL_LOAD_FUNC(glDeleteShader, PFNGLDELETESHADERPROC);
	GL_LOAD_FUNC(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
	GL_LOAD_FUNC(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);
	GL_LOAD_FUNC(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
	GL_LOAD_FUNC(glBufferSubData, PFNGLBUFFERSUBDATAPROC);
	GL_LOAD_FUNC(glUseProgram, PFNGLUSEPROGRAMPROC);
	GL_LOAD_FUNC(glEnable, PFNGLENABLEPROC);
	GL_LOAD_FUNC(glBlendFunc, PFNGLGLBLENDFUNCPROC);
	GL_LOAD_FUNC(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
	GL_LOAD_FUNC(glUniform1i, PFNGLUNIFORM1IPROC);
	GL_LOAD_FUNC(glDrawElementsBaseVertex, PFNGLDRAWELEMENTSBASEVERTEXPROC);
	GL_LOAD_FUNC(glActiveTexture, PFNGLACTIVETEXTUREPROC);
	GL_LOAD_FUNC(glGetError, PFNGLGETERRORPROC);

#undef GL_LOAD_FUNC

	return true;
}

//
//
//

static const char *g_GLSLVertexShader = R"Foo(
#version 410 core
layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec4 VertexColor;

uniform mat4 Projection;

out vec2 TexCoord;
out vec4 Color;

void main() {
	TexCoord = VertexTexCoord;
	Color = VertexColor;
	gl_Position = Projection * vec4(VertexPosition, 0, 1);
}
)Foo";

static const char *g_GLSLFragmentShader = R"Foo(
#version 410 core
out vec4 PixelColor;

in vec2 TexCoord;
in vec4 Color;

uniform sampler2D TexImage;

void main() {
	vec4 sampled = texture(TexImage, TexCoord);
	PixelColor = sampled * Color;
}
)Foo";

struct ImplOpenGL {
	GLuint VertexArrayObject;
	GLuint VertexBufferId;
	GLuint IndexBufferId;

	GLuint ShaderId;
	GLint ProjectionLocation;
	GLint TexImageLocation;
};

static ImplOpenGL g_OpenGL;

uint32_t CreateTexture(uint8_t *pixels, uint32_t width, uint32_t height, uint32_t channels) {
	GLenum gl_format;
	GLint gl_internal_format;

	switch (channels) {
		case 1:
		case 2:
		return 0;
		break;

		case 3:
		gl_format = GL_RGB;
		gl_internal_format = GL_RGB;
		break;

		case 4:
		gl_format = GL_RGBA;
		gl_internal_format = GL_RGBA;
		break;
	}

	GLuint texid;
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, gl_internal_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texid;
}

void DestroyTexture(uint32_t tex) {
	glDeleteTextures(1, &tex);
}

uint32_t CreateTextureFromFile(Platform *platform, const char *file) {
	int w, h;
	uint8_t *pixels = LoadBMPFromFile(platform, file, &w, &h);

	uint32_t t = CreateTexture(pixels, (uint32_t)w, (uint32_t)h, 4);
	platform->Free(pixels);
	return t;
}

uint32_t CreateShader(Platform *platform, const char *src, GLenum type) {
	GLuint shaderid = glCreateShader(type);

	glShaderSource(shaderid, 1, &src, nullptr);

	glCompileShader(shaderid);

	GLint compiled;
	glGetShaderiv(shaderid, GL_COMPILE_STATUS, &compiled);
	if (compiled != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar  message[2048];
		glGetShaderInfoLog(shaderid, 2048, &log_length, message);
		const char *shader_type_name = "-unknown-";
		if (type == GL_VERTEX_SHADER)
			shader_type_name = "Vertex";
		else if (type == GL_FRAGMENT_SHADER)
			shader_type_name = "Fragment";

		platform->Log("OpenGL %s Shader compilation failed: %s", shader_type_name, message);
	}

	return shaderid;
}

uint32_t CreateShaderProgram(Platform *platform, const char *vertex, const char *fragment) {
	uint32_t v = CreateShader(platform, vertex, GL_VERTEX_SHADER);
	uint32_t f = CreateShader(platform, fragment, GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, v);
	glAttachShader(program, f);
	glLinkProgram(program);

	glDeleteShader(v);
	glDeleteShader(f);

	GLint program_linked;
	glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar  message[2048];
		glGetProgramInfoLog(program, 2048, &log_length, message);
		platform->Log("OpenGL Shader program link failed (%s) in pipeline %s", message);
		glDeleteProgram(program);
		return 0;
	}

	return program;
}

void DestroyShaderProgram(uint32_t program) {
	glDeleteProgram(program);
}

void ImplOpenGLInitializeRenderer2D(Platform *platform) {
	if (!InitializeRenderer2D(platform)) {
		platform->FatalError("Failed to Initialize Renderer2D");
	}

	glGenVertexArrays(1, &g_OpenGL.VertexArrayObject);
	glGenBuffers(1, &g_OpenGL.VertexBufferId);
	glGenBuffers(1, &g_OpenGL.IndexBufferId);

	glBindVertexArray(g_OpenGL.VertexArrayObject);

	GLsizeiptr vertex_buffer_size = (char *)g_RendererContext.Vertex.Last - (char *)g_RendererContext.Vertex.Pointer;
	GLsizeiptr index_buffer_size = (char *)g_RendererContext.Index.Last - (char *)g_RendererContext.Index.Pointer;

	glBindBuffer(GL_ARRAY_BUFFER, g_OpenGL.VertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_OpenGL.IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)(offsetof(Vertex2D, Position)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)(offsetof(Vertex2D, TexCoord)));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)(offsetof(Vertex2D, Color)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	g_OpenGL.ShaderId = CreateShaderProgram(platform, g_GLSLVertexShader, g_GLSLFragmentShader);
	g_OpenGL.ProjectionLocation = glGetUniformLocation(g_OpenGL.ShaderId, "Projection");
	g_OpenGL.TexImageLocation = glGetUniformLocation(g_OpenGL.ShaderId, "TexImage");

	uint8_t pixels[] = { 0xff, 0xff, 0xff, 0xff };
	uint32_t tex = CreateTexture(pixels, 1, 1, 4);
	if (tex == 0) {
		platform->FatalError("Failed to create texture");
	}
	SetDefaultTexture(tex);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_SCISSOR_TEST);
}

void ImplOpenGLFrameRenderer2D(float w, float h) {
	FrameRenderer2D(Rect(0, 0, w, h));
}

void ImplOpenGLRender() {
	GLint x = (GLint)g_RendererContext.ClipRect.Min.x;
	GLint y = (GLint)g_RendererContext.ClipRect.Min.y;
	GLsizei w = (GLsizei)(g_RendererContext.ClipRect.Max.x - g_RendererContext.ClipRect.Min.x);
	GLsizei h = (GLsizei)(g_RendererContext.ClipRect.Max.y - g_RendererContext.ClipRect.Min.y);

	glViewport(x, y, w, h);
	glScissor(x, y, w, h);

	Vec4 c = GetClearColor();
	glClearColor(c.x, c.y, c.z, c.w);
	glClear(GL_COLOR_BUFFER_BIT);

	auto data = GetDraw2DBufferView();
	if (data.VertexBufferSize && data.IndexBufferSize) {
		glBindVertexArray(g_OpenGL.VertexArrayObject);

		glBindBuffer(GL_ARRAY_BUFFER, g_OpenGL.VertexBufferId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data.VertexBufferSize, data.VertexBufferPtr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_OpenGL.IndexBufferId);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data.IndexBufferSize, data.IndexBufferPtr);

		glUseProgram(g_OpenGL.ShaderId);

		auto queue = GetDraw2DListQueue();

		for (auto &cmd_list : queue) {
			glUniformMatrix4fv(g_OpenGL.ProjectionLocation, 1, GL_TRUE, cmd_list.ViewTransform.m);

			DrawCmd2D *cmd = cmd_list.Cmds;
			uint32_t   count = cmd_list.CmdCount;
			for (uint32_t index = 0; index < count; ++index, ++cmd) {
				x = (GLint)cmd->ClipRect.Min.x;
				y = (GLint)cmd->ClipRect.Min.y;
				w = (GLsizei)(cmd->ClipRect.Max.x - cmd->ClipRect.Min.x);
				h = (GLsizei)(cmd->ClipRect.Max.y - cmd->ClipRect.Min.y);

				glScissor(x, y, w, h);
				glBindTexture(GL_TEXTURE_2D, cmd->Texture);
				glActiveTexture(GL_TEXTURE0);
				glUniform1i(g_OpenGL.TexImageLocation, 0);

				glDrawElementsBaseVertex(GL_TRIANGLES, cmd->IndexCount, GL_UNSIGNED_INT,
										 (void *)(cmd->IndexOffset * sizeof(GLuint)), (GLint)cmd->VertexOffset);
			}
		}
	}
}

//
// End Platform: OpenGL
//

//
// Begin Platform: Windows
//

#if defined(OS_WINDOWS)
#include <Windows.h>
#include <windowsx.h>
#include <avrt.h>
#include <wingdi.h>

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Avrt.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "shell32.lib")

static WINDOWPLACEMENT g_WindowPlacement;
static Platform g_Platform;

static constexpr int WINDOWS_MAX_KEYS = 256;
static Key           g_WindowsKeyMap[WINDOWS_MAX_KEYS]; // This number should be enough

typedef PROC(APIENTRY WGLGetProcAddress)(LPCSTR arg);
typedef HGLRC(APIENTRY WGLCreateContextFunc)(HDC arg);
typedef BOOL(APIENTRY WGLMakeCurrent)(HDC, HGLRC);
typedef BOOL(APIENTRY WGLDeleteContext)(HGLRC arg);

static HDC					    g_WindowDC;
static HMODULE				    g_OpenGLModule;
static WGLGetProcAddress *g_WGLGetProcAddress;
static WGLCreateContextFunc *g_WGLCreateContext;
static WGLMakeCurrent *g_WGLMakeCurrent;
static WGLDeleteContext *g_WGLDeleteContext;

static int (APIENTRY *g_OpenGLSetSwapInterval)(int interval);
static int (APIENTRY *g_OpenGLGetSwapInterval)();

static constexpr int WGL_DRAW_TO_WINDOW_ARB = 0x2001;
static constexpr int WGL_SUPPORT_OPENGL_ARB = 0x2010;
static constexpr int WGL_DOUBLE_BUFFER_ARB = 0x2011;
static constexpr int WGL_PIXEL_TYPE_ARB = 0x2013;
static constexpr int WGL_TYPE_RGBA_ARB = 0x202B;
static constexpr int WGL_COLOR_BITS_ARB = 0x2014;
static constexpr int WGL_DEPTH_BITS_ARB = 0x2022;
static constexpr int WGL_STENCIL_BITS_ARB = 0x2023;
static constexpr int WGL_CONTEXT_MAJOR_VERSION_ARB = 0x2091;
static constexpr int WGL_CONTEXT_MINOR_VERSION_ARB = 0x2092;
static constexpr int WGL_CONTEXT_LAYER_PLANE_ARB = 0x2093;
static constexpr int WGL_CONTEXT_FLAGS_ARB = 0x2094;
static constexpr int WGL_CONTEXT_PROFILE_MASK_ARB = 0x9126;
static constexpr int WGL_CONTEXT_DEBUG_BIT_ARB = 0x0001;
static constexpr int WGL_SAMPLE_BUFFERS_ARB = 0x2041;
static constexpr int WGL_SAMPLES_ARB = 0x2042;
static constexpr int WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB = 0x20A9;
static constexpr int WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 0x0001;

static void *WindowsOpenGLGetProcAddress(const char *name) {
	void *result = NULL;
	result = g_WGLGetProcAddress(name);
	if (result == NULL) {
		result = (void *)GetProcAddress(g_OpenGLModule, name);
	}
	return result;
}

void LoadOpenGL(HWND window_handle) {
	g_OpenGLModule = LoadLibraryW(L"opengl32.dll");
	if (!g_OpenGLModule) {
		FatalAppExitW(0, L"Failed to Load OpenGL Library");
	}
	Defer{ FreeLibrary(g_OpenGLModule); };

	WNDCLASSEXW wnd_class = {};
	wnd_class.cbSize = sizeof(wnd_class);
	wnd_class.style = CS_HREDRAW | CS_VREDRAW;
	wnd_class.lpfnWndProc = DefWindowProcW;
	wnd_class.hInstance = GetModuleHandleW(0);
	wnd_class.lpszClassName = L"OpenGLDummyWindow";
	RegisterClassExW(&wnd_class);
	Defer{ UnregisterClassW(L"OpenGLDummyWindow", GetModuleHandleW(0)); };

	HWND dummy_wnd = CreateWindowExW(0, L"OpenGLDummyWindow", L"OpenGLDummyWindow", 0,
									 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
									 0, 0, GetModuleHandleW(0), 0);
	if (!dummy_wnd) {
		FatalAppExitW(0, L"Failed to Create Window");
	}
	HDC dummy_dc = GetDC(dummy_wnd);
	Defer{ ReleaseDC(dummy_wnd, dummy_dc); DestroyWindow(dummy_wnd); };

	PIXELFORMATDESCRIPTOR dummy_pixel_format = {};
	dummy_pixel_format.nSize = sizeof(dummy_pixel_format);
	dummy_pixel_format.nVersion = 1;
	dummy_pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	dummy_pixel_format.iPixelType = PFD_TYPE_RGBA;
	dummy_pixel_format.cColorBits = 32;
	dummy_pixel_format.cDepthBits = 24;
	dummy_pixel_format.cStencilBits = 8;
	int pfi = ChoosePixelFormat(dummy_dc, &dummy_pixel_format);
	if (pfi == 0) {
		FatalAppExitW(0, L"Unsupported pixel format for dummy window. OpenGL Context creation failed");
	}

	PIXELFORMATDESCRIPTOR suggested_pixel_format;
	int                   num_pixel_fmts = DescribePixelFormat(dummy_dc, pfi, sizeof(suggested_pixel_format), &suggested_pixel_format);
	if (num_pixel_fmts == 0) {
		FatalAppExitW(0, L"OpenGL Pixel formats could not be described for dummy window");
	}

	if (!SetPixelFormat(dummy_dc, pfi, &suggested_pixel_format)) {
		FatalAppExitW(0, L"OpenGL Pixel formats could not be set for dummy window");
	}

	g_WGLCreateContext = (WGLCreateContextFunc *)GetProcAddress(g_OpenGLModule, "wglCreateContext");
	if (!g_WGLCreateContext) {
		FatalAppExitW(0, L"wglCreateContext not found in OpenGL module");
	}
	g_WGLMakeCurrent = (WGLMakeCurrent *)GetProcAddress(g_OpenGLModule, "wglMakeCurrent");
	if (!g_WGLMakeCurrent) {
		FatalAppExitW(0, L"wglMakeCurrent not found in OpenGL module");
	}
	g_WGLGetProcAddress = (WGLGetProcAddress *)GetProcAddress(g_OpenGLModule, "wglGetProcAddress");
	if (!g_WGLGetProcAddress) {
		FatalAppExitW(0, L"wglGetProcAddress not found in OpenGL module");
	}
	g_WGLDeleteContext = (WGLDeleteContext *)GetProcAddress(g_OpenGLModule, "wglDeleteContext");
	if (!g_WGLDeleteContext) {
		FatalAppExitW(0, L"wglDeleteContext not found in OpenGL module");
	}

	HGLRC dummy_gl_context = g_WGLCreateContext(dummy_dc);
	if (!dummy_gl_context) {
		FatalAppExitW(0, L"OpenGL dummy context could not be created");
	}

	if (!g_WGLMakeCurrent(dummy_dc, dummy_gl_context)) {
		FatalAppExitW(0, L"OpenGL dummy context could not be used");
	}

	typedef HGLRC WINAPI            WGLCreateContextAttribsARBFunc(HDC hdc, HGLRC hShareContext, const int *attribList);
	WGLCreateContextAttribsARBFunc *wgl_create_context_attribs_arb;
	typedef BOOL WINAPI             WGLChoosePixelFormatARBFunc(HDC hdc, const int *piAttribIList, const float *pfAttribFList, uint32_t nMaxFormats, int *piFormats, uint32_t *nNumFormats);
	WGLChoosePixelFormatARBFunc *wgl_choose_pixel_format_arb;
	typedef BOOL(APIENTRY WGLSwapIntervalEXTFunc)(int interval);
	typedef int(APIENTRY WGLGetSwapIntervalEXTFunc)();

	wgl_create_context_attribs_arb = (WGLCreateContextAttribsARBFunc *)g_WGLGetProcAddress("wglCreateContextAttribsARB");
	if (!wgl_create_context_attribs_arb) {
		FatalAppExitW(0, L"wglCreateContextAttribsARB not found in OpenGL module");
	}
	wgl_choose_pixel_format_arb = (WGLChoosePixelFormatARBFunc *)g_WGLGetProcAddress("wglChoosePixelFormatARB");
	if (!wgl_choose_pixel_format_arb) {
		FatalAppExitW(0, L"wglChoosePixelFormatARB not found in OpenGL module");
	}

	g_OpenGLSetSwapInterval = (WGLSwapIntervalEXTFunc *)g_WGLGetProcAddress("wglSwapIntervalEXT");
	g_OpenGLGetSwapInterval = (WGLGetSwapIntervalEXTFunc *)g_WGLGetProcAddress("wglGetSwapIntervalEXT");

	int attrib_list[] = {
		WGL_DRAW_TO_WINDOW_ARB, 1,
		WGL_SUPPORT_OPENGL_ARB, 1,
		WGL_DOUBLE_BUFFER_ARB, 1,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, 1,
		WGL_SAMPLE_BUFFERS_ARB, 1,
		WGL_SAMPLES_ARB, 2,
		0
	};

	g_WindowDC = GetDC(window_handle);

	int pixel_format;
	uint32_t num_formats;
	if (!wgl_choose_pixel_format_arb(g_WindowDC, attrib_list, 0, 1, &pixel_format, &num_formats)) {
		FatalAppExitW(0, L"OpenGL Pixel format search failed!");
	}

	if (num_formats == 0) {
		FatalAppExitW(0, L"OpenGL Compatible Pixel Format not found!");
	}

	PIXELFORMATDESCRIPTOR pfd;
	num_pixel_fmts = DescribePixelFormat(g_WindowDC, pixel_format, sizeof(pfd), &pfd);
	if (num_pixel_fmts == 0) {
		FatalAppExitW(0, L"OpenGL Pixel formats could not be described");
	}

	if (!SetPixelFormat(g_WindowDC, pixel_format, &pfd)) {
		FatalAppExitW(0, L"OpenGL Pixel formats could not be set");
	}

	int gl_version_attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB,
		4,
		WGL_CONTEXT_MINOR_VERSION_ARB,
		2,
		WGL_CONTEXT_PROFILE_MASK_ARB,
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#		if defined(_DEBUG) || defined(DEBUG)
		WGL_CONTEXT_FLAGS_ARB,
		WGL_CONTEXT_DEBUG_BIT_ARB,
#		endif
		0,
	};

	HGLRC glContext = wgl_create_context_attribs_arb(g_WindowDC, 0, gl_version_attribs);
	g_WGLMakeCurrent(0, 0);
	g_WGLDeleteContext(dummy_gl_context);
	g_WGLMakeCurrent(g_WindowDC, glContext);

	if (g_OpenGLSetSwapInterval) {
		g_OpenGLSetSwapInterval(1);
	}

	if (!LoadOpenGLFunctions(WindowsOpenGLGetProcAddress)) {
		FatalAppExitW(0, L"Failed to load OpenGL functions");
	}
}

void WindowsMapKeys() {
	g_WindowsKeyMap[(uint32_t)'A'] = KeyA;
	g_WindowsKeyMap[(uint32_t)'B'] = KeyB;
	g_WindowsKeyMap[(uint32_t)'C'] = KeyC;
	g_WindowsKeyMap[(uint32_t)'D'] = KeyD;
	g_WindowsKeyMap[(uint32_t)'E'] = KeyE;
	g_WindowsKeyMap[(uint32_t)'F'] = KeyF;
	g_WindowsKeyMap[(uint32_t)'G'] = KeyG;
	g_WindowsKeyMap[(uint32_t)'H'] = KeyH;
	g_WindowsKeyMap[(uint32_t)'I'] = KeyI;
	g_WindowsKeyMap[(uint32_t)'J'] = KeyJ;
	g_WindowsKeyMap[(uint32_t)'K'] = KeyK;
	g_WindowsKeyMap[(uint32_t)'L'] = KeyL;
	g_WindowsKeyMap[(uint32_t)'M'] = KeyM;
	g_WindowsKeyMap[(uint32_t)'N'] = KeyN;
	g_WindowsKeyMap[(uint32_t)'O'] = KeyO;
	g_WindowsKeyMap[(uint32_t)'P'] = KeyP;
	g_WindowsKeyMap[(uint32_t)'Q'] = KeyQ;
	g_WindowsKeyMap[(uint32_t)'R'] = KeyR;
	g_WindowsKeyMap[(uint32_t)'S'] = KeyS;
	g_WindowsKeyMap[(uint32_t)'T'] = KeyT;
	g_WindowsKeyMap[(uint32_t)'U'] = KeyU;
	g_WindowsKeyMap[(uint32_t)'V'] = KeyV;
	g_WindowsKeyMap[(uint32_t)'W'] = KeyW;
	g_WindowsKeyMap[(uint32_t)'X'] = KeyX;
	g_WindowsKeyMap[(uint32_t)'Y'] = KeyY;
	g_WindowsKeyMap[(uint32_t)'Z'] = KeyZ;

	g_WindowsKeyMap[(uint32_t)'0'] = Key0;
	g_WindowsKeyMap[(uint32_t)'1'] = Key1;
	g_WindowsKeyMap[(uint32_t)'2'] = Key2;
	g_WindowsKeyMap[(uint32_t)'3'] = Key3;
	g_WindowsKeyMap[(uint32_t)'4'] = Key4;
	g_WindowsKeyMap[(uint32_t)'5'] = Key5;
	g_WindowsKeyMap[(uint32_t)'6'] = Key6;
	g_WindowsKeyMap[(uint32_t)'7'] = Key7;
	g_WindowsKeyMap[(uint32_t)'8'] = Key8;
	g_WindowsKeyMap[(uint32_t)'9'] = Key9;

	g_WindowsKeyMap[VK_RETURN] = KeyReturn;
	g_WindowsKeyMap[VK_ESCAPE] = KeyEscape;
	g_WindowsKeyMap[VK_BACK] = KeyBackSpace;
	g_WindowsKeyMap[VK_TAB] = KeyTab;
	g_WindowsKeyMap[VK_SPACE] = KeySpace;
	g_WindowsKeyMap[VK_SHIFT] = KeyShift;
	g_WindowsKeyMap[VK_CONTROL] = KeyCtrl;

	g_WindowsKeyMap[VK_F1] = KeyF1;
	g_WindowsKeyMap[VK_F2] = KeyF2;
	g_WindowsKeyMap[VK_F3] = KeyF3;
	g_WindowsKeyMap[VK_F4] = KeyF4;
	g_WindowsKeyMap[VK_F5] = KeyF5;
	g_WindowsKeyMap[VK_F6] = KeyF6;
	g_WindowsKeyMap[VK_F7] = KeyF7;
	g_WindowsKeyMap[VK_F8] = KeyF8;
	g_WindowsKeyMap[VK_F9] = KeyF9;
	g_WindowsKeyMap[VK_F10] = KeyF10;
	g_WindowsKeyMap[VK_F11] = KeyF11;
	g_WindowsKeyMap[VK_F12] = KeyF12;

	g_WindowsKeyMap[VK_SNAPSHOT] = KeyPrintScreen;
	g_WindowsKeyMap[VK_INSERT] = KeyInsert;
	g_WindowsKeyMap[VK_HOME] = KeyHome;
	g_WindowsKeyMap[VK_PRIOR] = KeyPageUp;
	g_WindowsKeyMap[VK_NEXT] = KeyPageDown;
	g_WindowsKeyMap[VK_DELETE] = KeyDelete;
	g_WindowsKeyMap[VK_END] = KeyEnd;
	g_WindowsKeyMap[VK_RIGHT] = KeyRight;
	g_WindowsKeyMap[VK_LEFT] = KeyLeft;
	g_WindowsKeyMap[VK_DOWN] = KeyDown;
	g_WindowsKeyMap[VK_UP] = KeyUp;
	g_WindowsKeyMap[VK_DIVIDE] = KeyDivide;
	g_WindowsKeyMap[VK_MULTIPLY] = KeyMultiply;
	g_WindowsKeyMap[VK_ADD] = KeyPlus;
	g_WindowsKeyMap[VK_SUBTRACT] = KeyMinus;
	g_WindowsKeyMap[VK_DECIMAL] = KeyPeriod;
	g_WindowsKeyMap[VK_OEM_3] = KeyBackTick;

	g_WindowsKeyMap[VK_NUMPAD0] = KeyPad0;
	g_WindowsKeyMap[VK_NUMPAD1] = KeyPad1;
	g_WindowsKeyMap[VK_NUMPAD2] = KeyPad2;
	g_WindowsKeyMap[VK_NUMPAD3] = KeyPad3;
	g_WindowsKeyMap[VK_NUMPAD4] = KeyPad4;
	g_WindowsKeyMap[VK_NUMPAD5] = KeyPad5;
	g_WindowsKeyMap[VK_NUMPAD6] = KeyPad6;
	g_WindowsKeyMap[VK_NUMPAD7] = KeyPad7;
	g_WindowsKeyMap[VK_NUMPAD8] = KeyPad8;
	g_WindowsKeyMap[VK_NUMPAD9] = KeyPad9;
}

void ToggleFullscreen(HWND hwnd) {
	DWORD dwStyle = GetWindowLongW(hwnd, GWL_STYLE);
	if (dwStyle & WS_OVERLAPPEDWINDOW) {
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(hwnd, &g_WindowPlacement) &&
			GetMonitorInfoW(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY),
							&mi)) {
			SetWindowLongW(hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
						 mi.rcMonitor.right - mi.rcMonitor.left,
						 mi.rcMonitor.bottom - mi.rcMonitor.top,
						 SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	} else {
		SetWindowLongW(hwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hwnd, &g_WindowPlacement);
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
					 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
					 SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}

LRESULT CALLBACK WindowProcedure(HWND wnd, UINT msg, WPARAM wparam,
								 LPARAM lparam) {
	LRESULT result = 0;

	switch (msg) {
		case WM_DPICHANGED:
		{
			RECT *const suggested_rect = (RECT *)lparam;
			auto        left = suggested_rect->left;
			auto        top = suggested_rect->top;
			auto        width = suggested_rect->right - suggested_rect->left;
			auto        height = suggested_rect->bottom - suggested_rect->top;
			SetWindowPos(wnd, 0, left, top, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
		} break;

		case WM_SIZE:
		{
			uint32_t x = (uint32_t)LOWORD(lparam);
			uint32_t y = (uint32_t)HIWORD(lparam);
			g_Platform.OnWindowResize(&g_Platform, x, y);
			result = DefWindowProcW(wnd, msg, wparam, lparam);
		} break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);
		} break;

		case WM_MOUSEMOVE:
		{
			RECT rc;
			GetClientRect(wnd, &rc);
			int window_w = rc.right - rc.left;
			int window_h = rc.bottom - rc.top;

			int x = GET_X_LPARAM(lparam);
			int y = GET_Y_LPARAM(lparam);

			CURSORINFO info;
			info.cbSize = sizeof(info);
			if (GetCursorInfo(&info) && (info.flags == 0)) {
				// Cursor is hidden, place cursor always at center
				POINT pt = { rc.left, rc.top };
				POINT pt2 = { rc.right, rc.bottom };
				ClientToScreen(wnd, &pt);
				ClientToScreen(wnd, &pt2);
				SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);
				ClipCursor(&rc);
				int c_x = rc.left + (rc.right - rc.left) / 2;
				int c_y = rc.top + (rc.bottom - rc.top) / 2;
				SetCursorPos(c_x, c_y);
				g_Platform.Mouse.Position.x = (float)c_x;
				g_Platform.Mouse.Position.y = (float)c_y;
			} else {
				g_Platform.Mouse.Position.x = (float)x;
				g_Platform.Mouse.Position.y = (float)y;
			}
		} break;

		case WM_INPUT:
		{
			if (GET_RAWINPUT_CODE_WPARAM(wparam) == RIM_INPUT) {
				RAWINPUT input;
				UINT     size = sizeof(input);
				if (GetRawInputData((HRAWINPUT)lparam, RID_INPUT, &input, &size, sizeof(RAWINPUTHEADER))) {
					if (input.header.dwType == RIM_TYPEMOUSE) {
						MONITORINFO monitor_info;
						monitor_info.cbSize = sizeof(monitor_info);
						if (GetMonitorInfoW(MonitorFromWindow(wnd, MONITOR_DEFAULTTONEAREST), &monitor_info)) {
							LONG monitor_w = monitor_info.rcMonitor.right - monitor_info.rcMonitor.left;
							LONG monitor_h = monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top;
							LONG xrel = input.data.mouse.lLastX;
							LONG yrel = input.data.mouse.lLastY;
							g_Platform.Mouse.Delta.x = (float)xrel / (float)monitor_w;
							g_Platform.Mouse.Delta.y = (float)yrel / (float)monitor_h;
						}
					}
				}
			}
			result = DefWindowProcW(wnd, msg, wparam, lparam);
		} break;

		case WM_LBUTTONDOWN:
		{
			g_Platform.Mouse.IsDown[ButtonLeft] = true;
		} break;

		case WM_MBUTTONDOWN:
		{
			g_Platform.Mouse.IsDown[ButtonMiddle] = true;
		} break;

		case WM_RBUTTONDOWN:
		{
			g_Platform.Mouse.IsDown[ButtonRight] = true;
		} break;

		case WM_LBUTTONUP:
		{
			g_Platform.Mouse.IsDown[ButtonLeft] = false;
			g_Platform.Mouse.Transitions[ButtonLeft] += 1;
		} break;

		case WM_MBUTTONUP:
		{
			g_Platform.Mouse.IsDown[ButtonMiddle] = false;
			g_Platform.Mouse.Transitions[ButtonMiddle] += 1;
		} break;

		case WM_RBUTTONUP:
		{
			g_Platform.Mouse.IsDown[ButtonRight] = false;
			g_Platform.Mouse.Transitions[ButtonRight] += 1;
		} break;

		case WM_LBUTTONDBLCLK:
		{
			g_Platform.Mouse.DoubleClick[ButtonLeft] += 1;
		} break;

		case WM_MBUTTONDBLCLK:
		{
			g_Platform.Mouse.DoubleClick[ButtonMiddle] += 1;
		} break;

		case WM_RBUTTONDBLCLK:
		{
			g_Platform.Mouse.DoubleClick[ButtonRight] += 1;
		} break;

		case WM_KEYDOWN:
		{
			if (wparam == VK_F11) {
				ToggleFullscreen(wnd);
			}

			uint32_t key = g_WindowsKeyMap[wparam];
			g_Platform.Keyboard.IsDown[key] = true;
			g_Platform.Keyboard.Repeat[key] = ((lparam & (1 << 30)) == (1 << 30));
		} break;

		case WM_KEYUP:
		{
			uint32_t key = g_WindowsKeyMap[wparam];
			g_Platform.Keyboard.IsDown[key] = false;
			g_Platform.Keyboard.Transitions[key] += 1;
		} break;

		case WM_MOUSEWHEEL:
		{
			g_Platform.Mouse.Scroll.y = (float)GET_WHEEL_DELTA_WPARAM(wparam) / (float)WHEEL_DELTA;
		} break;

		case WM_MOUSEHWHEEL:
		{
			g_Platform.Mouse.Scroll.x = (float)GET_WHEEL_DELTA_WPARAM(wparam) / (float)WHEEL_DELTA;
		} break;

		default:
		{
			result = DefWindowProcW(wnd, msg, wparam, lparam);
		}
	}

	return result;
}

void *WindowsAlloc(size_t size) {
	return HeapAlloc(GetProcessHeap(), 0, size);
}

void *WindowsRealloc(void *ptr, size_t size) {
	if (ptr)
		return HeapReAlloc(GetProcessHeap(), 0, ptr, size);
	return HeapAlloc(GetProcessHeap(), 0, size);
}

void WindowsFree(void *ptr) {
	HeapFree(GetProcessHeap(), 0, ptr);
}

void WindowsLog(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}

void WindowsFatalError(const char *msg) {
	FatalAppExitA(0, msg);
}

int main(int argc, char **argv) {
	DWORD  task_index = 0;
	HANDLE task_handle = AvSetMmThreadCharacteristicsW(L"Games", &task_index);

	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	WindowsMapKeys();

	const size_t scratch_size = MegaBytes(32);
	uint8_t *ptr = (uint8_t *)VirtualAlloc(NULL, scratch_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (ptr == nullptr) {
		FatalAppExitW(0, L"Failed to Allocate Scratch Memory!");
	}

	float const dt = 1.0f / 60.0f;

	g_Platform.Scratch = CreateArena(ptr, scratch_size);
	g_Platform.Alloc = WindowsAlloc;
	g_Platform.Realloc = WindowsRealloc;
	g_Platform.Free = WindowsFree;
	g_Platform.UserPointer = nullptr;
	g_Platform.Log = WindowsLog;
	g_Platform.FatalError = WindowsFatalError;
	g_Platform.RenderTargetWidth = 800;
	g_Platform.RenderTargetHeight = 600;
	g_Platform.Time.FixedDeltaTime = dt;
	g_Platform.Time.DeltaTime = dt;
	g_Platform.Time.RealDeltaTime = dt;
	g_Platform.Time.Time = 0;
	g_Platform.Time.RealTime = 0;
	g_Platform.Time.SimulationSpeedFactor = 1;

	g_Platform.OnLoad = PlatformOnLoadStub;
	g_Platform.FixedUpdate = PlatformFixedUpdateStub;
	g_Platform.UpdateAndRender = PlatformUpdateAndRenderStub;
	g_Platform.OnWindowResize = PlatformOnWindowResizeStub;
	g_Platform.Name = "CppGame - Untitled";
	g_Platform.Running = true;

	CppGameInitialize(&g_Platform, argc, argv);

	if (g_Platform.Running == false) return 0;

	if (!g_Platform.OnLoad) g_Platform.OnLoad = PlatformOnLoadStub;
	if (!g_Platform.FixedUpdate) g_Platform.FixedUpdate = PlatformFixedUpdateStub;
	if (!g_Platform.UpdateAndRender) g_Platform.UpdateAndRender = PlatformUpdateAndRenderStub;
	if (!g_Platform.OnWindowResize) g_Platform.OnWindowResize = PlatformOnWindowResizeStub;

	if (g_Platform.Name == nullptr) g_Platform.Name = "CppGame - Untitled";
	if (g_Platform.RenderTargetWidth <= 0) g_Platform.RenderTargetWidth = 800;
	if (g_Platform.RenderTargetHeight <= 0) g_Platform.RenderTargetHeight = 600;

	int len = MultiByteToWideChar(CP_UTF8, 0, g_Platform.Name, -1, nullptr, 0);
	wchar_t *window_title = (wchar_t *)PushSize(&g_Platform.Scratch, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, g_Platform.Name, -1, window_title, len);

	WNDCLASSEXW window_class = { sizeof(window_class) };
	window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = WindowProcedure;
	window_class.hInstance = GetModuleHandleW(0);
	window_class.hIcon = (HICON)LoadImageW(GetModuleHandleW(0), MAKEINTRESOURCEW(101), IMAGE_ICON, 0, 0, 0);
	window_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
	window_class.lpszClassName = L"CppGame";

	RegisterClassExW(&window_class);

	RECT client_rect;
	client_rect.left = 0;
	client_rect.top = 0;
	client_rect.right = (LONG)g_Platform.RenderTargetWidth;
	client_rect.bottom = (LONG)g_Platform.RenderTargetHeight;
	AdjustWindowRectEx(&client_rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

	HWND window = CreateWindowExW(0, L"CppGame",
								  window_title, WS_OVERLAPPEDWINDOW,
								  CW_USEDEFAULT, CW_USEDEFAULT,
								  client_rect.right - client_rect.left, client_rect.bottom - client_rect.top,
								  NULL, NULL, GetModuleHandleW(0), NULL);

	if (window == NULL) {
		FatalAppExitW(0, L"Window could not be created");
	}

	RAWINPUTDEVICE device;
	device.usUsagePage = 0x1;
	device.usUsage = 0x2;
	device.dwFlags = 0;
	device.hwndTarget = window;

	if (!RegisterRawInputDevices(&device, 1, sizeof(device))) {
		DestroyWindow(window);
		UnregisterClassW(L"ZeroWindowClass", GetModuleHandleW(0));
		FatalAppExitW(0, L"Raw Input not supported");
	}

	ShowWindow(window, SW_SHOWNORMAL);
	UpdateWindow(window);

	g_WindowPlacement.length = sizeof(g_WindowPlacement);
	GetWindowPlacement(window, &g_WindowPlacement);

	ResetArena(&g_Platform.Scratch);

	LoadOpenGL(window);

	ImplOpenGLInitializeRenderer2D(&g_Platform);

	if (!g_Platform.OnLoad(&g_Platform))
		return 1;

	float accumulator = dt;

	LARGE_INTEGER frequency;
	LARGE_INTEGER counter;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);

	while (g_Platform.Running) {
		memcpy(g_Platform.Keyboard.WasDown, g_Platform.Keyboard.IsDown, sizeof(g_Platform.Keyboard.IsDown));
		memcpy(g_Platform.Mouse.WasDown, g_Platform.Mouse.IsDown, sizeof(g_Platform.Mouse.IsDown));
		memset(g_Platform.Keyboard.Transitions, 0, sizeof(g_Platform.Keyboard.Transitions));
		memset(g_Platform.Mouse.Transitions, 0, sizeof(g_Platform.Mouse.Transitions));
		memset(g_Platform.Mouse.DoubleClick, 0, sizeof(g_Platform.Mouse.DoubleClick));
		g_Platform.Mouse.Scroll = Vec2(0);

		MSG msg;
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				g_Platform.Running = false;
				break;
			}

			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		RECT rect;
		GetClientRect(window, &rect);
		g_Platform.RenderTargetWidth = (float)(rect.right - rect.left);
		g_Platform.RenderTargetHeight = (float)(rect.bottom - rect.top);
		g_Platform.AspectRatio = g_Platform.RenderTargetWidth / g_Platform.RenderTargetHeight;

		while (accumulator >= dt) {
			g_Platform.FixedUpdate(&g_Platform, dt);
			accumulator -= dt;
		}

		ImplOpenGLFrameRenderer2D(g_Platform.RenderTargetWidth, g_Platform.RenderTargetHeight);

		float alpha = accumulator / dt;

		g_Platform.UpdateAndRender(&g_Platform, g_Platform.Time.DeltaTime, alpha);

		ImplOpenGLRender();

		SwapBuffers(g_WindowDC);

		ResetArena(&g_Platform.Scratch);

		LARGE_INTEGER new_counter;
		QueryPerformanceCounter(&new_counter);

		auto counts = new_counter.QuadPart - counter.QuadPart;
		counter = new_counter;

		g_Platform.Time.RealDeltaTime = ((1000000.0f * (float)counts) / (float)frequency.QuadPart) / 1000000.0f;
		g_Platform.Time.RealTime += g_Platform.Time.RealDeltaTime;

		g_Platform.Time.DeltaTime = g_Platform.Time.RealDeltaTime * g_Platform.Time.SimulationSpeedFactor;
		g_Platform.Time.Time += g_Platform.Time.DeltaTime;

		accumulator += g_Platform.Time.DeltaTime;
		accumulator = Minimum(accumulator, 0.2f);
	}

	return 0;
}

#endif

//
// End Platform: Windows
//
