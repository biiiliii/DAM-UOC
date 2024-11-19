#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>

#define NUMBER_TO_FILL_WITH -1
#define ARRAY_SIZE 100
#define TIME_TO_SLEEP 0
#define ASCII_FOUND_MARK 219	

void inicializaMenosUno(int entero, int *tabla) {
    int i = 0;
    while (i < ARRAY_SIZE) {
        tabla[i] = NUMBER_TO_FILL_WITH;
        i++;
    }
}

void imprimeCarton(int tabla[ARRAY_SIZE]) {
    int i = 0;
    
    printf("-------------------------------------------------\n");
    while (i < 100) {
        int line = 0;
        while (line < 10) {
            if (tabla[i] == ASCII_FOUND_MARK)
                printf("| %c ", tabla[i]);
            else if (tabla[i] == -1)
                printf("|   ");
            else
                printf("| %d ", tabla[i]);
            line++;
            i++;
        }
        printf("|\n");
        printf("-------------------------------------------------\n");
    }
}

void generaCarton(int *tabla) {
    int i = 0;
    while (i < ARRAY_SIZE / 5) {
        int entero = rand() % 4;
        tabla[entero + (i * 5)] = entero + (i * 5);
        i++;
    }
}

int is_number_in_array(int *tabla, int entero) {
    if (entero < ARRAY_SIZE) {
        if (tabla[entero] == entero)
            return 1;
    }
    return 0;
}

void count_found(int *array_to_count, int *counter) {
    int i = -1;
	*counter = 0;
    while (++i < ARRAY_SIZE) {
        if (array_to_count[i] == ASCII_FOUND_MARK)
            *counter = *counter + 1;
    }
}



void generaNumerosAleatorios(int *tabla, int *entero) {
    *entero = rand() % ARRAY_SIZE;
    while (is_number_in_array(tabla, *entero))
        *entero = rand() % ARRAY_SIZE;
    tabla[*entero] = *entero;
}

void marcaAciertos(int *tabla, int aleatorio, int *aciertos_carton) {
    if (is_number_in_array(tabla, aleatorio)) {
        tabla[aleatorio] = ASCII_FOUND_MARK;
    }
	count_found(tabla, aciertos_carton);
}

void gen_x_game_numbers(int tabla[], int x, int player1[], int player2[]) {
    int entero;
	int counter_player1 = 0;
	int counter_player2 = 0;

    while (x > 0) {
        
        generaNumerosAleatorios(tabla, &entero);
        
        marcaAciertos(player1, entero, &counter_player1);
        marcaAciertos(player2, entero, &counter_player2);
        
        printf("Ha salido el numero: %d\n", entero);
        imprimeCarton(player1);
        imprimeCarton(player2);
	
        x--;
        sleep(TIME_TO_SLEEP);
        system("clear");
		if (counter_player1 == ARRAY_SIZE / 5 || counter_player2 == ARRAY_SIZE / 5)
			return ;
    }
}

int main()
{
    srand(time(NULL));
    
    int player1[ARRAY_SIZE];
    int player2[ARRAY_SIZE];
    int game[ARRAY_SIZE];
    
    int counter_player1 = 0;
	int counter_player2 = 0;

    inicializaMenosUno(ARRAY_SIZE, player1);
    inicializaMenosUno(ARRAY_SIZE, player2);
    inicializaMenosUno(ARRAY_SIZE, game);
    
    generaCarton(player1);
    generaCarton(player2);
    
    gen_x_game_numbers(game, ARRAY_SIZE, player1, player2);
    
    printf("Mi cartón: \n");
    imprimeCarton(player1);
    
    printf("Tu cartón: \n");
    imprimeCarton(player2);
    
    printf("Numeros que han salido: \n");
    imprimeCarton(game);
    
	count_found(player1, &counter_player1);
	count_found(player2, &counter_player2);

    if (counter_player1 == ARRAY_SIZE / 5 && counter_player2 == ARRAY_SIZE / 5)
        printf("Hemos empatado!!\n");
    else if (counter_player1 == ARRAY_SIZE / 5)
        printf("He ganado yo!!\n");
    else if (counter_player2 == ARRAY_SIZE / 5)
        printf("Has ganado tu!!");
    
    return 0;
}