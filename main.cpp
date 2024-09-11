#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

enum GameState {
	PLAYING = 1,
	WON = 2,
	LOST = 3
};

void inputListen();
void draw();
void displayHangman(GameState state);
std::string getRandomWord();
std::string getFormattedWord();

const vector<string> words = {"banana", "elephant", "giraffe", "notebook", "umbrella", "chocolate", "pineapple", "airplane", "bicycle", "volcano", "rainbow", "astronaut", "jungle", "puzzle", "mountain", "dolphin", "parrot", "sunglasses", "butterfly", "snowflake"};  
string word;
static int mistakes = 0;
static int guesses = 0;

//hate this >:(
const vector<string> mistakesArray = {
	"____\n|/\n|\n|\n|\n|\n|\n|\n|_____",
	"____\n|/ |\n|\n|\n|\n|\n|\n|\n|_____",
	"____\n|/ |\n| (_)\n|\n|\n|\n|\n|\n|_____",
	"____\n|/ |\n| (_)\n|  |\n|  |\n|\n|\n|\n|_____",
	"____\n|/ |\n| (_)\n| /|\n|  |\n|\n|\n|\n|_____",
	"____\n|/ |\n| (_)\n| /|\\\n|  |\n| \n|\n|\n|_____",
	"____\n|/ |\n| (_)\n| /|\\\n|  |\n| /\n|\n|\n|_____",
	"____\n|/ |\n| (_)\n| /|\\\n|  |\n| / \\ \n|\n|\n|_____"
};

vector<char> guessedLetters = {};

std::string getRandomWord() {
	std::random_device random_device;
	std::mt19937 engine{random_device()};
	std::uniform_int_distribution<int> dist(0, words.size() - 1);
	return words[dist(engine)];
};

std::string getFormattedWord() {
	std::string formatted = "";

	for (int i = 0; i < word.length(); i++) {
		formatted += (std::find(guessedLetters.begin(), guessedLetters.end(), word[i]) != guessedLetters.end()) ? word[i] : '_';
	}

	return formatted;
}

bool didWin() {
	for (char letter : word) {
		if (count(guessedLetters.begin(), guessedLetters.end(), letter) <= 0) return false;
	}

	return true;
}

bool tryToEndGame(std::string input) {
	if (mistakes >= mistakesArray.size() - 1) {
		guesses++;
		displayHangman(LOST);
		return true;
	} else if (didWin()) {
		displayHangman(WON);
		return true;
	} else if (input.compare(word) == 0) {
		displayHangman(WON);
		return true;
	}

	return false;
}

void displayHangman(GameState state) {
	system("cls");
	std::string mistakeString = mistakesArray[mistakes];
	
	cout << endl << "HANGMAN" << endl;
	cout << mistakeString << endl << endl;

	switch (state) {
		case 1:
			cout << "Word: " << getFormattedWord() << endl;
			break;
		case 2:
			cout << "Word: " << word << endl;
			cout << "Congratulations! You guessed the word in " << guesses << " guesses." << endl;
			break;
		case 3:
			cout << "You Lost! The word was: " << word << endl;
			break;
	}
}

void inputListen() {
	cout << endl << "Your guess: ";

	string input;
	cin >> input;

	if (tryToEndGame(input)) return;

	char guess = tolower(input[0]);
	if (std::find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
		cout << "You already guessed that!" << endl;
		inputListen();
		return;
	}

	guessedLetters.push_back(guess);
	guesses++;

	if (word.find(guess) == string::npos) mistakes++;
	if (tryToEndGame(input)) return;

	draw();
}

void draw() {
	system("cls");
	displayHangman(PLAYING);
	inputListen();
}

int main() {
	word = getRandomWord();
	draw();

	return 0;
}