#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include<QPixmap>
#include <QTextStream>
#include <QRandomGenerator>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString imagePath = QCoreApplication::applicationDirPath() + "/img2/FlashCard_Generator.jpg";
    QPixmap pixmap(imagePath);

    loadFlashcards();

    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::on_btnAdd_clicked);
    connect(ui->btnView, &QPushButton::clicked, this, &MainWindow::on_btnView_clicked);
    connect(ui->btnEdit, &QPushButton::clicked, this, &MainWindow::on_btnEdit_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::on_btnDelete_clicked);
    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::on_btnSearch_clicked);
    connect(ui->btnQuiz, &QPushButton::clicked, this, &MainWindow::on_btnQuiz_clicked);
}

MainWindow::~MainWindow()
{
    saveFlashcards();
    delete ui;
}

void MainWindow::loadFlashcards() {
    flashcards.clear();
    QFile file("flashcards.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        if (parts.size() == 5) {
            Flashcard newCard;
            newCard.category = parts[0];
            newCard.question = parts[1];
            newCard.answer = parts[2];
            newCard.hint = parts[3];
            newCard.difficulty = parts[4];
            flashcards.append(newCard);
        }
    }
    file.close();
}

void MainWindow::saveFlashcards() {
    QFile file("flashcards.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for (const auto &flashcard : flashcards) {
        out << flashcard.category << "|" << flashcard.question << "|" << flashcard.answer
            << "|" << flashcard.hint << "|" << flashcard.difficulty << "\n";
    }
    file.close();
}
void MainWindow::on_btnSearch_clicked() {
    if (flashcards.isEmpty()) {
        QMessageBox::warning(this, "Search Flashcards", "No flashcards available to search!");
        return;
    }

    bool ok;
    QString keyword = QInputDialog::getText(this, "Search Flashcards", "Enter a keyword to search:", QLineEdit::Normal, "", &ok);

    if (ok && !keyword.isEmpty()) {
        QString resultText;
        int foundCount = 0;

        for (const auto &flashcard : flashcards) {
            if (flashcard.question.contains(keyword, Qt::CaseInsensitive) ||
                flashcard.answer.contains(keyword, Qt::CaseInsensitive)) {
                resultText += "[" + flashcard.category + "]\nQ: " + flashcard.question +
                              "\nA: " + flashcard.answer + "\nHint: " + flashcard.hint + "\n\n";
                foundCount++;
            }
        }

        if (foundCount == 0) {
            QMessageBox::information(this, "Search Flashcards", "Search Unsuccessful: Flashcard Not Found!");
        } else {
            QMessageBox::information(this, "Search Results", resultText);
        }
    }
}
void MainWindow::on_btnView_clicked() {
    if (flashcards.isEmpty()) {
        QMessageBox::information(this, "View Flashcards", "No flashcards available!");
        return;
    }

    QString displayText = "Flashcards:\n\n";
    for (const auto &flashcard : flashcards) {
        QString difficultyStr = flashcard.difficulty;
        if (difficultyStr == "0") difficultyStr = "Easy";
        else if (difficultyStr == "1") difficultyStr = "Medium";
        else if (difficultyStr == "2") difficultyStr = "Hard";

        displayText += "[" + flashcard.category + " | Difficulty: " + difficultyStr + "]\nQ: "
                       + flashcard.question + "\nA: " + flashcard.answer + "\nHint: " + flashcard.hint + "\n\n";

    }

    QMessageBox::information(this, "Flashcards", displayText);
}

void MainWindow::on_btnEdit_clicked() {
    if (flashcards.isEmpty()) {
        QMessageBox::warning(this, "Error", "No flashcards available to edit.");
        return;
    }

    bool ok;
    int index = QInputDialog::getInt(this, "Edit Flashcard", "Enter the flashcard number:", 1, 1, flashcards.size(), 1, &ok);
    if (!ok) return;
    index--;

    QString newQuestion = QInputDialog::getText(this, "Edit Question", "New Question:", QLineEdit::Normal, flashcards[index].question, &ok);
    if (!ok || newQuestion.isEmpty()) return;
    flashcards[index].question = newQuestion;

    QString newAnswer = QInputDialog::getText(this, "Edit Answer", "New Answer:", QLineEdit::Normal, flashcards[index].answer, &ok);
    if (!ok || newAnswer.isEmpty()) return;
    flashcards[index].answer = newAnswer;

    QString newHint = QInputDialog::getText(this, "Edit Hint", "New Hint:", QLineEdit::Normal, flashcards[index].hint, &ok);
    if (!ok) return;
    flashcards[index].hint = newHint;

    bool conversionOk;
    QString newDifficulty = QInputDialog::getText(this, "Edit Difficulty", "New Difficulty (Easy, Medium, Hard):");
    if (!conversionOk) return;
    flashcards[index].difficulty = newDifficulty;

    saveFlashcards();
    QMessageBox::information(this, "Success", "Flashcard updated successfully!");
}

void MainWindow::on_btnAdd_clicked() {
    if (ui->txtQuestion->toPlainText().isEmpty() || ui->txtAnswer->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Error", "Question and Answer fields cannot be empty!");
        return;
    }

    Flashcard newCard;
    newCard.category = ui->comboCategory->currentText();
    newCard.question = ui->txtQuestion->toPlainText();
    newCard.answer = ui->txtAnswer->toPlainText();
    newCard.hint = ui->txtHint->toPlainText();
    newCard.difficulty = ui->comboDifficulty->currentText();

    flashcards.append(newCard);
    saveFlashcards();
    QMessageBox::information(this, "Success", "Flashcard added!");

    ui->txtQuestion->clear();
    ui->txtAnswer->clear();
    ui->txtHint->clear();
}

void MainWindow::on_btnDelete_clicked() {
    if (flashcards.isEmpty()) {
        QMessageBox::warning(this, "Delete Flashcard", "No flashcards available to delete!");
        return;
    }

    bool ok;
    int index = QInputDialog::getInt(this, "Delete Flashcard", "Enter the number of the flashcard to delete:", 1, 1, flashcards.size(), 1, &ok);
    if (ok) {
        flashcards.removeAt(index - 1);
        saveFlashcards();
        QMessageBox::information(this, "Delete Flashcard", "Flashcard deleted successfully!");
    }
}

void MainWindow::on_btnQuiz_clicked() {
    if (flashcards.isEmpty()) {
        QMessageBox::information(this, "Quiz Mode", "No flashcards available for the quiz!");
        return;
    }

    bool ok;
    int questionCount = QInputDialog::getInt(this, "Quiz Mode", "Enter number of questions (-1 for all):", 1, -1, flashcards.size(), 1, &ok);
    if (!ok) return;

    if (questionCount == -1) questionCount = flashcards.size();

    std::shuffle(flashcards.begin(), flashcards.end(), *QRandomGenerator::global());

    int correctAnswers = 0;
    int askedQuestions = 0;

    while (askedQuestions < questionCount) {
        while(true){
        QString userAnswer = QInputDialog::getText(this, "Quiz Mode", "Question: " + flashcards[askedQuestions].question, QLineEdit::Normal, "", &ok);
        if (!ok) return;

        if (userAnswer.toLower() == flashcards[askedQuestions].answer.toLower()) {
            correctAnswers++;
            QMessageBox::information(this, "Result", "Correct!");
            break;
        } else if(userAnswer.toLower() == "hint"){
            QMessageBox::information(this, "Result", "Hint: " + flashcards[askedQuestions].hint);
            continue;
        }
        else {
            QMessageBox::information(this, "Result", "Incorrect! The correct answer is: " + flashcards[askedQuestions].answer);
            break;
        }}
        askedQuestions++;
    }
    QString summary = QString("Quiz Completed!\nCorrect: %1\nIncorrect: %2").arg(correctAnswers).arg(questionCount - correctAnswers);
    QMessageBox::information(this, "Quiz Summary", summary);
}

void MainWindow::on_lineEdit_6_cursorPositionChanged(int arg1, int arg2)
{

}


void MainWindow::on_label_pic_linkHovered(const QString &link)
{

}

