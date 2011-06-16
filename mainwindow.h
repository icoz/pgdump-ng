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

    void on_edtPass_returnPressed();

    void on_btnNext_Table_clicked();

    void on_cbxFormat_currentIndexChanged(int index);

    void on_btnRunDump_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
