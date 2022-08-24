
/*退票*/
#ifndef REFUND_DIALOG_H
#define REFUND_DIALOG_H

#include <QDialog>

namespace Ui {
class Refund_Dialog;
}

class Refund_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Refund_Dialog(QWidget *parent = nullptr);
    ~Refund_Dialog();

    QString Passenger_Name();
    QString Date_Choose;//选择的是哪一天
    int Bus_Choose();//选哪一辆车
    int Seat_Choose();//选哪一个座位

private slots:
    void on_radio_Today_clicked();

    void on_radio_Tomo_clicked();

    void on_radio_Dayafter_clicked();

private:
    Ui::Refund_Dialog *ui;
};

#endif // REFUND_DIALOG_H
