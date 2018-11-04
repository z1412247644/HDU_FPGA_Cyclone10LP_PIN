#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QGraphicsView>
#include <QtGui>
#include <QtWidgets>
#include<QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitDict(dict);
    textEdit = new QTextEdit(this);
    textEdit->setVisible(false);
    //setCentralWidget(textEdit);
    /*
    QPainter painter;
    QPixmap pix;
    pix.load(":/img/logo");
    painter.drawPixmap(0, 0, 129, 66, pix);
    */
}
MainWindow::~MainWindow()
{
    delete ui;
    DestroyDict(dict);
}

void MainWindow::creatFile(QString path,QString text)
{
    //QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << text;
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::CB_Check(){
    AddDict(dict,C_clock,ui->CB_clock->isChecked());
    AddDict(dict,C_segment,ui->CB_segment->isChecked());
    AddDict(dict,C_LED,ui->CB_LED->isChecked());
    AddDict(dict,C_switch,ui->CB_switch->isChecked());
    AddDict(dict,C_button,ui->CB_button->isChecked());
    AddDict(dict,C_ROM,ui->CB_ROM->isChecked());
    AddDict(dict,C_VGA,ui->CB_VGA->isChecked());
    AddDict(dict,C_SDRAM,ui->CB_SDRAM->isChecked());
    AddDict(dict,C_arduino,ui->CB_arduion->isChecked());
}

void MainWindow::on_PB_generate_clicked()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    QString path = QFileDialog::getExistingDirectory(),path_qdf,path_qsf;
    path_qdf = path +"/"+ ui->lineEdit_Pro_name->text() +".qpf";
    /*creat project.qdf*/
    QString S_qdf("DATE = \"");
    S_qdf += current_date;
    S_qdf += "\n"
            "QUARTUS_VERSION = \"17.1.0\"\n"
            "\n"
            "#Revisions\n"
            "\n"
            "PROJIECT_REVISON =\"TEST\"\n"
            "\n";
    creatFile(path_qdf,S_qdf);

    /*creat project.qsf*/
    QString S_qsf,S_CLOCK,S_LED,S_SEG8,S_KEY,S_SW,S_BEEP,S_VGA;
    S_qsf = "#================================================================================\n"
            "# SYSTEM CONFIG\n"
            "#================================================================================\n"
            "set_global_assignment -name FAMILY \"Cyclone 10 LP\"\n"
            "set_global_assignment -name DEVICE 10CL006YU256C8G\n"
            "set_global_assignment -name TOP_LEVEL_ENTITY TEST\n"     //!!need to change
            "set_global_assignment -name ORIGINAL_QUARTUS_VERSION 18.1.0\n"
            "set_global_assignment -name LAST_QUARTUS_VERSION \"17.1.0 Standard Edition\"\n"
            "set_global_assignment -name DEVICE_FILTER_PACKAGE UFBGA\n"
            "set_global_assignment -name DEVICE_FILTER_PIN_COUNT 256\n"
            "set_global_assignment -name DEVICE_FILTER_SPEED_GRADE 8\n"
            "set_global_assignment -name ERROR_CHECK_FREQUENCY_DIVISOR 1\n"
            "set_global_assignment -name NOMINAL_CORE_SUPPLY_VOLTAGE 1.2V\n"
            "set_global_assignment -name EDA_SIMULATION_TOOL \"ModelSim-Altera (Verilog)\"\n"
            "set_global_assignment -name EDA_TIME_SCALE \"1 ps\" -section_id eda_simulation\n"
            "set_global_assignment -name EDA_OUTPUT_DATA_FORMAT \"VERILOG HDL\" -section_id eda_simulation\n"
            "set_global_assignment -name EDA_GENERATE_FUNCTIONAL_NETLIST ON -section_id eda_simulation\n"
            "\n";
    S_CLOCK = "#================================================================================\n"
              "# CLOCK\n"
              "#================================================================================\n"
              "\n";
    S_LED = "#================================================================================\n"
            "# LED\n"
            "#================================================================================\n"
            "\n";
    S_SEG8 =  "#================================================================================\n"
              "# SEG8\n"
              "#================================================================================\n"
              "\n";
    S_KEY =   "#================================================================================\n"
              "# KEY\n"
              "#================================================================================\n"
              "\n";
    S_SW = "#================================================================================\n"
           "# SW\n"
           "#================================================================================\n"
           "\n";
    S_BEEP = "#================================================================================\n"
             "# BEEP\n"
             "#================================================================================\n"
             "\n";
    S_VGA = "#================================================================================\n"
            "# VGA\n"
            "#================================================================================\n"
            "\n";

    if(ui->CB_clock->isChecked())
        S_qsf += S_CLOCK;
    if(ui->CB_segment->isChecked())
        S_qsf += S_SEG8;
    if(ui->CB_LED->isChecked())
        S_qsf += S_LED;
    if(ui->CB_switch->isChecked())
        S_qsf += S_SW;
    if(ui->CB_button->isChecked())
        S_qsf += S_KEY;
    if(ui->CB_VGA->isChecked())
        S_qsf += S_VGA;

    path_qsf = path +"/"+ ui->lineEdit_Pro_name->text() +".qsf";
    creatFile(path_qsf,S_qsf);

}

void MainWindow::on_PB_save_clicked()
{

}

void MainWindow::on_PB_load_clicked()
{
    openFile();
}

void MainWindow::on_PB_exit_clicked()
{
    this->close();
}
