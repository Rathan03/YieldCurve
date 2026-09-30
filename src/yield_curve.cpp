#include "yield_curve/yield_curve.h"
#include "yield_curve/curve_point.h"

#include <vector>
#include <algorithm>
#include <stdexcept>


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

    if (time == points[0].get_time()) {return points[0].get_dcf();}
    if (time == points.back().get_time()) {return points.back().get_dcf();}

    if (it == points.begin())
    {
        throw std::out_of_range("Time given is before the range of yield curve.");
    } else if (it == points.end())
    {
        throw std::out_of_range("Time given is after the range of yield curve.");
    }


    const CurvePoint& next_point = *it;
    const CurvePoint& prev_point = *(it-1);

    return prev_point.get_dcf() + (next_point.get_dcf()-prev_point.get_dcf()) * (time - prev_point.get_time())/(next_point.get_time()-prev_point.get_time());
}