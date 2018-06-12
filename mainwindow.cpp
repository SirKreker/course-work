#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QMessageBox>
using namespace std;

int NUMG=1;
int QuesNUM=4; //количество вопросов
QString strNUMG=QString::number(NUMG);
QString strQuesNUM=QString::number(QuesNUM);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BackButton->setEnabled(false);
    ui->label->setText(strNUMG + " из " + strQuesNUM);
    ui->EndButton->setEnabled(false);
    connect(ui->actionLoadFile,SIGNAL(triggered(bool)),this,SLOT(on_LoadFile_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadFile_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this,tr("Save Xml"), ".",tr("Xml files (*.xml)"));
    /*if(FileName != ""){
        ui->TestNameEdit->setText(FileName);
    }*/
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
                /* Проверяем, является ли элемент началом тега
                 * */
                if(xmlReader.isStartElement())
                {
                    if(xmlReader.name() == "Name")
                    {
                        ui->TestNameEdit->setText(xmlReader.readElementText());
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
