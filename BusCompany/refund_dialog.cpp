#include "refund_dialog.h"
#include "ui_refund_dialog.h"

Refund_Dialog::Refund_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Refund_Dialog)
{
    ui->setupUi(this);
}

Refund_Dialog::~Refund_Dialog()
{
    delete ui;
}

QString Refund_Dialog::Passenger_Name(){
    return ui->textEdit_name->toPlainText();
}

void Refund_Dialog::on_radio_Today_clicked()
{
    Date_Choose="今天";
}

void Refund_Dialog::on_radio_Tomo_clicked()
{
    Date_Choose="明天";
}

void Refund_Dialog::on_radio_Dayafter_clicked()
{
    Date_Choose="后天";
}

int Refund_Dialog::Seat_Choose(){
    QString sSeatNumber = ui->textEdit_SeatNumber->toPlainText();
    int number = sSeatNumber.toInt();
    return number;
}

int Refund_Dialog::Bus_Choose(){
    QString sSeatNumber = ui->textEdit_BusID->toPlainText();
    int number = sSeatNumber.toInt();
    return number;
}

