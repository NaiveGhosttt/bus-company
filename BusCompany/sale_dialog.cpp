#include "sale_dialog.h"
#include "ui_sale_dialog.h"

Sale_Dialog::Sale_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sale_Dialog)
{
    ui->setupUi(this);
}

Sale_Dialog::~Sale_Dialog()
{
    delete ui;
}

QString Sale_Dialog::Passenger_Name(){
    return ui->textEdit_Name->toPlainText();
}

QString Sale_Dialog::Passenger_ID(){
    return ui->textEdit_ID->toPlainText();
}

int Sale_Dialog::Bus_ID(){
    QString sBus_ID = ui->textEdit_BusID->toPlainText();
    int number = sBus_ID.toInt();
    return number;
}

int Sale_Dialog::SeatNumber(){
    QString sSeatNumber = ui->textEdit_SeatNumber->toPlainText();
    int number = sSeatNumber.toInt();
    return number;
}

void Sale_Dialog::on_radio_Today_clicked()
{
    Date_Choose="今天";
}


void Sale_Dialog::on_radio_Tomo_clicked()
{
    Date_Choose="明天";
}



void Sale_Dialog::on_radio_Dayafter_clicked()
{
    Date_Choose="后天";
}
