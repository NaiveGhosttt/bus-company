#include "a_bus.h"

//构造函数设置每个成员的默认值
A_Bus::A_Bus()
{
    BusID=0;
    Date="今天";//日期默认为今天
    SeatAmount=0;
    for(int i=0;i<50;i++){
        Seats[i].seated=false;//默认每个座位还没有坐人
        Seats[i].Seat_Number=i+1;
        Seats[i].Name="NULL";
        Seats[i].ID="000";
    }
}

//析构
A_Bus::~A_Bus(){

}

//拷贝构造
A_Bus::A_Bus(const A_Bus &temp_A_Bus){
    BusID=temp_A_Bus.BusID;
    Date=temp_A_Bus.Date;
    DepTime=temp_A_Bus.DepTime;
    Destination=temp_A_Bus.Destination;
    SeatAmount=temp_A_Bus.SeatAmount;

    for(int i=0;i<50;i++){
        Seats[i]=temp_A_Bus.Seats[i];
    }
}

//赋值=重载
A_Bus& A_Bus::operator=(const A_Bus &temp_A_Bus){
    BusID=temp_A_Bus.BusID;
    Date=temp_A_Bus.Date;
    DepTime=temp_A_Bus.DepTime;
    Destination=temp_A_Bus.Destination;
    SeatAmount=temp_A_Bus.SeatAmount;

    for(int i=0;i<50;i++){
        Seats[i]=temp_A_Bus.Seats[i];
    }
    return *this;
}

//往流文件中写入车的所有座位信息
void A_Bus::Save_Seats(QTextStream &aStream){
    for(int i=0;i<SeatAmount;i++){
        aStream<<Seats[i].Seat_Number<<" "<<Seats[i].Name<<" "<<Seats[i].ID<<'\n';
    }
}

//从流文件读车的所有座位信息
void A_Bus::Read_Seats(QTextStream &aStream){
    for(int i=0;i<SeatAmount;i++)
        aStream>>Seats[i].Seat_Number>>Seats[i].Name>>Seats[i].ID;
}

//往流文件中写入一辆车信息
void A_Bus::Save_A_Bus(QTextStream &aStream){
    aStream<<BusID<<" "<<Date<<" "<<DepTime<<" "<<Destination<<" "<<SeatAmount<<'\n';
    Save_Seats(aStream);
}

//从流文件中读一辆车信息
void A_Bus::Read_A_Bus(QTextStream &aStream){
    aStream>>BusID>>Date>>DepTime>>Destination>>SeatAmount;
    Read_Seats(aStream);
}
