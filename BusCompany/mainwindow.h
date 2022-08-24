#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "infotable.h"
#include "QStandardItemModel"
#include "sale.h"
#include "ticketleft_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector <Sale> Sale_Refund;//容器存：姓名、身份证、发车日期、班次、座位号
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    void ShowInfoTable();//显示班次信息
private slots:
    void on_ShowInfotableView_changed();//

    void on_action_openfile_triggered();//打开文件

    void on_action_savefile_triggered();//保存文件

    void on_action_add_Info_triggered();//添加车辆

    void on_action_sale_triggered();//售票

    void on_action_refund_triggered();//退票

    void on_action_Today_search_triggered();//查询-班次信息-今天

    void on_action_tomorrow_search_triggered();//查询-班次信息-明天

    void on_action_DAT_search_triggered();//查询-班次信息-后天

    void on_action_search_PassengerList_triggered();//查询-乘客列表

    void on_actionSearchTicketLeft_triggered();//查询-余票查询

private:
    InfoTable my_InfoTable;//数据汇总类
    QStandardItemModel * InforModel; //显示表格信息的数据模型
    int m_iCurTable; //0--初始状态；1--显示班次信息；2--显示一辆车信息；
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
