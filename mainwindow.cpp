#include "mainwindow.h"
#include "ui_mainwindow.h"
int num_first,gradus,minute,second;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     connect(ui->plus,SIGNAL(clicked()),this,SLOT(math_operations()));
     connect(ui->minus,SIGNAL(clicked()),this,SLOT(math_operations()));
     connect(ui->delenie,SIGNAL(clicked()),this,SLOT(math_operations()));
     connect(ui->mult,SIGNAL(clicked()),this,SLOT(math_operations()));
     ui->delenie->setCheckable(true);
     ui->plus->setCheckable(true);
     ui->minus->setCheckable(true);
     ui->mult->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::math_operations()
{
QPushButton *button = (QPushButton *)sender();
num_first=(ui->lineEdit_gradus->text().toInt())*3600+(ui->lineEdit_minute->text().toInt())*60+ui->lineEdit_second->text().toInt();
ui->lineEdit_second->setText("");
ui->lineEdit_minute->setText("");
ui->lineEdit_gradus->setText("");
button->setChecked(true);
}


void MainWindow::on_clear_clicked()
{
ui->plus->setChecked(false);
ui->minus->setChecked(false);
ui->mult->setChecked(false);
ui->delenie->setChecked(false);
ui->label_second->setText("");
ui->label_minute->setText("");
ui->label_gradus->setText("");
ui->lineEdit_second->setText("");
ui->lineEdit_minute->setText("");
ui->lineEdit_gradus->setText("");
ui->lineEdit_number->setText("");
}


void MainWindow::on_result_clicked()
{
    int num_second,int_number;
    QString label_gradus, label_minute, label_second;
    num_second=(ui->lineEdit_gradus->text().toInt())*3600+(ui->lineEdit_minute->text().toInt())*60+ui->lineEdit_second->text().toInt();
    int_number=ui->lineEdit_number->text().toInt();
if(ui->plus->isChecked()){
    gradus=(num_first+num_second)/3600;
    minute=(num_first+num_second)/60-((num_first+num_second)/3600)*60;
    second=(num_first+num_second)%60;
    label_gradus= QString::number(gradus,'g',15);
    ui->label_gradus->setText(label_gradus);
    label_minute= QString::number(minute,'g',15);
    ui->label_minute->setText(label_minute);
    label_second= QString::number(second,'g',15);
    ui->label_second->setText(label_second);
    ui->plus->setChecked(false);
}
else if(ui->minus->isChecked()){
    second=num_first%60-num_second%60;
    minute=(num_first/60-num_second/60)-(num_first/3600*60-num_second/3600*60);
    if (second<0)
    {
    while (second<0)
    {
        second=second+60;
        minute--;
    }
    }
    gradus=(num_first/3600-num_second/3600);
    if (minute<0)
    {
    while (minute<0)
    {
        minute=minute+60;
        gradus--;
    }
    }
    label_gradus= QString::number(gradus,'g',15);
    ui->label_gradus->setText(label_gradus);
    label_minute= QString::number(minute,'g',15);
    ui->label_minute->setText(label_minute);
    label_second= QString::number(second,'g',15);
    ui->label_second->setText(label_second);
    ui->minus->setChecked(false);
}
else if(ui->mult->isChecked()){
    gradus=(num_first*int_number)/3600;
    minute=(num_first*int_number)/60-((num_first*int_number)/3600)*60;
    second=(num_first*int_number)%60;
    label_gradus= QString::number(gradus,'g',15);
    ui->label_gradus->setText(label_gradus);
    label_minute= QString::number(minute,'g',15);
    ui->label_minute->setText(label_minute);
    label_second= QString::number(second,'g',15);
    ui->label_second->setText(label_second);
    ui->mult->setChecked(false);
}
else if(ui->delenie->isChecked()){
    if(int_number==0){
        ui->lineEdit_gradus->setText("ERROR");
        ui->lineEdit_minute->setText("ERROR");
        ui->lineEdit_second->setText("ERROR");
    }
    else
    {
    gradus=(num_first/int_number)/3600;
    minute=(num_first/int_number)/60-((num_first/int_number)/3600)*60;
    second=(num_first/int_number)%60;
    label_gradus= QString::number(gradus,'g',15);
    ui->label_gradus->setText(label_gradus);
    label_minute= QString::number(minute,'g',15);
    ui->label_minute->setText(label_minute);
    label_second= QString::number(second,'g',15);
    ui->label_second->setText(label_second);
    ui->delenie->setChecked(false);
}
}
}

