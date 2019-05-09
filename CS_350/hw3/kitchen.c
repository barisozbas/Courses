#include "meal.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define GLOVE_COUNT 3
#define POT_SIZE 3
#define APPRENTICE_COUNT 3
#define MEALS_TO_PREPARE 4
#define REQUIRED_INGREDIENTS 3

struct meal Menu[4] = {
    {"Menemen", {{"Tomato", 3}, {"Onion", 4}, {"Egg", 1}}, 10},
    {"Chicken Pasta", {{"Pasta", 2}, {"Chicken", 5}, {"Curry", 2}}, 8}, 
    {"Beef Steak", {{"Beef", 7}, {"Pepper", 3}, {"Garlic", 2}}, 13}, 
    {"Ali Nazik", {{"Eggplant", 4}, {"Lamb Meat", 4}, {"Yoghurt", 1}}, 10}
};  // Info about the meal

int meal_index = 0;
int meal_ing_counter = 0;
int pot_counter = 0;

// Define all required mutexes here
pthread_mutex_t glove_mutexes[GLOVE_COUNT] = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pot_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fridge_mutex = PTHREAD_MUTEX_INITIALIZER;

void put_gloves(int apprentice_id) {
    printf("Apprentice %d is picking gloves \n", apprentice_id);
    pthread_mutex_lock(&glove_mutexes[apprentice_id]);
    pthread_mutex_lock(&glove_mutexes[((apprentice_id + 1) % GLOVE_COUNT)]);
    printf("Apprentice %d has picked gloves\n", apprentice_id);
}

void remove_gloves(int apprentice_id) {
    pthread_mutex_unlock(&glove_mutexes[apprentice_id]);
    pthread_mutex_unlock(&glove_mutexes[((apprentice_id + 1) % GLOVE_COUNT)]);
    printf("Apprentice %d has removed gloves\n", apprentice_id);
}

void pick_ingredient(int apprentice_id, int* ing_index) {
    put_gloves(apprentice_id);
    pthread_mutex_lock(&fridge_mutex);
    *ing_index = meal_ing_counter;
    printf("Apprentice %d has taken ingredient %s\n", apprentice_id, Menu[meal_index].ingredients[*ing_index].name);
    meal_ing_counter = meal_ing_counter + 1;
    pthread_mutex_unlock(&fridge_mutex);
    remove_gloves(apprentice_id);
} 

void prepare_ingredient(int apprentice_id, int meal_index, int ing_index) {
    printf("Apprentice %d is preparing: %s \n", apprentice_id, Menu[meal_index].ingredients[ing_index].name);
    sleep(Menu[meal_index].ingredients[ing_index].time_to_process);
    printf("Apprentice %d is done preparing %s \n", apprentice_id, Menu[meal_index].ingredients[ing_index].name);
}

void put_ingredient(int id, int meal_index, int ing_index) {
    while(1) {
        if(pot_counter != REQUIRED_INGREDIENTS) {
            printf("Apprentince %d is trying to put %s into pot\n", id, Menu[meal_index].ingredients[ing_index].name);
            pthread_mutex_lock(&pot_mutex);
            printf("Apprentince %d has put %s into pot\n", id, Menu[meal_index].ingredients[ing_index].name);
            pot_counter = pot_counter + 1;
            pthread_mutex_unlock(&pot_mutex);
            break;
        }
    }
}

void help_chef(int apprentice_id) {
    if(meal_ing_counter == REQUIRED_INGREDIENTS) return;
    int meal_ingredient_index;
    pick_ingredient(apprentice_id, &meal_ingredient_index);
    prepare_ingredient(apprentice_id, meal_index, meal_ingredient_index);
    put_ingredient(apprentice_id, meal_index, meal_ingredient_index);
}

void *apprentice(int *apprentice_id) {
    printf("Im apprentice %d\n", *apprentice_id);
    while(1) {
        help_chef(*apprentice_id);
        break;
    }
    pthread_exit(NULL);
}

void *chef() {
    while(1) {
        if(pot_counter == POT_SIZE) {
            pthread_mutex_lock(&pot_mutex);
            printf("Chef is preparing meal %s\n", Menu[meal_index].name);
            sleep(Menu[meal_index].time_to_prepare);
            printf("Chef prepared the meal %s\n",  Menu[meal_index].name);
            meal_ing_counter = 0;
            pot_counter = 0;
            pthread_mutex_unlock(&pot_mutex);
            break;
        }
    }
    pthread_exit(NULL);
}

void prepare_meal(int meal_to_prep) {
    pthread_t apprentice_threads[APPRENTICE_COUNT];
    pthread_t chef_thread;
    meal_index = meal_to_prep;

    int apprentice_ids[APPRENTICE_COUNT] = {0 ,1 ,2};
    pthread_create(&chef_thread, NULL, chef, NULL);

    for(size_t i = 0; i < APPRENTICE_COUNT; i++)
        pthread_create(&apprentice_threads[i], NULL, apprentice, &apprentice_ids[i]);

    for (size_t i = 0; i < APPRENTICE_COUNT; i++)
        pthread_join(apprentice_threads[i],NULL);
    pthread_join(chef_thread, NULL);
}


int main(int argc,char* argv[]) {
    int input = atoi(argv[1]);

  if(input == 0)
	printf("Customer wants: Menemen\n");
  if(input == 1)
	printf("Customer wants: Chicken Pasta\n");
  if(input == 2)
	printf("Customer wants: Beef Steak\n");
  if(input == 3)
	printf("Customer wants: Ali Nazik\n");

  prepare_meal(input);
  
  

}



