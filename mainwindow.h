#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QCheckBox>
#include "Dict.h"
#include "choice_to_int.h"

class QTextEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Dictptr dict;
private slots:
    void openFile();
    void saveFile();
    void creatFile(QString,QString);

    void on_PB_generate_clicked();

    void on_PB_save_clicked();

    void on_PB_load_clicked();

    void CB_Check();

    void on_PB_exit_clicked();

private:
    QTextEdit *textEdit;
};

#endif // MAINWINDOW_H
