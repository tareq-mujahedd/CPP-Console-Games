
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoise { Stone = 1, Paper = 2, scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {

	short RoundNumber = 0;
	enGameChoise Player1Choise;
	enGameChoise ComputerChoise;
	enWinner Winner;
	string WinnerName;

};

struct stGameResult {

	short GameRounds = 0;
	short PlayerWinTime = 0;
	short ComputerWinTime = 0;
	short DrawTime = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

short ReadHowManyRounds() {

	short GameRounds = 1;

	do {
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

enGameChoise ReadPlayer1Choice() {

	short Choise = 1;

	do {

		cout << "\n Your Choise : [1]:Stone , [2]:Paper , [3]:Sicssors ? ";
		cin >> Choise;

	} while (Choise < 1 || Choise > 3);

	return (enGameChoise)Choise;
}

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

enGameChoise GetComputerChoise() {

	return (enGameChoise)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {

	if (RoundInfo.Player1Choise == RoundInfo.ComputerChoise)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choise) {

	case enGameChoise::Stone:
		if (RoundInfo.ComputerChoise == enGameChoise::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoise::Paper:
		if (RoundInfo.ComputerChoise == enGameChoise::scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoise::scissors:
		if (RoundInfo.ComputerChoise == enGameChoise::Stone)
		{
			return enWinner::Computer;
		}
		break;

	}

	return enWinner::Player1;

}

void SetWinnerScreenColor(enWinner Winner) {

	switch (Winner) {

	case enWinner::Player1:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	default:
		system("color 6F");
		break;
	}
}

string ChoiceName(enGameChoise Choise) {

	string arrGameChoise[3] = { "Stone" , "Paper" , "Scissors" };
	return arrGameChoise[Choise - 1];
}

string WinnerName(enWinner Winner) {

	string arrWinnerName[3] = { "Player1" , "Computer" , "No Winner" };
	return arrWinnerName[Winner - 1];
}


void PrintRoundResult(stRoundInfo RoundInfo) {

	cout << "\n----------Round [" << RoundInfo.RoundNumber << "]--------------\n\n";
	cout << "Player1 Choise : " << ChoiceName(RoundInfo.Player1Choise) << endl;
	cout << "Computer Choise : " << ChoiceName(RoundInfo.ComputerChoise) << endl;
	cout << "Round  Winner : [" << RoundInfo.WinnerName << "]\n";
	cout << "-----------------\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWinTheGame(short PlayerWinTimes, short ComputerWinTimes) {

	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > PlayerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;

}

stGameResult FillGameResults(int GameRound, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {

	stGameResult GameResults;

	GameResults.GameRounds = GameRound;
	GameResults.PlayerWinTime = PlayerWinTimes;
	GameResults.ComputerWinTime = ComputerWinTimes;
	GameResults.DrawTime = DrawTimes;
	GameResults.GameWinner = WhoWinTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

stGameResult PlayGame(short HowManyRounds) {

	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\n Round [" << GameRound << "] begins : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choise = ReadPlayer1Choice();
		RoundInfo.ComputerChoise = GetComputerChoise();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}

	return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}


string Tabs(short NumberOfTabs) {

	string t = "";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen() {

	cout << Tabs(2) << "-------------------------------------------------------------\n\n";
	cout << Tabs(2) << "                   +++ Game Over +++\n";
	cout << Tabs(2) << "-------------------------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResult GameResuls) {

	cout << Tabs(2) << "-------------------- [Game Results ]-------------------\n";
	cout << Tabs(2) << "Game Rounds : " << GameResuls.GameRounds << endl;
	cout << Tabs(2) << "Player1 Won Times : " << GameResuls.PlayerWinTime << endl;
	cout << Tabs(2) << "Computer Won Times: " << GameResuls.ComputerWinTime << endl;
	cout << Tabs(2) << "Draw Time : " << GameResuls.DrawTime << endl;
	cout << Tabs(2) << "Final Winner: " << GameResuls.WinnerName << endl;
	cout << Tabs(2) << "-----------------------------------------------------------\n";

	SetWinnerScreenColor(GameResuls.GameWinner);

}

void ResetScreen() {

	system("cls");
	system("color 0F");

}


void StartGame() {

	char PlayAgain = 'Y';

	do {

		ResetScreen();
		stGameResult GameResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResult);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}



int main() {

	srand((unsigned)time(NULL));

	StartGame();



}

