#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QGraphicsView>
//#include <QtGui>
#include <QtWidgets>
#include<QDateTime>
#include<QImage>
#include<QListWidget>
#include<QMap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //InitDict(dict);

    textEdit = new QTextEdit(this);
    textEdit->setVisible(false);

    ui->lineEdit_Pro_name->setText("HX1006A");
    /*rect visible init*/
    ui->Rect_BEEP->setVisible(false);
    ui->Rect_KEY->setVisible(false);
    ui->Rect_LED->setVisible(false);
    ui->Rect_PS2->setVisible(false);
    ui->Rect_SDRAM->setVisible(false);
    ui->Rect_SEG->setVisible(false);
    ui->Rect_SW->setVisible(false);
    ui->Rect_Serial->setVisible(false);
    ui->Rect_VGA->setVisible(false);
    ui->Rect_FLASH->setVisible(false);

    //CBB_init
    ui->CBB_O_name->insertItem(0,"CLK_50");

    CAN_BE_CHANGE_NAME = false;

    PIN_MODE_INIT();

    //setWindowFlags(Qt::FramelessWindowHint);
    ui->actionAbout_3->connect(ui->actionAbout_3,SIGNAL(triggered()),this,SLOT(about_show()));
    ui->actionhelp->connect(ui->actionhelp,SIGNAL(triggered()),this,SLOT(help_show()));
    ui->actionPIN_MAP->connect(ui->actionPIN_MAP, SIGNAL(triggered()),this,SLOT(pin_map_show()));
}
MainWindow::~MainWindow()
{
    FinalChange();
    delete ui;
    delete textEdit;
//    DestroyDict(dict);
//    delete img_main;
//    delete img_logo;
//    delete img_main_Scaled;
//    delete img_logo_Scaled;
}

void MainWindow::PIN_MODE_INIT(){
    PIN_INOUT.insert("KEY","input");
    PIN_INOUT.insert("SW","input");
    PIN_INOUT.insert("LED","output");
    PIN_INOUT.insert("CLK_50","output");
    PIN_INOUT.insert("VGA_B","output");
    PIN_INOUT.insert("VGA_G","output");
    PIN_INOUT.insert("VGA_R","output");
    PIN_INOUT.insert("VGA_HS","output");
    PIN_INOUT.insert("VGA_VS","output");
    PIN_INOUT.insert("PS2_DAT","inout");
    PIN_INOUT.insert("PS2_DAT2","inout");
    PIN_INOUT.insert("PS2_CLK","inout");
    PIN_INOUT.insert("PS2_CLK2","inout");
    PIN_INOUT.insert("UART_TXD","output");
    PIN_INOUT.insert("UART_RXD","input");
    PIN_INOUT.insert("SD_CLK","output");
    PIN_INOUT.insert("SD_CMD","inout");
    PIN_INOUT.insert("SD_DAT","inout");
    PIN_INOUT.insert("BEEP","output");
    PIN_INOUT.insert("SPIFLASH_CS","output");
    PIN_INOUT.insert("SPIFLASH_SCLK","inout");
    PIN_INOUT.insert("SPIFLASH_HOLD","inout");
    PIN_INOUT.insert("SPIFLASH_SDI","inout");
    PIN_INOUT.insert("SPIFLASH_SDO","inout");
    PIN_INOUT.insert("SPIFLASH_WP","inout");
    PIN_INOUT.insert("DRAM_ADDR","output");
    PIN_INOUT.insert("DRAM_BA","output");
    PIN_INOUT.insert("DRAM_CAS_N","output");
    PIN_INOUT.insert("DRAM_CKE","output");
    PIN_INOUT.insert("DRAM_CLK","output");
    PIN_INOUT.insert("DRAM_CS_N","output");
    PIN_INOUT.insert("DRAM_LDQM","output");
    PIN_INOUT.insert("DRAM_RAS_N","output");
    PIN_INOUT.insert("DRAM_UDQM","output");
    PIN_INOUT.insert("DRAM_WE_N","output");
    PIN_INOUT.insert("DRAM_DQ","inout");
}
void MainWindow::creatFile(QString path,QString text)
{
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

void MainWindow::openFile(QFile &file,QString f_path)
{
    //QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
    file.setFileName(f_path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
        return;
    }
        //textEdit->setText(in.readAll());
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
//    AddDict(dict,C_clock,ui->CB_clock->isChecked());
//    AddDict(dict,C_segment,ui->CB_segment->isChecked());
//    AddDict(dict,C_LED,ui->CB_LED->isChecked());
//    AddDict(dict,C_switch,ui->CB_switch->isChecked());
//    AddDict(dict,C_button,ui->CB_button->isChecked());
//    AddDict(dict,C_,ui->CB_ROM->isChecked());
//    AddDict(dict,C_VGA,ui->CB_VGA->isChecked());
//    AddDict(dict,C_SDRAM,ui->CB_SDRAM->isChecked());
//    AddDict(dict,C_arduino,ui->CB_PS2->isChecked());
}

void MainWindow::on_PB_generate_clicked()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    path = QFileDialog::getExistingDirectory();
    QString path_qdf,path_qsf,path_v;
    path = path + "/" + ui->lineEdit_Pro_name->text();
    /*Check dir exist,if not exist then creat dir*/
    QDir dir;
    if (!dir.exists(path))
    {
       bool res = dir.mkpath(path);
       if(!res)
           QMessageBox::warning(this, tr("ERROR"), tr("Creat DIR:\n%1\nERROR!").arg(path));
    }
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
    QString S_qsf,S_CLOCK,S_LED,S_SEG8,S_KEY,S_SW,S_BEEP,S_VGA,S_DRAM,S_PS2,S_SDCard,S_Serial,S_FLASH;
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
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to CLK_50\n"
              "set_location_assignment PIN_E15 -to CLK_50\n"
              "\n";
    S_LED = "#================================================================================\n"
            "# LED\n"
            "#================================================================================\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to LED[0]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to LED[1]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to LED[2]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to LED[3]\n"
            "set_location_assignment PIN_T10 -to LED[0]\n"
            "set_location_assignment PIN_R9 -to LED[1]\n"
            "set_location_assignment PIN_T9 -to LED[2]\n"
            "set_location_assignment PIN_K8 -to LED[3]\n"
            "\n";
    S_SEG8 =  "#================================================================================\n"
              "# SEG8\n"
              "#================================================================================\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[0]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[1]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[2]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[3]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[4]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[5]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[6]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SEL[7]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[0]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[1]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[2]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[3]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[4]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[5]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[6]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DIG[7]\n"
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
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to KEY[0]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to KEY[1]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to KEY[2]\n"
              //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to KEY[3]\n"
              "set_location_assignment PIN_M1 -to KEY[0]\n"
              "set_location_assignment PIN_F3 -to KEY[1]\n"
              "set_location_assignment PIN_E1 -to KEY[2]\n"
              "set_location_assignment PIN_E2 -to KEY[3]\n"
              "\n";
    S_SW = "#================================================================================\n"
           "# SW\n"
           "#================================================================================\n"
           //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SW[0]\n"
           //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SW[1]\n"
           //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SW[2]\n"
           //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SW[3]\n"
           "set_location_assignment PIN_E16 -to SW[0]\n"
           "set_location_assignment PIN_M16 -to SW[1]\n"
           "set_location_assignment PIN_M15 -to SW[2]\n"
           "set_location_assignment PIN_M2 -to SW[3]\n"
           "\n";
    S_BEEP = "#================================================================================\n"
             "# BEEP\n"     //!SET BUZ/SW TO BUZ
             "#================================================================================\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to BEEP\n"
            "set_location_assignment PIN_K10 -to BEEP\n"
             "\n";
    S_PS2 = "#================================================================================\n"
            "# PS/2\n"
            "#================================================================================\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to PS2_DAT\n"
            "#set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to PS2_DAT2\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to PS2_CLK\n"
            "#set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to PS2_CLK2\n"
            "set_location_assignment PIN_A8 -to PS2_DAT\n"
            "#set_location_assignment PIN_R9 -to PS2_DAT2\n"
            "set_location_assignment PIN_B8 -to PS2_CLK\n"
            "#set_location_assignment PIN_B9 -to PS2_CLK2\n"
            "\n";
    S_VGA = "#================================================================================\n"
            "# VGA\n"
            "#================================================================================\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[0]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[1]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[2]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_B[3]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[0]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[1]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[2]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_G[3]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[0]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[1]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[2]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_R[3]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_HS\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to VGA_VS\n"
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
            "set_location_assignment PIN_F16 -to VGA_R[2]\n"    //!PIN_F16
            "set_location_assignment PIN_F15 -to VGA_R[3]\n"
            "set_location_assignment PIN_P16 -to VGA_HS\n"
            "set_location_assignment PIN_N15 -to VGA_VS\n"
            "set_global_assignment -name CYCLONEII_RESERVE_NCEO_AFTER_CONFIGURATION \"USE AS REGULAR IO\""  //!PIN_F16 need Multiplexing
            "\n";

    S_SDCard = "#================================================================================\n"
               "# SDCard\n"
               "#================================================================================\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SD_DAT[0]\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SD_DAT[1]\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SD_DAT[2]\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SD_DAT[3]\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SD_CLK\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to SD_CMD\n"
               "set_location_assignment PIN_T11 -to SD_DAT[0]\n"
               "set_location_assignment PIN_R10 -to SD_DAT[1]\n"
               "set_location_assignment PIN_T13 -to SD_DAT[2]\n"
               "set_location_assignment PIN_R12 -to SD_DAT[3]\n"
               "set_location_assignment PIN_R11 -to SD_CLK\n"
               "set_location_assignment PIN_T12 -to SD_CMD\n"
               "\n";
    S_Serial = "#================================================================================\n"
               "# Serial Prot\n"
               "#================================================================================\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to RXD\n"
               //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to TXD\n"
               "set_location_assignment PIN_B7 -to UART_RXD\n"
               "set_location_assignment PIN_A7 -to UART_TXD\n"
               "\n";
    S_FLASH = "#================================================================================\n"
              "# SPIFLASH\n"
              "#================================================================================\n"
              "set_location_assignment PIN_R13 -to SPIFLASH_CS\n"
              "set_location_assignment PIN_T14 -to SPIFLASH_HOLD\n"
              "set_location_assignment PIN_T15 -to SPIFLASH_SCLK\n"
              "set_location_assignment PIN_P15 -to SPIFLASH_SDI\n"
              "set_location_assignment PIN_R14 -to SPIFLASH_SDO\n"
              "set_location_assignment PIN_R16 -to SPIFLASH_WP\n"
              "\n";
    S_DRAM = "#================================================================================\n"
             "# DRAM\n"
             "#================================================================================\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[0]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[1]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[2]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[3]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[4]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[5]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[6]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[7]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[8]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[9]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[10]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[11]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_ADDR[12]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_BA[0]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_BA[1]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CAS_N\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CKE\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CLK\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_CS_N\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[0]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[1]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[2]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[3]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[4]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[5]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[6]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[7]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[8]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[9]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[10]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[11]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[12]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[13]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[14]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_DQ[15]\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_LDQM\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_RAS_N\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_UDQM\n"
            //"set_instance_assignment -name IO_STANDARD \"3.3-V LVTTL\" -to DRAM_WE_N\n"
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

    /*creat project.v*/
    QString S_V,S_V_CLOCK,S_V_LED,S_V_SEG8,S_V_KEY,S_V_SW,S_V_BEEP,S_V_VGA,S_V_DRAM,S_V_PS2,S_V_SDCard,S_V_Serial,S_V_FLASH;
    S_V = "//=======================================================\n"
          "//  This code is generated by System Builder\n"
          "//=======================================================\n"
          "\n";
    S_V += "module " + ui->lineEdit_Pro_name->text() + "(\n\n";

    S_V_CLOCK = "////////////CLOCK//////////\n"
                "input 		          		CLK_50,\n"
                "\n";
    S_V_LED = "////////////LED//////////\n"
              "output		     [3:0]		LED,\n"
                "\n";
    S_V_SEG8 = "////////////SEG8//////////\n"
               "output 		   [7:0]       	SEL,\n"
               "output 		   [7:0]     	DIG,\n"
                "\n";
    S_V_KEY = "////////////KEY//////////\n"
              "input 		     [3:0]		KEY,\n"
                "\n";
    S_V_SW = "////////////SW//////////\n"
             "input 		     [3:0]		SW,\n"
                "\n";
    S_V_BEEP = "////////////BEEP//////////\n"
               "output 		          		BEEP,\n"
                "\n";
    S_V_PS2 = "////////////PS/2//////////\n"
              "inout 		          		PS2_DAT,\n"
              "//inout 		          		PS2_DAT2,\n"
              "inout 		          		PS2_CLK,\n"
              "//inout 		          		PS2_CLK2,\n"
              "\n";
    S_V_SDCard = "////////////SDCard//////////\n"
                 "output 		          		SD_CLK,\n"
                 "inout 		          		SD_CMD,\n"
                 "inout           [3:0]       	SD_DAT,\n"
                "\n";
    S_V_Serial = "////////////Serial Port//////////\n"
                 "output 		          		UART_TXD,\n"
                 "input 		          		UART_RXD,\n"
                 "\n";
    S_V_VGA = "////////////VGA//////////\n"
              "output		     [3:0]		VGA_B,\n"
              "output		     [3:0]		VGA_G,\n"
              "output		          		VGA_HS,\n"
              "output		     [3:0]		VGA_R,\n"
              "output		          		VGA_VS,\n"
              "\n";
    S_V_FLASH = "////////////SPIFLASH//////////\n"
                "output             		SPIFLASH_CS,\n"
                "output             		SPIFLASH_SCLK,\n"
                "inout                      SPIFLASH_HOLD,\n"
                "inout                      SPIFLASH_SDI,\n"
                "inout                      SPIFLASH_SDO,\n"
                "inout                      SPIFLASH_WP,\n"
                "\n";
    S_V_DRAM = "////////////DRAM//////////\n"
               "output		    [12:0]		DRAM_ADDR,\n"
               "output		     [1:0]		DRAM_BA,\n"
               "output		          		DRAM_CAS_N,\n"
               "output		          		DRAM_CKE,\n"
               "output		          		DRAM_CLK,\n"
               "output		          		DRAM_CS_N,\n"
               "inout 		    [15:0]		DRAM_DQ,\n"
               "output		          		DRAM_LDQM,\n"
               "output		          		DRAM_RAS_N,\n"
               "output		          		DRAM_UDQM,\n"
               "output		          		DRAM_WE_N,\n"
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
    if(ui->CB_Serial->isChecked()){
        S_qsf += S_Serial;
        S_V += S_V_Serial;
    }
    if(ui->CB_SDCard->isChecked()){
        S_qsf += S_SDCard;
        S_V += S_V_SDCard;
    }
    if(ui->CB_BEEP->isChecked()){
        S_qsf += S_BEEP;
        S_V += S_V_BEEP;
    }
    if(ui->CB_FLASH->isChecked()){
        S_qsf += S_FLASH;
        S_V += S_V_FLASH;
    }
    int index_dot = S_V.lastIndexOf(",",-1);

    if(index_dot!=-1)
        S_V[index_dot] = ' ';   //remove "," from the end of last item
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
    
    QFile::copy(":/html/html",path +"/"+ ui->lineEdit_Pro_name->text() +".html");

    CAN_BE_CHANGE_NAME = true;
    QMessageBox::information(this,"INFO","Generate project sucessfull");
}

void MainWindow::on_PB_exit_clicked()
{
    this->close();
}

void MainWindow::on_CB_segment_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_SEG->setVisible(true);
    else
        ui->Rect_SEG->setVisible(false);
}

void MainWindow::on_CB_LED_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_LED->setVisible(true);
    else
        ui->Rect_LED->setVisible(false);
}

void MainWindow::on_CB_switch_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_SW->setVisible(true);
    else
        ui->Rect_SW->setVisible(false);
}

void MainWindow::on_CB_button_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_KEY->setVisible(true);
    else
        ui->Rect_KEY->setVisible(false);
}

void MainWindow::on_CB_Serial_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_Serial->setVisible(true);
    else
        ui->Rect_Serial->setVisible(false);
}

void MainWindow::on_CB_VGA_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_VGA->setVisible(true);
    else
        ui->Rect_VGA->setVisible(false);
}

void MainWindow::on_CB_SDRAM_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_SDRAM->setVisible(true);
    else
        ui->Rect_SDRAM->setVisible(false);
}

void MainWindow::on_CB_PS2_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_PS2->setVisible(true);
    else
        ui->Rect_PS2->setVisible(false);
}

void MainWindow::on_CB_BEEP_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_BEEP->setVisible(true);
    else
        ui->Rect_BEEP->setVisible(false);
}

void MainWindow::on_CB_FLASH_stateChanged(int arg1)
{
    if(arg1)
        ui->Rect_FLASH->setVisible(true);
    else
        ui->Rect_FLASH->setVisible(false);
}

void MainWindow::on_CB_Change_clicked()
{
    if(!CAN_BE_CHANGE_NAME){
        QMessageBox::information(this,"WARNING","Please generate the project first");
        return;
    }
    DNode temp;
    temp.key=ui->CBB_O_name->currentText();
    temp.value=ui->N_Name->text();       
    ui->listWidget->addItem(temp.key+" ==> "+temp.value);
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    q.enqueue(temp);
    Name_Change();
}

void MainWindow::Name_Change(){
    QString path_qsf,path_v,s_temp,s_get,s_,s_special_name,s_o_name,s_comment;
    QRegExp regrxp_num("\\[(\\d+)"),regrxp_name("(.*)\\[");
    QFile f_temp;
    QTextStream f_stream(&f_temp);
    DNode temp;
    QMessageBox::StandardButton YorN;

    path_qsf = path +"/"+ ui->lineEdit_Pro_name->text() +".qsf";
    path_v = path +"/"+ ui->lineEdit_Pro_name->text() +".v";

    while(!q.empty()){
        temp = q.dequeue();
        s_o_name = s_get = temp.key;
        s_get.replace(QRegExp("\\["),"\\[");
        s_get.replace(QRegExp("\\]"),"\\]");

        /*qsf change*/
        openFile(f_temp,path_qsf);
        s_temp =  f_stream.readAll();
        if(s_o_name.contains("ALL")){   //Change the Grop name
            s_temp.replace(s_o_name.mid(0,s_o_name.lastIndexOf("_")),temp.value);
        }
        else if(!s_o_name.contains("[")){
            s_temp.replace(QRegExp(s_get),temp.value);
        }
        else {         //Change one item name
            YorN = QMessageBox::question(this,"Waring","This action will break the port group,\nDo you want to continue?",QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
            if(YorN == QMessageBox::No){
                ui->listWidget->takeItem(ui->listWidget->currentRow());
                break;
            }
            s_temp.replace(QRegExp(s_get),temp.value);
        }
        f_temp.close();
        f_temp.open(QIODevice::Truncate);
        f_temp.close();
        f_temp.open(QIODevice::WriteOnly);
        f_stream<<s_temp;
        f_temp.close();

        /*v change*/
        openFile(f_temp,path_v);
        s_temp =  f_stream.readAll();
        if(s_o_name.contains("ALL")){   //Change the Grop name
            //QMessageBox::about(NULL,"NO",s_temp.replace(s_o_name.mid(0,s_o_name.indexOf("_"))+",",temp.value+","));               
            if(s_temp.replace(s_o_name.mid(0,s_o_name.lastIndexOf("_"))+",",temp.value+",")==s_temp)
                s_temp.replace(s_o_name.mid(0,s_o_name.lastIndexOf("_"))+" ",temp.value);
        }
        else if(!s_o_name.contains("[")){
             s_temp.replace(s_o_name,temp.value);
             QMessageBox::information(this,"CHANGE","RENAME "+temp.key+" TO "+temp.value);
        }
        else {      //Change one item name
            if(YorN == QMessageBox::No)
                break;
            int pos = regrxp_name.indexIn(s_o_name);
            if(pos!=-1){                
                s_special_name = regrxp_name.cap(1);
                ui->label->setText(s_special_name);
                //s_comment = QString("\n//!!PIN %1 has been change to %2,dont use this PIN\n").arg(s_o_name).arg(temp.value);
                //s_comment = QString("\n//!!PIN Group %1 has been break ,Please see the .qsf file for details.\n").arg(s_special_name);

                s_comment = PIN_INOUT[s_special_name]+"            "+temp.value+",\n";

                int locate = s_temp.lastIndexOf(s_special_name+",");
                if(locate==-1)
                    locate = s_temp.lastIndexOf(s_special_name+" ");

                s_temp.insert(locate+s_special_name.length()+1,s_comment);
                //s_temp.remove(QRegularExpression("\\n(.*?)"+ s_special_name + ","));

                QDelete.insert(s_special_name);
                QMessageBox::information(this,"CHANGE","RENAME "+temp.key+" TO "+temp.value);
            }            
        }
        f_temp.close();
        f_temp.open(QIODevice::Truncate);
        f_temp.close();
        f_temp.open(QIODevice::WriteOnly);
        f_stream<<s_temp;
        f_temp.close();                

    }
}

void MainWindow::on_CBB_GPIO_currentIndexChanged(int index)
{
    switch(index){
    case 0: //clk
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"CLK_50");
        break;
    case 1: //led
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"LED_ALL");
        ui->CBB_O_name->insertItem(1,"LED[0]");
        ui->CBB_O_name->insertItem(2,"LED[1]");
        ui->CBB_O_name->insertItem(3,"LED[2]");
        ui->CBB_O_name->insertItem(4,"LED[3]");
        break;
    case 2: //key
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"KEY_ALL");
        ui->CBB_O_name->insertItem(1,"KEY[0]");
        ui->CBB_O_name->insertItem(2,"KEY[1]");
        ui->CBB_O_name->insertItem(3,"KEY[2]");
        ui->CBB_O_name->insertItem(4,"KEY[3]");
        break;
    case 3: //sw
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"SW_ALL");
        ui->CBB_O_name->insertItem(1,"SW[0]");
        ui->CBB_O_name->insertItem(2,"SW[1]");
        ui->CBB_O_name->insertItem(3,"SW[2]");
        ui->CBB_O_name->insertItem(4,"SW[3]");
        break;
    case 4: //vga
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"VGA_B_ALL");
        ui->CBB_O_name->insertItem(1,"VGA_G_ALL");
        ui->CBB_O_name->insertItem(2,"VGA_R_ALL");
        ui->CBB_O_name->insertItem(3,"VGA_B[0]");
        ui->CBB_O_name->insertItem(4,"VGA_B[1]");
        ui->CBB_O_name->insertItem(5,"VGA_B[2]");
        ui->CBB_O_name->insertItem(6,"VGA_B[3]");
        ui->CBB_O_name->insertItem(7,"VGA_G[0]");
        ui->CBB_O_name->insertItem(8,"VGA_G[1]");
        ui->CBB_O_name->insertItem(9,"VGA_G[2]");
        ui->CBB_O_name->insertItem(10,"VGA_G[3]");
        ui->CBB_O_name->insertItem(11,"VGA_R[0]");
        ui->CBB_O_name->insertItem(12,"VGA_R[1]");
        ui->CBB_O_name->insertItem(13,"VGA_R[2]");
        ui->CBB_O_name->insertItem(14,"VGA_R[3]");
        ui->CBB_O_name->insertItem(15,"VGA_HS");
        ui->CBB_O_name->insertItem(16,"VGA_VS");
        break;
    case 5: //seg
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"SEL_ALL");
        ui->CBB_O_name->insertItem(1,"DIG_ALL");
        ui->CBB_O_name->insertItem(2,"SEL[0]");
        ui->CBB_O_name->insertItem(3,"SEL[1]");
        ui->CBB_O_name->insertItem(4,"SEL[2]");
        ui->CBB_O_name->insertItem(5,"SEL[3]");
        ui->CBB_O_name->insertItem(6,"SEL[4]");
        ui->CBB_O_name->insertItem(7,"SEL[5]");
        ui->CBB_O_name->insertItem(8,"SEL[6]");
        ui->CBB_O_name->insertItem(9,"SEL[7]");
        ui->CBB_O_name->insertItem(10,"DIG[0]");
        ui->CBB_O_name->insertItem(11,"DIG[1]");
        ui->CBB_O_name->insertItem(12,"DIG[2]");
        ui->CBB_O_name->insertItem(13,"DIG[3]");
        ui->CBB_O_name->insertItem(14,"DIG[4]");
        ui->CBB_O_name->insertItem(15,"DIG[5]");
        ui->CBB_O_name->insertItem(16,"DIG[6]");
        ui->CBB_O_name->insertItem(17,"DIG[7]");
        break;
    case 6: //PS/2
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"PS2_DAT");
        ui->CBB_O_name->insertItem(1,"PS2_CLK");
        ui->CBB_O_name->insertItem(2,"PS2_DAT2");
        ui->CBB_O_name->insertItem(3,"PS2_CLK2");
        break;
    case 7: //UART
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"UART_TXD");
        ui->CBB_O_name->insertItem(1,"UART_RXD");
        break;
    case 8: //SD_CARD
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"SD_CLK");
        ui->CBB_O_name->insertItem(1,"SD_CMD");
        ui->CBB_O_name->insertItem(2,"SD_DAT_ALL");
        ui->CBB_O_name->insertItem(3,"SD_DAT[0]");
        ui->CBB_O_name->insertItem(4,"SD_DAT[1]");
        ui->CBB_O_name->insertItem(5,"SD_DAT[2]");
        ui->CBB_O_name->insertItem(6,"SD_DAT[3]");
        break;
    case 9: //SPI_FLASH
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"SPIFLASH_CS");
        ui->CBB_O_name->insertItem(1,"SPIFLASH_SCLK");
        ui->CBB_O_name->insertItem(2,"SPIFLASH_HOLD");
        ui->CBB_O_name->insertItem(3,"SPIFLASH_SDI");
        ui->CBB_O_name->insertItem(4,"SPIFLASH_SDO");
        ui->CBB_O_name->insertItem(5,"SPIFLASH_WP");
        break;
    case 10: //UART
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"BEEP");
        break;
    case 11: //SDRAM
        ui->CBB_O_name->clear();
        ui->CBB_O_name->insertItem(0,"DRAM_ADDR_ALL");
        ui->CBB_O_name->insertItem(1,"DRAM_DQ_ALL");
        ui->CBB_O_name->insertItem(2,"DRAM_BA_ALL");
        ui->CBB_O_name->insertItem(3,"DRAM_CAS_N");
        ui->CBB_O_name->insertItem(4,"DRAM_CKE");
        ui->CBB_O_name->insertItem(5,"DRAM_CLK");
        ui->CBB_O_name->insertItem(6,"DRAM_CS_N");
        ui->CBB_O_name->insertItem(7,"DRAM_LDQM");
        ui->CBB_O_name->insertItem(8,"DRAM_RAS_N");
        ui->CBB_O_name->insertItem(9,"DRAM_UDQM");
        ui->CBB_O_name->insertItem(10,"DRAM_WE_N");
        break;
    default:
        ui->CBB_O_name->clear();
        break;
    }
    ui->CBB_O_name->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

void MainWindow::FinalChange(){
    QString s_comment,s_temp,s_special_name,path_v;
    QFile f_temp;
    QTextStream f_stream(&f_temp);

    if(!CAN_BE_CHANGE_NAME)
        return;

    path_v = path +"/"+ ui->lineEdit_Pro_name->text() +".v";
    openFile(f_temp,path_v);
    s_temp =  f_stream.readAll();

    auto p = QDelete.begin();
    for(int i = 0;i<QDelete.size();i++){
        s_special_name = *(p+i);
        s_comment = QString("\n//!!PIN Group %1 has been break ,Please see the .qsf file for details.\n").arg(s_special_name);

        int locate = s_temp.lastIndexOf(s_special_name+",");
        if(locate==-1)
            locate = s_temp.lastIndexOf(s_special_name+" ");

        s_temp.insert(locate+s_special_name.length()+1,s_comment);
        s_temp.remove(QRegularExpression("\\n(.*?)"+ s_special_name + ","));
    }

    f_temp.close();
    f_temp.open(QIODevice::Truncate);
    f_temp.close();
    f_temp.open(QIODevice::WriteOnly);
    f_stream<<s_temp;
    f_temp.close();

}

void MainWindow::about_show(){
    QMessageBox message(QMessageBox::NoIcon, "About", "\nAuthor:\nPD Zhang");
    message.setIconPixmap(QPixmap(":/img/pic_about").scaled(600,350));
    message.exec();
}

void MainWindow::pin_map_show(){
    QDesktopServices::openUrl(QUrl("./HX1006A.html"));
}

void MainWindow::help_show(){
    QDesktopServices::openUrl(QUrl("./help.html"));
}
