#include <iostream>
#include <stdexcept>
#include <string>
#include <new>
using namespace std;
class ClaimError : public runtime_error { public: using runtime_error::runtime_error; };
double approve(double billed,double cover){
    if(billed<0||cover<0) throw invalid_argument("negative amount");
    if(billed>cover) throw ClaimError("exceeds cover");
    return billed;
}
double settle(double billed,double cover){
    try{return approve(billed,cover);}
    catch(const ClaimError&e){cout<<"audit: "<<e.what()<<'\n';throw;}
}
double parseAmount(const string&s){size_t used=0;double v=stod(s,&used);if(used!=s.size())throw invalid_argument("not a valid number");return v;}
struct Resource { ~Resource() noexcept { cout<<"resource released\n"; } };
int main(){
    double cases[][2]={{40000,50000},{60000,50000},{-1,50000}};
    for(auto&c:cases){try{double paid=settle(c[0],c[1]);cout<<"approved "<<paid<<'\n';}catch(const ClaimError&e){cout<<"claim rejected: "<<e.what()<<'\n';}catch(const exception&e){cout<<"error: "<<e.what()<<'\n';}}
    try{double value=parseAmount("abc");cout<<"parsed "<<value<<'\n';}catch(const invalid_argument&e){cout<<"input error: "<<e.what()<<'\n';}
    try{Resource r; throw bad_alloc();}catch(const bad_alloc&){cout<<"allocation failure caught (controlled test)\n";}
    try{throw 7;}catch(...){cout<<"top-level catch(...) handled an unknown error\n";}
}
