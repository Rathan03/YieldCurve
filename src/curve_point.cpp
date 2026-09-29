#include "yield_curve/curve_point.h"

#include <stdexcept>

CurvePoint::CurvePoint(double time, double dcf):
    time{time},
    dcf{dcf}
{
    if (time <= 0)
    {
        throw std::invalid_argument("Time to maturity must be positive");
    }
    if (dcf <= 0)
    {
        throw std::invalid_argument("Discount factor must be positive");
    }
}

double CurvePoint::get_time() const
{
    return time;
}

double CurvePoint::get_dcf() const
{
    return dcf;
}