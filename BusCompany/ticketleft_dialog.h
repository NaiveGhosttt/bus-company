#ifndef TICKETLEFT_DIALOG_H
#define TICKETLEFT_DIALOG_H

#include <QDialog>

namespace Ui {
class TicketLeft_Dialog;
}

class TicketLeft_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit TicketLeft_Dialog(QWidget *parent = nullptr);
    ~TicketLeft_Dialog();

    QString Date_Choose;//选择的是哪一天
    int Bus_ID();


private slots:
    void on_radio_Today_clicked();

    void on_radio_Tomo_clicked();

    void on_radio_Dayafter_clicked();

private:
    Ui::TicketLeft_Dialog *ui;
};

#endif // TICKETLEFT_DIALOG_H
