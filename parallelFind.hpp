#ifndef _PARALLEL_FIND_HPP_
#define _PARALLEL_FIND_HPP_

#include <future> 
#include <algorithm>
template<class InputIterator, class T>
InputIterator parallelFind (InputIterator first, InputIterator last, const T& val)
{ 
    int dist=std::distance(first,last);
    int coreCount = std::thread::hardware_concurrency();
    std::future<InputIterator> th[coreCount];

    for(int i=0;i<coreCount;++i){
        if(i!=coreCount-1){
            th[i]=std::move(std::async(std::launch::async,[&first,&last,&val,coreCount,dist,i]{return std::find(std::next(first,(dist*i/coreCount)),std::next(first,(dist*(i+1)/coreCount)),val);}));
            
        }else
        {
            th[i]=std::move(std::async(std::launch::async,[&first,&last,&val,coreCount,dist,i]{return std::find(std::next(first,(dist*i/coreCount)),last,val);}));
            
        }
    } 
  
    InputIterator result;
    for(int i=0;i<coreCount;++i){
        if(i!=coreCount-1){
            result = th[i].get();
            if(result!=std::next(first,(dist*(i+1)/coreCount))){
                return result;
            }
            
        }else{
            result = th[i].get();
            if(result!=last){
                return result;
            }
        }
    }
    return last; 
}
#endif