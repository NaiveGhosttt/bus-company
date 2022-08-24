#ifndef PASSENGERLIST_DIALOG_H
#define PASSENGERLIST_DIALOG_H

#include <QDialog>

namespace Ui {
class PassengerList_Dialog;
}

class PassengerList_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassengerList_Dialog(QWidget *parent = nullptr);
    ~PassengerList_Dialog();

    QString Date_Choose;//选择的是哪一天
    int Bus_Choose();//选哪一辆车

private slots:
    void on_radio_Today_clicked();

    void on_radio_Tomo_clicked();

    void on_radio_Dayafter_clicked();

private:
    Ui::PassengerList_Dialog *ui;
};

#endif // PASSENGERLIST_DIALOG_H
