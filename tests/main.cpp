#include "SLList.h"

int main(){
    SLList<int> lista;
    for(int i = 0; i < 500; i++){
        lista.push_front(i);
    }
    lista.print();
    return 0;
}
