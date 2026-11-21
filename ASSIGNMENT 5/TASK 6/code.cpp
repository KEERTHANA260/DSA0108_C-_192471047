#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Bill { protected: string patient; public: explicit Bill(string p):patient(move(p)){} virtual ~Bill()=default; virtual double total()const=0; virtual string type()const=0; void print()const{cout<<type()<<" "<<patient<<": "<<total()<<'\n';}};
class OutPatient:public Bill{double consultation,tests;public:OutPatient(string p,double c,double t):Bill(move(p)),consultation(c),tests(t){}double total()const override{return consultation+tests;}string type()const override{return "OP";}};
class InPatient:public Bill{int days;double perDay,surgery;public:InPatient(string p,int d,double r,double s):Bill(move(p)),days(d),perDay(r),surgery(s){}double total()const override{return days*perDay+surgery;}string type()const override{return "IP";}};
class DayCare:public Bill{double package;public:DayCare(string p,double v):Bill(move(p)),package(v){}double total()const override{return package;}string type()const override{return "DayCare";}};
class Emergency:public Bill{double base,hourly;int hours;public:Emergency(string p,double b,double h,int n):Bill(move(p)),base(b),hourly(h),hours(n){}double total()const override{return base+hourly*hours;}string type()const override{return "Emergency";}};
class Payer{public:virtual~Payer()=default;virtual double amountCovered(const Bill&)const=0;virtual string name()const=0;};
class SelfPay:public Payer{public:double amountCovered(const Bill&b)const override{return b.total();}string name()const override{return "SelfPay";}};
class Insurance:public Payer{double limit,copay;public:Insurance(double l,double c):limit(l),copay(c){}double amountCovered(const Bill&b)const override{return min(limit,b.total()*(1-copay/100));}string name()const override{return "Insurance";}};
class Government:public Payer{double rate;public:explicit Government(double r):rate(r){}double amountCovered(const Bill&b)const override{return min(rate,b.total());}string name()const override{return "Government";}};
int main(){
 vector<unique_ptr<Bill>> bills;
 bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
 bills.push_back(make_unique<InPatient>("Meena",3,2500,40000));
 bills.push_back(make_unique<DayCare>("Arun",18000));
 bills.push_back(make_unique<Emergency>("Sara",2000,750,4));
 vector<unique_ptr<Payer>> payers;
 payers.push_back(make_unique<SelfPay>());payers.push_back(make_unique<Insurance>(50000,20));payers.push_back(make_unique<Government>(15000));
 double grand=0;for(const auto&b:bills){b->print();grand+=b->total();}
 cout<<"Grand total: "<<grand<<'\n';
 for(const auto&p:payers){double covered=0;for(const auto&b:bills)covered+=p->amountCovered(*b);cout<<p->name()<<" total covered: "<<covered<<'\n';}
}
