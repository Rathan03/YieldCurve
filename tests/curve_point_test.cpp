#include <gtest/gtest.h>
#include "yield_curve/curve_point.h"

#include <stdexcept>

TEST(Curve_Point_Tests, Valid_Construction)
{
    auto lambda = []() {
        return CurvePoint{1.0,0.95};
    };

    EXPECT_NO_THROW(lambda());
}

TEST(Curve_Point_Tests, Zero_Time)
{
    auto lambda = []() {
        return CurvePoint{0.0,0.95};
    };

    EXPECT_THROW(lambda(),std::invalid_argument);
}

TEST(Curve_Point_Tests, Negative_Time)
{
    auto lambda = []() {
        return CurvePoint{-1.0,0.95};
    };

    EXPECT_THROW(lambda(),std::invalid_argument);
}


TEST(Curve_Point_Tests, Zero_DCF)
{
    auto lambda = []() {
        return CurvePoint{1.0,0.0};
    };

    EXPECT_THROW(lambda(),std::invalid_argument);
}

TEST(Curve_Point_Tests, Negative_DCF)
{
    auto lambda = []() {
        return CurvePoint{1.0,-1.0};
    };

    EXPECT_THROW(lambda(),std::invalid_argument);
}

TEST(Curve_Point_Tests, Getter_Tests)
{
    CurvePoint point {1.0,2.0};

    EXPECT_DOUBLE_EQ(1.0, point.get_time());
    EXPECT_DOUBLE_EQ(2.0, point.get_dcf());
}