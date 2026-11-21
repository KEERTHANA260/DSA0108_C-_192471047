#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;
class Bill{protected:string patient;public:explicit Bill(string p):patient(move(p)){}virtual~Bill()=default;virtual double total()const=0;virtual string type()const=0;string patientName()const{return patient;}void print()const{cout<<type()<<" "<<patient<<": "<<total()<<'\n';}};
class OPBill:public Bill{double c,t;public:OPBill(string p,double x,double y):Bill(move(p)),c(x),t(y){}double total()const override{if(c<0||t<0)throw invalid_argument("negative OP charge");return c+t;}string type()const override{return "OP";}};
class IPBill:public Bill{int days;double rate,procedure;public:IPBill(string p,int d,double r,double x):Bill(move(p)),days(d),rate(r),procedure(x){}double total()const override{if(days<0||rate<0||procedure<0)throw invalid_argument("invalid IP charge");return days*rate+procedure;}string type()const override{return "IP";}};
// New bill type: corporate wellness package.
class CorporatePackageBill:public Bill{double packageFee,discount;public:CorporatePackageBill(string p,double f,double d):Bill(move(p)),packageFee(f),discount(d){}double total()const override{if(packageFee<0||discount<0||discount>100)throw invalid_argument("invalid corporate package");return packageFee*(1-discount/100);}string type()const override{return "CorporatePackage";}};
class Payer{public:virtual~Payer()=default;virtual double amountCovered(const Bill&)const=0;virtual string name()const=0;};
class InsurancePayer:public Payer{double limit;public:explicit InsurancePayer(double l):limit(l){}double amountCovered(const Bill&b)const override{return min(limit,b.total());}string name()const override{return "Insurance";}};
// New payer type: corporate tie-up covers 90 percent.
class CorporateTieUp:public Payer{public:double amountCovered(const Bill&b)const override{return b.total()*0.90;}string name()const override{return "CorporateTieUp";}};
int main(){vector<unique_ptr<Bill>> bills;bills.push_back(make_unique<OPBill>("Ravi",500,1200));bills.push_back(make_unique<IPBill>("Meena",3,2500,40000));bills.push_back(make_unique<CorporatePackageBill>("Anu",20000,10));double total=0;for(const auto&b:bills){b->print();total+=b->total();}cout<<"Total: "<<total<<'\n';InsurancePayer insurance(50000);CorporateTieUp corporate;for(const auto&b:bills)cout<<corporate.name()<<" covers "<<b->patientName()<<": "<<corporate.amountCovered(*b)<<'\n';cout<<"Insurance covers first bill: "<<insurance.amountCovered(*bills.front())<<'\n';}
