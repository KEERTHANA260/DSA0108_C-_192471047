#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <memory>
using namespace std;
using Clock=chrono::steady_clock;
struct BillData{int type;double a,b;int days;};
struct Base{virtual~Base()=default;virtual double total()const=0;};
struct OP:Base{double a,b;OP(double x,double y):a(x),b(y){}double total()const override{return a+b;}};
struct IP:Base{double a;int d;IP(double x,int n):a(x),d(n){}double total()const override{return a*d;}};
double switchTotal(const BillData&x){switch(x.type){case 0:return x.a+x.b;default:return x.a*x.days;}}
volatile double sink=0;
template<class F> double measure(F f){auto s=Clock::now();double v=f();auto e=Clock::now();sink=v;return chrono::duration<double,milli>(e-s).count();}
void validate(bool bad){if(bad)throw runtime_error("invalid");}
int main(){cout<<fixed<<setprecision(3);
 for(int n:{1000,1000000,10000000}){
  vector<BillData> data;data.reserve(n);vector<unique_ptr<Base>> poly;poly.reserve(n);
  for(int i=0;i<n;++i){if(i%2==0){data.push_back({0,500,1200,0});poly.push_back(make_unique<OP>(500,1200));}else{data.push_back({1,2500,0,3});poly.push_back(make_unique<IP>(2500,3));}}
  double sw=measure([&]{double z=0;for(const auto&x:data)z+=switchTotal(x);return z;});
  double virt=measure([&]{double z=0;for(const auto&x:poly)z+=x->total();return z;});
  cout<<"Bills "<<n<<": switch="<<sw<<" ms, virtual="<<virt<<" ms, totals="<<switchTotal(data[0])+switchTotal(data[1])<<" (first pair)\n";
 }
 const int n=1000000;
 for(int pct:{0,1,50}){
  vector<unsigned char> invalid(n,0);for(int i=0;i<n*pct/100;++i)invalid[i]=1;
  auto status=measure([&]{long ok=0;for(auto x:invalid){if(!x)++ok;}return double(ok);});
  auto except=measure([&]{long ok=0;for(auto x:invalid){try{validate(x!=0);++ok;}catch(const exception&){} }return double(ok);});
  cout<<"Invalid "<<pct<<"%: return-code="<<status<<" ms, exceptions="<<except<<" ms\n";
 }
 cout<<"Timing varies by CPU, compiler and system load.\n";
}
