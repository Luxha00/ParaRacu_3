//
// Created by Luka Hauko on 30/11/2021.
//

# include "reaktor.h"
using namespace std ;
void narediNic (){}
void Reaktor :: novoOpravilo ( function < void () > funk ){
    opravila.vstavi(funk);
}
Reaktor ::~ Reaktor (){
    izhod.store ( true );
    novoOpravilo (& narediNic );
    nit.join ();
}
void Reaktor :: run (){
    while (!izhod.load ())opravila.beri()();
}

