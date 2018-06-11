#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
using namespace std;

int NUMG=1;
int QuesNUM=4;
QString strNUMG=QString::number(NUMG);
QString strQuesNUM=QString::number(QuesNUM);

//QString str5 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.xml");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BackButton->setEnabled(false);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
    ui->EndButton->setEnabled(false);
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

    //QString str = ui->NumVarSpinBox->text();
    //int k = str.toInt();
    int k=4; //количество вариантов ответа
    QLayoutItem *child;
    while((child = ui->AnswerLayout->takeAt(0))!=0)
    {
        delete child->widget();
        delete child;
    }
    for(int i=1;i<=k;i++)
    {
        QCheckBox *checkBox = new QCheckBox(this);
        QLineEdit *lineEdit = new QLineEdit(this);
        checkBox->setText(QString::number(i)+")");
        lineEdit->setReadOnly(true);
        ui->AnswerLayout->addWidget(checkBox);
        ui->AnswerLayout->addWidget(lineEdit);
        //Line.push_back(lineEdit);
        //Check.push_back(checkBox);
    }

}

void MainWindow::on_NextButton_clicked()
{
    if (NUMG+1==QuesNUM){
        ui->NextButton->setEnabled(false);
        ui->EndButton->setEnabled(true);
    }
    else {
        ui->BackButton->setEnabled(true);
    }

    NUMG++;
    strNUMG=QString::number(NUMG);
    ui->label->setText(strNUMG + " из " + strQuesNUM);

    //QString str = ui->NumVarSpinBox->text();
    //int k = str.toInt();
    int k=8; //количество вариантов ответа
    QLayoutItem *child;
    while((child = ui->AnswerLayout->takeAt(0))!=0)
    {
        delete child->widget();
        delete child;
    }
    for(int i=1;i<=k;i++)
    {
        QCheckBox *checkBox = new QCheckBox(this);
        QLineEdit *lineEdit = new QLineEdit(this);
        checkBox->setText(QString::number(i)+")");
        lineEdit->setReadOnly(true);
        ui->AnswerLayout->addWidget(checkBox);
        ui->AnswerLayout->addWidget(lineEdit);
        //Line.push_back(lineEdit);
        //Check.push_back(checkBox);
    }

}

void MainWindow::on_EndButton_clicked()
{

}
