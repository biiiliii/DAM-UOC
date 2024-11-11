#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main() {
    int aleatorio, num = 0, usuario, uno = 171, dos = 171, tres = 171, cuatro = 171, cinco = 171, uno_u, dos_u, tres_u, cuatro_u, cinco_u;
    bool uno_b = false, dos_b = false, tres_b = false, cuatro_b = false, cinco_b = false, premio = false;
    //Generamos numero aleatorio entre 0 y 9
    srand(time(NULL));
    aleatorio = rand() % 10;
    //Generamos los 5 dígitos
    while (num < 5) {
        printf("%d\n", aleatorio);
        sleep(1);
        num = num + 1;
        system("clear");
        //Almacenamos los dígitos en variables
        if (num == 1) uno = aleatorio;
        if (num == 2) dos = aleatorio;
        if (num == 3) tres = aleatorio;
        if (num == 4) cuatro = aleatorio;
        if (num == 5) cinco = aleatorio;
//Printamos como char para que aparezca el carácter 171
        printf("*****\n");
        printf("* %d %c %c %c %c *\n", uno, dos + 48, tres + 48, cuatro + 48, cinco + 48);
        printf("*****\n");
        aleatorio = rand() % 10;
    }
    //Preguntamos al usuario que número ha jugado
    printf("Que numero has jugado?\n");
    scanf("%d", &usuario);
    //Extraemos los dígitos del número introducido por el usuario
    uno_u = usuario / 10000;
    dos_u = (usuario % 10000) / 1000;
    tres_u = (usuario % 1000) / 100;
    cuatro_u = (usuario % 100) / 10;
    cinco_u = usuario % 10;

    //Desvelamos los números acertados
    if (uno == uno_u) { uno_u += 48; uno_b = true; } else { uno_u = 171; }
    if (dos == dos_u) { dos_u += 48; dos_b = true; } else { dos_u = 171; }
    if (tres == tres_u) { tres_u += 48; tres_b = true; } else { tres_u = 171; }
    if (cuatro == cuatro_u) { cuatro_u += 48; cuatro_b = true; } else { cuatro_u = 171; }
    if (cinco == cinco_u) { cinco_u += 48; cinco_b = true; } else { cinco_u = 171; }
    
    printf("*****\n");
    printf("* %c %c %c %c %c *\n", uno_u, dos_u, tres_u, cuatro_u, cinco_u);
    printf("*****\n");
    //Vamos a mirar ahora que premios tienes
    //los 5 números 1000000 euros
    if (uno_b && dos_b && tres_b && cuatro_b && cinco_b) {
        printf("Has acertado los 5 números. Has ganado 1000000 euros!!\n");
    }
    //los 4 últimos 10000 euros
    if (!uno_b && dos_b && tres_b && cuatro_b && cinco_b) {
		printf("Has acertado los 4 ultimos números. Has ganado 100000 euros!!\n");
    }
    //los 3 últimos 1000 euros
    if (!uno_b && !dos_b && tres_b && cuatro_b && cinco_b) {
        printf("Has acertado los 3 ultimos numeros. Has ganado 1000 euros!!\n");
    }
    //los 2 últimos 100 euros
    if (!uno_b && !dos_b && !tres_b && cuatro_b && cinco_b) {
        printf("Has acertado los 2 ultimos numeros. Has ganado 100 euros!!\n");
    }
    //el último o el primero, o ambos, 100 euros
    if ((uno_b && !dos_b && !tres_b && !cuatro_b && !cinco_b) || (!uno_b && !dos_b && !tres_b && !cuatro_b && cinco_b)) {
        printf("Has acertado el primero o el ultimo. Has ganado 10 euros!!\n");
    }
    return 0;
}