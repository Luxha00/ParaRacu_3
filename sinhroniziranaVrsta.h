//
// Created by hauko on 11/25/21.
//

#ifndef PARARACU_3_SINHRONIZIRANAVRSTA_H
#define PARARACU_3_SINHRONIZIRANAVRSTA_H

# include <list >
# include <mutex >
# include <condition_variable >
template < typename T >
class sinhroniziranaVrsta {
public :
    sinhroniziranaVrsta (){}
    void vstavi ( const T & podatki );
    T beri ();
    bool empty ();
    int vrstaSize();
    std :: list <T > vrsta ;
private :
    sinhroniziranaVrsta (const sinhroniziranaVrsta &);
    sinhroniziranaVrsta & operator =(const sinhroniziranaVrsta &);
    std :: mutex mojMutex ;
    std :: condition_variable mojCv ;
};

template < typename T >
void sinhroniziranaVrsta <T >:: vstavi (const T& podatki ){
    std :: unique_lock < std :: mutex > lck ( mojMutex );
    vrsta . push_back ( podatki );
    mojCv . notify_one ();
}
template < typename T >
T sinhroniziranaVrsta <T >:: beri (){
    std :: unique_lock < std :: mutex > lck ( mojMutex );
    while ( vrsta . empty ()) mojCv . wait ( lck );
    T result = vrsta . front ();
    vrsta . pop_front ();
    return result ;
}

template < typename T >
bool sinhroniziranaVrsta <T>:: empty(){
    if(vrsta.empty()){
        return true;
    }
    else return false;
}

template <typename T>
int sinhroniziranaVrsta <T>:: vrstaSize() {
    return vrsta.size();
}

#endif //PARARACU_3_SINHRONIZIRANAVRSTA_H
