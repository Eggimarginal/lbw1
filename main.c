/*
 * main.c
 *
 *  Created on:
 *      Author:
 */

/* подключение вспомогательных функций */
#include "lifegame.c"

/* если нужно подключить другие заголовочные файлы - это нужо делать здесь */

#include <unistd.h>
#include <stdlib.h>

/* количество поколений */
#define NUM_GENERATIONS 50


/* функции, которые необходимо реализовать */

/* эта функция должна устанавливать состояние всех ячеек
   следующего поколения и вызывать 
   finalize_evolution() для обновления текущего состояния мира
   на следующее поколение */
void next_generation(void);

/* эта функция должна возвращать состояние ячейки в позиции (x,y)
   в следующем поколении в соответствии с правилами игры "Жизнь"
   (смотри описание игры) */
int get_next_state(int x, int y);

/* эта функция должна вычислять количество живых соседей ячейки в позиции (x,y) */
int num_neighbors(int x, int y);

int main(void)
{
	int n;
	initialize_world ();
	/* TODO: инициализируйте мир */


	for (n = 0; n < NUM_GENERATIONS; n++) {
		next_generation();
		output_world ();
		sleep (1);
		system ("clear");
	}
	/* TODO: выведите финальное состояние мира */
	output_world ();
	return 0;
}

void next_generation(void) {
	 int x,y;
	 for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			get_next_state(x,y);
		}
	}
	finalize_evolution(); 
}

int get_next_state(int x, int y) {
	if ( get_cell_state (x,y)==DEAD && num_neighbors(x,y)==3 ){
		nextstates[x][y]=ALIVE;
	}
	else if (get_cell_state (x,y)==ALIVE && ( num_neighbors(x,y)==3 || num_neighbors(x,y)==2 ) ){
		nextstates[x][y]=ALIVE;
	}
	else {
		nextstates[x][y]=DEAD;
	}
	return nextstates[x][y];
}

int num_neighbors(int x, int y) {
	int num = 0;
	int t,p;
	for (p=x-1; p<x+2; p++) {
		for (t=y-1; t<y+2; t++) {
			num=num+get_cell_state (p,t);
		}
	}
	num=num-get_cell_state (x,y);
	return num;	
}