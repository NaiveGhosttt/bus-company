#include "ticketleft_dialog.h"
#include "ui_ticketleft_dialog.h"

TicketLeft_Dialog::TicketLeft_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketLeft_Dialog)
{
    ui->setupUi(this);
}

TicketLeft_Dialog::~TicketLeft_Dialog()
{
    delete ui;
}

void TicketLeft_Dialog::on_radio_Today_clicked()
{
    Date_Choose="今天";
}

void TicketLeft_Dialog::on_radio_Tomo_clicked()
{
    Date_Choose="明天";
}

void TicketLeft_Dialog::on_radio_Dayafter_clicked()
{
    Date_Choose="后天";
}

int TicketLeft_Dialog::Bus_ID(){
    QString sBus_ID = ui->textEdit_BusID->toPlainText();
    int number = sBus_ID.toInt();
    return number;

}
