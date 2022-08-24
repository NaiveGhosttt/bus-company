#ifndef SALE_H
#define SALE_H
#include <QString>

class Sale
{
public:
    Sale();

     //容器存：姓名、身份证、发车日期、班次、座位号
    QString NameSale;
    QString IDSale;
    QString DateSale;
    int BusIDSale;
    int SeatSale;
    QString State;//已售票；已退票
};

#endif // SALE_H
