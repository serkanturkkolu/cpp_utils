#include <chrono>

enum class MeasureTimeType{
    NanoSeconds,
    MicroSeconds,
    MilliSeconds,
    Seconds,
    Minutes,
    Hours
};

template<class Functor>
auto measureSpentTime(Functor func,MeasureTimeType measureTimeType=MeasureTimeType::NanoSeconds)->std::chrono::time_point<std::chrono::high_resolution_clock>::rep{ // You can use this function with std::bind function for void parameter -> "func()".
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end=std::chrono::high_resolution_clock::now();
    auto spentTime=-1LL;
    switch (measureTimeType)
    {
    case MeasureTimeType::NanoSeconds:
        spentTime=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); 
        break;
    case MeasureTimeType::MicroSeconds:
        spentTime=std::chrono::duration_cast<std::chrono::microseconds>(end-start).count(); 
        break;
    case MeasureTimeType::MilliSeconds:
        spentTime=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); 
        break;
    case MeasureTimeType::Seconds:
        spentTime=std::chrono::duration_cast<std::chrono::seconds>(end-start).count(); 
        break; 
    case MeasureTimeType::Minutes:
        spentTime=std::chrono::duration_cast<std::chrono::minutes>(end-start).count(); 
        break;
    case MeasureTimeType::Hours:
        spentTime=std::chrono::duration_cast<std::chrono::hours>(end-start).count(); 
        break;     
    } 
    return spentTime;
}
