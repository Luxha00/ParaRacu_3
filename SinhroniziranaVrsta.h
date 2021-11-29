//
// Created by hauko on 11/25/21.
//

#ifndef PARARACU_3_SINHRONIZIRANAVRSTA_H
#define PARARACU_3_SINHRONIZIRANAVRSTA_H

# include <list >
# include <mutex >
# include <condition_variable >
template < typename T >
class SinhroniziranaVrsta {
public :
    SinhroniziranaVrsta (){}
    void vstavi ( const T & podatki );
    T beri ();
private :
    SinhroniziranaVrsta ( const SinhroniziranaVrsta &);
    SinhroniziranaVrsta & operator =( const SinhroniziranaVrsta &);
    std :: list <T > vrsta ;
    std :: mutex mojMutex ;
    std :: conditionVariable mojCv ;
};

template < typename T >
void SinhroniziranaVrsta <T >:: vstavi ( const T& podatki ){
    std :: unique_lock < std :: mutex > lck ( mojMutex );
    vrsta . push_back ( podatki );
    mojCv . notify_one ();
}
template < typename T >
T SinhroniziranaVrsta <T >:: beri (){
    std :: unique_lock < std :: mutex > lck ( mojMutex );
    while ( vrsta . empty ()) mojCv . wait ( lck );
    T result = vrsta . front ();
    vrsta . pop_front ();
    return result ;
}
# end

#endif //PARARACU_3_SINHRONIZIRANAVRSTA_H