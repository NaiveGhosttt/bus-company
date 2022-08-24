
/*管理很多辆车的班次信息以及座位信息*/
#ifndef INFOTABLE_H
#define INFOTABLE_H
#include"a_bus.h"
#include <vector>
#include <QVector>

class InfoTable
{
public:
    InfoTable();

    bool Read_Bus_FromFile(const QString &aReadFileName);//从文件读取所有班次信息（包括其座位信息）
    bool Save_Bus_ToFile(const QString &aSaveFileName);//往流文件写入所有班次信息（包括其座位信息）

    void Add_Bus(A_Bus & bus);//往InfoTable的对象里添加一辆车
    A_Bus & Get_A_Bus(int index);//从InfoTable的对象里返回一辆车
    int Get_Bus_Amount();//返回InfoTable的对象里的车辆总数

    QVector<A_Bus>Buses;//存所有的车辆及其座位
    int Bus_Amount;//InfoTable的对象里的车辆总数
};

#endif // INFOTABLE_H
