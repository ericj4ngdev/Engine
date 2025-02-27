#include "Include.h"
#pragma once
#define M_PI 3.14159265358979323846

template <typename T>
static int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T>
static constexpr T ValueSelect(T comparand, T valueGEZero, T valueLTZero) {
    return comparand >= 0.f ? valueGEZero : valueLTZero;
}