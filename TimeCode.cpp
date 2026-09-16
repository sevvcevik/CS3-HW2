#include "TimeCode.h"


long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
    // I did not do bounds-checking here on purpose
    // Because the constructor relies on this function to accept min/sec out of range
    // It folds them into the total instead of rejecting them
    return (static_cast<long long unsigned int>(hr) * 3600) + (static_cast<long long unsigned int>(min) * 60) + sec;

    // Source for static_cast: https://www.geeksforgeeks.org/cpp/static_cast-in-cpp/
}

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    hr = static_cast<unsigned int>(t / 3600);
    long long unsigned int remainder = t % 3600;
    min = static_cast<unsigned int>(remainder / 60);
    sec = static_cast<unsigned int>(remainder % 60);
}



TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}



void TimeCode::SetHours(unsigned int hours) {
    // There is no validation for hours, unlike min or sec because hours has no upper bound
    // Also it's unsigned so it can't be negative either
    unsigned int h;
    unsigned int m;
    unsigned int s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(hours, m, s);
}

void TimeCode::SetMinutes(unsigned int minutes) {
    // SetMinutes only changes the min component and leaves hrs and sec unchanged
    // Thus, we need to check if minutes is less than 60, if not that would roll over into hours
    if (minutes >= 60) {
        throw invalid_argument("Enter a value between 0 and 59. Invalid minutes value: " + to_string(minutes));
    }

    unsigned int h;
    unsigned int m;
    unsigned int s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);
}

void TimeCode::SetSeconds(unsigned int seconds) {
    // Same logic as SetMinutes, but for seconds.
    if (seconds >= 60) {
        throw invalid_argument("Enter a value between 0 and 59. Invalid seconds value: " + to_string(seconds));
    }

    unsigned int h;
    unsigned int m;
    unsigned int s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);
}

void TimeCode::reset() {
    t = 0;
}



unsigned int TimeCode::GetHours() const {
    unsigned int h;
    unsigned int m;
    unsigned int s;
    GetComponents(h, m, s);
    return h;
}

unsigned int TimeCode::GetMinutes() const {
    unsigned int h;
    unsigned int m;
    unsigned int s;
    GetComponents(h, m, s);
    return m;
}

unsigned int TimeCode::GetSeconds() const {
    unsigned int h;
    unsigned int m;
    unsigned int s;
    GetComponents(h, m, s);
    return s;
}



string TimeCode::ToString() const {
    unsigned int h;
    unsigned int m;
    unsigned int s;
    GetComponents(h, m, s);
    return to_string(h) + ":" + to_string(m) + ":" + to_string(s);
}



TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, t + other.t);
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    // Because t is unsigned, if other.t > t, t - other.t would be a huge negative number
    // So instead of going negative , I throw an exception to indicate that the operation is invalid before returning
    if (other.t > t) {
        throw invalid_argument("Enter a value less than the current TimeCode for subtraction because TimeCode cannot be negative. Current TimeCode: " + ToString() + ", Invalid TimeCode to subtract: " + other.ToString());
    }

    return TimeCode(0, 0, t - other.t);
}

TimeCode TimeCode::operator*(double a) const {
    if (a < 0) {
        throw invalid_argument("Enter a positive value for multiplication. Invalid multiplier: " + to_string(a));
    }

    // t * a is multiplying an integer by a double, so the result of t * a is itself a double and can have a fractional part
    // But TimeCode accepts t as an unsigned long long int, so we need to convert the double to an integer
    // I used static_cast because the assignment says not to use <cmath> and thus std::round() is not allowed
    // static_cast gets rid of the fractional part and keeps the integer part, it doesn't round
    return TimeCode(0, 0, static_cast<long long unsigned int>(t * a));
}

TimeCode TimeCode::operator/(double a) const {
    if (a <= 0) {
        throw invalid_argument("Enter a positive value for division. Invalid divisor: " + to_string(a));
    }

    // same logic as multiplication
    return TimeCode(0, 0, static_cast<long long unsigned int>(t / a));
}



bool TimeCode::operator==(const TimeCode& other) const { 
    return t == other.t; 
}

bool TimeCode::operator!=(const TimeCode& other) const {
     return t != other.t; 
}

bool TimeCode::operator< (const TimeCode& other) const { 
    return t <  other.t; 
}

bool TimeCode::operator<=(const TimeCode& other) const { 
    return t <= other.t; 
}

bool TimeCode::operator> (const TimeCode& other) const { 
    return t >  other.t; 
}

bool TimeCode::operator>=(const TimeCode& other) const { 
    return t >= other.t; 
}