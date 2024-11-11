#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>

#define ARRAY_SIZE 100
#define TIME_TO_SLEEP 0
#define ASCII_FOUND_MARK 219

void fill_array(int *array_to_fill, int number_to_fill_with) {
    int i = 0;
    while (i < ARRAY_SIZE) {
        array_to_fill[i] = number_to_fill_with;
        i++;
    }
}

void print_array(int array_to_print[ARRAY_SIZE]) {
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

void gen_player_array(int *array_to_fill) {
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

int gen_game_number(int *game_array) {
    int random_number = rand() % ARRAY_SIZE;
    while (is_number_in_array(game_array, random_number))
        random_number = rand() % ARRAY_SIZE;
    game_array[random_number] = random_number;
    return random_number;
}

int count_found(int *array_to_count) {
    int i = -1;
    int counter = 0;
    while (++i < ARRAY_SIZE) {
        if (array_to_count[i] == ASCII_FOUND_MARK)
            counter++;
    }
    return counter;
}

void gen_x_game_numbers(int game_array[], int x, int player1[], int player2[]) {
    int random_number;
    while (x > 0) {
        
        random_number = gen_game_number(game_array);
        
        change_if_found(player1, random_number);
        change_if_found(player2, random_number);
        
        printf("Ha salido el numero: %d\n", random_number);
        print_array(player1);
        print_array(player2);
        
        x--;
        sleep(TIME_TO_SLEEP);
        system("clear");
        if (count_found(player1) == ARRAY_SIZE / 5 || count_found(player2) == ARRAY_SIZE / 5)
            return ;
    }
}

int main()
{
    srand(time(NULL));
    
    int player1[ARRAY_SIZE];
    int player2[ARRAY_SIZE];
    int game[ARRAY_SIZE];
    
    
    fill_array(player1, -1);
    fill_array(player2, -1);
    fill_array(game, -1);
    
    gen_player_array(player1);
    gen_player_array(player2);
    
    gen_x_game_numbers(game, ARRAY_SIZE, player1, player2);
    
    printf("Mi cartón: \n");
    print_array(player1);
    
    printf("Tu cartón: \n");
    print_array(player2);
    
    printf("Numeros que han salido: \n");
    print_array(game);
    
    if (count_found(player1) == ARRAY_SIZE / 5 && count_found(player2) == ARRAY_SIZE / 5)
        printf("Hemos empatado!!\n");
    else if (count_found(player1) == ARRAY_SIZE / 5)
        printf("He ganado yo!!\n");
    else if (count_found(player2) == ARRAY_SIZE / 5)
        printf("Has ganado tu!!");
    
    return 0;
}