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
    //Dictptr dict;
    //QImage* img_main=new QImage,*img_logo= new QImage;
    //QImage* img_main_Scaled = new QImage,*img_logo_Scaled = new QImage;
private slots:
    void openFile();
    void saveFile();
    void creatFile(QString,QString);

    void on_PB_generate_clicked();

    void on_PB_save_clicked();

    void on_PB_load_clicked();

    void CB_Check();

    void on_PB_exit_clicked();

    void on_CB_segment_stateChanged(int arg1);

    void on_CB_LED_stateChanged(int arg1);

    void on_CB_switch_stateChanged(int arg1);

    void on_CB_button_stateChanged(int arg1);

    void on_CB_Serial_stateChanged(int arg1);

    void on_CB_VGA_stateChanged(int arg1);

    void on_CB_SDRAM_stateChanged(int arg1);

    void on_CB_PS2_stateChanged(int arg1);

    void on_CB_BEEP_stateChanged(int arg1);

private:
    QTextEdit *textEdit;
};

#endif // MAINWINDOW_H
