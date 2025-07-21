/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define num_leaders 5
#define int_max 99999999

typedef struct Player {
	char name[20];
	int num_guesses;
} Player;

typedef enum { F = 0, T = 1 } Bool;

int PlayGuessingGame();
void WriteLeaders(const char* filename, Player leaders[]);
void initializeLeaders();
int GetGuess();
void InsertPlayer(Player leaders[], Player current_player);
void Printleaders(Player leaders[]);
void ReadLeaders(const char* filename, Player leaders[]);
void WriteLeaders(const char* filename, Player leaders[]);

Player leaders[num_leaders];

int main() {

	initializeLeaders();

	//read file
	ReadLeaders("C:/Users/ddavi/OneDrive/CSE240/leaderboard.txt", leaders);

	printf("Welcome! Press 'q' to quit or any other key to continue: \n");

	char c, game_over = 0;

	while (!game_over) {

		scanf(" %c", &c);

		if (c == 'q') {
			game_over = 1;
			printf("Bye Bye!\n");
		}

		else {
			Player current_player;
			printf("Please enter your name to start: \n");
			scanf(" %s", &current_player.name);

			current_player.num_guesses = PlayGuessingGame();
			printf("You made %d guesses.\n", current_player.num_guesses);

			InsertPlayer(leaders, current_player);
			Printleaders(leaders);

			printf("Press 'q' to quit or any other key to continue: \n");
		}

	}

	//write to file
	WriteLeaders("C:/Users/ddavi/OneDrive/CSE240/leaderboard.txt", leaders);

	return 0;

}

int PlayGuessingGame() {

	// Generate a random number between 10 and 100 and find its square root
	srand((unsigned int)time(NULL)); // Seed rand with current time
	int numberToGuess = rand() % 91 + 10;
	double squareRoot = sqrt(numberToGuess);
	printf("%.8f is the square root of what number?\n", squareRoot);

	Bool done = F;
	int guess;
	int attempts = 0;

	while (!done) {
		guess = GetGuess();
		attempts++;

		if (guess < numberToGuess)
			printf("Too low, guess again: ");
		else if (guess > numberToGuess)
			printf("Too high, guess again: ");
		else
			done = T;
	}

	printf("You got it, baby!\n");
	return attempts;

}

void initializeLeaders() {

	for (int i = 0; i < num_leaders; i++) {
		leaders[i].num_guesses = int_max;
		strcpy(leaders[i].name, "");
	}

}

int GetGuess() {

	int guess;
	scanf(" %d", &guess);
	return guess;

}

void InsertPlayer(Player leaders[], Player current_player) {
	for (int i = 0; i < num_leaders; i++) {

		if (current_player.num_guesses < leaders[i].num_guesses) {

			for (int j = num_leaders - 1; j > i; j--) {
				if (j > 0) {
					leaders[j] = leaders[j - 1];
				}
			}

			leaders[i] = current_player;
			break;

		}
	}
}

void Printleaders(Player leaders[]) {

	printf("Here are the current leaders: \n");
	for (int i = 0; i < num_leaders; i++) {
		if (leaders[i].num_guesses != int_max) {
			printf("%s has made %d guesses\n", leaders[i].name, leaders[i].num_guesses);
		}
	}

}

void ReadLeaders(const char* filename, Player leaders[]) {

	FILE* file = fopen(filename, "r");

	//check for file
	if (file == NULL) {
		return;
	}

	for (int i = 0; fscanf(file, "%19s %d", leaders[i].name, &leaders[i].num_guesses) == 2 && i < num_leaders; i++) {}

	fclose(file);

}

void WriteLeaders(const char* filename, Player leaders[]) {

	FILE* file = fopen(filename, "w");

	for (int i = 0; i < num_leaders; i++) {
		if (leaders[i].num_guesses != int_max) {
			fprintf(file, "%s %d\n", leaders[i].name, leaders[i].num_guesses);
		}
	}

	fclose(file);
}

*/