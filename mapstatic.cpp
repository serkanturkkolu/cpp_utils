#include <cstring>

namespace Util{
    namespace Container {
            template<typename Key,typename Val,int Capacity=10>
            class MapStatic{
                Key keyArray[Capacity]={};
                Val valArray[Capacity]={};
                int iter=0;
            public:
                Val& operator[](Key key){
                    for(int i=0;i<iter;++i){
                        if(memcmp(&key,&keyArray[i],sizeof(key))==0){
                            return valArray[i];
                        }
                    }
                    if(iter<Capacity-1){
                        keyArray[iter]=key;
                        return valArray[iter++];
                    }
                    throw std::exception();

                }
                Val erase(Key key){
                    for(int i=0;i<iter;++i){
                        if(memcmp(&key,&keyArray[i],sizeof(key))==0){
                            Val tempVal=valArray[i];
                            valArray[i]=valArray[iter-1];
                            keyArray[i]=keyArray[iter-1];
                            valArray[iter-1]=0;
                            keyArray[iter-1]=0;
                            --iter;
                            return tempVal;
                        }
                    }
                    throw std::exception();
                }
                bool insert(Key key,Val val){
                    for(int i=0;i<iter;++i){
                        if(memcmp(&key,&keyArray[i],sizeof(key))==0){
                            (*this)[key]=val;
                            return true;
                        }
                    }
                    if(iter<Capacity-1){
                        keyArray[iter]=key;
                        valArray[iter++]=val;
                        return true;
                    }
                    return false;
                }
            };
    }
}
