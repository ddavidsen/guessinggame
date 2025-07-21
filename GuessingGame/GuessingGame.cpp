#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

int GetGuess();
int PlayGuessingGame();

class Player {

public:
	Player() : num_guesses(99999999) {}
	Player(string nm, int ng) : name(nm), num_guesses(ng) {};

	string getName() const { return name; }
	int getNumGuesses() const { return num_guesses; }
	char* getNamePtr() { return &name[0]; }

	void setName(string nm) { name = nm; }
	void setNumGuesses(int ng) { num_guesses = ng; }

private:
	string name;
	int num_guesses;

};

class LeaderBoard {

public:
	LeaderBoard() {
		for (int i = 0; i < NUM_LEADERS; i++) {
			leaders[i] = Player("", 99999999);
		}
	};

	void InsertPlayer(Player player) {
		for (int i = 0; i < NUM_LEADERS; i++) {
			if (player.getNumGuesses() < leaders[i].getNumGuesses()) {
				for (int j = NUM_LEADERS - 1; j > i; j--) {
					leaders[j] = leaders[j - 1];
				}
				leaders[i] = player;
				break;
			} 
		}
	};

	void PrintLeaders() {
		cout << "Here are the current leaders: " << endl;
		for (int i = 0; i < NUM_LEADERS; i++) {
			if (leaders[i].getNumGuesses() != 99999999) {
				cout << leaders[i].getName() << " has made " << leaders[i].getNumGuesses() << " guesses " << endl;
			}
		}
	}

	void ReadLeaders(const string& filename) {
		FILE* file = fopen(filename.c_str(), "r");
		if (file != NULL) {
			char name[20];
			int guesses;
			for (int i = 0; i < NUM_LEADERS && fscanf(file, "% 19s %d", name, &guesses) == 2; i++) {
				leaders[i].setName(string(name));
				leaders[i].setNumGuesses(guesses);
			}
			fclose(file);
		} 
	}

	void WriteLeaders(const string& filename) {
		FILE* file = fopen(filename.c_str(), "w");
		if (file != NULL) {
			for (int i = 0; i < NUM_LEADERS; i++) {
				if (leaders[i].getNumGuesses() != 99999999) {
					fprintf(file, "%s %d\n", leaders[i].getName().c_str(), leaders[i].getNumGuesses());
				}
			}
			fclose(file);
		}
	}

private:
	static const int NUM_LEADERS = 5;
	Player leaders[NUM_LEADERS];

};

int main(int argc, const char * argv[]) {

	LeaderBoard leaderboard;

	leaderboard.ReadLeaders("C:/Users/ddavi/OneDrive/CSE240/leaderboard.txt");

	cout << "Welcome! Press 'q' to quit or any other key to continue: " << endl;

	char c;
	bool game_over = false;

	while (!game_over) {

		cin >> c;

		if (c == 'q') {
			game_over = true;
			cout << "Bye Bye!" << endl;
		}

		else {
			string playerName;
			cout << "Please enter your name to start: " << endl;
			cin >> playerName;

			Player current_player;
			current_player.setName(playerName);
			current_player.setNumGuesses(PlayGuessingGame());

			leaderboard.InsertPlayer(current_player);
			leaderboard.PrintLeaders();

			cout << "Press 'q' to quit or any other key to continue: " << endl;
		}
	}

	return 0;

}

int PlayGuessingGame() {

	// Generate a random number between 10 and 100 and find its square root
	srand((unsigned int)time(NULL)); // Seed rand with current time
	int numberToGuess = rand() % 91 + 10;
	double squareRoot = sqrt(numberToGuess);
	cout << squareRoot << " is the square root of what number?" << endl;

	bool done = false;
	int guess;
	int attempts = 0;

	while (!done) {
		guess = GetGuess();
		attempts++;

		if (guess < numberToGuess)
			cout << "Too low, guess again: " << endl;
		else if (guess > numberToGuess)
			cout << "Too high, guess again: " << endl;
		else
			done = true;
	}

	cout << "You got it, baby!" << endl;
	return attempts;

}

int GetGuess() {
	int guess;
	cin >> guess;
	return guess;
}