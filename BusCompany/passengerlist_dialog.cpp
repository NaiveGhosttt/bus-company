#include "passengerlist_dialog.h"
#include "ui_passengerlist_dialog.h"

PassengerList_Dialog::PassengerList_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassengerList_Dialog)
{
    ui->setupUi(this);
}

PassengerList_Dialog::~PassengerList_Dialog()
{
    delete ui;
}

void PassengerList_Dialog::on_radio_Today_clicked()
{
    Date_Choose="今天";
}


void PassengerList_Dialog::on_radio_Tomo_clicked()
{
    Date_Choose="明天";
}


void PassengerList_Dialog::on_radio_Dayafter_clicked()
{
    Date_Choose="后天";
}

int PassengerList_Dialog::Bus_Choose()
{
    QString sNumber = ui->textEdit_Bus_Choose->toPlainText();
    int number = sNumber.toInt();
    return number;
}
