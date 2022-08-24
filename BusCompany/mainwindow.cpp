#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "a_bus.h"
#include "infotable.h"
#include "readonlydelegate.h"
#include "add_a_bus_dialog.h"
#include "sale_dialog.h"
#include "refund_dialog.h"
#include "passengerlist_dialog.h"
#include "sale.h"
#include "ticketleft_dialog.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

QString temp1="查询指定班次座位情况";

//构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InforModel=new QStandardItemModel;
    ui->ShowInfotableView->setModel(InforModel);
    connect(ui->ShowInfotableView->itemDelegate(),&QAbstractItemDelegate::closeEditor,this,&MainWindow::on_ShowInfotableView_changed);
    m_iCurTable=0;
}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
    delete InforModel;
}

//随窗口改变大小
void MainWindow::resizeEvent(QResizeEvent *event)
{
    //父类的保持
    QMainWindow::resizeEvent(event);

    int x = this->frameGeometry().width();
    int y = this->frameGeometry().height();

    //窗口改变大小的时候列表控件跟着改变
    ui->ShowInfotableView->setGeometry(5,5,x*0.99,y*0.87);
}

//显示班次信息
void MainWindow::ShowInfoTable()
{
    m_iCurTable = 1; //表示当前显示的是班次信息
    InforModel->clear();//刷新一遍
    InforModel->setColumnCount(5); //5列

    //表头
    QStringList templist;
    templist.append("班次");
    templist.append("发车日期");
    templist.append("发车时间");
    templist.append("终点城市");
    templist.append("座位数量");
    InforModel->setHorizontalHeaderLabels(templist);

    int RowCnt = my_InfoTable.Get_Bus_Amount(); //行数（不含标题）,多少辆车就有多少行
    InforModel->setRowCount(RowCnt);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr_BusID;
    QString tempStr_SeatAmount;
    for(int i=0; i<RowCnt; ++i)
    {
        A_Bus tempbus=my_InfoTable.Get_A_Bus(i);//从容器中获取一辆车的信息返回给tempbus

        tempStr_BusID = QString::number(tempbus.BusID);//将BusID(int)转换为QString
        tempStr_SeatAmount = QString::number(tempbus.SeatAmount);//将SeatAmount(int)转换为QString

        aTempItem = new QStandardItem(tempStr_BusID);
        InforModel->setItem(i, 0, aTempItem);

        aTempItem = new QStandardItem(tempbus.Date);
        InforModel->setItem(i, 1, aTempItem);

        aTempItem = new QStandardItem(tempbus.DepTime);
        InforModel->setItem(i, 2, aTempItem);

        aTempItem = new QStandardItem(tempbus.Destination);
        InforModel->setItem(i, 3, aTempItem);

        aTempItem = new QStandardItem(tempStr_SeatAmount);
        InforModel->setItem(i, 4, aTempItem);
    }
   //只读（日期，终点）
   ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
   ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(1, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(2, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(3, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(4, readOnlyDelegate);
}

//on_ShowInfotableView_changed//检测到ShowInfotableView内容改变
void MainWindow::on_ShowInfotableView_changed()
{
    QModelIndex index = ui->ShowInfotableView->currentIndex();
    int iBus = index.row(); //哪一辆车
    int iCol = index.column(); //哪个列
    A_Bus & bus = my_InfoTable.Get_A_Bus(iBus); //获取当前车辆，一定要是引用
    QVariant data; //数据

    switch (m_iCurTable) //根据当前选择的表格不同进行对应的班次/车辆的修改
    {
    case 1: //当前是班次信息表

        data = InforModel->data(index);//获取数值

        switch (iCol)
        {
        case 0: //班次号
            bus.BusID = data.toInt();
            break;
        case 1: //始发日期
            bus.Date = data.toString();
            break;
        case 2: //始发时间
            bus.DepTime = data.toString();
            break;
        case 3://终点
            bus.Destination = data.toString();
            break;
        case 4://座位数量
            bus.SeatAmount = data.toInt();
            break;
        default:
            break;
        }
        break;

        ShowInfoTable(); //重新显示，更新数据
        break;
    }
}

//on_action_openfile_triggered//打开文件
void MainWindow::on_action_openfile_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    if(aFileName.isEmpty())
        return;

    //创建成功，打开文件
    my_InfoTable.Read_Bus_FromFile(aFileName);

    ShowInfoTable();//显示班次信息
}

//on_action_savefile_triggered//保存文件
void MainWindow::on_action_savefile_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);

    if(aFileName.isEmpty())
        return;
    my_InfoTable.Save_Bus_ToFile(aFileName);
}

//on_action_add_Info_triggered添加班次
void MainWindow::on_action_add_Info_triggered()
{
    Add_A_Bus_Dialog dlg;
    int ret = dlg.exec();
    if(ret==Add_A_Bus_Dialog::Accepted)
    {
        A_Bus tempBus;
        tempBus.BusID=dlg.BusID_Add();

        if(dlg.m_iSelectIndex==0){
            tempBus.Date="今天";
        }
        if(dlg.m_iSelectIndex==1){
            tempBus.Date="明天";
        }
        if(dlg.m_iSelectIndex==2){
            tempBus.Date="后天";
        }
        tempBus.DepTime=dlg.DepTime_Add();
        tempBus.Destination=dlg.Destin_Add();
        tempBus.SeatAmount=dlg.Seat_Amount_Add();

        my_InfoTable.Add_Bus(tempBus);//往内存中容器里添加了一辆车，还未存入文件

        ShowInfoTable();
    }
}

//on_action_sale_triggered办理-售票
void MainWindow::on_action_sale_triggered()
{
    Sale_Dialog dlg;
    int ret = dlg.exec();
    if(ret==QDialog::Accepted){
        InforModel->clear();//刷新一遍
        int SeatSaleAmount=0;//办理了多少人的票
        Sale tempsale;//临时容器
        int ErrorState=0;//0-可正常办理;1-未查询到车辆;2-该车无此座位;3-此座位已售
        bool state=false;
        for(int i=0;i<my_InfoTable.Get_Bus_Amount();i++){
            QString tempDate=my_InfoTable.Buses[i].Date;
            int tempBusID=my_InfoTable.Buses[i].BusID;
            //找到这辆车
            if((tempDate  == dlg.Date_Choose)&&(tempBusID==dlg.Bus_ID())){
                state=true;
                if(my_InfoTable.Buses[i].SeatAmount>dlg.SeatNumber()){
                    if(my_InfoTable.Buses[i].Seats[dlg.SeatNumber()-1].Name=="NULL"){
                        my_InfoTable.Buses[i].Seats[dlg.SeatNumber()-1].Name=dlg.Passenger_Name();
                        my_InfoTable.Buses[i].Seats[dlg.SeatNumber()-1].ID=dlg.Passenger_ID();
                        my_InfoTable.Buses[i].Seats[dlg.SeatNumber()-1].seated=true;

                        SeatSaleAmount++;
                        tempsale.NameSale=dlg.Passenger_Name();
                        tempsale.IDSale=dlg.Passenger_ID();
                        tempsale.DateSale=dlg.Date_Choose;
                        tempsale.BusIDSale=dlg.Bus_ID();
                        tempsale.SeatSale=dlg.SeatNumber();
                        tempsale.State="已售票";
                        Sale_Refund.push_back(tempsale);
                    }
                    else
                        ErrorState=3;//3-此座位已售
                }
                else{
                    ErrorState=2;//2-该车无此座位;
                }
            }
        }
        //可正常办理
        if(ErrorState==0){
            InforModel->clear();//刷新一遍
            InforModel->setColumnCount(6); //6列
            //表头
            QStringList templist;
            templist.append("姓名");
            templist.append("身份证");
            templist.append("日期");
            templist.append("班次");
            templist.append("座位号");
            templist.append("办理状态");
            InforModel->setHorizontalHeaderLabels(templist);

            int RowCnt = Sale_Refund.size(); //行数
            InforModel->setRowCount(RowCnt);

            QString tempSale_BusID;
            QString tempSale_SeatID;
            QStandardItem *aTempItem; //临时的item
            for(int i=0; i<RowCnt; ++i)
            {
                Sale tempsale2=Sale_Refund[i];//从容器中获取一次办理的信息返回给tempsale2

                tempSale_BusID = QString::number(tempsale2.BusIDSale);//将BusIDSale(int)转换为QString
                tempSale_SeatID = QString::number(tempsale2.SeatSale);//将SeatSale(int)转换为QString

                aTempItem = new QStandardItem(tempSale_BusID);
                InforModel->setItem(i, 3, aTempItem);

                aTempItem = new QStandardItem(tempsale2.DateSale);
                InforModel->setItem(i, 2, aTempItem);

                aTempItem = new QStandardItem(tempsale2.NameSale);
                InforModel->setItem(i, 0, aTempItem);

                aTempItem = new QStandardItem(tempsale2.IDSale);
                InforModel->setItem(i, 1, aTempItem);

                aTempItem = new QStandardItem(tempSale_SeatID);
                InforModel->setItem(i, 4, aTempItem);

                aTempItem = new QStandardItem(tempsale2.State);
                InforModel->setItem(i, 5, aTempItem);
                if(tempsale2.State=="已售票")
                    InforModel->item(i,5)->setForeground(QBrush(QColor(255,77,0)));
                else
                    InforModel->item(i,5)->setForeground(QBrush(QColor(255,219,112)));
            }
        }
        //弹出警告⚠
        //1-未查询到车辆;
        if(state==false)
            QMessageBox::critical(this,tr("错误"),tr("未查询到车辆"));
        //2-该车无此座位;
        if(ErrorState==2){
            QMessageBox::critical(this,tr("错误"),tr("该车无此座位"));
        }
        //3-此座位已售
        if(ErrorState==3){
            QMessageBox::critical(this,tr("错误"),tr("此座位已售"));
        }
    }
}

//on_action_refund_triggered办理-退票
void MainWindow::on_action_refund_triggered()
{
    Refund_Dialog dlg;
    int ret=dlg.exec();

    if(ret==QDialog::Accepted){
        Sale tempRefund;//临时的容器
        bool found=false;
        for(int i=0;i<my_InfoTable.Get_Bus_Amount();i++){
            QString tempDate=my_InfoTable.Buses[i].Date;
            int tempBusID=my_InfoTable.Buses[i].BusID;
            if((my_InfoTable.Buses[i].Seats[dlg.Seat_Choose()-1].Name==dlg.Passenger_Name())&&(tempDate  == dlg.Date_Choose)&&(tempBusID==dlg.Bus_Choose())){
                QString temp=my_InfoTable.Buses[i].Seats[dlg.Seat_Choose()-1].ID;
                my_InfoTable.Buses[i].Seats[dlg.Seat_Choose()-1].Name="NULL";
                my_InfoTable.Buses[i].Seats[dlg.Seat_Choose()-1].ID="000";
                my_InfoTable.Buses[i].Seats[dlg.Seat_Choose()-1].seated=false;

                tempRefund.NameSale=dlg.Passenger_Name();
                tempRefund.DateSale=dlg.Date_Choose;
                tempRefund.BusIDSale=dlg.Bus_Choose();
                tempRefund.SeatSale=dlg.Seat_Choose();
                tempRefund.IDSale=temp;
                tempRefund.State="已退票";
                Sale_Refund.push_back(tempRefund);
                found=true;
            }
        }

        if(found==false)//弹出警告⚠
            QMessageBox::critical(this,tr("错误"),tr("该座位未曾售出，无法退票"));
        else{
            InforModel->clear();//刷新一遍
            InforModel->setColumnCount(6); //6列
            //表头
            QStringList templist;
            templist.append("姓名");
            templist.append("身份证");
            templist.append("日期");
            templist.append("班次");
            templist.append("座位号");
            templist.append("办理状态");
            InforModel->setHorizontalHeaderLabels(templist);

            int RowCnt = Sale_Refund.size(); //行数（不含标题）,多少次办理就有多少行
            InforModel->setRowCount(RowCnt);

            QString tempRefund_BusID;
            QString tempRefund_SeatID;
            QStandardItem *aTempItem; //临时的item
            for(int i=0; i<RowCnt; ++i)
            {
                Sale tempRefund2=Sale_Refund[i];//从容器中获取一次办理的信息返回给tempRefund2

                tempRefund_BusID = QString::number(tempRefund2.BusIDSale);//将BusID(int)转换为QString
                tempRefund_SeatID = QString::number(tempRefund2.SeatSale);//将SeatAmount(int)转换为QString

                aTempItem = new QStandardItem(tempRefund_BusID);
                InforModel->setItem(i, 3, aTempItem);

                aTempItem = new QStandardItem(tempRefund2.DateSale);
                InforModel->setItem(i, 2, aTempItem);

                aTempItem = new QStandardItem(tempRefund2.NameSale);
                InforModel->setItem(i, 0, aTempItem);

                aTempItem = new QStandardItem(tempRefund2.IDSale);
                InforModel->setItem(i, 1, aTempItem);

                aTempItem = new QStandardItem(tempRefund_SeatID);
                InforModel->setItem(i, 4, aTempItem);

                aTempItem = new QStandardItem(tempRefund2.State);
                InforModel->setItem(i, 5, aTempItem);
                if(tempRefund2.State=="已退票")
                    InforModel->item(i,5)->setForeground(QBrush(QColor(255,219,112)));
                else
                    InforModel->item(i,5)->setForeground(QBrush(QColor(255,77,0)));
            }
        }
    }
}

//查询-班次信息-今天
void MainWindow::on_action_Today_search_triggered()
{
    InforModel->clear();//刷新一遍
    InforModel->setColumnCount(5); //5列

    //表头
    QStringList templist;
    templist.append("发车日期");
    templist.append("班次");
    templist.append("发车时间");
    templist.append("终点城市");
    templist.append("座位数量");
    InforModel->setHorizontalHeaderLabels(templist);

    int Today_Bus_Amount=0;
    QVector<A_Bus>Today_Buses;//将所有日期为“今天”的车放入容器

    for(int i=0;i<my_InfoTable.Get_Bus_Amount();i++){
        if(my_InfoTable.Buses[i].Date=="今天"){
            Today_Bus_Amount++;
            Today_Buses.push_back(my_InfoTable.Buses[i]);
        }
    }

    int RowCnt = Today_Bus_Amount; //行数（不含标题）,多少辆车就有多少行
    InforModel->setRowCount(RowCnt);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr_BusID;
    QString tempStr_SeatAmount;
    for(int i=0; i<RowCnt; ++i)
    {
        A_Bus tempbus=Today_Buses[i];//从容器中获取一辆车的信息返回给tempbus

        tempStr_BusID = QString::number(tempbus.BusID);//将BusID(int)转换为QString
        tempStr_SeatAmount = QString::number(tempbus.SeatAmount);//将SeatAmount(int)转换为QString

        aTempItem = new QStandardItem(tempbus.Date);
        InforModel->setItem(i, 0, aTempItem);

        aTempItem = new QStandardItem(tempStr_BusID);
        InforModel->setItem(i, 1, aTempItem);

        aTempItem = new QStandardItem(tempbus.DepTime);
        InforModel->setItem(i, 2, aTempItem);

        aTempItem = new QStandardItem(tempbus.Destination);
        InforModel->setItem(i, 3, aTempItem);

        aTempItem = new QStandardItem(tempStr_SeatAmount);
        InforModel->setItem(i, 4, aTempItem);
    }
   //只读
   ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
   ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(1, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(2, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(3, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(4, readOnlyDelegate);
}

//查询-班次信息-明天
void MainWindow::on_action_tomorrow_search_triggered()
{
    InforModel->clear();//刷新一遍
    InforModel->setColumnCount(5); //5列

    //表头
    //发车日期，班次，发车时间，终点城市，座位数量
    QStringList templist;
    templist.append("发车日期");
    templist.append("班次");
    templist.append("发车时间");
    templist.append("终点城市");
    templist.append("座位数量");
    InforModel->setHorizontalHeaderLabels(templist);

    int Today_Bus_Amount=0;
    QVector<A_Bus>Today_Buses;//将所有日期为“明天”的车放入容器

    for(int i=0;i<my_InfoTable.Get_Bus_Amount();i++){
        if(my_InfoTable.Buses[i].Date=="明天"){
            Today_Bus_Amount++;
            Today_Buses.push_back(my_InfoTable.Buses[i]);
        }
    }

    int RowCnt = Today_Bus_Amount; //行数（不含标题）,多少辆车就有多少行
    InforModel->setRowCount(RowCnt);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr_BusID;
    QString tempStr_SeatAmount;
    for(int i=0; i<RowCnt; ++i)
    {
        A_Bus tempbus=Today_Buses[i];//从容器中获取一辆车的信息返回给tempbus

        tempStr_BusID = QString::number(tempbus.BusID);//将BusID(int)转换为QString
        tempStr_SeatAmount = QString::number(tempbus.SeatAmount);//将SeatAmount(int)转换为QString

        aTempItem = new QStandardItem(tempbus.Date);
        InforModel->setItem(i, 0, aTempItem);

        aTempItem = new QStandardItem(tempStr_BusID);
        InforModel->setItem(i, 1, aTempItem);

        aTempItem = new QStandardItem(tempbus.DepTime);
        InforModel->setItem(i, 2, aTempItem);

        aTempItem = new QStandardItem(tempbus.Destination);
        InforModel->setItem(i, 3, aTempItem);

        aTempItem = new QStandardItem(tempStr_SeatAmount);
        InforModel->setItem(i, 4, aTempItem);
    }
   //只读（日期，终点）
   ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
   ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(1, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(2, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(3, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(4, readOnlyDelegate);
}

//查询-班次信息-后天
void MainWindow::on_action_DAT_search_triggered()
{
    InforModel->clear();//刷新一遍
    InforModel->setColumnCount(5); //5列

    //表头
    //发车日期，班次，发车时间，终点城市，座位数量
    QStringList templist;
    templist.append("发车日期");
    templist.append("班次");
    templist.append("发车时间");
    templist.append("终点城市");
    templist.append("座位数量");
    InforModel->setHorizontalHeaderLabels(templist);

    int Today_Bus_Amount=0;
    QVector<A_Bus>Today_Buses;//将所有日期为“后天”的车放入容器

    for(int i=0;i<my_InfoTable.Get_Bus_Amount();i++){
        if(my_InfoTable.Buses[i].Date=="后天"){
            Today_Bus_Amount++;
            Today_Buses.push_back(my_InfoTable.Buses[i]);
        }
    }

    int RowCnt = Today_Bus_Amount; //行数（不含标题）,多少辆车就有多少行
    InforModel->setRowCount(RowCnt);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr_BusID;
    QString tempStr_SeatAmount;
    for(int i=0; i<RowCnt; ++i)
    {
        A_Bus tempbus=Today_Buses[i];//从容器中获取一辆车的信息返回给tempbus

        tempStr_BusID = QString::number(tempbus.BusID);//将BusID(int)转换为QString
        tempStr_SeatAmount = QString::number(tempbus.SeatAmount);//将SeatAmount(int)转换为QString

        aTempItem = new QStandardItem(tempbus.Date);
        InforModel->setItem(i, 0, aTempItem);

        aTempItem = new QStandardItem(tempStr_BusID);
        InforModel->setItem(i, 1, aTempItem);

        aTempItem = new QStandardItem(tempbus.DepTime);
        InforModel->setItem(i, 2, aTempItem);

        aTempItem = new QStandardItem(tempbus.Destination);
        InforModel->setItem(i, 3, aTempItem);

        aTempItem = new QStandardItem(tempStr_SeatAmount);
        InforModel->setItem(i, 4, aTempItem);
    }
   //只读（日期，终点）
   ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
   ui->ShowInfotableView->setItemDelegateForColumn(0, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(1, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(2, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(3, readOnlyDelegate);
   ui->ShowInfotableView->setItemDelegateForColumn(4, readOnlyDelegate);
}

//查询-乘客列表
void MainWindow::on_action_search_PassengerList_triggered()
{
    PassengerList_Dialog dlg;
    int ret=dlg.exec();
    if(ret==QDialog::Accepted){
        //遍历容器中所有车辆
        A_Bus tempbus;
        bool found=false;
        for(int i=0;i<my_InfoTable.Get_Bus_Amount();i++){
            //找到要查询的车
            if((my_InfoTable.Buses[i].Date==dlg.Date_Choose) && (my_InfoTable.Buses[i].BusID==dlg.Bus_Choose())){
                tempbus=my_InfoTable.Get_A_Bus(i);
                found=true;
            }
        }

        if(found==false)//弹出警告⚠
            QMessageBox::critical(this,tr("错误"),tr("找不到要查询车辆"));
        else{
            InforModel->clear();//刷新一遍
            InforModel->setColumnCount(4); //4列

            //表头
            //座位，姓名，身份证
            QStringList templist;
            templist.append("座位");
            templist.append("状态");
            templist.append("姓名");
            templist.append("身份证");

            InforModel->setHorizontalHeaderLabels(templist);

            int RowCnt = tempbus.SeatAmount; //行数（不含标题）,多少座位就有多少行
            InforModel->setRowCount(RowCnt);

            //遍历，插入数据
            QStandardItem *aTempItem; //临时的item
            QString tempStr_SeatNumber;
            QString state;

            QString NULL_Name=" ";
            QString NULL_ID=" ";

            for(int j=0; j<RowCnt; ++j)
            {
                    if(tempbus.Seats[j].Name=="NULL"){
                        A_Seat_Info tempSeat=tempbus.Seats[j];

                        tempStr_SeatNumber = QString::number(tempSeat.Seat_Number);
                        aTempItem = new QStandardItem(tempStr_SeatNumber);
                        InforModel->setItem(j, 0, aTempItem);

                        state="未售出";
                        aTempItem = new QStandardItem(state);
                        InforModel->setItem(j, 1, aTempItem);
                        InforModel->item(j,1)->setForeground(QBrush(QColor(255,219,112)));

                        aTempItem = new QStandardItem(NULL_Name);
                        InforModel->setItem(j, 2, aTempItem);

                        aTempItem = new QStandardItem(NULL_ID);
                        InforModel->setItem(j, 3, aTempItem);
                    }
                    else{
                        A_Seat_Info tempSeat=tempbus.Seats[j];

                        tempStr_SeatNumber = QString::number(tempSeat.Seat_Number);
                        aTempItem = new QStandardItem(tempStr_SeatNumber);
                        InforModel->setItem(j, 0, aTempItem);

                        state="已售出";
                        aTempItem = new QStandardItem(state);
                        InforModel->setItem(j, 1, aTempItem);
                        InforModel->item(j,1)->setForeground(QBrush(QColor(255,77,0)));


                        aTempItem = new QStandardItem(tempSeat.Name);
                        InforModel->setItem(j, 2, aTempItem);

                        aTempItem = new QStandardItem(tempSeat.ID);
                        InforModel->setItem(j, 3, aTempItem);
                    }

            }
        }

    }
}

//查询-余票查询(输入日期，班次，显示该班次未坐人的座位号)
void MainWindow::on_actionSearchTicketLeft_triggered()
{
    TicketLeft_Dialog dlg;
    int ret=dlg.exec();
    if(ret==QDialog::Accepted){
        //遍历my_InfoTable容器，寻找该辆车
        A_Bus tempbus;
        bool found=false;
        for(int i=0;i<my_InfoTable.Get_Bus_Amount();i++){
            if(my_InfoTable.Buses[i].Date==dlg.Date_Choose && my_InfoTable.Buses[i].BusID==dlg.Bus_ID()){
                tempbus=my_InfoTable.Buses[i];
                found=true;
            }
        }
        if(found==false){//弹出警告⚠
            QMessageBox::critical(this,tr("错误"),tr("该日无此班次"));
            //TicketLeft_Dialog *dialog=new TicketLeft_Dialog;//警告后重新打开TicketLeft_Dialog窗口
            //dialog->setModal(false);
            //dialog->open();
        }
        else
        {
            //遍历该辆车的所有座位，寻找未坐人的有哪些
            QVector <int> SeatRemained;
            for(int i=0;i<tempbus.SeatAmount;i++){
                if(tempbus.Seats[i].Name=="NULL")
                    SeatRemained.push_back(tempbus.Seats[i].Seat_Number);
            }
            //显示余票
            InforModel->clear();//刷新一遍
            InforModel->setColumnCount(4); //4列
            QStringList templist;
            templist.append("发车日期");
            templist.append("班次");
            templist.append("座位号");
            templist.append("状态");
            InforModel->setHorizontalHeaderLabels(templist);
            int RowCnt = SeatRemained.size(); //行数（不含标题）,多少座位就有多少行
            InforModel->setRowCount(RowCnt);
            QStandardItem *aTempItem; //临时的item
            for(int i=0;i<RowCnt;i++){
                aTempItem = new QStandardItem(dlg.Date_Choose);
                InforModel->setItem(i, 0, aTempItem);

                QString tempBusID = QString::number(dlg.Bus_ID());
                aTempItem = new QStandardItem(tempBusID);
                InforModel->setItem(i, 1, aTempItem);

                QString tempSeat=QString::number(SeatRemained[i]);
                aTempItem = new QStandardItem(tempSeat);
                InforModel->setItem(i, 2, aTempItem);

                QString state="剩余";
                aTempItem = new QStandardItem(state);
                InforModel->setItem(i, 3, aTempItem);
                InforModel->item(i,3)->setForeground(QBrush(QColor(255,219,112)));
            }
        }
    }
}
