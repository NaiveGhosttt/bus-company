/*添加车辆*/
#ifndef ADD_A_BUS_DIALOG_H
#define ADD_A_BUS_DIALOG_H
#include <QDialog>

namespace Ui {
class Add_A_Bus_Dialog;
}

class Add_A_Bus_Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Add_A_Bus_Dialog(QWidget *parent = nullptr);
    ~Add_A_Bus_Dialog();

    int BusID_Add();//返回添加车辆的班次号
    QString DepTime_Add();//返回添加车辆的发车时间
    QString Destin_Add();//返回添加车辆的终点
    int Seat_Amount_Add();//返回添加车辆的座位数量

    int m_iSelectIndex; //0--今天；1--明天；2--后天

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
private:
    Ui::Add_A_Bus_Dialog *ui;
};

#endif // ADD_A_BUS_DIALOG_H
