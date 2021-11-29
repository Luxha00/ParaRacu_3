//
// Created by Luka Hauko on 29/11/2021.
//

#ifndef PARARACU_3_NIT_H
#define PARARACU_3_NIT_H

# include <atomic >
# include <thread >


class Nit {
public :
    Nit ();
    ~ Nit ();
private :
    virtual void run ();
    //Nit ( const & Nit);
    Nit & operator =( const Nit &);
protected :
    std :: thread nit ;
    std :: atomic <bool > izhod ;
};

#endif //PARARACU_3_NIT_H
