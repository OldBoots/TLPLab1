#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool check_volid_data();
private slots:
    void del_empty_rules_slot();
    void start_slot();
    void bgyryjh_slot();
    void statr_check_volid_slot();
private:
    QStringList abc;
    QVector <QStringList> vec_list_rules;
    QVector <QLineEdit *> vec_rules;


};
#endif // MAINWINDOW_H
