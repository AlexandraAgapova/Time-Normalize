#include <iostream>

using namespace std;

class Time {
    int hours, minutes, seconds;
public:
    Time(): hours(0), minutes(0), seconds(0) {};
    Time(int h, int m, int s): hours (h), minutes(m), seconds(s){
        Normalize();
    };

    Time& operator += (int s) {
        seconds += s;
        Normalize();
        return *this;
    }

    Time operator - (int s) const {
        Time result = *this;
        result.seconds -= s;
        result.Normalize();
        return result;
    }

    Time& operator -= (int s) {
        seconds -= s;
        Normalize();
        return *this;
    }

    bool operator == (const Time& other) const {
        return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
    }

    void Normalize(){
        if (seconds < 0){
            int minutesDec = (-seconds + 59) / 60;
            minutes -= minutesDec;
            seconds += minutesDec * 60;
        } else if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }

        if (minutes < 0) {
            int hour_decrement = (-minutes + 59) / 60;
            hours -= hour_decrement;
            minutes += hour_decrement * 60;
        } else if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }

        if (hours < 0) {
            hours = 0;
            minutes = 0;
            seconds = 0;
        } else if (hours > 23) {
            hours = 23;
            minutes = 59;
            seconds = 59;
        }
    }

    int ToSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    int GetHours() const {return hours;}
    int GetMinutes() const {return minutes;}
    int GetSeconds() const {return seconds;}
};


int main() {
    Time t1(2, 30, 80);

    // test Normalize()
    cout << "Normalized time: " << t1.GetHours() << ":"
    << t1.GetMinutes() << ":" << t1.GetSeconds() << endl;

    // test ToSeconds()
    cout << "Seconds from the start of the day: "
    << t1.ToSeconds() << endl;

    // test "-=", "-", "=="
    Time t2(3, 30, 44);
    Time t3(3, 31, 45);

    t2 -= 90;
    cout << "Time2 - 90 = " << t2.GetHours() << ":"
         << t2.GetMinutes() << ":" << t2.GetSeconds() << endl;

    Time t4 = t3 - 900;
    cout << "Time4 = Time3 - 900 = " << t4.GetHours() << ":"
    << t4.GetMinutes() << ":" << t4.GetSeconds() << endl;

    if (t4 == t3) {
        cout << "Time4 are equal Time3" << endl;
    }
    else {
        cout << "Time4 are not equal Time3" << endl;
    }

    return 0;
}