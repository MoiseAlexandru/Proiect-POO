#include <iostream>
#include <cstring>
#include <ctime>
#include <string>
#include <set>

int minNumberOfPlayers = 2;
int maxNumberOfPlayers = 4;
int numberOfPlayers = 0;

/// Clasa de zaruri
/// Contine doua zaruri, aruncare de zaruri, retine cate duble s-au dat la rand

class Dices {
	public:
	int dice1;
	int dice2;
	int consecutiveRolls;
	Dices() {
		dice1 = 1;
		dice2 = 1;
		consecutiveRolls = 0;
	}
	void diceRoll() {
		dice1 = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;
		if(dice1 == dice2)
			consecutiveRolls++;
	}
};


/// Pion - tine informatii despre culoare, pozitia jucatorului, nume jucator
class Pawn {
public:
	int position;
	int player;
	std::string playerName;
	std::string color;
	Pawn() = default;
	Pawn(int player, std::string playerName, std::string color) {
		this -> position = 1;
		this -> player = player;
		this -> playerName = playerName;
		this -> color = color;
	};
};


/// Jucator - tine practic cam toate informatiile jucatorului
class Player {
private:
	int bani;
public:
	std::string playerName;
	int position;
	Pawn pawn;
	Dices dices;
	Player() = default;
	Player(std::string name, Pawn pion)
	{
		playerName = name;
		this -> pawn = pion;
	};
};

void turn()
{

}

void readNumberOfPlayers()
{
	std::cout << "Enter the number of players (" << minNumberOfPlayers << "-" << maxNumberOfPlayers << "): ";
	std::string s;
	getline(std::cin, s);
	bool goodInput = true;
	for(int i = 0; i < s.size(); i++)
		if(!isdigit(s[i]))
			goodInput = false;
	if(goodInput == false || s.size() >= 9)
	{
		std::cout << "Wrong input format, try again.\n\n";
		readNumberOfPlayers();
		return;
	}
	for(int i = 0; i < s.size(); i++)
		numberOfPlayers = numberOfPlayers * 10 + s[i] - '0';
	if(numberOfPlayers < minNumberOfPlayers || numberOfPlayers > maxNumberOfPlayers)
	{
		std::cout << s << " " << numberOfPlayers << "\n";
		std::cout << "There should be between " << minNumberOfPlayers << " and " << maxNumberOfPlayers << " players. Try again.\n";
		numberOfPlayers = 0;
		readNumberOfPlayers();
		return;
	}
};

Player players[100];

std::set <std::string> remainingColors;

void readPlayerNames()
{
	std::cout << "Now the players!\n";
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		std::string name;
		std::string color;
		std::cout << "Enter the name of player " << i << ":\n";
		getline(std::cin, name);
		std::cout << "Enter the name of the color. You can choose between:\n";
		int cnt = 0;
		for(auto it : remainingColors)
		{
			cnt++;
			std::cout << cnt << ". " << it << "\n";
		}
		std::cin >> color;
		while(remainingColors.find(color) == remainingColors.end()) {
			std::cout << "Wrong input. Try again: ";
			std::cin >> color;
		}
		auto posDelete = remainingColors.find(color);
		remainingColors.erase(posDelete);
		Pawn pawn(i, name, color);
		Player currentPLayer(name, pawn);
		players[i] = currentPLayer;
	}
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		std::cout << players[i].playerName << " will play with the " << players[i].pawn.color << " pawn!\n";
	}
}

void intro()
{

}

void startOfGame()
{
	srand(time(NULL));
	intro();
	readNumberOfPlayers();
	remainingColors.insert("red");
	remainingColors.insert("blue");
	remainingColors.insert("yellow");
	remainingColors.insert("black");
	remainingColors.insert("green");
	readPlayerNames();
}

int main()
{
	startOfGame();
	return 0;
}