#include "resource.h"
#include <QString>
#include <iostream>
using namespace std;

Resource::Resource()
{
    //manque id;
    price=0;
    type="unkown";
    alloc=0;
    stock=1;
    storage=1;
    date_exp="0";
}

Resource::~Resource(){
    cout<<"Resource deleted"<<endl;
}
/////////////////////////////////////////////////Getters
int Resource::getidr(){
    return idr;
}
int Resource::getprice(){
    return price;
}
string Resource::gettype(){
    return type;
}
int Resource::getalloc(){
    return alloc;
}
int Resource::getstock(){
    return stock;
}
int Resource::getstorage(){
    return storage;
}
string Resource::getdate_exp(){
    return date_exp;
}
/////////////////////////////////////////////////Setters
void Resource::setidr(int a){
    idr=a;
}
void Resource::setprice(int a){
    price=a;
}
void Resource::settype(string h){
    type=h;
}
void Resource::setalloc(int a){
    alloc=a;
}
void Resource::setstock(int a){
    stock=a;
}
void Resource::setstorage(int a){
    storage=a;
}
void Resource::setdate_exp(string h){
    date_exp=h;
}
