#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<direct.h>

using namespace std;

void intro() {
	cout<<"\n";
	cout<<"\t\t\t||\t\t C++ Project On Hotel Management System  \t\t||";
	cout<<"\n\t\t\t||\t\t\t\t   MADE BY\t\t\t\t||";
	cout<<"\n\t\t\t||\t\t\t\tMANMAY GHOSH\t\t\t\t||";
}

void head() {
	cout<<endl;
	cout<<"\n\t\t\t||\t\t\t\t  MyOwn Hotel\t\t\t\t||"<< endl;	
}

void time() {
	int i=0;
	long long j;
	cout<<"	\n\n\n	Connecting to Server\n 	Syncing DaTa";
	while(i<10)	{
		for (j=5;j>4;j++) {
			if (j==99999) {
				cout<<".";
				break;
			}
		}
		++i;
	}
}

//Hotel Class Here =>
class hotel {
	private:
			int room_no;
			char name[30];
			char address[50];
			char phone[15];
			int days;
			float fare;
	public:
			void main_menu();		//to display the main menu
			void add();				//to book a room
			void display(); 		//to display the customer record
			void rooms();			//to display allotted rooms
			void edit();			//to edit the customer record
			int check(int);	     	//to check room status
			void modify(int);		//to modify the record
			void delete_rec(int);   //to delete the record
};

void hotel::main_menu() {
	int choice;
	while(choice!=5) {
		head();
		cout<<"\n\t\t\t\t\t\t\t***************";
		cout<<"\n\t\t\t\t\t\t\t** MAIN MENU **";
		cout<<"\n\t\t\t\t\t\t\t***************";
		cout<<"\n\n\t\t\t1.Book A Room";
		cout<<"\n\t\t\t2.Customer Record";
		cout<<"\n\t\t\t3.Rooms Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;
		switch(choice) {
			case 1:	add();
					break;
			case 2: display();
					break;
			case 3: rooms();
					break;
			case 4:	edit();
					break;
			case 5: exit(0);
			default: {
				cout<<"\n\n\t\t\tWrong choice.....!!!";
				cout<<"\n\t\t\tPress any key to continue....!!";
				getch();
			}
		}
	}
}

void hotel::add() {
	head();
	int r,flag;
	ofstream fout("Record.data",ios::app);
	cout<<"\n Enter Customer Details";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: \t";
	cin>>r;
	flag=check(r);											//check room vacant or not therefore check fn called
	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";
	else {
		room_no=r;
		cout<<" Name: \t";									// no adding name of customer
		gets(name);
		cout<<" Address: \t";
		gets(address);
		cout<<" Phone No: \t";
		gets(phone);
		cout<<" No of Days to Checkout: \t";
		cin>>days;
		fare=days*900;						//900 is currently set as the
											//default price per day
		fout.write((char*)this,sizeof(hotel));
		cout<<"\n Room is booked...!!!";
	}
	cout<<"\n Press any key to continue.....!!";
	getch();
	fout.close();
}

void hotel::display() {								//error same space while displaying values which should not be there
	head();
	ifstream fin("Record.data",ios::in);
	int r,flag=0;
	cout<<"\n Enter room no: \t";
	cin>>r;
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			head();
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: \t"<<room_no;
			cout<<"\n Name: \t"<<name;
			cout<<"\n Address: \t"<<address;
			cout<<"\n Phone no: \t"<<phone;
			cout<<"\n Days: \t"<<days;									//terminal display error
			cout<<"\n Total Fare: \t"<<fare;
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant....!!";
	cout<<"\n\n Press any key to continue....!!";
	getch();
	fin.close();
}

void hotel::rooms() {								//error same space while displaying values which should not be there
	head();
	ifstream fin("Record.data",ios::in);
	cout<<"\n\t\t\t    List Of Rooms Allotted";
	cout<<"\n\t\t\t    ----------------------";
	while(!fin.eof()) {								//return same room number values when same room number is accessed multiple time in a single run time
		fin.read((char*)this,sizeof(hotel));
		cout<<"\n Room no: \t"<<room_no<<"\n Name: \t"<<name;
		cout<<"\n Address: \t"<<address<<"\n Phone: \t"<<phone;
		cout<<"\n Days: \t"<<days<<"\n Total: \t"<<fare;
		cout<<"\n**********************************";
	}
	cout<<"\n\n\n\t\t\tPress any key to continue.....!!";
	getch();
	fin.close();
}

void hotel::edit() {
	head();
	int choice,r;
	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;
	head();
	cout<<"\n Enter room no: " ;
	cin>>r;
	switch(choice) {
		case 1:	modify(r);
				break;
		case 2:	delete_rec(r);
				break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
}

int hotel::check(int r) {
	int flag=0;
	ifstream fin("Record.data",ios::in);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			flag=1;
			break;
		}
	}
	fin.close();
	return(flag);
}

void hotel::modify(int r) {
	head();
	long pos,flag=0;
	fstream file("Record.data",ios::in|ios::out);		//|ios::binary);
	while(!file.eof()) {
		pos=file.tellg();
		file.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			cout<<"\n Enter New Details";
			cout<<"\n -----------------";
			cout<<"\n Name: \t\t";
			gets(name);
			cout<<" Address: \t\t";
			gets(address);
			cout<<" Phone no: \t\t";
			gets(phone);
			cout<<" Days: \t\t";
			cin>>days;
			fare=days*900;
			file.seekg(pos);
			file.write((char*)this,sizeof(hotel));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		}
	}
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant...!!";
	file.close();
}

void hotel::delete_rec(int r) {
	head();
	int flag=0;
	char ch;
	ifstream fin("Record.data",ios::in);
	ofstream fout("temp.data",ios::out);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			cout<<"\n Name: \t"<<name;
			cout<<"\n Address: \t"<<address;
			cout<<"\n Phone No: \t"<<phone;
			cout<<"\n Days: \t"<<days;
			cout<<"\n Total Fare: \t"<<fare;
			cout<<"\n\n Do you want to delete this record(y/n): \t";
			cin>>ch;
			if(ch=='n')
				fout.write((char*)this,sizeof(hotel));
			flag=1;
			break;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}
	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else {
		remove("Record.txt");
		rename("temp.txt","Record.txt");
	}
}

int main() {
	
	hotel h;
	cout<<"\n\n";
	intro();
	time();
	cout<<"\n\n\t\t\tPress any key to continue....!!";
	getch();
	head();
	char id[5],pass[7];
	cout<<"\n\n\t\t\t\tusername => ";
	cin>>id;
	cout<<"\t\t\t\tpassword => ";
	cin>>pass;
	cout<<"\n\n\t";
	time();
	cout<<"\t";
	if(strcmp(id,"admin")==0&&strcmp(pass,"******")==0)
		cout<<"\n\n\t\t\t  !!!Login Successfull!!!";
	else {
		cout<<"\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
		getch();
		exit(1);
	}
	h.main_menu();
	getch();
	
	return 0;
}