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