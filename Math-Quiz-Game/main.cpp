

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


enum enQuestionsLevel { EeasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };


struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswer = 0;
	short NumberOfRightAnswer = 0;
	bool IsPass = false;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestion()
{
	short NumberOfQuestion;

	do {
		cout << "How Many Questions do you want answer ? ";
		cin >> NumberOfQuestion;

	} while (NumberOfQuestion < 1 || NumberOfQuestion > 10);

	return NumberOfQuestion;
}

enQuestionsLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do
	{

		cout << "Enter Question Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType;

	do
	{
		cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mult , [4] Div , [5] MixOp ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;
	default:
		return Number1 + Number2;

	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionsLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionsLevel == enQuestionsLevel::Mix)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	Question.QuestionLevel = QuestionsLevel;

	if (OpType == enOperationType::MixOp)
	{
		OpType = (enOperationType)RandomNumber(1, 4);
	}

	Question.OperationType = OpType;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EeasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	}

	return Question;

}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Qusstion = 0; Qusstion < Quizz.NumberOfQuestions; Qusstion++)
	{
		Quizz.QuestionList[Qusstion] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy" , "Mid" , "Hard" , "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Qustion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n---------" << endl;
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswer++;

		cout << "Wrong Answer :-(\n";
		cout << "The Right answer is : ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswer++;

		cout << "Right Answer :-)\n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);

}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "*----------------------------\n\n";
	cout << "* Final Result is " << GetFinalResultText(Quizz.IsPass);
	cout << "\n----------------------------------\n\n";

	cout << "Number of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "Op Type : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answer : " << Quizz.NumberOfRightAnswer << endl;
	cout << ".Number Of Wrong Answer : " << Quizz.NumberOfWrongAnswer << endl;

}

void PlayGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestion();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResult(Quizz);
}

void RestScreen()
{
	system("cls");
	system("color 0F");

}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		RestScreen();
		PlayGame();

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}




int main() {

	srand((unsigned)time(NULL));

	StartGame();



}

