//
//  Timer.hpp
//  KTTimming
//
//  Created by Kam on 2021/5/10.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>
#include <tuple>
#include <string>

namespace KT {
    class TimeRecord {
        double WallTime;
        double UserTime;
        double SystemTime;
    public:
        TimeRecord() : WallTime(0), UserTime(0), SystemTime(0) {}
        double getProcessTime() const { return UserTime + SystemTime; }
        double getUserTime() const { return UserTime; }
        double getSystemTime() const { return SystemTime; }
        double getWallTime() const { return WallTime; }
        void operator+=(const TimeRecord &RHS);
        void operator-=(const TimeRecord &RHS);
        void print();
        static TimeRecord getCurrentTime();
    };

    class Timer {
        TimeRecord Time;          ///< The total time captured.
        TimeRecord StartTime;     ///< The time startTimer() was last called.
        std::string Name;         ///< The name of this time variable.
        std::string Description;  ///< Description of this time variable.
        bool Running;
    public:
        explicit Timer(std::string TimerName, std::string TimerDescription="");
        ~Timer();
    };
}

#endif /* Timer_hpp */
