#pragma once

#include "yield_curve/curve_point.h"
#include <span>
#include <vector>

class YieldCurve
{
public:
    YieldCurve(std::span<const CurvePoint> points);

    void add_curve_point(const CurvePoint& point, bool replace_duplicates);
    void add_curve_points(std::span<const CurvePoint> points, bool replace_duplicates);

    std::span<const CurvePoint> get_points() const;

private:
    std::vector<CurvePoint> points;
};