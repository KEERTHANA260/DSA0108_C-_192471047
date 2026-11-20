#include <iostream>
struct Parcel{double kg;bool express,insured;};
double charge(double kg,bool express=false,bool insured=false){return 50*kg+(express?30:0)+(insured?20:0);}
double charge(int grams){return charge(grams/1000.0);}
double charge(Parcel p){return charge(p.kg,p.express,p.insured);}
int main(){std::cout<<"charge(2): "<<charge(2)<<'\n'<<"charge(2.0f): "<<charge(2.0f)<<'\n'<<"grams: "<<charge(1500)<<'\n'<<"express: "<<charge(2.0,true)<<'\n'<<"insured: "<<charge(2.0,false,true)<<'\n'<<"Parcel: "<<charge(Parcel{3,true,true})<<'\n';}
