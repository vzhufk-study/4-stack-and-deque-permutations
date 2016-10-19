#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ogrie.h>

#include <QFileDialog>

OgrieParty rezult;

void MainWindow::reCountRezult(){
    OgrieParty rez;
    unsigned short N = ui->spinBox->value();
    if (ui->CB_struct->currentIndex() == 0){
        rez.createByRangedValues(*(new std::stack<int>), *(new Ogrie), 0, N);
    }else{
        rez.createByRangedValues(*(new std::deque<int>), *(new Ogrie), 0, N);
    }
    rezult = rez;
}

void MainWindow::reFillComboBoxOfRezults(){
    QStringList list;
    ui->CB_rezults->clear();
    for ( unsigned int i = 0; i < rezult.size(); ++i){
        list<<QString::fromStdString(rezult[i].toString());
    }
    ui->CB_rezults->addItems(list);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_CB_struct_currentIndexChanged(int index)
{
    reCountRezult();
    reFillComboBoxOfRezults();

    if (ui->CB_struct->currentIndex() == 0){
        ui->spinBox->setMaximum(8);
    }else{
        ui->spinBox->setMaximum(5);
    }

    initalizeForVisualization();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    reCountRezult();
    reFillComboBoxOfRezults();
    initalizeForVisualization();
}

void MainWindow::on_spinBox_editingFinished()
{
    reCountRezult();
    reFillComboBoxOfRezults();
    initalizeForVisualization();
}

unsigned int currentNumber = 0;
unsigned int currentActionIndex = 0;
unsigned int currentSize = 0;
Ogrie currentRezult;

void MainWindow::initalizeForVisualization(){
    currentNumber = 0;
    currentActionIndex = 0;
    currentSize = 0;
    currentRezult = rezult[ui->CB_rezults->currentIndex()];
    ui->TB_actions->clear();
    ui->LW_struct_visual->clear();

}

void MainWindow::on_B_run_visual_clicked()
{

    currentRezult = rezult[ui->CB_rezults->currentIndex()];

    QString tmp;
    switch (currentRezult.getAction(currentActionIndex++)){
    case 0:
        if (currentSize != 0){
            tmp = ui->TB_actions->toPlainText();
            tmp.append("pop_front();\n");
            ui->TB_actions->setText(tmp);

            currentSize--;
            ui->LW_struct_visual->takeItem(0);
        }
        break;
    case 1:
        currentSize++;
        tmp = ui->TB_actions->toPlainText();
        tmp.append("push_front(");
        tmp.append(QString::number(currentNumber));
        tmp.append(");\n");
        ui->TB_actions->setText(tmp);

        ui->LW_struct_visual->insertItem(0, QString::number(currentNumber++));
        break;
    case 2:
        tmp = ui->TB_actions->toPlainText();
        tmp.append("pop_back();\n");
        ui->TB_actions->setText(tmp);


        ui->LW_struct_visual->takeItem(--currentSize);
        break;
    case 3:
        currentSize++;
        tmp = ui->TB_actions->toPlainText();
        tmp.append("push_back(");
        tmp.append(QString::number(currentNumber));
        tmp.append(");\n");
        ui->TB_actions->setText(tmp);

        ui->LW_struct_visual->addItem(QString::number(currentNumber++));
        break;
    }
}

void MainWindow::on_actionSave_one_rezult_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    fileName.append(".txt");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(currentRezult.toString(1).c_str());
    file.close();
}

void MainWindow::on_actionSave_all_rezults_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    fileName.append(".txt");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    for (unsigned int i = 0; i < rezult.size(); ++i){
        file.write("[");
        char number[8];
        itoa(i, number, 10);
        file.write(number);
        file.write("]");
        file.write(rezult[i].toString(1).c_str());
        file.write("\n\n");
    }
    file.close();
}
