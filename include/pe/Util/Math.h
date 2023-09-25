#pragma once

#include <sead/math/seadMathNumbers.h>
#include <sead/math/seadQuat.h>
#include <sead/math/seadVector.h>

namespace pe {

template <typename T>
struct Constants {
    Constants() = delete;

    constexpr static T degreesToRadians = sead::numbers::pi_v<T> / 180;
    constexpr static T radiansToDegrees = 180 / sead::numbers::pi_v<T>;
};

sead::Vector3f quatToRotate(const sead::Quatf& quat);

template <typename T>
sead::Vector2<T> abs(const sead::Vector2<T>& vec)
{
    sead::Vector2<T> newVec = vec;
    newVec.x = std::abs(newVec.x);
    newVec.y = std::abs(newVec.y);
    return newVec;
}

template <typename T>
sead::Vector3<T> abs(const sead::Vector3<T>& vec)
{
    sead::Vector3<T> newVec = vec;
    newVec.x = std::abs(newVec.x);
    newVec.y = std::abs(newVec.y);
    newVec.z = std::abs(newVec.z);
    return newVec;
}

} // namespace pe