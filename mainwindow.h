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
    void reCountRezult();
    void reFillComboBoxOfRezults();
    void drawStructure(unsigned int, int);
    void initalizeForVisualization();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_input_N_textChanged();

    void on_CB_struct_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_editingFinished();

    void on_B_run_visual_clicked();

    void on_actionSave_one_rezult_triggered();

    void on_actionSave_all_rezults_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
