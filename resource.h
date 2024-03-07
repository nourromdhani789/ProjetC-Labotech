#ifndef RESOURCE_H
#define RESOURCE_H
#include <string.h>
#include <iostream>
using namespace std;

class Resource
{
private :
    int idr;
    int price;
    string type;
    int alloc;
    int stock;
    int storage;
    string date_exp;
public:
    //getters
    int getidr();
    int getprice();
    string gettype();
    int getalloc();
    int getstock();
    int getstorage();
    string getdate_exp();

    //setters
    void setidr(int a);
    void setprice(int a);
    void settype(string h);
    void setalloc(int a);
    void setstock(int a);
    void setstorage(int a);
    void setdate_exp(string h);

    /////////////////////////////////////ctor and dtor
    Resource();
    ~Resource();
};

#endif // RESOURCE_H
