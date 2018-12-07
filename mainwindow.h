#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QCheckBox>
#include "Dict.h"
#include "choice_to_int.h"
#include<QQueue>
#include <QtGui>
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
    QQueue<DNode> q;
    //QImage* img_main=new QImage,*img_logo= new QImage;
    //QImage* img_main_Scaled = new QImage,*img_logo_Scaled = new QImage;
private slots:
    void openFile(QFile &file,QString f_path);
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

    void on_CB_Change_clicked();

    void Name_Change(); //using to change the pin_name

    void on_CBB_GPIO_currentIndexChanged(int index);

private:
    QTextEdit *textEdit;
    QString path;
    QMap<QString,QString> PIN_INOUT;
};

#endif // MAINWINDOW_H
