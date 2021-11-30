//
// Created by Luka Hauko on 30/11/2021.
//
# include "nit.h"
# include <chrono >
# include <functional >
# include <iostream >
using namespace std ;
using namespace std :: chrono ;
Nit :: Nit (): nit ( bind (& Nit :: run , this )) , izhod ( false ) {}
void Nit :: run (){
    while (! izhod . load ()){
        cout <<" Delo " << endl ;
        this_thread :: sleep_for ( milliseconds (500));
    }
}

Nit::~Nit() {
    if( izhod . load ()) return ;
    izhod . store ( true );
    nit . join ();
}
