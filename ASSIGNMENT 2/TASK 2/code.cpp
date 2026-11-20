#include <iostream>
int& highest(int a[],int n){int k=0;for(int i=1;i<n;i++)if(a[i]>a[k])k=i;return a[k];}
int highestIndex(const int a[],int n){int k=0;for(int i=1;i<n;i++)if(a[i]>a[k])k=i;return k;}
int highestCopy(const int a[],int n){return a[highestIndex(a,n)];}
int main(){int marks[]={78,91,85,88,91};highest(marks,5)+=2;std::cout<<"Highest after moderation: "<<highest(marks,5)<<'\n';std::cout<<"Index: "<<highestIndex(marks,5)<<'\n';std::cout<<"Copy: "<<highestCopy(marks,5)<<'\n';const int& readOnly=highest(marks,5);std::cout<<"Const reference: "<<readOnly<<'\n';}
