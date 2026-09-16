#ifndef TIMECODE_H
#define TIMECODE_H

#include <iostream> // use for the throw "Negative Condition" lines
// I don't think I use <iostream> instead I use <stdexcept> for the throw lines
// Should I keep it?

#include <stdexcept> // I put in this file because so that any file including this header can catch invalid_argument
#include <string>

using namespace std;

class TimeCode {

    public:
        TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0);
        TimeCode(const TimeCode& tc);
        ~TimeCode(){};
        
        void SetHours (unsigned int hours);
        void SetMinutes(unsigned int minutes);
        void SetSeconds(unsigned int seconds);
        
        void reset ();
        
        unsigned int GetHours() const;
        unsigned int GetMinutes() const;
        unsigned int GetSeconds() const;
        
        long long unsigned int GetTimeCodeAsSeconds() const { return t; }; 
        void GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const;
        static long long unsigned int ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec);
        
        string ToString() const;
        
        TimeCode operator+(const TimeCode& other) const; 
        TimeCode operator-(const TimeCode& other) const; 
        TimeCode operator*(double a) const;
        TimeCode operator/(double a) const;
        
        bool operator == (const TimeCode& other) const;
        bool operator != (const TimeCode& other) const; 

        bool operator < (const TimeCode& other) const;
        bool operator <= (const TimeCode& other) const;
        
        bool operator > (const TimeCode& other) const;
        bool operator >= (const TimeCode& other) const;
        
        
    private:
        long long unsigned int t = 0;
};

#endif