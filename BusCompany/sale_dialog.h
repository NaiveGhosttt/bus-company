#ifndef SALE_DIALOG_H
#define SALE_DIALOG_H

#include <QDialog>
#include <qbuttongroup.h>

namespace Ui {
class Sale_Dialog;
}

class Sale_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Sale_Dialog(QWidget *parent = nullptr);
    ~Sale_Dialog();

    QString Passenger_Name();
    QString Passenger_ID();
    int Bus_ID();
    int SeatNumber();

    QString Date_Choose;//选择的是哪一天

private slots:

    void on_radio_Today_clicked();

    void on_radio_Tomo_clicked();

    void on_radio_Dayafter_clicked();

private:
    Ui::Sale_Dialog *ui;
    //QButtonGroup * RadioGroup;
};

#endif // SALE_DIALOG_H
