#ifndef MATHLIB_IMPL_MATRIX3_HPP
#define MATHLIB_IMPL_MATRIX3_HPP

#include "Vector3.hpp"

#include <array>

namespace Math
{
    template <typename T>
    class Matrix3T final
    {
    public:
        using ScalarType = T;
        using VectorType = Vector3T<T>;
        static constexpr size_t Dimension = 3;

        constexpr explicit Matrix3T() noexcept
            : rows({})
        {}

        constexpr explicit Matrix3T(T diag) noexcept
            : rows({})
        {
            for (size_t i = 0; i < 3; ++i) { rows[i][i] = diag; }
        }

        constexpr explicit Matrix3T(const Vector3T<T>& row0,
                                    const Vector3T<T>& row1,
                                    const Vector3T<T>& row2)
        noexcept
            : rows({ row0,
                     row1,
                     row2 })
        {}

        constexpr explicit Matrix3T(T m00, T m01, T m02,
                                    T m10, T m11, T m12,
                                    T m20, T m21, T m22)
        noexcept
            : rows({{ {m00, m01, m02},
                      {m10, m11, m12},
                      {m20, m21, m22} }})
        {}

        constexpr       Vector3T<T>& operator[] (size_t index)       { return rows[index]; }
        constexpr const Vector3T<T>& operator[] (size_t index) const { return rows[index]; }
    private:
        std::array<Vector3T<T>, 3> rows;
    };
}

#endif //MATHLIB_IMPL_MATRIX3_HPP
