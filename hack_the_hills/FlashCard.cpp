/*
OFFLINE Flash Card Generator by Kali Forces!
Features: Add / Edit / Delete / View All Flashcards. A Customised Quiz Mode.
Team Members: Avadh, Mayank, Ishaan, Yash

*/
#include<bits/stdc++.h>
#include <windows.h>

using namespace std;

const int MAX_FLASHCARDS = 100;
struct Flashcard {
    string category;
    string question;
    string answer;
    string hint;
    string difficulty;
};

Flashcard flashcards[MAX_FLASHCARDS];
int flashcardCount = 0;

string toLower(string s){
    char ch;
    string str="";
    for(char &ch:s){
        ch=tolower(ch);
        str+=ch;
    }
    return str;
}

// Function to save all flashcards to a file
void saveFlashcards() {
    ofstream file("flashcards.txt");
    if (file.is_open()) {
        for (int i = 0; i < flashcardCount; i++) {
            file << flashcards[i].category << "|" << flashcards[i].question << "|" 
                 << flashcards[i].answer << "|" << flashcards[i].hint << "|" 
                 << flashcards[i].difficulty << endl;
        }
        file.close();
    } 
    else {
        Sleep(1000);
        cout << "\tError: Could not save flashcards!\n";
        Sleep(2000);
    }
}

// Function to load flashcards from the file
void loadFlashcards() {
    ifstream file("flashcards.txt");
    string category, question, answer, hint, difficulty;
    flashcardCount = 0;

    if (!file) {
        Sleep(1000);
        cout << "\tNo Flashcards found. Add some first!\n";
        Sleep(1000);
        return;
    }

    while (getline(file, category, '|') && getline(file, question, '|') && 
           getline(file, answer, '|') && getline(file, hint, '|') && 
           getline(file, difficulty) && flashcardCount < MAX_FLASHCARDS) {
        flashcards[flashcardCount++] = {category, question, answer, hint, difficulty};
    }
    file.close();
}

// Function to display flashcards
void displayFlashcards() {
    if (flashcardCount == 0) {
        Sleep(500);
        cout << "\tNo flashcards available!\n";
        Sleep(500);
        return;
    }Sleep(1000);
    cout << "\n\tFlashcards:\n\n";
    for (int i = 0; i < flashcardCount; i++) {
        cout << "\t" << i + 1 << ". [" << flashcards[i].category << " | Difficulty: " << flashcards[i].difficulty << "] \n\tQ: " << flashcards[i].question
             << " | A: " << flashcards[i].answer << " | Hint: " << flashcards[i].hint
             << "\n\n";
        Sleep(500);
    }
}

// Function to edit a flashcard
void editFlashcard() {
    Sleep(500);
    displayFlashcards();
    Sleep(500);
    cout << "\tEnter the Number of the Flashcard to Edit:\t";
    Sleep(500);
    int index;
    cin >> index;
    cin.ignore();
    if (index < 1 || index > flashcardCount) {
        cout << "\tInvalid choice!\n";
        return;
    }
    index--;
    Sleep(500);
    cout << "\tEnter New Question:\t";
    getline(cin, flashcards[index].question);
    cout << "\tEnter New Answer:\t";
    getline(cin, flashcards[index].answer);
    cout << "\tEnter New Hint:\t\t";
    getline(cin, flashcards[index].hint);
    cout << "\tEnter New Difficulty (Easy, Medium, Hard):\t";
    getline(cin, flashcards[index].difficulty);
    saveFlashcards();
    Sleep(1000);
}

// Function to delete a flashcard
void deleteFlashcard() {
    Sleep(1000);
    displayFlashcards();
    cout << "\tEnter the number of the Flashcard to delete:\t";
    int index;
    cin >> index;
    cin.ignore();
    if (index < 1 || index > flashcardCount) {
        cout << "\tInvalid choice!\n";
        return;
    }
    for (int i = index - 1; i < flashcardCount - 1; i++) {
        flashcards[i] = flashcards[i + 1];
    }
    flashcardCount--;
    saveFlashcards();
}

// Function to search for flashcards
void searchFlashcards() {
    cout << "\tEnter a keyword to search:\t";
    Sleep(1000);
    string keyword;
    int flag=0;
    getline(cin, keyword);
    for (int i = 0; i < flashcardCount; i++) {
        if (flashcards[i].question.find(keyword) != string::npos || 
            flashcards[i].answer.find(keyword) != string::npos) {
                Sleep(1000);
            cout << "\t[" << flashcards[i].category << "] \n\tQ: " << flashcards[i].question
                 << " | A: " << flashcards[i].answer << " | Hint: " << flashcards[i].hint << endl;
                 flag++;
        }
    }
    if(flag==0)
    cout << "\tSearch Unsuccessful :(\n\tFlashcard Not Found!\n";
}

// Function to take a quiz
void quizMode() {
    if (flashcardCount == 0) {
        cout << "\n\tNo flashcards available for quiz!\n";
        return;
    }
    srand(time(0));
    int correct = 0;
    

    // Shuffle flashcards
    for (int i = flashcardCount - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(flashcards[i], flashcards[j]);
    }

    string question_count;
    cout<<"\tEnter Number of Questions you want for the quiz (Enter -1 to ask for all possible questions):\t";
    getline(cin,question_count);
    cout<<endl;
    if (question_count == "-1") question_count = to_string(flashcardCount);
    int selectedCount = stoi(question_count);
    

    for (int i = 0; i < selectedCount; i++) {
        Sleep(500);
        cout << "\n\tCategory:\t" << flashcards[i].category << " | Difficulty:\t" << flashcards[i].difficulty << "\n\tQuestion:\t" << flashcards[i].question << "\n\t";
        cout << "(Type 'hint' for a hint) \n";

        string userAnswer;
        ans:
        Sleep(200);
        cout << "\n\tYour Answer:\t";
        getline(cin, userAnswer);

        if (toLower(userAnswer) == toLower(flashcards[i].answer)) {
            cout << "\tYAY! Correct Answer :)\n";
            correct++;
            Sleep(500);
        } 
        else if(toLower(userAnswer) == "hint"){
            cout <<'\t'<<"Hint    :\t"<<flashcards[i].hint;
            goto ans;
        }
        else {
            cout << "\tOOPS! Incorrect Answer :("<<endl;
            Sleep(500);
            cout << "\tCorrect Answer:\t" << (flashcards[i].answer) <<endl;
        }
    }
    Sleep(500);
    // Quiz summary
    cout << "\n\t\t------------";
    cout << "\n\t\tQuiz Summary";
    cout << "\n\t\t------------\n";
    cout << "\n\tCorrect Answers:\t" << correct << endl;
    cout << "\tIncorrect Answers:\t" << (selectedCount - correct) << endl;
    cout << "\tAccuracy:\t" << ((float)correct / selectedCount) * 100 << "%\n";
   
}


// Main menu
int main() {
    int choice;
    do {
        Sleep(500);
        cout << "\n\t\t\t=======================";
        cout << "\n\t\t\t  Flashcard Generator\n";
        cout <<   "\t\t\t=======================\n\n";
        Sleep(1000);
        cout << "\t1. Add Flashcard\n";
        Sleep(500);
        cout << "\t2. View Flashcards\n";
        Sleep(500);
        cout << "\t3. Edit Flashcards\n";
        Sleep(500);
        cout << "\t4. Delete Flashcards\n";
        Sleep(500);
        cout << "\t5. Search Flashcards\n";
        Sleep(500);
        cout << "\t6. Take Quiz\n";
        Sleep(500);
        cout << "\t7. Exit\n";
        Sleep(600);
        loadFlashcards();
        Sleep(600);
        cout << "\n\tChoice:\t";
        cin >> choice;
        cin.ignore();
        

        if (choice == 1) {
            if (flashcardCount >= MAX_FLASHCARDS) {
                Sleep(500);
                cout << "\tFlashcard limit reached!\n";
                continue;
            }
            Flashcard newCard;
            cout << "\tEnter Category:\t";
            getline(cin, newCard.category);
            cout << "\tEnter Question:\t";
            getline(cin, newCard.question);
            cout << "\tEnter Answer:\t";
            getline(cin, newCard.answer);
            cout << "\tEnter Hint:\t";
            getline(cin, newCard.hint);
            cout << "\tEnter Difficulty (Easy, Medium, Hard):\t";
            getline(cin, newCard.difficulty);
            flashcards[flashcardCount++] = newCard;
            saveFlashcards();
        } else if (choice == 2) displayFlashcards();
        else if (choice == 3) editFlashcard();
        else if (choice == 4) deleteFlashcard();
        else if (choice == 5) searchFlashcards();
        else if (choice == 6) quizMode();
    } while (choice != 7);
    Sleep(500);
    printf("\n\tGOODBYE! Hope You Learned Something New!\t");
    Sleep(500);
    return 0;
}
