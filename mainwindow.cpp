#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "question.h"
#include <QDebug>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <vector>
using namespace std;

int NUMG=1;
int QuesNUM;
QString strNUMG=QString::number(NUMG);
QString strQuesNUM;
Question q;
int NumAnswer;
int c;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BackButton->setEnabled(false);
    ui->NextButton->setEnabled(false);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
    ui->EndButton->setEnabled(false);
    connect(ui->actionLoadFile,SIGNAL(triggered(bool)),this,SLOT(on_LoadFile_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

vector <QLineEdit*> Line;
vector <QCheckBox*> Check;
QString* temp;
int* tempc;
vector <Question> Questions;

void MainWindow::on_LoadFile_clicked()
{
    Questions.clear();
    QString FileName = QFileDialog::getOpenFileName(this,tr("Save Xml"), ".",tr("Xml files (*.xml)"));
    QFile file(FileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Ошибка файла","Не удалось открыть файл",QMessageBox::Ok);
        } else {
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(&file);
            xmlReader.readNext();
            while(!xmlReader.atEnd())
            {
                if(xmlReader.isStartElement())
                {
                    if(xmlReader.name() == "Name")
                    {
                        ui->TestNameEdit->setText(xmlReader.readElementText());
                    }
                    else if(xmlReader.name() == "NUMG")
                    {
                        QuesNUM=xmlReader.readElementText().toInt(); //количество вопросов
                        strQuesNUM=QString::number(QuesNUM);
                        ui->label->setText(strNUMG + " из " + strQuesNUM);
                        if(QuesNUM>1){
                            ui->NextButton->setEnabled(true);
                        } else {
                            ui->EndButton->setEnabled(true);
                        }
                    }
                    else if(xmlReader.name() == "NameQuestion"){
                        q.name_question=xmlReader.readElementText();
                        q.Answer.clear();
                        delete []q.correct;
                        delete []q.userAnswer;
                        NumAnswer=0;
                    }
                    else if(xmlReader.name() == "NUMV")
                    {
                        c = xmlReader.readElementText().toInt();
                        q.correct = new int[c];
                        q.userAnswer = new int[c];
                    }
                    else if(xmlReader.name() == "Correct")
                    {
                        q.correct[NumAnswer]=xmlReader.readElementText().toInt();
                        q.userAnswer[NumAnswer]=0;
                        NumAnswer++;
                    }
                    else if(xmlReader.name() == "TextAnswer")
                    {
                        q.Answer.push_back(xmlReader.readElementText());
                        if(NumAnswer==c){
                            Questions.push_back(q);
                        }
                    }
                }
                xmlReader.readNext();
            }
            file.close();
        }
}

void MainWindow::on_BackButton_clicked()
{
    if (NUMG-1==1){
        ui->BackButton->setEnabled(false);
    }
    ui->NextButton->setEnabled(true);
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
    ui->BackButton->setEnabled(true);
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
    ui->BackButton->setEnabled(false);
    ui->NextButton->setEnabled(false);
    ui->EndButton->setEnabled(false);
}
