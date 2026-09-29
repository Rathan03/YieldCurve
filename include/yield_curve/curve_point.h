#pragma once


class CurvePoint
{
    public:
        CurvePoint(double time, double dcf); // dcf stands for discount factor
    
        double get_time() const;
        double get_dcf() const;

    private:
        const double time;
        const double dcf;
};