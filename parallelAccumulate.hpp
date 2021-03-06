#ifndef _PARALLEL_ACCUMULATE_HPP_
#define _PARALLEL_ACCUMULATE_HPP_
#include <numeric>  
#include <future> 



template< class InputIt, class T, class BinaryOperation >
T parallelAccumulate(InputIt first, InputIt last, T init, BinaryOperation biOp ){
    int dist=std::distance(first,last);
    int coreCount = std::thread::hardware_concurrency();
    std::future<T> th[coreCount];
    for(int i=0;i<coreCount;++i){
        if(i!=coreCount-1){
            th[i]=std::move(std::async(std::launch::async,[&first,&last,&biOp,coreCount,dist,i]{return std::accumulate(std::next(first,(dist*i/coreCount)),std::next(first,(dist*(i+1)/coreCount)),0,biOp);}));
            
        }else
        {
            th[i]=std::move(std::async(std::launch::async,[&first,&last,&biOp,coreCount,dist,i]{return std::accumulate(std::next(first,(dist*i/coreCount)),last,0,biOp);}));
            
        }
        
    } 
    int result=0;
    for(auto &val : th)
        result += val.get();
    return result+init; 
}

template< class InputIt, class T, class BinaryOperation >
T pureParallelAccumulate(InputIt first, InputIt last, T init, BinaryOperation biOp ){ //It doesn't use std::accumulate STL function. But low performance.
    auto local_accumulate = [](InputIt first,InputIt last,T init, BinaryOperation biOp){
        T res{};    
        for(auto iter=first;iter!=last;++iter){
            res+=*iter;
        } 
        return res;
    };
    int dist=std::distance(first,last);
    int coreCount = std::thread::hardware_concurrency(); 
    std::future<T> th[coreCount];
    
    for(int i=0;i<coreCount;++i){
        if(i!=coreCount-1){
            th[i]=std::move(std::async(std::launch::async,local_accumulate,std::next(first,(dist*i/coreCount)),std::next(first,(dist*(i+1)/coreCount)),0,biOp));
            
        }else
        {
            th[i]=std::move(std::async(std::launch::async,local_accumulate,std::next(first,(dist*i/coreCount)),last,0,biOp));
            
        }
        
    } 
    int result=0;
    for(auto &val : th)
        result += val.get();
    return result+init; 
}

#endif
