#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>

#define NUMBER_TO_FILL_WITH -1
#define ARRAY_SIZE 100
#define TIME_TO_SLEEP 0
#define ASCII_FOUND_MARK 219	

void inicializaMenosUno(int *array_to_fill) {
    int i = 0;
    while (i < ARRAY_SIZE) {
        array_to_fill[i] = NUMBER_TO_FILL_WITH;
        i++;
    }
}

void imprimeCarton(int array_to_print[ARRAY_SIZE]) {
    int i = 0;
    
    printf("-------------------------------------------------\n");
    while (i < 100) {
        int line = 0;
        while (line < 10) {
            if (array_to_print[i] == ASCII_FOUND_MARK)
                printf("| %c ", array_to_print[i]);
            else if (array_to_print[i] == -1)
                printf("|   ");
            else
                printf("| %d ", array_to_print[i]);
            line++;
            i++;
        }
        printf("|\n");
        printf("-------------------------------------------------\n");
    }
}

void generaCarton(int *array_to_fill) {
    int i = 0;
    while (i < ARRAY_SIZE / 5) {
        int random_number = rand() % 4;
        array_to_fill[random_number + (i * 5)] = random_number + (i * 5);
        i++;
    }
}

int is_number_in_array(int *array_to_check, int number_to_check) {
    if (number_to_check < ARRAY_SIZE) {
        if (array_to_check[number_to_check] == number_to_check)
            return 1;
    }
    return 0;
}

void change_if_found(int *array_to_check, int number_to_check) {
    if (is_number_in_array(array_to_check, number_to_check)) {
        array_to_check[number_to_check] = ASCII_FOUND_MARK;
    }
}

void generaNumerosAleatorios(int *game_array, int *random_number) {
    *random_number = rand() % ARRAY_SIZE;
    while (is_number_in_array(game_array, *random_number))
        *random_number = rand() % ARRAY_SIZE;
    game_array[*random_number] = *random_number;
}

void count_found(int *array_to_count, int *counter) {
    int i = -1;
	*counter = 0;
    while (++i < ARRAY_SIZE) {
        if (array_to_count[i] == ASCII_FOUND_MARK)
            *counter = *counter + 1;
    }
}

void gen_x_game_numbers(int game_array[], int x, int player1[], int player2[]) {
    int random_number;
	int counter_player1 = 0;
	int counter_player2 = 0;

    while (x > 0) {
        
        generaNumerosAleatorios(game_array, &random_number);
        
        change_if_found(player1, random_number);
        change_if_found(player2, random_number);
        
        printf("Ha salido el numero: %d\n", random_number);
        imprimeCarton(player1);
        imprimeCarton(player2);
	
        x--;
        sleep(TIME_TO_SLEEP);
        system("clear");
		count_found(player1, &counter_player1);
		count_found(player2, &counter_player2);
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

    inicializaMenosUno(player1);
    inicializaMenosUno(player2);
    inicializaMenosUno(game);
    
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