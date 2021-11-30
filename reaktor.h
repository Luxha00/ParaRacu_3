//
// Created by Luka Hauko on 30/11/2021.
//

#ifndef PARARACU_3_REAKTOR_H
#define PARARACU_3_REAKTOR_H

# include <functional >
# include "sinhroniziranaVrsta.h"
# include "nit.h"
class Reaktor : public Nit {
public :
    void novoOpravilo ( std :: function < void () > funk );
    virtual ~Reaktor();
private :
    virtual void run ();
    sinhroniziranaVrsta <std::function <void ()>> opravila ;
};

#endif //PARARACU_3_REAKTOR_H
