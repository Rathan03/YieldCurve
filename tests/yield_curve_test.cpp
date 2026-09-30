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

TEST(Yield_Curve_Tests, Midpoint_Interpolation)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_DOUBLE_EQ(curve.get_discount_factor(1.5), 0.875);
    
}

TEST(Yield_Curve_Tests, Beginning_Interpolation)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_DOUBLE_EQ(curve.get_discount_factor(1.0), 0.95);
    
}

TEST(Yield_Curve_Tests, End_Interpolation)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_DOUBLE_EQ(curve.get_discount_factor(2.0), 0.8);
    
}

TEST(Yield_Curve_Tests, Arbitrary_Interpolation)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_DOUBLE_EQ(curve.get_discount_factor(2.25), 0.75);
    
}

TEST(Yield_Curve_Tests, Below_Curve)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_THROW(curve.get_discount_factor(0.5), std::out_of_range);
    
}

TEST(Yield_Curve_Tests, Above_Curve)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_THROW(curve.get_discount_factor(3.5), std::out_of_range);
    
}

TEST(Yield_Curve_Tests, Known_Zero_Rate)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_NEAR(curve.get_zero_rate(2),0.11157, 1e-5);  
}

TEST(Yield_Curve_Tests, Interpolated_Zero_Rate)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_NEAR(curve.get_zero_rate(2.5),0.14266, 1e-5);  
}

TEST(Yield_Curve_Tests, Out_Of_Range_Zero_Rate)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_THROW(curve.get_zero_rate(3.5), std::out_of_range);  
}

TEST(Yield_Curve_Tests, Zero_Time_Zero_Rate)
{
    CurvePoint p_1{1.0,0.95};
    CurvePoint p_2{2.0,0.8};
    CurvePoint p_3{3.0,0.6};

    YieldCurve curve{std::vector<CurvePoint>{p_1, p_2, p_3}};

    EXPECT_THROW(curve.get_zero_rate(0.0), std::out_of_range);  
}
