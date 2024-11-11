#include <stdio.h>
#include <stdbool.h>

int main()
{
    int centenas, decenas, unidades, millares, contador, num;
    bool cumple;
    
    contador = 0;
    num = 100;
    
    while (num < 10000) {
        cumple = false;
        
        if (num < 1000){
            centenas = num / 100;
            decenas = num % 100 / 10;
            unidades = num % 10;
            
            if (centenas + decenas == unidades) {
                cumple = true;
                contador += 1;
            }
        }
        else {
            millares = num / 1000;
            centenas = num % 1000 / 100;
            decenas = num % 100 / 10;
            unidades = num % 10;
            
            if (millares + centenas + decenas == unidades) {
                cumple = true;
                contador += 1;
            }
        }
        if (cumple) {
            printf("%d. %d\n", contador, num);
        }
        num += 1;
        
        
        
    }

    return 0;
}