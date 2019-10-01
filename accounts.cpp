//Errors Fixed 
//Assignment # 2, Applied Programming 2
//By Adnan Jelani
//Answer for Q2

#include<iostream> 
#include<fstream> 
#include<cctype> 
#include<iomanip> 
using namespace std; 

class accounts
{
int ano;
char name[100];
int dep;
char type;
public:
void createaccount(); 
void showacccount() const; 
void modify(); 
void acceptDeposit(int) ;
void draw(int); 
void report() const; 
int retano() const; 
int retbal() const; 
char qtype() const; 
}; 

void accounts::createaccount()
{
cout<<"\nEnter The Account Number :";
cin>>ano;
cout<<"\n\nEnter, Name of The Account Holder : ";
cin.ignore();
cin.getline(name,100);
cout<<"\nEnter Type of Account(Current/Savings) : ";
cin>>type;
cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
cin>>dep; 
cout<<"\n\n\nCongrats Account Has Been Created..";
}

void accounts::showacccount() const
{
cout<<"\nAccount Number : "<<ano;
cout<<"\nAccount Holder Name : ";
cout<<name;
cout<<"\nType of Account : "<<type;
cout<<"\nBalance amount : "<<dep;
}


void accounts::modify()
{
cout<<"\nAccount Number : "<<ano;
cout<<"\nModify Account Holder Name : ";
cin.ignore();
cin.getline(name,100);
cout<<"\nModify Type of Account : ";
cin>>type;
cout<<"\nModify Balance amount : ";
cin>>dep;
}

void accounts::acceptDeposit(int x)
{
dep+=x;
}
  
void accounts::draw(int x)
{
dep-=x;
}
  
void accounts::report() const
{
cout<<ano<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<dep<<endl;
}
  
int accounts::retano() const
{
return ano;
}

int accounts::retbal() const
{
return dep;
}

char accounts::qtype() const
{
return type;
}

void write_acc(); 
void display_sp(int); 
void modify_acc(int); 
void delete_acc(int); 
void display_all(); 
void dep_withdraw(int, int); 
void intro(); 

int main()
{
char ch;
int num;
intro();
do
{
system("cls"); 
cout<<"\n\n\n\tACTION MENU";
cout<<"\n\n\t01. NEW ACCOUNT";
cout<<"\n\n\t02. DEPOSIT";
cout<<"\n\n\t03. WITHDRAW";
cout<<"\n\n\t04. BALANCE ENQUIRY";
cout<<"\n\n\t05. COMPLETE ACCOUNT HOLDERS LIST";
cout<<"\n\n\t06. CLOSE AN ACCOUNT";
cout<<"\n\n\t07. MODIFY AN ACCOUNT";
cout<<"\n\n\t08. EXIT";
cout<<"\n\n\tSelect Your Option (1-8) ";
cin>>ch;
system("cls"); 
switch(ch)
{
case '1':
write_acc();
break;
case '2':
cout<<"\n\n\tEnter The Account Number : "; cin>>num;
dep_withdraw(num, 1);
break;
case '3':
cout<<"\n\n\tEnter The Account Number : "; cin>>num;
dep_withdraw(num, 2);
break;
case '4':
cout<<"\n\n\tEnter The Account Number : "; cin>>num;
display_sp(num);
break;
case '5':
display_all();
break;
case '6':
cout<<"\n\n\tEnter The Account Number : "; cin>>num;
delete_acc(num);
break;
case '7':
cout<<"\n\n\tEnter The Account Number : "; cin>>num;
modify_acc(num);
break;
case '8':
cout<<"\n\n\tThanks For Visiting Our Bank!";
break;
default :cout<<"\a";
}
cin.ignore();
cin.get();
}while(ch!='8');
return 0;
}
void write_acc()
{
accounts ac;
ofstream x;
x.open("info.dat",ios::binary|ios::app);
ac.createaccount();
x.write(reinterpret_cast<char *> (&ac), sizeof(accounts));
x.close();
}


void display_sp(int n) 
{
accounts ac;
bool flag=false;
ifstream x;
x.open("info.dat",ios::binary);
if(!x)
{
cout<<"File could not be opened!! Press any Key to exit...";
return;
}
cout<<"\nBALANCE DETAILS\n";

while(x.read(reinterpret_cast<char *> (&ac), sizeof(accounts)))
{
if(ac.retano()==n)
{
ac.showacccount();
flag=true;
}
}
x.close();
if(flag==false)
cout<<"\n\nAccount number does not exist";
}
void modify_acc(int n)
{
bool found=false;
accounts ac;
fstream x;
x.open("info.dat",ios::binary|ios::in|ios::out);
if(!x)
{
cout<<"File could not be open !! Press any Key...";
return;
}
while(!x.eof() && found==false)
{
x.read(reinterpret_cast<char *> (&ac), sizeof(accounts));
if(ac.retano()==n)
{
ac.showacccount();
cout<<"\n\nEnter The New Details of account"<<endl;
ac.modify();
int pos=(-1)*static_cast<int>(sizeof(accounts));
x.seekp(pos,ios::cur);
x.write(reinterpret_cast<char *> (&ac), sizeof(accounts));
cout<<"\n\n\t Record Updated";
found=true;
}
}
x.close();
if(found==false)
cout<<"\n\n Record Not Found ";
}
void delete_acc(int n)
{
accounts ac;
ifstream x;
ofstream y;
x.open("info.dat",ios::binary);
if(!x)
{
cout<<"File could not be open !! Press any Key...";
return;
}
y.open("Temp.dat",ios::binary);
x.seekg(0,ios::beg);
while(x.read(reinterpret_cast<char *> (&ac), sizeof(accounts)))
{
if(ac.retano()!=n)
{
y.write(reinterpret_cast<char *> (&ac), sizeof(accounts));
}
}
x.close();
y.close();
remove("info.dat");
rename("Temp.dat","info.dat");
cout<<"\n\n\tRecord Deleted ..";
}
void display_all()
{
accounts ac;
ifstream x;
x.open("info.dat",ios::binary);
if(!x)
{
cout<<"File could not be open !! Press any Key...";
return;
}
cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
cout<<"====================================================\n";
cout<<"A/c no. NAME Type Balance\n";
cout<<"====================================================\n";
while(x.read(reinterpret_cast<char *> (&ac), sizeof(accounts)))
{
ac.report();
}
x.close();
}
void dep_withdraw(int n, int option)
{
int amt;
bool found=false;
accounts ac;
fstream x;
x.open("info.dat", ios::binary|ios::in|ios::out);
if(!x)
{
cout<<"File could not be open !! Press any Key...";
return;
}
while(!x.eof() && found==false)
{
x.read(reinterpret_cast<char *> (&ac), sizeof(accounts));
if(ac.retano()==n)
{
ac.showacccount();
if(option==1)
{
cout<<"\n\n\tTO DEPOSITE AMOUNT ";
cout<<"\n\nEnter The amount to be deposited";
cin>>amt;
ac.acceptDeposit(amt);
}
if(option==2)
{
cout<<"\n\n\tTO WITHDRAW AMOUNT ";
cout<<"\n\nEnter The amount to be withdraw";
cin>>amt;
int bal=ac.retbal()-amt;
if((bal<500 && ac.qtype()=='S') || (bal<1000 && ac.qtype()=='C'))
cout<<"Insufficient balance";
else
ac.draw(amt);
}
int pos=(-1)*static_cast<int>(sizeof(ac));
x.seekp(pos,ios::cur);
x.write(reinterpret_cast<char *> (&ac), sizeof(accounts));
cout<<"\n\n\t Record Updated";
found=true;
}
}
x.close();
if(found==false)
cout<<"\n\n Record Not Found ";
}
void intro()
{
cout<<"\n\n\n\tWelcome To BANK MANAGEMENT SYSTEM";
cout<<"\n\nA AP Assignment #1 Adnan Jelani, FAST NUCES";

cout<<"\nPress Enter To Continue........";
cin.get();
}
