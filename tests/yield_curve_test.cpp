#include <gtest/gtest.h>
#include "yield_curve/curve_point.h"
#include "yield_curve/yield_curve.h"

#include <stdexcept>

TEST(Yield_Curve_Tests, Valid_Construction)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};

    auto lambda = [p_1,p_2]() {
        YieldCurve curve{std::vector<CurvePoint>{p_1,p_2}};
    };

    EXPECT_NO_THROW(lambda());
}

TEST(Yield_Curve_Tests, Duplicate_Construction)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0, 0.88};
    CurvePoint p_3{1.0,0.8};

    auto lambda = [p_1, p_2, p_3]() {
        YieldCurve curve{std::vector<CurvePoint>{p_1,p_2,p_3}};
    };

    EXPECT_THROW(lambda(), std::invalid_argument);
}

TEST(Yield_Curve_Tests, Sorting_Check)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.65};

    YieldCurve curve{std::vector<CurvePoint>{p_2,p_3,p_1}};
    
    auto points = curve.get_points();
    auto point_check_1 = points[0];
    auto point_check_2 = points[1];
    auto point_check_3 = points[2];

    EXPECT_DOUBLE_EQ(point_check_1.get_time(), p_1.get_time());
    EXPECT_DOUBLE_EQ(point_check_2.get_time(), p_2.get_time());
    EXPECT_DOUBLE_EQ(point_check_3.get_time(), p_3.get_time());
}