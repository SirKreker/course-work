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
int k;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BackButton->setEnabled(false);
    ui->NextButton->setEnabled(false);
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
    Line.clear();
    Check.clear();
    ui->BackButton->setEnabled(false);
    ui->NextButton->setEnabled(false);
    ui->EndButton->setEnabled(false);
    NUMG=1;
    strNUMG=QString::number(NUMG);
    Questions.clear();
    QString FileName = QFileDialog::getOpenFileName(this,tr("Открыть xml файл"), ".",tr("Xml files (*.xml)"));
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
                    q.correct.clear();
                    q.userAnswer.clear();
                    NumAnswer=0;
                }
                else if(xmlReader.name() == "NUMV")
                {
                    c = xmlReader.readElementText().toInt();
                }
                else if(xmlReader.name() == "Correct")
                {
                    q.correct.push_back(xmlReader.readElementText());
                    q.userAnswer.push_back("0");
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
    ui->label->setText(strNUMG + " из " + strQuesNUM);

    ui->NameQuestEdit->setText(Questions.at(NUMG-1).name_question);
    QLayoutItem *child;
    while((child = ui->AnswerLayout->takeAt(0))!=0)
    {
        delete child->widget();
        delete child;
    }
    k=Questions.at(NUMG-1).Answer.size();
    for(int i=1;i<=k;i++)
    {
        QCheckBox *checkBox = new QCheckBox(this);
        QLineEdit *lineEdit = new QLineEdit(this);
        checkBox->setText(QString::number(i)+")");
        lineEdit->setReadOnly(true);
        ui->AnswerLayout->addWidget(checkBox);
        ui->AnswerLayout->addWidget(lineEdit);
        Line.push_back(lineEdit);
        Check.push_back(checkBox);
    }
    for(int i=0;i<k;i++)
    {
        Line.at(i)->setText(Questions.at(NUMG-1).Answer.at(i));
        if(Questions.at(NUMG-1).userAnswer.at(i)=="0")
            Check.at(i)->setChecked(false);
        else if(Questions.at(NUMG-1).userAnswer.at(i)=="1")
            Check.at(i)->setChecked(true);
    }
}

void MainWindow::on_BackButton_clicked()
{
    k=Questions.at(NUMG-1).userAnswer.size();
    for(int i=0;i<k;i++)
    {
        if(Check.at(i)->checkState())
        {
            Questions.at(NUMG-1).userAnswer.at(i)="1";
        }
        else
        {
            Questions.at(NUMG-1).userAnswer.at(i)="0";
        }
    }
    Line.clear();
    Check.clear();
    if (NUMG-1==1){
        ui->BackButton->setEnabled(false);
    }
    ui->NextButton->setEnabled(true);
    NUMG--;
    strNUMG=QString::number(NUMG);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
    ui->NameQuestEdit->setText(Questions.at(NUMG-1).name_question);
    QLayoutItem *child;
    while((child = ui->AnswerLayout->takeAt(0))!=0)
    {
        delete child->widget();
        delete child;
    }
    k=Questions.at(NUMG-1).Answer.size();
    for(int i=1;i<=k;i++)
    {
        QCheckBox *checkBox = new QCheckBox(this);
        QLineEdit *lineEdit = new QLineEdit(this);
        checkBox->setText(QString::number(i)+")");
        lineEdit->setReadOnly(true);
        ui->AnswerLayout->addWidget(checkBox);
        ui->AnswerLayout->addWidget(lineEdit);
        Line.push_back(lineEdit);
        Check.push_back(checkBox);
    }
    for(int i=0;i<k;i++)
    {
        Line.at(i)->setText(Questions.at(NUMG-1).Answer.at(i));
        if(Questions.at(NUMG-1).userAnswer.at(i)=="0")
            Check.at(i)->setChecked(false);
        else if(Questions.at(NUMG-1).userAnswer.at(i)=="1")
            Check.at(i)->setChecked(true);
    }

}

void MainWindow::on_NextButton_clicked()
{
    k=Questions.at(NUMG-1).userAnswer.size();
    for(int i=0;i<k;i++)
    {
        if(Check.at(i)->checkState())
        {
            Questions.at(NUMG-1).userAnswer.at(i)="1";
        }
        else
        {
            Questions.at(NUMG-1).userAnswer.at(i)="0";
        }
    }
    Line.clear();
    Check.clear();
    if (NUMG+1==QuesNUM){
        ui->NextButton->setEnabled(false);
        ui->EndButton->setEnabled(true);
    }
    ui->BackButton->setEnabled(true);
    NUMG++;
    strNUMG=QString::number(NUMG);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
    ui->NameQuestEdit->setText(Questions.at(NUMG-1).name_question);
    QLayoutItem *child;
    while((child = ui->AnswerLayout->takeAt(0))!=0)
    {
        delete child->widget();
        delete child;
    }
    k=Questions.at(NUMG-1).Answer.size();
    for(int i=1;i<=k;i++)
    {
        QCheckBox *checkBox = new QCheckBox(this);
        QLineEdit *lineEdit = new QLineEdit(this);
        checkBox->setText(QString::number(i)+")");
        lineEdit->setReadOnly(true);
        ui->AnswerLayout->addWidget(checkBox);
        ui->AnswerLayout->addWidget(lineEdit);
        Line.push_back(lineEdit);
        Check.push_back(checkBox);
    }
    for(int i=0;i<k;i++)
    {
        Line.at(i)->setText(Questions.at(NUMG-1).Answer.at(i));
        if(Questions.at(NUMG-1).userAnswer.at(i)=="0")
            Check.at(i)->setChecked(false);
        else if(Questions.at(NUMG-1).userAnswer.at(i)=="1")
            Check.at(i)->setChecked(true);
    }
}

void MainWindow::on_EndButton_clicked()
{
    ui->BackButton->setEnabled(false);
    ui->NextButton->setEnabled(false);
    //ui->EndButton->setEnabled(false);
    k=Questions.at(NUMG-1).userAnswer.size();
    for(int i=0;i<k;i++)
    {
        if(Check.at(i)->checkState())
        {
            Questions.at(NUMG-1).userAnswer.at(i)="1";
        }
        else
        {
            Questions.at(NUMG-1).userAnswer.at(i)="0";
        }
    }
    int Result=0;
    int answerResult;
    for (int i=0;i<QuesNUM;i++){
        k=Questions.at(i).userAnswer.size();
        answerResult=0;
        for (int j=0;j<k;j++){
            if (Questions.at(i).userAnswer.at(j)!=Questions.at(i).correct.at(j)){
                answerResult++;
            }
        }
        if (answerResult==0){
            Result++;
        }
    }
    QString strResult=QString::number(Result);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Результат");
    msgBox.setText("Вы ответили правильно на " + strResult + " из " + strQuesNUM+" вопросов");
    msgBox.exec();
}
