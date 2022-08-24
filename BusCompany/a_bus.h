/*管理一辆车的信息，含该车辆的所有座位的信息*/
#ifndef A_BUS_H
#define A_BUS_H
#include <qstring.h>
#include <QTime>
#include <qdatetime.h>
#include <QTextStream>

//某个座位的座位号、乘客姓名、身份证号
typedef struct A_Seat_Info {
    bool seated;//该座位有人否
    int Seat_Number;
    QString Name;
    QString ID;
}A_Seat_Info;


//某辆客车的班次号、出发时间、目的地、座位数及每个座位的信息
class A_Bus
{
public:
    A_Bus();
    virtual ~A_Bus();

    A_Bus(const A_Bus &temp_A_Bus);
    A_Bus &operator=(const A_Bus &temp_A_Bus);

    void Save_Seats(QTextStream &aStream); //往流文件中写入车的所有座位信息
    void Read_Seats(QTextStream &aStream); //从流文件读车的所有座位信息
    void Save_A_Bus(QTextStream &aStream); //往流文件中写入一辆车信息
    void Read_A_Bus(QTextStream &aStream); //从流文件中读一辆车信息

    int BusID;//班次号
    QString Date;//出发日期
    QString DepTime;//出发时间
    QString Destination;//终点
    int SeatAmount;//座位数量
    A_Seat_Info Seats[50];//客运汽车座位数一般在50以内
};

#endif // A_BUS_H
