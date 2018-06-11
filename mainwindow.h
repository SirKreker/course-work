#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_NextButton_clicked();
    void on_BackButton_clicked();
    void on_EndButton_clicked();
    void on_LoadFile_clicked();
    void on_Test_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
