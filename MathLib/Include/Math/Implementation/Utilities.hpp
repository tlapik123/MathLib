#ifndef MATHLIB_IMPL_UTILITIES_HPP
#define MATHLIB_IMPL_UTILITIES_HPP

#include "../Common/Concepts.hpp"

namespace Math
{
    template <ConceptVectorN Vec>
    [[nodiscard]] constexpr
    typename Vec::ScalarType Dot(const Vec& u, const Vec& v) noexcept
    {
        typename Vec::ScalarType dot{};
        for (size_t i = 0; i < Vec::Dimension; ++i)
        {
            dot += (u[i] * v[i]);
        }
        return dot;
    }

    template <ConceptVectorN Vec>
    [[nodiscard]] constexpr
    Vec Normalize(const Vec& u) noexcept
    {
        auto len = u.Length();
        return u / len;
    }

    template <ConceptVector2 Vec>
    [[nodiscard]] constexpr
    Vec Perp(const Vec& u) noexcept
    {
        return Vec(u.y, -u.x);
    }

    template <ConceptVector3 Vec>
    [[nodiscard]] constexpr
    Vec Cross(const Vec& u, const Vec& v) noexcept
    {
        Vec w;
        w.x = u.y * v.z - u.z * v.y;
        w.y = u.z * v.x - u.x * v.z;
        w.z = u.x * v.y - u.y * v.x;
        return w;
    }

    template <ConceptMatrixN Mat>
    [[nodiscard]] constexpr
    Mat Transpose(const Mat& m) noexcept
    {
        Mat result = m;
        for (size_t i = 0; i < Mat::Dimension; ++i)
        {
            for (size_t j = i + 1; j < Mat::Dimension; ++j)
            {
                std::swap(result[i][j], result[j][i]);
            }
        }
        return result;
    }

    template <ConceptMatrix2 Mat>
    [[nodiscard]] constexpr
    typename Mat::ScalarType Determinant(const Mat& m) noexcept
    {
        return (m[0][0] * m[1][1])
             - (m[0][1] * m[1][0]);
    }

    template <ConceptMatrix3 Mat>
    [[nodiscard]] constexpr
    typename Mat::ScalarType Determinant(const Mat& m) noexcept
    {
        return (m[0][0] * m[1][1] * m[2][2])
             + (m[0][1] * m[1][2] * m[2][0])
             + (m[0][2] * m[1][0] * m[2][1])
             - (m[0][2] * m[1][1] * m[2][0])
             - (m[0][1] * m[1][0] * m[2][2])
             - (m[0][0] * m[1][2] * m[2][1]);
    }

    template <ConceptMatrix4 Mat>
    [[nodiscard]] constexpr
    typename Mat::ScalarType Determinant(const Mat& m) noexcept
    {
        return (m[0][0] * m[1][1] * m[2][2] * m[3][3])
             + (m[0][0] * m[1][2] * m[2][3] * m[3][1])
             + (m[0][0] * m[1][3] * m[2][1] * m[3][2])
             - (m[0][0] * m[1][3] * m[2][2] * m[3][1])
             - (m[0][0] * m[1][2] * m[2][1] * m[3][3])
             - (m[0][0] * m[1][1] * m[2][3] * m[3][2])
             - (m[0][1] * m[1][0] * m[2][2] * m[3][3])
             - (m[0][2] * m[1][0] * m[2][3] * m[3][1])
             - (m[0][3] * m[1][0] * m[2][1] * m[3][2])
             + (m[0][3] * m[1][0] * m[2][2] * m[3][1])
             + (m[0][2] * m[1][0] * m[2][1] * m[3][3])
             + (m[0][1] * m[1][0] * m[2][3] * m[3][2])
             + (m[0][1] * m[1][2] * m[2][0] * m[3][3])
             + (m[0][2] * m[1][3] * m[2][0] * m[3][1])
             + (m[0][3] * m[1][1] * m[2][0] * m[3][2])
             - (m[0][3] * m[1][2] * m[2][0] * m[3][1])
             - (m[0][2] * m[1][1] * m[2][0] * m[3][3])
             - (m[0][1] * m[1][3] * m[2][0] * m[3][2])
             - (m[0][1] * m[1][2] * m[2][3] * m[3][0])
             - (m[0][2] * m[1][3] * m[2][1] * m[3][0])
             - (m[0][3] * m[1][1] * m[2][2] * m[3][0])
             + (m[0][3] * m[1][2] * m[2][1] * m[3][0])
             + (m[0][2] * m[1][1] * m[2][3] * m[3][0])
             + (m[0][1] * m[1][3] * m[2][2] * m[3][0]);
    }

    template <ConceptMatrix2 Mat>
    [[nodiscard]] constexpr
    Mat Invert(const Mat& m) noexcept
    {
        Mat result = m;
        result[0][0] =  m[1][1];
        result[0][1] = -m[0][1];
        result[1][0] = -m[1][0];
        result[1][1] =  m[0][0];
        result = result * (typename Mat::ScalarType(1) / Determinant(m));
        return result;
    }

    template <ConceptMatrix3 Mat>
    [[nodiscard]] constexpr
    Mat Invert(const Mat& m) noexcept
    {
        Mat result;
        result[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
        result[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]);
        result[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
        result[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]);
        result[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]);
        result[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]);
        result[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
        result[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]);
        result[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
        result = result * (typename Mat::ScalarType(1) / Determinant(m));
        return result;
    }

    template <ConceptMatrix4 Mat>
    [[nodiscard]] constexpr
    Mat Invert(const Mat& m) noexcept
    {
        // The content of this function was originally taken from
        // this repository: https://github.com/willnode/N-Matrix-Programmer
        // It is licensed by the original author under the MIT license.
        // Copyright (c) 2017 Wildan Mubarok

        typename Mat::ScalarType A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
        typename Mat::ScalarType A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
        typename Mat::ScalarType A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
        typename Mat::ScalarType A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
        typename Mat::ScalarType A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
        typename Mat::ScalarType A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
        typename Mat::ScalarType A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
        typename Mat::ScalarType A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
        typename Mat::ScalarType A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
        typename Mat::ScalarType A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
        typename Mat::ScalarType A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
        typename Mat::ScalarType A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        typename Mat::ScalarType A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
        typename Mat::ScalarType A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
        typename Mat::ScalarType A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
        typename Mat::ScalarType A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
        typename Mat::ScalarType A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
        typename Mat::ScalarType A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

        typename Mat::ScalarType det = m[0][0] * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223)
                                     - m[0][1] * (m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223)
                                     + m[0][2] * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123)
                                     - m[0][3] * (m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);

        Mat result;
        result[0][0] =  (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223);
        result[0][1] = -(m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223);
        result[0][2] =  (m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213);
        result[0][3] = -(m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212);
        result[1][0] = -(m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223);
        result[1][1] =  (m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223);
        result[1][2] = -(m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213);
        result[1][3] =  (m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212);
        result[2][0] =  (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123);
        result[2][1] = -(m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123);
        result[2][2] =  (m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113);
        result[2][3] = -(m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112);
        result[3][0] = -(m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);
        result[3][1] =  (m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123);
        result[3][2] = -(m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113);
        result[3][3] =  (m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112);

        result = result * (typename Mat::ScalarType(1) / det);
        return result;
    }

    template <ConceptUtilType T>
    [[nodiscard]] constexpr
    bool Equal(const T& u, const T& v, typename T::ScalarType epsilon = Constants::Epsilon<typename T::ScalarType>::Value) noexcept
    {
        for (size_t i = 0; i < T::Dimension; ++i)
        {
            if (!Equal(u[i], v[i], epsilon))
            {
                return false;
            }
        }

        return true;
    }

    template <ConceptVectorN Vec>
    [[nodiscard]] constexpr
    bool HasNaN(const Vec& u) noexcept
    {
        for (size_t i = 0; i < Vec::Dimension; ++i)
        {
            if (u[i] != u[i])
            {
                return true;
            }
        }

        return false;
    }

    template <ConceptBasicPoint Pnt>
    [[nodiscard]] constexpr
    bool HasNaN(const Pnt& p) noexcept
    {
        for (size_t i = 0; i < Pnt::Dimension; ++i)
        {
            if (p[i] != p[i])
            {
                return true;
            }
        }

        return false;
    }

    template <ConceptMatrixN Mat>
    [[nodiscard]] constexpr
    bool HasNaN(const Mat& m)
    {
        for (size_t i = 0; i < Mat::Dimension; ++i)
        {
            if (HasNaN(m[i]))
            {
                return true;
            }
        }

        return false;
    }
}

#endif //MATHLIB_IMPL_UTILITIES_HPP
