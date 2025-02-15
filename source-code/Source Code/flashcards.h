#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <QString>

class Flashcard {
public:
    QString category;
    QString question;
    QString answer;
    QString hint;
    QString difficulty;

    Flashcard() = default;  // Default constructor
    Flashcard(const QString &cat, const QString &ques, const QString &ans, const QString &h, const QString diff)
        : category(cat), question(ques), answer(ans), hint(h), difficulty(diff) {}
};

#endif // FLASHCARD_H
