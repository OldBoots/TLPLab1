#include "mainwindow.h"
#include "ui_mainwindow.h"
/*!*/
/*!Конструктор класса MainWindow. Здесь происходит отрисовка интерфейса.*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Отрисовка UI
    ui->setupUi(this);
    setWindowTitle("КС-грамматика");
    // Создание первого поля ввода правила
    vec_rules << new QLineEdit;
    ui->vLayout->addWidget(vec_rules[vec_rules.size() - 1]);
    ui->vLayout->setAlignment(Qt::AlignTop);
    // Коннект сигналов с их слотами
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(start_slot()));
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(statr_check_volid_slot()));
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(start_slot()));
    connect(vec_rules[vec_rules.size() - 1], SIGNAL(editingFinished()), SLOT(bgyryjh_slot()));
    connect(vec_rules[vec_rules.size() - 1], SIGNAL(editingFinished()), SLOT(del_empty_rules_slot()));
}
/*!Диструктор класса MainWindow*/
MainWindow::~MainWindow()
{
    delete ui;
}
/*!Слот, в котором происходит считывание данных*/
void MainWindow::start_slot(){

    qDebug() << vec_list_rules;
}
/*!Слот создания и отрисовки нового поля ввода правила*/
void MainWindow::bgyryjh_slot(){
    // Добавляем поле ввода правила
    if(!vec_rules[vec_rules.size() - 1]->text().isEmpty() && vec_rules.size() < 10){
        vec_rules << new QLineEdit;
        ui->vLayout->addWidget(vec_rules[vec_rules.size() - 1]);
    }
    // Коннектим сигналы созданых виджитов со слотами
    connect(vec_rules[vec_rules.size() - 1], SIGNAL(editingFinished()), SLOT(bgyryjh_slot()));
    connect(vec_rules[vec_rules.size() - 1], SIGNAL(editingFinished()), SLOT(del_empty_rules_slot()));
}
/*!Слот удаления поля ввода правила*/
void MainWindow::del_empty_rules_slot(){
    // Удаляем поле ввода правила
    for(int i = 0; i < vec_rules.size() - 1; i++){
        if(vec_rules[i]->text().isEmpty()){
            ui->vLayout->removeWidget(vec_rules[i]);
            delete(vec_rules[i]);
            vec_rules.remove(i);
        }
    }
}
/*!Слот запуска проверки введенных данных*/
void MainWindow::statr_check_volid_slot(){
    if(check_volid_data()){
        qDebug("Fatal error");
    }
}
/*!Метод проверки введенных данных*/
bool MainWindow::check_volid_data(){
    if(vec_rules.size() == 0){
        qDebug() << "Syntax error # no rules.";
        return true;
    }
    if(ui->lineEdit->text().isEmpty()){
        qDebug() << "Syntax error # no abc.";
        return true;
    }
    // Считываем поле алфавита в лист abc без пробелов
    abc = ui->lineEdit->text().replace(" ", "").split(",");
    // Считываем поля правил в вектор листов vec_list_rules
    QStringList temp_list;
    QStringList list_rules;
    for(int i = 0; i < vec_rules.size() - 1; i++){
        temp_list = vec_rules[i]->text().split("=");
        list_rules << temp_list[0] << temp_list[1].split("|");
        vec_list_rules << list_rules;
        temp_list.clear();
        list_rules.clear();
        // Проверка левой части правила
        if(vec_list_rules[i][0].size() != 1){
            qDebug() << "Syntax error # in " + QString::number(i + 1) + "rule.";
            return true;
        }
    }
    return false;
}
