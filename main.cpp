#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <string>
#include <Windows.h>
#include <set>
#include <unordered_map>

const int minNumberOfPlayers = 2;
const int maxNumberOfPlayers = 4;
int numberOfPlayers = 0;
std::unordered_map <std::string, int> playerId; /// zice id-ul (pozitia) jucatorului

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

	void diceReset() {
		dice1 = 1;
		dice2 = 1;
		consecutiveRolls = 0;
	}

	void diceRoll() {
		std::cout << "Scrie 'roll' pentru a arunca cu zarurile\n";
		std::string input;
		std::cin >> input;
		while(input != "roll")
		{
			std::cout << "Unknown command. Try again.\n";
			std::cin >> input;
		}
		dice1 = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;
		std::cout << "Zarurile au fost aruncate. ";
		Sleep(1000);
		std::cout << dice1 << " si " << dice2 << "\n";
		Sleep(1000);
		if(dice1 == dice2)
			consecutiveRolls++;
		if(consecutiveRolls == 3)
			std::cout << "Prea mult noroc. Mergi la inchisoare!\n";
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

	void updatePosition(int newPosition)
	{
		this -> position = newPosition;
	}
};

/// Clasa cartilor "proprietate". Ele contin informatii despre costuri inchiriere, cumparare, amanetare
class PropertyTitleCard {
public:
	std::string name;
	int color; /// culoarea setului din care face parte
	int placeRentCost;
	int rentApartmentCosts[5];
	int rentHotelCost;
	int apartmentCost;
	int hotelCost;
	int amanetCost; /// nu gasesc traducere la amanet in engleza
	PropertyTitleCard(std::string name, int color, int placeRentCost, int a1, int a2, int a3, int a4, int hotelRent, int apartmentCost, int hotelCost, int amanetCost)
	{
		this -> name = name;
		this -> placeRentCost = placeRentCost * 1000;
		this -> rentApartmentCosts[1] = a1 * 1000;
		this -> rentApartmentCosts[2] = a2 * 1000;
		this -> rentApartmentCosts[3] = a3 * 1000;
		this -> rentApartmentCosts[4] = a4 * 1000;
		this -> rentHotelCost = hotelRent * 1000;
		this -> hotelCost = hotelCost * 1000;
		this -> apartmentCost = apartmentCost * 1000;
		this -> amanetCost = amanetCost * 2000;
	}
	PropertyTitleCard() = default;

	friend std::ostream& operator<<(std::ostream&os, const PropertyTitleCard& card)
	{
		os << "Titlu de proprietate.\nNume: " << card.name << "\n" << "Costuri inchiriere apartamente:\n";
		for(int i = 1; i <= 4; i++)
			os << i << ". " << card.rentApartmentCosts[i] << "\n";
		os << "Cost inchiriere hotel: " << card.rentHotelCost << "\n" << "Cost apartament: " << card.apartmentCost << "\n";
		os << "Cost hotel: " << card.hotelCost << "\n" << "Cost amanet: " << card.amanetCost << "\n";
		return os;
	}

	void update(std::string name, int color, int placeRentCost, int a1, int a2, int a3, int a4, int hotelRent, int apartmentCost, int hotelCost, int amanetCost)
	{
		this -> name = name;
		this -> rentApartmentCosts[1] = a1 * 1000;
		this -> rentApartmentCosts[2] = a2 * 1000;
		this -> rentApartmentCosts[3] = a3 * 1000;
		this -> rentApartmentCosts[4] = a4 * 1000;
		this -> rentHotelCost = hotelRent * 1000;
		this -> hotelCost = hotelCost * 1000;
		this -> apartmentCost = apartmentCost * 1000;
		this -> amanetCost = amanetCost * 2000;
	}
};

/// Clasa cu informatii despre celulele taxa
class TaxCells {
public:
	std::string name;
	int amount;
	TaxCells(std::string name, int amount)
	{
		this -> name = name;
		this -> amount = amount * 1000;
	}
	TaxCells() = default;
};

/// Clasa cu informatii despre celulele de tip utilitate
class Utility {
public:
	std::string name;
	int amanetCost;
	Utility(std::string name, int amanetCost)
	{
		this -> name = name;
		this -> amanetCost = amanetCost * 1000;
	}
	Utility() = default;
};
Utility utilities[10];

/// Clasa cu informatii despre celulele de tip transport
class Transport {
public:
	std::string name;
	int buyCost;
	int rentCosts[5]; /// costurile chiriei daca jucatorul detine 1 / 2 / 3 / 4 statii de transport
	int amanetCost;
	Transport(std::string name, int cost1, int cost2, int cost3, int cost4, int amanetCost)
	{
		this -> name = name;
		this -> buyCost = 2000000;
		this -> rentCosts[1] = cost1 * 1000;
		this -> rentCosts[2] = cost2 * 1000;
		this -> rentCosts[3] = cost3 * 1000;
		this -> rentCosts[4] = cost4 * 1000;
		this -> amanetCost = amanetCost * 1000;
	}
	Transport() = default;
};

Transport transports[10];

class Chance {

};

class CommunityBox {

};

std::string toWord(int type) {  /// o functie care primeste ca parametrul tipul (int) si imi returneaza semnificatia lui
	std::string output;
	if(type == 0)
		output = "'proprietate'";
	if(type == 1)
		output = "'start'";
	if(type == 2)
		output = "'sansa'";
	if(type == 3)
		output = "'cutia comunitatii'";
	if(type == 4)
		output = "'inchisoare'";
	if(type == 5)
		output = "'utilitati'";
	if(type == 6)
		output = "'taxe'";
	if(type == 7)
		output = "'mergi la inchisoare'";
	if(type == 8)
		output = "'transport'";
	if(type == 9)
		output = "'parcare gratis'";
	return output;
}

/// Basically clasa cu patratelele de pe tabla: tipul, informatii, etc.
class Cell {
public:
	int type; /// 0-tip normal, 1-start, 2-sansa, 3-cutia comunitatii, 4-inchisoare, 5-utilitati, 6-taxe, 7-mergi la inchisoare, 8-transport
	int owner; /// proprietarul, sau 0 daca nu este detinut de nimeni
	int constructionLevel = 0; /// in cazul in care este o proprietate, 0 = loc inchiriat, 1, 2, 3, 4 = apartamente, 5 = hotel
	std::string cellName;
	PropertyTitleCard costs;
	Utility utility;
	Transport transport;
	Chance chance;
	TaxCells taxCost;
	CommunityBox communityBox;

	void transferOwnership(int newOwner)
	{
		this -> owner = newOwner;
	}

	Cell(PropertyTitleCard property)
	{
		this -> cellName = property.name;
		this -> type = 0;
		this -> costs = property;
	}
	Cell(Utility utility)
	{
		this -> cellName = utility.name;
		this -> type = 5;
		this -> utility = utility;
	}
	Cell(Transport transport)
	{
		this -> cellName = transport.name;
		this -> type = 8;
		this -> transport = transport;
	}
	Cell(TaxCells tax)
	{
		this -> cellName = tax.name;
		this -> type = 6;
		this -> taxCost = tax;
	}
	Cell(int type, std::string name)
	{
		this -> cellName = name;
		this -> type = type;
	}
	Cell() = default;

	friend std::ostream& operator<<(std::ostream& os, const Cell& cell)
	{
		os << "Tipul " << toWord(cell.type) << " cu numele '" << cell.cellName << "'\n";
		return os;
	}
};

PropertyTitleCard properties[55];
Cell squares[55];void printColoredText(std::string text, std::string color) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  /// pentru a colora textul din consola
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	if(color == "red")
		SetConsoleTextAttribute(hConsole, 4);
	if(color == "blue")
		SetConsoleTextAttribute(hConsole, 1);
	if(color == "yellow")
		SetConsoleTextAttribute(hConsole, 6);
	if(color == "green")
		SetConsoleTextAttribute(hConsole, 2);
	if(color == "purple")
		SetConsoleTextAttribute(hConsole, 5);

	std::cout << text;
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);

}

/// Jucator - tine practic cam toate informatiile jucatorului
class Player {
private:
	int money;
public:
	bool isInPrison; /// 1-daca este la inchisoare, 0 daca nu
	bool eliminated; /// 1-daca a fost eliminat, 0 daca nu
	int getOutOfPrisonTries; /// numarul de aruncari cu zarul incercand sa iasa de la ichisoare
	                         /// daca se arunca de 3 ori si nu iese, trebuie sa plateasca sau sa foloseasca un card
	std::vector <int> posUtilities; /// pozitiile utilitatilor pe care le detine
	std::vector <int> posTransports; /// pozitiile transporturilor pe care le detine
	std::vector <int> posProperties; /// pozitiile proprietatilor pe care le detine
	int freePrisonExits; /// numarul de iesiri gratis de la inchisoare
	std::string playerName;
	Pawn pawn;
	Dices dices;
	Player() = default;
	Player(std::string name, Pawn pion)
	{
		money = 15000000; /// la inceput fiecare jucator are 15M
		playerName = name;
		this -> pawn = pion;
	};
	
	friend std::ostream& operator<<(std::ostream& os, const Player& player)
	{
		os << "Jucatorul are numele " << player.pawn.playerName << " si joaca cu pionul de culoarea " << player.pawn.color << "\n";
		return os;
	}

	void displayStatus()
	{
		std::cout << "Nume jucator: " << this -> playerName << "\n";
		std::cout << "Avere: " << this -> money << "\n";
		std::cout << "In inchisoare? 0-nu, 1-da: " << this -> isInPrison << "\n";
		std::cout << "Numar iesiri gratis: " << this -> freePrisonExits << "\n";
	}

	void displayFullStatus()
	{
		displayStatus();
		std::cout << "Proprietati detinute: ";
		for(auto it : this -> posProperties)
			std::cout << squares[it].cellName << " ";
		std::cout << "\nLinii de transport detinute: ";
		for(auto it : this -> posTransports)
			std::cout << squares[it].cellName << " ";
		std::cout << "\nUtilitati detinute: ";
		for(auto it : posUtilities)
			std::cout << squares[it].cellName << " ";
		std::cout << "\n";
	}

	void sendToPrison()
	{
		std::cout << "Esti trimis la inchisoare. Poti sta la inchisoare ('stay') pana dai o dubla, sa platesti iesirea ('pay') sau sa iti folosesti o iesire gratis daca ai ('free').\n";
		std::cout << "De asemenea, poti vedea statistici despre tine\n";
		std::cout << "Scrie 'status' pentru a vedea informatii despre jucator sau 'fullstatus' pentru a vedea informatiile complete";
		std::string input;
		std::cin >> input;
		this -> pawn.position = 11; /// trimit la inchisoare (pe patratul 11)
		while(1)
		{
			if(input == "status")
				this -> displayStatus();
			if(input == "fullstatus")
				this -> displayFullStatus();
			if(input == "free")
			{
				if(this -> freePrisonExits > 0)
				{
					std::cout << "Esti liber sa pleci de la tura viitoare.";
					this -> freePrisonExits--;
					displayGeneralMessage();
					break;
				}
				if(this -> freePrisonExits == 0)
					std::cout << "Nu ai iesiri gratis. Incearca altceva\n";
			}
			if(input == "stay")
			{
				std::cout << "O sa arunci cu zarul pana putrezesti\n";
				this -> isInPrison = 1;
				displayGeneralMessage();
				break;
			}
			if(input == "pay")
			{
				if(this -> money >= 500000) /// daca ai destui bani sa platesti inchisoarea, e ok
				{
					std::cout << "Ai mituit cu succes paznicii. Esti liber sa pleci de tura viitoare.\n";
					displayGeneralMessage();
					break;
				}
				else
					std::cout << "Esti prea sarac sa iti permiti o mita. Incearca altceva.\n";
			}
			std::cin >> input;

		}

	}

	void collect(int sum)
	{
		this -> money += sum;
		return;
	}


	void addMoney(int amount) {
		this -> money += amount;
	}
	void removeMoney(int amount) {
		this -> money -= amount;
	}

	void collectStart()
	{
		this -> collect(2000000); /// Cand se trece pe la start se primeste
		return;
	}

	int getBalance()
	{
		return this -> money;
	}

	void transferMoneyTo(int otherPlayer, int amount)
	{
		this -> removeMoney(amount);
		players[otherPlayer].addMoney(amount);
		printColoredText(this -> playerName, this -> pawn.color);
		printColoredText(" removed ", "red");
		std::cout << amount << "\n";
		printColoredText(players[otherPlayer].playerName, players[otherPlayer].pawn.color);
		printColoredText(" received", "green");
		std::cout << amount << "\n";
	}

	void displayGeneralMessage()
	{
		std::cout << "Nicio alta actiune posibila.\nScrie 'status' pentru a vedea informatii despre jucator, 'fullstatus' pentru a vedea informatiile complete sau 'end' pentru a termina tura: ";
		std::string action;
		std::cin >> action;
		while(action != "end")
		{
			if(action == "status")
			{
				this -> displayStatus();
				std::cout << "Scrie 'status' pentru a vedea informatii despre jucator, 'fullstatus; pentru a vedea informatiile complete sau 'end' pentru a termina tura: ";
			}
			else
				std::cout << "Wrong input format, try again:\n";
			std::cin >> action;
		}
	}

	void displayBuyMessage(int buyCost, std::string target) /// costul cumpararii si tipul de celula cumparat
	{
		std::cout << "Scrie 'status' pentru a vedea informatii despre jucator, 'fullstatus' pentru informatii complete, 'buy' pentru a cumpara celula sau 'end' pentru a termina tura: ";
		std::string action;
		std::cin >> action;
		bool bought = 0;
		while(action != "end")
		{
			if(action == "status" || action == "fullstatus")
			{
				if(action == "status")
					this -> displayStatus();
				if(action == "fullstatus")
					this -> displayFullStatus();
				if(bought == 0)
					std::cout << "Scrie 'status' pentru a vedea informatii despre jucator, 'fullstatus' pentru informatii complete, 'buy' pentru a cumpara sau 'end' pentru a termina tura: ";
				else
				{
					this -> displayGeneralMessage();
					return;
				}
			}
			else if(action == "buy")
			{
				if(this -> money >= buyCost)
				{
					squares[this -> pawn.position].transferOwnership(playerId[this -> playerName]);
					if(target == "transport")
						this -> posTransports.push_back(this -> pawn.position);
					if(target == "utility")
						this -> posUtilities.push_back(this -> pawn.position);
					if(target == "property")
						this -> posProperties.push_back(this -> pawn.position);
					std::cout << "Transaction successfull!\n";
					printColoredText(this -> playerName, this -> pawn.color);
					std::cout << " removed ";
					printColoredText(std::to_string(buyCost), "red");
					std::cout << " but ";
					printColoredText("gained ownership", "green");
					std::cout << " of " << squares[this -> pawn.position].cellName << "!\n";
					this -> displayGeneralMessage();
					return;
				}
				else
				{
					std::cout << "Not enough money." << "\n";
					displayGeneralMessage();
					return;
				}
			}
			else if(action == "end")
				break;
			else
				std::cout << "Wrong input format, try again:\n";
			std::cin >> action;
		}
	}

	bool payUtilityTo(int cellOwner)
	{
		int numUtilities = players[cellOwner].posUtilities.size();
		int amountNeeded = 0;
		int dicesSum = this -> dices.dice1 + this -> dices.dice2;
		if(numUtilities == 1)
			amountNeeded = 4 * 10000 * dicesSum;
		else if(numUtilities == 2)
			amountNeeded = 10 * 10000 * dicesSum;
		if(this -> money >= amountNeeded)
		{
			this -> transferMoneyTo(cellOwner, amountNeeded);
			return 1;
		}
		return 0;
	}

	bool payTransportTo(int cellOwner)
	{
		int numTransports = players[cellOwner].posTransports.size();
		int amountNeeded = squares[this -> pawn.position].transport.buyCost * numTransports;
		if(this -> money >= amountNeeded)
		{
			this -> transferMoneyTo(cellOwner, amountNeeded);
			return 1;
		}
		return 0;
	}

	bool payTax()
	{
		int pos = this -> pawn.position;
		if(this -> money >= squares[pos].taxCost.amount)
		{
			removeMoney(squares[pos].taxCost.amount);
			return 1;
		}
		return 0;
	}

	bool payPropertyRent(int cellOwner)
	{
		int pos = this -> pawn.position;
		int amountNeeded = 0;
		if(squares[pos].constructionLevel == 0)
			amountNeeded = squares[pos].costs.placeRentCost;
		if(squares[pos].constructionLevel == 1)
			amountNeeded = squares[pos].costs.rentApartmentCosts[squares[pos].constructionLevel];
		if(squares[pos].constructionLevel == 5)
			amountNeeded = squares[pos].costs.rentHotelCost;
		if(this -> money >= amountNeeded)
		{
			transferMoneyTo(cellOwner, amountNeeded);
			return 1;
		}
		return 0;
	}

	void displayBuyLevel(std::string upgradeTo, int level)
	{
		std::cout << "Scrie 'status' pentru a vedea informatii despre jucator, 'fullstatus' pentru informatii complete, 'upgrade' pentru a upgrada proprietatea sau 'end' pentru a termina tura: ";
		std::string action;
		std::cin >> action;
		bool bought = 0;
		while(action != "end")
		{
			if(action == "status" || action == "fullstatus")
			{
				if(action == "status")
					this -> displayStatus();
				if(action == "fullstatus")
					this -> displayFullStatus();
				if(bought == 0)
					std::cout << "Scrie 'status' pentru a vedea informatii despre jucator, 'fullstatus' pentru informatii complete, 'buy' pentru a cumpara sau 'end' pentru a termina tura: ";
				else
				{
					this -> displayGeneralMessage();
					return;
				}
			}
			else if(action == "upgrade")
			{
				bought = 1;
				int pos = this -> pawn.position;
				if(this -> money >= squares[pos].costs.apartmentCost)
				{
					squares[pos].constructionLevel++;
					printColoredText(this -> playerName, this -> pawn.color);
					std::cout << " removed ";
					printColoredText(std::to_string(squares[pos].costs.apartmentCost), "red");
					std::cout << " but ";
					printColoredText("upgraded ", "green");
					std::cout << squares[this -> pawn.position].cellName << "!\n";
					this -> displayGeneralMessage();
					return;
				}
			}
			else if(action == "end")
				break;
			else
				std::cout << "Wrong input format, try again:\n";
			std::cin >> action;
		}
	}

	void actions()
	{
		int pos = this -> pawn.position;
		if(squares[pos].type == 1)  /// Celula de tip start
		{
			std::cout << "Ai ajuns pe 'Start', nu se intampla nimic.\n";
			this -> displayGeneralMessage();
			return;
		}
		if(squares[pos].type == 2)  /// Celula de tip sansa
		{
			std::cout << "Ai ajuns pe o 'Sansa', nu am implementat, asa ca nu se intampla nimic\n";
			this -> displayGeneralMessage();
			return;
		}
		if(squares[pos].type == 3)  /// Celula de tip cutia comunitatii
		{
			std::cout << "Ai ajuns pe 'Cutia comunitatii', nu am implementat, asa ca nu se intampla nimic\n";
			this -> displayGeneralMessage();
			return;
		}
		if(squares[pos].type == 4)  /// Celula de tip inchisoare
		{
			std::cout << "Ai ajuns in vizita la inchisoare, nu se intampla nimic\n";
			this -> displayGeneralMessage();
			return;
		}
		if(squares[pos].type == 5)  /// Celula de tip utilitate
		{
			std::cout << "Ai ajuns pe o utilitate.\n";
			
			if(squares[pos].owner == playerId[this -> playerName]) /// nu trebuie platit nimic
			{
				std::cout << "Aceasta utilitate este detinuta de tine, nu trebuie sa platesti nimic";
				this -> displayGeneralMessage();
				return;
			}
			else if(squares[pos].owner == 0) /// daca este libera, ai posibilitatea de a cumpara
			{
				std::cout << "Aceasta celula nu este detinuta de nimeni, asa ca nu trebuie sa platesti nimic. In schimb o poti cumpara, daca ai destui bani\n";
				this -> displayBuyMessage(1500000, "utility");
				return;
			}
			else /// trebuie sa platesti celui care detine utilitatea
			{
				int cellOwner = squares[pos].owner;
				std::cout << "Aceasta celula este detinuta de ";
				printColoredText(players[cellOwner].playerName, players[cellOwner].pawn.color);
				std::cout << "; va trebui sa platesti.";
				bool successfulPay = this -> payUtilityTo(squares[pos].owner);
				if(successfulPay == false)
				{
					std::cout << "Nu ai destui bani, esti eliminat din joc";
					this -> eliminated = true;
					return;
				}
				displayGeneralMessage();
			}
		}
		if(squares[pos].type == 6) /// Celula de tip taxa
		{
			std::cout << "Aceasta celula este de tip taxa, asa ca va trebui sa platesti\n";
			bool successfullPay = this -> payTax();
			if(successfullPay == false)
			{
				std::cout << "Nu ai destui bani, esti eliminat din joc";
				this -> eliminated = true;
				return;
			}
			printColoredText(this -> playerName, this -> pawn.color);
			printColoredText(" removed ", "red");
			std::cout << squares[this -> pawn.position].taxCost.amount << "\n";
			displayGeneralMessage();
		}
		if(squares[pos].type == 7) /// Celula de tip mergi la inchisoare
			sendToPrison();
		if(squares[pos].type == 8) /// Celula de tip transport
		{
			std::cout << "Ai ajuns pe o linie de transport";
			if(squares[pos].owner == playerId[this -> playerName]) /// daca celula iti apartine
			{
				std::cout << "Linia aceasta este detinuta de tine.\n";
				displayGeneralMessage();
				return;
			}
			if(squares[pos].owner == 0)
			{
				std::cout << "Linia aceasta nu este detinuta de nimeni, dar o poti cumpara\n";
				displayBuyMessage(squares[pos].transport.buyCost, "transport");
				return;
			}
			if(squares[pos].owner != playerId[this -> playerName]) /// daca celula apartine altcuiva
			{
				int cellOwner = squares[pos].owner;
				std::cout << "Aceasta linie de transport este detinuta de ";
				printColoredText(players[cellOwner].playerName, players[cellOwner].pawn.color);
				std::cout << "; va trebui sa platesti.";
				bool successfullPay = payTransportTo(cellOwner);
				if(successfullPay == false)
				{
					std::cout << "Nu ai destui bani, esti eliminat din joc";
					this -> eliminated = true;
					return;
				}
				displayGeneralMessage();
			}
		}
		if(squares[pos].type == 9)
		{
			std::cout << "Ai picat pe locul 'parcare gratis'. Nu se intampla nimic\n";
			displayGeneralMessage();
		}
		if(squares[pos].type == 0)
		{
			std::cout << "Ai picat pe o proprietate.\n";
			if(squares[pos].owner == playerId[this -> playerName]) /// ai picat pe o proprietate pe care o detii
			{
				std::cout << "Proprietatea este detinuta de tine.\n";
				if(squares[pos].constructionLevel == 5) /// e hotel, nu mai poti face nimic
				{
					displayGeneralMessage();
					return;
				}
				if(squares[pos].constructionLevel <= 3) /// se mai poate construi un apartament
				{
					displayBuyLevel(std::to_string(squares[pos].constructionLevel) + "apartament(e)?", squares[pos].constructionLevel);
					return;
				}
				if(squares[pos].constructionLevel == 4) /// are deja 4 apartamente, putem upgrada la hotel
				{
					displayBuyLevel("hotel", 4);
					return;
				}
			}
			if(squares[pos].owner == 0) /// proprietatea nu are owner, atunci poti cumpara
			{
				std::cout << "Proprietatea nu este detinuta de nimeni, dar o poti cumpara.\n";
				displayBuyMessage(squares[pos].costs.apartmentCost, "property");
				return;
			}
			if(squares[pos].owner != playerId[this -> playerName]) /// esti pe o proprietate straina
			{
				std::cout << "Proprietatea este detinuta de ";
				int cellOwner = squares[pos].owner;
				printColoredText(players[cellOwner].playerName, players[cellOwner].pawn.color);
				std::cout << ". Trebuie sa platesti chirie\n";
				bool successfullPay = payPropertyRent(cellOwner);
				if(successfullPay == 1)
				{
					displayGeneralMessage();
					return;
				}
				else
				{

				}
			}
		}
	}

};

Player players[100];

void playerTurn(int player)
{
	//std::cout << players[player].playerName << " a aruncat cu zarurile. " << players[player].dices.dice1 << " si " << players[player].dices.dice2 << "\n";
	int newPosition = players[player].pawn.position + players[player].dices.dice1 + players[player].dices.dice2;
	if(newPosition >  40) /// tabla are 40 de celule, daca trece de 40 o ia de la capat (si trece pe la start)
	{
		newPosition = newPosition - 40;
		players[player].collectStart();
	}
	players[player].pawn.updatePosition(newPosition);
	std::cout << "Jucatorul ";
	printColoredText(players[player].playerName, players[player].pawn.color);
	std::cout << " ajunge pe pozitia " << newPosition << ", care este:\n";
	std::cout << squares[newPosition] << "\n";
	Sleep(1000);
	players[player].actions();
}

void turn()
{
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		if(players[i].eliminated == 1)
			continue;
		std::cout << "Jucatorul " << i << " (";
		printColoredText(players[i].playerName, players[i].pawn.color);
		std::cout << ") " << " la mutare.\n";
		players[i].dices.diceReset(); /// incepe tura, se reseteaza zarurile
		players[i].dices.diceRoll();

		if(players[i].isInPrison == 1)
		{
			if(players[i].dices.dice1 == players[i].dices.dice2)
			{
				std::cout << "Ai dat dubla! Ai scapat de la inchisoare. Poti muta incepand de la tura viitoare.";
				players[i].isInPrison = 0;
				players[i].displayGeneralMessage();
				continue;
			}
		}
		playerTurn(i);
		if(players[i].dices.dice1 == players[i].dices.dice2) /// daca a dat dubla, mai face o tura
		{
			players[i].dices.diceRoll();
			playerTurn(i);
		}
		if(players[i].dices.dice1 == players[i].dices.dice2) /// daca a dat inca o dubla, mai face inca o tura
		{
			players[i].dices.diceRoll();
			playerTurn(i);
		}
		if(players[i].dices.dice1 == players[i].dices.dice2) /// daca a dat a treia dubla, trebuie trimis la inchisoare
			players[i].sendToPrison();
		players[i].displayGeneralMessage();
		std::cout << "\n";
	}
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
		std::cout << "There should be between " << minNumberOfPlayers << " and " << maxNumberOfPlayers << " players. Try again.\n\n";
		numberOfPlayers = 0;
		readNumberOfPlayers();
		return;
	}
	std::cout << "Now the players!\n";
};


std::set <std::string> remainingColors;

void readPlayers()
{
	remainingColors.insert("red");
	remainingColors.insert("blue");
	remainingColors.insert("yellow");
	remainingColors.insert("purple");
	remainingColors.insert("green");
	std::vector <std::string> playerNames;
	std::vector <std::string> playerColors;
	std::cout << "Enter the name of the players separated by spaces or newlines: \n";
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		std::string name;
		std::cin >> name;
		playerNames.push_back(name);
	}
	/*
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  /// pentru a colora textul din consola
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	std::cout << "Now enter the colors of the pawns (their names). Again, separated by spaces or newlines.\nYou can choose between: \n";
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << "1. Red\n";
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << "2. Blue\n";
	SetConsoleTextAttribute(hConsole, 6);
	std::cout << "3. Yellow\n";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "4. White\n";
	SetConsoleTextAttribute(hConsole, 2);
	std::cout << "5. Green\n";
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	*/
	std::cout << "Now enter the colors of the pawns (their names). Again, separated by spaces or newlines.\nYou can choose between: \n";
	printColoredText("1. Red\n", "red");
	printColoredText("2. Blue\n", "blue");
	printColoredText("3. Yellow\n", "yellow");
	printColoredText("4. Purple\n", "purple");
	printColoredText("5. Green\n", "green");
	/*
	for(auto it : remainingColors)
	{
		cnt++;
		std::cout << cnt << ". " << it << "\n";
	}
	*/
	bool inputError = false;
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		std::string color;
		std::cin >> color;
		if(remainingColors.find(color) == remainingColors.end()) {
			inputError = true;
		}
		auto posDelete = remainingColors.find(color);
		if(posDelete != remainingColors.end())
			remainingColors.erase(posDelete);
		playerColors.push_back(color);
	}
	/*
	std::cout << "Nume: ";
	for(auto it : playerNames)
		std::cout << it << " ";
	std::cout << "\n";
	for(auto it : playerColors)
		std::cout << it << " ";
	std::cout << "\n";
	*/
	for(int i = 0; i < numberOfPlayers; i++)
	{
		Pawn pawn(i + 1, playerNames[i], playerColors[i]);
		Player currentPlayer(playerNames[i], pawn);
		players[i + 1] = currentPlayer;
	}
	if(inputError)
	{
		std::cout << "There was an error. Please redo.\n\n";
		readPlayers();
	}
	/*
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		std::string name;
		std::string color;
		std::cout << "Enter the name of player " << i << ":\n";
		getline(std::cin, name);
		std::cout << "Enter the name of the color. You can choose between:\n";
		int cnt = 0;
		
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
	*/
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		std::cout << players[i].playerName << " will play with the ";
		printColoredText(players[i].pawn.color, players[i].pawn.color);
		std::cout << " pawn!\n";
	}
	std::cout << "\nIs this alright? Write 'yes' or 'no': ";
	std::string answer;
	std::cin >> answer;
	if(answer == "no")
		readPlayers();
	std::cout << "Proceeding...\n\n";
	for(int i = 1; i <= numberOfPlayers; i++)
		std::cout << players[i] << "\n";
}

void intro()
{
	
}

void insertCardsData()
{
	properties[1].update("Universitatea nationala de aparare", 1, 20, 100, 300, 900, 1600, 2500, 500, 500, 300);
	properties[2].update("Muzeul taranului roman", 1, 40, 200, 600, 1800, 3200, 4500, 500, 500, 300);
	properties[3].update("Institutul geologic", 2, 60, 300, 900, 2700, 4000, 5500, 500, 500, 500);
	properties[4].update("Muzeul de istorie naturala Antipa", 2, 60, 300, 900, 2700, 4000, 5500, 500, 500, 500);
	properties[5].update("Opera nationala", 2, 80, 400, 1000, 3000, 4500, 6000, 500, 500, 600);
	properties[6].update("Piata Kogalniceanu", 3, 100, 500, 1500, 4500, 6250, 7500, 1000, 1000, 700);
	properties[7].update("Universitatea", 3, 100, 500, 1500, 4500, 6250, 7500, 1000, 1000, 700);
	properties[8].update("Cercul militar national", 3, 120, 600, 1800, 5000, 7000, 9000, 1000, 1000, 800);
	properties[9].update("Casa presei libere", 4, 140, 700, 2000, 5500, 7500, 9500, 1000, 1000, 900);
	properties[10].update("Biblioteca universitara", 4, 140, 700, 2000, 5500, 7500, 9500, 1000, 1000, 900);
	properties[11].update("Parcul cismigiu", 4, 160, 800, 2200, 6000, 8000, 10000, 1000, 1000, 1000);
	properties[12].update("Muzeul de istorie", 5, 180, 900, 2500, 7000, 8750, 10500, 1500, 1500, 1100);
	properties[13].update("Muzeul George Enescu", 5, 180, 900, 2500, 7000, 8750, 10500, 1500, 1500, 1100);
	properties[14].update("Muzeul de arta", 5, 200, 1000, 3000, 7500, 9250, 11000, 1500, 1500, 1200);
	properties[15].update("Arcul de triumf", 6, 220, 1100, 3300, 8000, 9750, 11500, 1500, 1500, 1300);
	properties[16].update("Banca nationala", 6, 220, 1100, 3300, 8000, 9750, 11500, 1500, 1500, 1300);
	properties[17].update("Tribunalul", 6, 240, 1200, 3600, 8500, 10250, 12000, 1500, 1500, 1400);
	properties[18].update("Ateneul roman", 7, 260, 1300, 3900, 9000, 11000, 12750, 2000, 2000, 1500);
	properties[19].update("Piata unirii", 7, 260, 1300, 3900, 9000, 11000, 12750, 2000, 2000, 1500);
	properties[20].update("Teatrul national", 7, 280, 1500, 4500, 10000, 12000, 14000, 2000, 2000, 1600);
	properties[21].update("Cladirea CEC", 8, 350, 1750, 5000, 11000, 13000, 15000, 2000, 2000, 1750);
	properties[22].update("Casa poporului", 8, 500, 2000, 6000, 14000, 17000, 20000, 2000, 2000, 2000);

	transports[1] = Transport("Gara de nord", 250, 500, 1000, 2000, 1000);
	transports[2] = Transport("Aeroportul Henri Coanda", 250, 500, 1000, 2000, 1000);
	transports[3] = Transport("Gara Basarab", 250, 500, 1000, 2000, 1000);
	transports[4] = Transport("Aeroportul Baneasa", 250, 500, 1000, 2000, 1000);

	utilities[1] = Utility("Uzina electrica", 750);
	utilities[2] = Utility("Uzina de apa", 750);
	
	TaxCells tax1("Impozit Profit", 2000);
	TaxCells tax2("Taxa de lux", 1000);
	for(int i = 1; i <= 22; i++)
		std::cout << properties[i] << "\n\n";
	//0-tip normal, 1-start, 2-sansa, 3-cutia comunitatii, 4-inchisoare, 5-utilitati, 6-taxe, 7-mergi la inchisoare, 8-transport, 9-parcare gratis
	squares[1] = Cell(1, "Start");
	squares[2] = Cell(properties[1]);
	squares[3] = Cell(3, "Cutia comunitatii");
	squares[4] = Cell(properties[2]);
	squares[5] = Cell(tax1);
	squares[6] = Cell(transports[1]);
	squares[7] = Cell(properties[3]);
	squares[8] = Cell(2, "Sansa");
	squares[9] = Cell(properties[4]);
	squares[10] = Cell(properties[5]);
	squares[11] = Cell(4, "Inchisoare");
	squares[12] = Cell(properties[6]);
	squares[13] = Cell(utilities[1]);
	squares[14] = Cell(properties[7]);
	squares[15] = Cell(properties[8]);
	squares[16] = Cell(transports[2]);
	squares[17] = Cell(properties[9]);
	squares[18] = Cell(3, "Cutia comunitatii");
	squares[19] = Cell(properties[10]);
	squares[20] = Cell(properties[11]);
	squares[21] = Cell(9, "Parcare gratuita");
	squares[22] = Cell(properties[12]);
	squares[23] = Cell(2, "Sansa");
	squares[24] = Cell(properties[13]);
	squares[25] = Cell(properties[14]);
	squares[26] = Cell(transports[3]);
	squares[27] = Cell(properties[15]);
	squares[28] = Cell(properties[16]);
	squares[29] = Cell(utilities[2]);
	squares[30] = Cell(properties[17]);
	squares[31] = Cell(7, "Mergi la inchisoare");
	squares[32] = Cell(properties[18]);
	squares[33] = Cell(properties[19]);
	squares[34] = Cell(3, "Cutia comunitatii");
	squares[35] = Cell(properties[20]);
	squares[36] = Cell(transports[4]);
	squares[37] = Cell(2, "Sansa");
	squares[38] = Cell(properties[21]);
	squares[39] = Cell(tax2);
	squares[40] = Cell(properties[22]);

	for(int i = 1; i <= 40; i++)
		std::cout << "Celula cu numarul " << i << ": " << squares[i] << "\n";
}

void startOfGame()
{
	srand(time(NULL));
	intro();
	readNumberOfPlayers();
	readPlayers();
	insertCardsData();
}

std::pair <int, int> winner() /// functie ce returneaza un castigator (si numarul lor daca sunt mai multi)
{
	int ans = 0;
	int numberOfWinners = 0;
	for(int i = 1; i <= numberOfPlayers; i++)
	{
		if(players[i].eliminated == 1)
			continue;
		if(players[ans].getBalance() < players[i].getBalance())
		{
			ans = i;
			numberOfWinners = 1;
		}
		else if(players[ans].getBalance() == players[i].getBalance())
			numberOfWinners++;
	}
	return std::make_pair(ans, numberOfWinners);
}



int main()
{
	startOfGame();
	for(int i = 1; i <= 25; i++) /// 25 ture
		turn();
	while(winner().second > 1) /// daca dupa 25 de ture sunt cel putin doi oameni cu numar maxim de bani, atunci se joaca overtime-uri de cate 5 ture
		for(int i = 1; i <= 5; i++)
			turn();
	
	return 0;
}