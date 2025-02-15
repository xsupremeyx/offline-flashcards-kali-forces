#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "flashcards.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_btnView_clicked();
    void on_btnSearch_clicked();
    void on_btnQuiz_clicked();

    void on_lineEdit_6_cursorPositionChanged(int arg1, int arg2);

    void on_label_pic_linkHovered(const QString &link);

private:
    Ui::MainWindow *ui;
    QVector<Flashcard> flashcards;

    void loadFlashcards();
    void saveFlashcards();
};

#endif // MAINWINDOW_H
