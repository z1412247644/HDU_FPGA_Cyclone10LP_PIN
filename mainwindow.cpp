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
    AddDict(dict,C_arduino,ui->CB_PS2->isChecked());
}

void MainWindow::on_PB_generate_clicked()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    QString path = QFileDialog::getExistingDirectory(),path_qdf,path_qsf,path_v;
    path_qdf = path +"/"+ ui->lineEdit_Pro_name->text() +".qpf";
    /*creat project.qdf*/
    QString S_qdf("DATE = \"");
    S_qdf += current_date;
    S_qdf += "\n"
            "QUARTUS_VERSION = \"17.1.0\"\n"
            "\n"
            "# Revisions\n"
            "\n"
            "PROJECT_REVISON =\"";
    S_qdf += ui->lineEdit_Pro_name->text();
    S_qdf+= "\"\n"
            "\n";
    //creatFile(path_qdf,S_qdf);

    /*creat project.qsf*/
    QString S_qsf,S_CLOCK,S_LED,S_SEG8,S_KEY,S_SW,S_BEEP,S_VGA,S_DRAM,S_PS2;
    S_qsf = "#================================================================================\n"
            "# SYSTEM CONFIG\n"
            "#================================================================================\n"
            "set_global_assignment -name FAMILY \"Cyclone 10 LP\"\n"
            "set_global_assignment -name DEVICE 10CL006YU256C8G\n"
            "set_global_assignment -name TOP_LEVEL_ENTITY \"";
    S_qsf += ui->lineEdit_Pro_name->text();
    S_qsf+= "\"\n"
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
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to CLK_50\n"
              "set_location_assignment PIN_E15 -to CLK_50\n"
              "\n";
    S_LED = "#================================================================================\n"
            "# LED\n"
            "#================================================================================\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to LED[0]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to LED[1]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to LED[2]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to LED[3]\n"
            "set_location_assignment PIN_T10 -to LED[0]\n"
            "set_location_assignment PIN_R9 -to LED[1]\n"
            "set_location_assignment PIN_T9 -to LED[2]\n"
            "set_location_assignment PIN_K8 -to LED[3]\n"
            "\n";
    S_SEG8 =  "#================================================================================\n"
              "# SEG8\n"
              "#================================================================================\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[0]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[1]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[2]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[3]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[4]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[5]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[6]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[7]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[0]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[1]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[2]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[3]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[4]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[5]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[6]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[7]\n"
              "set_location_assignment PIN_D16 -to SEL[0]\n"
              "set_location_assignment PIN_C16 -to SEL[1]\n"
              "set_location_assignment PIN_B16 -to SEL[2]\n"
              "set_location_assignment PIN_B14 -to SEL[3]\n"
              "set_location_assignment PIN_B13 -to SEL[4]\n"
              "set_location_assignment PIN_B12 -to SEL[5]\n"
              "set_location_assignment PIN_B11 -to SEL[6]\n"
              "set_location_assignment PIN_B10 -to SEL[7]\n"
              "set_location_assignment PIN_D15 -to DIG[0]\n"
              "set_location_assignment PIN_C15 -to DIG[1]\n"
              "set_location_assignment PIN_A15 -to DIG[2]\n"
              "set_location_assignment PIN_A14 -to DIG[3]\n"
              "set_location_assignment PIN_A13 -to DIG[4]\n"
              "set_location_assignment PIN_A12 -to DIG[5]\n"
              "set_location_assignment PIN_A11 -to DIG[6]\n"
              "set_location_assignment PIN_A10 -to DIG[7]\n"
              "\n";
    S_KEY =   "#================================================================================\n"
              "# KEY\n"
              "#================================================================================\n"
              "set_instance_assignment -name IO_STANDARD \"3.3 V Schmitt Trigger\" -to KEY[0]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3 V Schmitt Trigger\" -to KEY[1]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3 V Schmitt Trigger\" -to KEY[2]\n"
              "set_instance_assignment -name IO_STANDARD \"3.3 V Schmitt Trigger\" -to KEY[3]\n"
              "set_location_assignment PIN_M1 -to KEY[0]\n"
              "set_location_assignment PIN_F3 -to KEY[1]\n"
              "set_location_assignment PIN_E1 -to KEY[2]\n"
              "set_location_assignment PIN_E2 -to KEY[3]\n"
              "\n";
    S_SW = "#================================================================================\n"
           "# SW\n"
           "#================================================================================\n"
           "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to SW[0]\n"
           "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to SW[1]\n"
           "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to SW[2]\n"
           "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to SW[3]\n"
           "set_location_assignment PIN_E16 -to SW[0]\n"
           "set_location_assignment PIN_M16 -to SW[1]\n"
           "set_location_assignment PIN_M15 -to SW[2]\n"
           "set_location_assignment PIN_M2 -to SW[3]\n"
           "\n";
    S_BEEP = "#================================================================================\n"
             "# BEEP\n"     //!SET BUZ/SW TO BUZ
             "#================================================================================\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to BEEP\n"
            "set_location_assignment PIN_K10 -to BEEP\n"
             "\n";
    S_PS2 = "#================================================================================\n"
            "# PS/2\n"
            "#================================================================================\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to PS2_DAT\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to PS2_DAT2\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to PS2_CLK\n"
            "set_instance_assignment -name IO_STANDARD \"3.3 V LVTTL\" -to PS2_CLK2\n"
            "set_location_assignment PIN_A8 -to PS2_DAT\n"
            "set_location_assignment PIN_R9 -to PS2_DAT2\n"
            "set_location_assignment PIN_B8 -to PS2_CLK\n"
            "set_location_assignment PIN_B9 -to PS2_CLK2\n"
            "\n";
    S_VGA = "#================================================================================\n"
            "# VGA\n"
            "#================================================================================\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[0]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[1]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[2]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[3]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[0]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[1]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[2]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[3]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[0]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[1]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[2]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[3]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_HS\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_VS\n"
            "set_location_assignment PIN_N16 -to VGA_B[0]\n"
            "set_location_assignment PIN_L15 -to VGA_B[1]\n"
            "set_location_assignment PIN_L16 -to VGA_B[2]\n"
            "set_location_assignment PIN_K15 -to VGA_B[3]\n"
            "set_location_assignment PIN_K16 -to VGA_G[0]\n"
            "set_location_assignment PIN_J15 -to VGA_G[1]\n"
            "set_location_assignment PIN_J16 -to VGA_G[2]\n"
            "set_location_assignment PIN_J11 -to VGA_G[3]\n"
            "set_location_assignment PIN_G16 -to VGA_R[0]\n"
            "set_location_assignment PIN_G15 -to VGA_R[1]\n"
            "set_location_assignment PIN_F16 -to VGA_R[2]\n"
            "set_location_assignment PIN_F15 -to VGA_R[3]\n"
            "set_location_assignment PIN_P16 -to VGA_HS\n"
            "set_location_assignment PIN_N15 -to VGA_VS\n"
            "\n";
    S_DRAM = "#================================================================================\n"
             "# DRAM\n"
             "#================================================================================\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[0]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[1]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[2]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[3]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[4]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[5]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[6]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[7]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[8]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[9]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[10]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[11]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[12]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_BA[0]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_BA[1]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CAS_N\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CKE\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CLK\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CS_N\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[0]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[1]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[2]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[3]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[4]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[5]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[6]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[7]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[8]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[9]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[10]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[11]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[12]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[13]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[14]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[15]\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_LDQM\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_RAS_N\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_UDQM\n"
            "set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_WE_N\n"
            "set_location_assignment PIN_J2 -to DRAM_ADDR[0]\n"
            "set_location_assignment PIN_K1 -to DRAM_ADDR[1]\n"
            "set_location_assignment PIN_K2 -to DRAM_ADDR[2]\n"
            "set_location_assignment PIN_L1 -to DRAM_ADDR[3]\n"
            "set_location_assignment PIN_T8 -to DRAM_ADDR[4]\n"
            "set_location_assignment PIN_R8 -to DRAM_ADDR[5]\n"
            "set_location_assignment PIN_T7 -to DRAM_ADDR[6]\n"
            "set_location_assignment PIN_R7 -to DRAM_ADDR[7]\n"
            "set_location_assignment PIN_T6 -to DRAM_ADDR[8]\n"
            "set_location_assignment PIN_R6 -to DRAM_ADDR[9]\n"
            "set_location_assignment PIN_J1 -to DRAM_ADDR[10]\n"
            "set_location_assignment PIN_T5 -to DRAM_ADDR[11]\n"
            "set_location_assignment PIN_R5 -to DRAM_ADDR[12]\n"
            "set_location_assignment PIN_G1 -to DRAM_BA[0]\n"
            "set_location_assignment PIN_J6 -to DRAM_BA[1]\n"
            "set_location_assignment PIN_C2 -to DRAM_CAS_N\n"
            "set_location_assignment PIN_T4 -to DRAM_CKE\n"
            "set_location_assignment PIN_R4 -to DRAM_CLK\n"
            "set_location_assignment PIN_G2 -to DRAM_CS_N\n"
            "set_location_assignment PIN_B5 -to DRAM_DQ[0]\n"
            "set_location_assignment PIN_A5 -to DRAM_DQ[1]\n"
            "set_location_assignment PIN_B6 -to DRAM_DQ[2]\n"
            "set_location_assignment PIN_A6 -to DRAM_DQ[3]\n"
            "set_location_assignment PIN_A4 -to DRAM_DQ[4]\n"
            "set_location_assignment PIN_B4 -to DRAM_DQ[5]\n"
            "set_location_assignment PIN_A3 -to DRAM_DQ[6]\n"
            "set_location_assignment PIN_B3 -to DRAM_DQ[7]\n"
            "set_location_assignment PIN_R3 -to DRAM_DQ[8]\n"
            "set_location_assignment PIN_T2 -to DRAM_DQ[9]\n"
            "set_location_assignment PIN_L2 -to DRAM_DQ[10]\n"
            "set_location_assignment PIN_N1 -to DRAM_DQ[11]\n"
            "set_location_assignment PIN_N2 -to DRAM_DQ[12]\n"
            "set_location_assignment PIN_P1 -to DRAM_DQ[13]\n"
            "set_location_assignment PIN_P2 -to DRAM_DQ[14]\n"
            "set_location_assignment PIN_R1 -to DRAM_DQ[15]\n"
            "set_location_assignment PIN_A2 -to DRAM_LDQM\n"
            "set_location_assignment PIN_D1 -to DRAM_RAS_N\n"
            "set_location_assignment PIN_T3 -to DRAM_UDQM\n"
            "set_location_assignment PIN_B1 -to DRAM_WE_N\n"
             "\n";
    /*if(ui->CB_clock->isChecked())
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
    */
    //path_qsf = path +"/"+ ui->lineEdit_Pro_name->text() +".qsf";
    //creatFile(path_qsf,S_qsf);

    /*creat project.v*/
    QString S_V,S_V_CLOCK,S_V_LED,S_V_SEG8,S_V_KEY,S_V_SW,S_V_BEEP,S_V_VGA,S_V_DRAM,S_V_PS2;
    S_V = "//=======================================================\n"
          "//  This code is generated by System Builder\n"
          "//=======================================================\n"
          "\n";
    S_V += "module " + ui->lineEdit_Pro_name->text() + "(\n\n";

    S_V_CLOCK = "//////////// CLOCK //////////\n"
                "\n";
    S_V_LED = "//////////// LED //////////\n"
                "\n";
    S_V_SEG8 = "//////////// SEG8 //////////\n"
                "\n";
    S_V_KEY = "//////////// KEY //////////\n"
                "\n";
    S_V_SW = "//////////// SW //////////\n"
                "\n";
    S_V_BEEP = "//////////// BEEP //////////\n"
                "\n";
    S_V_PS2 = "//////////// PS/2 //////////\n"
                "\n";
    S_V_VGA = "//////////// VGA //////////\n"
                "\n";
    S_V_DRAM = "//////////// DRAM //////////\n"
                "\n";

    /*Choice scan*/
    if(ui->CB_clock->isChecked()){
        S_qsf += S_CLOCK;
        S_V += S_V_CLOCK;
    }
    if(ui->CB_segment->isChecked()){
        S_qsf += S_SEG8;
        S_V += S_V_SEG8;
    }
    if(ui->CB_LED->isChecked()){
        S_qsf += S_LED;
        S_V += S_V_LED;
    }
    if(ui->CB_switch->isChecked()){
        S_qsf += S_SW;
        S_V += S_V_SW;
    }
    if(ui->CB_button->isChecked()){
        S_qsf += S_KEY;
        S_V += S_V_KEY;
    }
    if(ui->CB_VGA->isChecked()){
        S_qsf += S_VGA;
        S_V += S_V_VGA;
    }
    if(ui->CB_SDRAM->isChecked()){
        S_qsf += S_DRAM;
        S_V += S_V_DRAM;
    }
    if(ui->CB_PS2->isChecked()){
        S_qsf += S_PS2;
        S_V += S_V_PS2;
    }
    S_V += ");"
           "\n"
           "\n"
           "\n"
           "//=======================================================\n"
           "//  REG/WIRE declarations\n"
           "//=======================================================\n"
           "\n"
           "\n"
           "\n"
           "//=======================================================\n"
           "//  Structural coding\n"
           "//=======================================================\n"
           "\n"
           "\n"
           "\n"
           "endmodule"
           "\n";

    /*file create*/
    creatFile(path_qdf,S_qdf);

    path_qsf = path +"/"+ ui->lineEdit_Pro_name->text() +".qsf";
    creatFile(path_qsf,S_qsf);

    path_v = path +"/"+ ui->lineEdit_Pro_name->text() +".v";
    creatFile(path_v,S_V);

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
