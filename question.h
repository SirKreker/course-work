#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <QString>
using namespace std;

struct Question
{
    QString name_question;
    vector <QString> Answer;
    int* correct;

};

#endif // QUESTION_H
