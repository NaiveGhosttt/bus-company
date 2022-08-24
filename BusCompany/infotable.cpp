#include "infotable.h"
#include <qfile.h>
#include <QTextStream>
#include <QTextCodec>

InfoTable::InfoTable()
{
    Bus_Amount=0;
}

//从流文件逐个读车辆信息并push入vector容器
bool InfoTable::Read_Bus_FromFile(const QString &aReadFileName){//给定文件名
    QFile aFile(aReadFileName);
    if(!aFile.exists()) //文件不存在
        return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本方式打开
        return false;

    QTextStream aStream(&aFile); //用文本流读取文件
    aStream.setCodec(QTextCodec::codecForName("system")); //显示汉字

    //初始化
    Buses.clear();//将装每辆车的vector池子清零
    Bus_Amount = 0;//车辆总数

    //逐个读取车辆信息
    aStream>>Bus_Amount; //先读车辆总数
    A_Bus tempBus;
    if(Bus_Amount>0)
    {
        for(int i=0; i<Bus_Amount; i++)
        {
            tempBus.Read_A_Bus(aStream);
            Buses.push_back(tempBus);
        }
    }

    aFile.close();//关闭文件
    return true;
}

//将vector容器里的所有车辆信息存入流文件
bool InfoTable::Save_Bus_ToFile(const QString &aSaveFileName){
    QFile aFile(aSaveFileName);
    if(!aFile.open(QIODevice::WriteOnly| QIODevice::Text)) //保存为文本
        return false;
    QTextStream aStream(&aFile);//用文本流保存文件
    aStream.setCodec(QTextCodec::codecForName("system")); //显示汉字

    //逐个写入车辆信息
    aStream<<Bus_Amount<<'\n';//车辆总数
    if(Bus_Amount>0)
    {
        for(int i=0; i<Bus_Amount; i++)
            Buses[i].Save_A_Bus(aStream);
    }
    aFile.close(); //关闭文件
    return true;
}

//添加一辆车到vector容器
void InfoTable::Add_Bus(A_Bus &bus)
{
    Buses.push_back(bus);
    Bus_Amount++;
}

//返回vector容器指定下标的A_Bus对象
A_Bus & InfoTable::Get_A_Bus(int index){
    return Buses[index];
}

//返回vector容器里存了多少bus
int InfoTable::Get_Bus_Amount(){
    Bus_Amount = Buses.size();
    return Bus_Amount;
}
