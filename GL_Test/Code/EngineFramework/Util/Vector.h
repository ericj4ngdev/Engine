#pragma once

#include <cmath>

const float Pi = 4 * std::atan(1.0f);
const float TwoPi = 2 * Pi;

template <typename T>
class Vector2 {
public:
    T x;
    T y;
public:
    Vector2() {}

    Vector2(T x, T y) : x(x), y(y) {}

    ~Vector2() {}

    void Set(T x, T y) {
        this->x = x;
        this->y = y;
    }

    T Dot(const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    T Cross(const Vector2& v) const {
        return x * v.y - y * v.x;
    }

    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    bool operator < (const Vector2& v)const {
        return x != v.x ? x < v.x : y < v.y;
    }

    void operator+=(const Vector2& v) {
        *this = Vector2(x + v.x, y + v.y);
    }

    void operator-=(const Vector2& v) {
        *this = Vector2(x - v.x, y - v.y);
    }

    Vector2 operator/(T s) const {
        return Vector2(x / s, y / s);
    }

    Vector2 operator*(float s) const {
        return Vector2(x * s, y * s);
    }

    void operator/=(float s) {
        *this = Vector2(x / s, y / s);
    }

    void operator*=(float s) {
        *this = Vector2(x * s, y * s);
    }

    Vector2& Normalize() {
        float len = Length();
        assert(len != 0.f);
        x /= len;
        y /= len;
        return *this;
    }

    Vector2 Normalized() const {
        Vector2 v = *this;
        v.Normalize();
        return v;
    }

    T LengthSquared() const {
        return x * x + y * y;
    }

    T Length() const {
        return sqrt(LengthSquared());
    }

    explicit operator Vector2<float>() const {
        return Vector2<float>(x, y);
    }

    bool operator==(const Vector2& v) const {
        return x == v.x && y == v.y;
    }

    Vector2 Lerp(float t, const Vector2& v) const {
        return Vector2(x * (1 - t) + v.x * t,
            y * (1 - t) + v.y * t);
    }

    static float Distance(const Vector2& a, const Vector2& b) {
        return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
    }

    const T* Pointer() const {
        return &x;
    }

    template <typename P>
    P* Write(P* pData) {
        Vector2* pVector = (Vector2*)pData;
        *pVector++ = *this;
        return (P*)pVector;
    }

};

template <typename T>
class Vector3 {
public:
    T x;
    T y;
    T z;
public:
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    ~Vector3() {}

    void Set(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Normalize() {
        float s = 1.0f / std::sqrt(x * x + y * y + z * z);
        x *= s;
        y *= s;
        z *= s;
    }

    Vector3 Normalized() const {
        Vector3 v = *this;
        v.Normalize();
        return v;
    }

    Vector3 Cross(const Vector3& v) const {
        return Vector3(y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }

    T Dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    void operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    void operator/=(T s) {
        x /= s;
        y /= s;
        z /= s;
    }

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator*(T s) const {
        return Vector3(x * s, y * s, z * s);
    }

    Vector3 operator/(T s) const {
        return Vector3(x / s, y / s, z / s);
    }

    bool operator==(const Vector3& v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    Vector3 Lerp(float t, const Vector3& v) const {
        return Vector3(x * (1 - t) + v.x * t,
            y * (1 - t) + v.y * t,
            z * (1 - t) + v.z * t);
    }

    static Vector3 Lerp(float t, const Vector3& a, Vector3& b) {
        return Vector3(a.x * (1 - t) + b.x * t,
            a.y * (1 - t) + b.y * t,
            a.z * (1 - t) + b.z * t);
    }

    static float Distance(const Vector3& a, const Vector3& b) {
        return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
    }

    const T* Pointer() const {
        return &x;
    }

    template <typename P>
    P* Write(P* pData) {
        Vector3<T>* pVector = (Vector3<T>*) pData;
        *pVector++ = *this;
        return (P*)pVector;
    }

};
typedef Vector2<bool> bvec2;

typedef Vector2<int> ivec2;
typedef Vector3<int> ivec3;

typedef Vector2<float> vec2;
typedef Vector3<float> vec3;