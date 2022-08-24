#include "add_a_bus_dialog.h"
#include "ui_add_a_bus_dialog.h"

Add_A_Bus_Dialog::Add_A_Bus_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_A_Bus_Dialog)
{
    ui->setupUi(this);
}

Add_A_Bus_Dialog::~Add_A_Bus_Dialog()
{
    delete ui;
}

//返回要添加车辆的班次号
int Add_A_Bus_Dialog::BusID_Add()
{
    QString sNumber = ui->textEdit_BusID->toPlainText();
    int number = sNumber.toInt();
    return number;
}

//返回要添加车辆的发车时间
QString Add_A_Bus_Dialog::DepTime_Add()
{
    return ui->textEdit_DepTime->toPlainText();
}

//返回要添加车辆的终点
QString Add_A_Bus_Dialog::Destin_Add()
{
    return ui->textEdit_Destin->toPlainText();
}

//返回要添加车辆的座位数量
int Add_A_Bus_Dialog::Seat_Amount_Add()
{
    QString sNumber = ui->textEdit_Seat_Amount->toPlainText();
    int number = sNumber.toInt();
    return number;
}

//返回要添加车辆的发车日期
void Add_A_Bus_Dialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="今天")
    {
        m_iSelectIndex = 0;
    }

    if(arg1=="明天")
    {
        m_iSelectIndex = 1;
    }

    if(arg1=="后天")
    {
        m_iSelectIndex = 2;
    }
}
