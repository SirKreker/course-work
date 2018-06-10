#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
using namespace std;

int NUMG=1;
int QuesNUM=4;
QString strNUMG=QString::number(NUMG);
QString strQuesNUM=QString::number(QuesNUM);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BackButton->setEnabled(false);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BackButton_clicked()
{
    if (NUMG-1==1){
        ui->BackButton->setEnabled(false);
    }
    else {
        ui->NextButton->setEnabled(true);
    }
    NUMG--;
    strNUMG=QString::number(NUMG);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
}

void MainWindow::on_NextButton_clicked()
{
    if (NUMG+1==QuesNUM){
        ui->NextButton->setEnabled(false);
    }
    else {
        ui->BackButton->setEnabled(true);
    }
    NUMG++;
    strNUMG=QString::number(NUMG);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
}

void MainWindow::on_EndButton_clicked()
{

}
