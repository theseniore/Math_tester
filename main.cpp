#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enOperationType { Add = 1, Sub, Mul, Div, Mixed };
enum enQuestionsLevel { Easy = 1, Med, Hard, Mix };

string getOperationTypeString(enOperationType opType) {
    switch (opType) {
    case Add: return "Addition (+)";
    case Sub: return "Subtraction (-)";
    case Mul: return "Multiplication (*)";
    case Div: return "Division (/)";
    case Mixed: return "Mixed Operations";
    default: return "Unknown";
    }
}
string getQuestionLevelString(enQuestionsLevel qLevel) {
    switch (qLevel) {
    case Easy: return "Easy";
    case Med: return "Medium";
    case Hard: return "Hard";
    case Mix: return "Mixed";
    default: return "Unknown";
    }
}
struct stMathQuestion {
    int FirstNumber = 0;
    int SecondNumber = 0;
    float Result = 0;
    char OperationSign;
};
void green() { system("color 27"); }
void red() { cout << "\a" << endl; system("color 47"); }
void yellow() { system("color 67"); }
void resetGame() { system("cls"); system("color 07"); }

void printRightAnswer(int& RightMark) {
    green();
    cout << "Right answer :-)" << endl;
    RightMark++;
}

void printWrongAnswer(int& WrongMark, stMathQuestion& MathQuestion) {
    red();
    cout << "Wrong answer :-(" << endl;
    cout << "The right answer is: " << MathQuestion.Result << endl;
    WrongMark++;
}

int randomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

char randomChar() {
    char OperationType[] = { '+', '-', '*', '/' };
    return OperationType[randomNumber(0, 3)];
}

float readAnswer() {
    float Answer;
    cin >> Answer;
    return Answer;
}

string checkFinalResult(int RightMark, int WrongMark) {
    return (RightMark >= WrongMark) ? "Passed :-)" : "Failed :-(";
}

void printFinalResultState(int RightMark, int WrongMark) {
    cout << "_________________________________" << endl;
    cout << "Final Result: " << checkFinalResult(RightMark, WrongMark) << endl;
    cout << "_________________________________" << endl;
}

void printFinalResult(int N, enQuestionsLevel QuestionLevel, enOperationType OperationType, int RightMark, int WrongMark) {
    cout << "Number of questions: " << N << endl;
    cout << "Questions level    : " << getQuestionLevelString(QuestionLevel) << endl;
    cout << "Op type            : " << getOperationTypeString(OperationType)<< endl;
    cout << "Number of right answers: " << RightMark << endl;
    cout << "Number of wrong answers: " << WrongMark << endl;
    cout << "_________________________________" << endl;
}
int askForHowManyQuestions() {
    int Number;
    do {
        cout << "How many questions do you want to answer? ";
        cin >> Number;
    } while (Number < 1);
    return Number;
}
enQuestionsLevel askForQuestionLevel() {
    int QuestionLevel;
    cout << "Enter questions level [1] Easy, [2] Medium, [3] Hard, [4] Mixed: ";
    cin >> QuestionLevel;
    return (enQuestionsLevel)QuestionLevel;
}
enOperationType askForOperationType() {
    int OperationType;
    cout << "Enter operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mixed: ";
    cin >> OperationType;
    return (enOperationType)OperationType;
}
void generateQuestion(stMathQuestion& MathQuestion, enQuestionsLevel QuestionLevel) {
    switch (QuestionLevel) {
    case Easy:
        MathQuestion.FirstNumber = randomNumber(1, 10);
        MathQuestion.SecondNumber = randomNumber(1, 10);
        break;
    case Med:
        MathQuestion.FirstNumber = randomNumber(1, 50);
        MathQuestion.SecondNumber = randomNumber(1, 50);
        break;
    case Hard:
        MathQuestion.FirstNumber = randomNumber(10, 100);
        MathQuestion.SecondNumber = randomNumber(10, 100);
        break;
    case Mix:
        MathQuestion.FirstNumber = randomNumber(1, 100);
        MathQuestion.SecondNumber = randomNumber(1, 100);
        break;
    }
}
void assignOperation(stMathQuestion& MathQuestion, enOperationType OperationType) {
    if (OperationType == Mixed)
        MathQuestion.OperationSign = randomChar();
    else {
        switch (OperationType) {
        case Add: MathQuestion.OperationSign = '+'; break;
        case Sub: MathQuestion.OperationSign = '-'; break;
        case Mul: MathQuestion.OperationSign = '*'; break;
        case Div: MathQuestion.OperationSign = '/'; break;
        }
    }
}
void calculateResult(stMathQuestion& MathQuestion) {
    switch (MathQuestion.OperationSign) {
    case '+': MathQuestion.Result = MathQuestion.FirstNumber + MathQuestion.SecondNumber; break;
    case '-': MathQuestion.Result = MathQuestion.FirstNumber - MathQuestion.SecondNumber; break;
    case '*': MathQuestion.Result = MathQuestion.FirstNumber * MathQuestion.SecondNumber; break;
    case '/':
        if (MathQuestion.SecondNumber != 0)
            MathQuestion.Result = (float)MathQuestion.FirstNumber / MathQuestion.SecondNumber;
        else
            MathQuestion.Result = 0;
        break;
    }
}
void checkAnswer(stMathQuestion& MathQuestion, float Answer, int& RightMark, int& WrongMark) {
    calculateResult(MathQuestion);
    if (Answer == MathQuestion.Result)
        printRightAnswer(RightMark);
    else
        printWrongAnswer(WrongMark, MathQuestion);
}
void printQuestions(int N, enOperationType OperationType, enQuestionsLevel QuestionLevel) {
    int RightMark = 0, WrongMark = 0;

    for (int i = 0; i < N; i++) {
        stMathQuestion MathQuestion;
        generateQuestion(MathQuestion, QuestionLevel);
        assignOperation(MathQuestion, OperationType);
        calculateResult(MathQuestion);

        cout << "Question [" << i + 1 << "/" << N << "]:\n";
        cout << MathQuestion.FirstNumber << " " << MathQuestion.OperationSign << " " << MathQuestion.SecondNumber << " = ?" << endl;

        float Answer = readAnswer();
        checkAnswer(MathQuestion, Answer, RightMark, WrongMark);
    }

    printFinalResult(N, QuestionLevel, OperationType, RightMark, WrongMark);
    printFinalResultState(RightMark, WrongMark);
}
void startMathGame() {
    char YesOrNo;
    do {
        int N = askForHowManyQuestions();
        enQuestionsLevel QuestionLevel = askForQuestionLevel();
        enOperationType OperationType = askForOperationType();
        printQuestions(N, OperationType, QuestionLevel);

        cout << "Do you want to play again? (Y/N) ";
        cin >> YesOrNo;
    } while (YesOrNo == 'Y' || YesOrNo == 'y');
}
int main() {
    srand(time(NULL));
    startMathGame();
    return 0;
}
