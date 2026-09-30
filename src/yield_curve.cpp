#include "yield_curve/yield_curve.h"
#include "yield_curve/curve_point.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>


YieldCurve::YieldCurve(std::span<const CurvePoint> points):
    points{points.begin(),points.end()}
{
    std::sort(this->points.begin(), this->points.end(),
    [](const CurvePoint& a, const CurvePoint& b)
    {
        return a.get_time() < b.get_time();
    });

    for (std::size_t i{1}; i < this->points.size(); i++)
    {
        if(this->points[i].get_time() == this->points[i-1].get_time())
        {
            throw std::invalid_argument("Cannot construct yield curve with duplicates.");
        }
    }
}

std::span<const CurvePoint> YieldCurve::get_points() const
{
    return points;
}

double YieldCurve::get_discount_factor(double time) const
{
    auto points = get_points();
    auto it = std::lower_bound(points.begin(), points.end(), time, [](const CurvePoint& a, double b){ return a.get_time() < b;});

    if (it == points.begin())
    {
        if (it->get_time() == time)
        {
            return it->get_dcf();
        }

        throw std::out_of_range("Time is below the curve range");
    }

    if (it == points.end())
    {
        throw std::out_of_range("Time is above the curve range");
    }


    const CurvePoint& next_point = *it;
    const CurvePoint& prev_point = *(it-1);

    return prev_point.get_dcf() + (next_point.get_dcf()-prev_point.get_dcf()) * (time - prev_point.get_time())/(next_point.get_time()-prev_point.get_time());
}

double YieldCurve::get_zero_rate(double time) const
{
    return -(std::log(get_discount_factor(time)))/time;
}

double YieldCurve::get_forward_rate(double start_time, double end_time) const
{
    if (start_time <= 0)
    {
        throw std::invalid_argument("Start time of forward rate must be positive.");
    }
    
    if (start_time >= end_time)
    {
        throw std::invalid_argument("Start time of forward rate must preceed end time.");
    }

    double dcf_1 = get_discount_factor(start_time);
    double dcf_2 = get_discount_factor(end_time);

    return (std::log(dcf_1)-std::log(dcf_2))/(end_time-start_time);
}

double YieldCurve::get_par_rate(double maturity) const
{
    double denominator{};

    int full_years = static_cast<int>(maturity);

    for (int i{1}; i <= full_years; ++i)
    {
        denominator += get_discount_factor(i);
    }

    double fraction = maturity - full_years;

    if (fraction > 0)
    {
        denominator += fraction * get_discount_factor(maturity);
    }

    return (1 - get_discount_factor(maturity)) / denominator;
}