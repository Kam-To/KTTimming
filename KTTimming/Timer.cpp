//
//  Timer.cpp
//  KTTimming
//
//  Created by Kam on 2021/5/10.
//

#include "Timer.hpp"
#include <iostream>

namespace KT {

    using namespace std;
    using namespace std::chrono;

    template <typename D = nanoseconds>
    using TimePoint = time_point<system_clock, D>;

    inline microseconds toDuration(const struct timeval &TV) {
        return seconds(TV.tv_sec) + microseconds(TV.tv_usec);
    }

    class Process {
    public:
        static pair<microseconds, microseconds> getRUsageTimes() {
            struct rusage RU;
            ::getrusage(RUSAGE_SELF, &RU);
            return {
                toDuration(RU.ru_utime),
                toDuration(RU.ru_stime)
            };
        }
        
        static void GetTimeUsage(TimePoint<> &elapsed, nanoseconds &user_time, nanoseconds &sys_time) {
            elapsed = system_clock::now();
            tie(user_time, sys_time) = getRUsageTimes();
        }
    };

    TimeRecord TimeRecord::getCurrentTime() {
        using Seconds = std::chrono::duration<double, std::ratio<1>>;
        std::chrono::nanoseconds user, sys;
        TimeRecord Result;
        TimePoint<> now;
        Process::GetTimeUsage(now, user, sys);
        Result.WallTime = Seconds(now.time_since_epoch()).count();
        Result.UserTime = Seconds(user).count();
        Result.SystemTime = Seconds(sys).count();
        return Result;
    }

    void TimeRecord::operator+=(const TimeRecord &RHS) {
        WallTime   += RHS.WallTime;
        UserTime   += RHS.UserTime;
        SystemTime += RHS.SystemTime;
    }

    void TimeRecord::operator-=(const TimeRecord &RHS) {
        WallTime   -= RHS.WallTime;
        UserTime   -= RHS.UserTime;
        SystemTime -= RHS.SystemTime;
    }

    void TimeRecord::print() {
        printf("UserTime:   %lf\nSystemTime: %lf\nWallTime:   %lf\n\n",
               UserTime, SystemTime, WallTime);
    }

    Timer::Timer(std::string TimerName, std::string TimerDescription) :Name(TimerName), Description(TimerDescription) {
        Running = true;
        StartTime = TimeRecord::getCurrentTime();
    }

    Timer::~Timer() {
        Running = false;
        Time += TimeRecord::getCurrentTime();
        Time -= StartTime;
        printf("Name: %s\nDes: %s\n", Name.c_str(), Description.c_str());
        Time.print();
    }
}
