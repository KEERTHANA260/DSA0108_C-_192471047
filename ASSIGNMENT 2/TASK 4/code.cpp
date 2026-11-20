#include <iostream>
class SavingsAccount{long long number;double balance;double tx[10]{};int count=0;void record(double v){if(count<10)tx[count++]=v;else{for(int i=1;i<10;i++)tx[i-1]=tx[i];tx[9]=v;}}public:SavingsAccount(long long n,double b):number(n),balance(b){}void deposit(double);bool withdraw(double);void miniStatement()const{std::cout<<"Account "<<number<<" balance "<<balance<<"\nRecent transactions:\n";for(int i=0;i<count;i++)std::cout<<tx[i]<<'\n';}};
void SavingsAccount::deposit(double a){if(a>0){balance+=a;record(a);}}
bool SavingsAccount::withdraw(double a){if(a<=0||a>balance)return false;balance-=a;record(-a);return true;}
int main(){SavingsAccount a(123456,1000);a.deposit(200);a.withdraw(150);for(int i=0;i<10;i++)a.deposit(10);a.miniStatement();}
