#include <chrono>
#include <functional>

enum class MeasureTimeType{
    NanoSeconds,
    MicroSeconds,
    MilliSeconds,
    Seconds,
    Minutes,
    Hours
};

template<class Functor,class... TArgs>
auto measureSpentTime(MeasureTimeType measureTimeType,Functor func,TArgs&&... args)->std::chrono::time_point<std::chrono::high_resolution_clock>::rep{
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<TArgs>(args)...);
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
