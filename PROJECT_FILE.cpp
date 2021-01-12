#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
using namespace std;
int z,extra;
char choice;
int quantity;
float tot_amt;
class stock
{
	private:
		int pid;
		char pname[30];
		char pcat[30];
		float p_price;
		int units;
		char status[30];
		void status_check()
		{
			if(units==0)
				strcpy(status,"Empty Stock");
			else if(units<z)
				strcpy(status,"Danger Stock");
			else
				strcpy(status,"Safe Stock  ");
		}
		void check_stock()
		{
			while(units<z)
			{
				cout<<"Number of units in this category is less than minimum stock level!\n";
				cout<<"Do you want to add extra units to existing:(y/n)..";
				cin>>choice;
				if(choice=='Y'||choice=='y')
				{
					cout<<"Enter extra units to add:";
					cin>>extra;
					units+=extra;
				}
				else
					break;
			}
		}
	public:
		stock()
		{
			pid=0;
		}
		void input_id();
		void add_item();
		void update_item();
		void show_stock();
		void sale();
		int get_id()
		{
			return pid;
		}
		int get_cat(char ch[])
		{
			return (strcmp(pcat,ch));
		}
		int get_name(char nm[])
		{
			return (strcmp(pname,nm));
		}

};

void stock::input_id()
{
	cout<<"Enter Product ID:";
	cin>>pid;
}
void stock::add_item()
{
	cout<<"Enter Product Category:";
	cin>>pcat;
	cout<<"Enter Product Name:";
	cin>>pname;
	cout<<"Enter Number of Units:";
	cin>>units;
	cout<<"Enter Price per Unit:";
	cin>>p_price;
	if(units<z)
	{
		check_stock();
	}
	status_check();
}
void stock::show_stock()
{
	cout<<" Product ID: "<<pid<<endl;
	cout<<" Product Category: "<<pcat<<endl;
	cout<<" Product Name: "<<pname<<endl;
	cout<<" Price per Unit: "<<p_price<<endl;
	cout<<" Product Available: "<<units<<endl;
	cout<<" Stock Status: "<<status<<endl;
}
void stock::sale()
{
	
	if(units<=0)
	{
		cout<<"Product Currently Unavailable\n";
		return;
	}
	cout<<"Product ID: "<<pid<<endl;
	cout<<"Product Category: "<<pcat<<endl;
	cout<<"Product Name: "<<pname<<endl;
	cout<<"No. of Units: "<<units<<endl;
	cout<<"Price per Unit: "<<p_price<<"\n\n";
	int x;
	float amt;
	cout<<"Enter Quantity to purchase:";
	cin>>x;
	while(units-x<0)
	{
		cout<<"Not enough Stock Available!!\n";
		cout<<"Current Stock:"<<units<<endl;
		cout<<"Enter Appropriate Quantity:";
		cin>>x;
	}
	units=units-x;
	amt=x*p_price;
	
	cout<<"Quantity Purchased: "<<x<<endl;
	cout<<"Amount: "<<amt<<endl;
	//cout<<"Thank You!!\n";
	cout<<x<<" product(s) of "<<pname<<" "<<pcat<<" sold.\n";	
	if(units<z)
	{
		check_stock();
	}
	status_check();
	quantity+=x;
	tot_amt+=amt;	
}
void stock::update_item()
{
	cout<<"Product ID: "<<pid<<endl;
	cout<<"Product Category: "<<pcat<<endl;
	cout<<"Product Name: "<<pname<<endl;
	cout<<"No. of Units: "<<units<<endl;
	cout<<"Price per Unit: "<<p_price<<"\n\n";
	char nm[30]="",ch,op;
	int qty;
	float cost;
	cout<<"New Product Name:(Enter '.'to retain old one):";
	cin>>nm;
	cout<<"Do you want to update quantity:(Y/N)";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		cout<<"Enter Quantity to add/subtract:";
		cin>>qty;
		cout<<"Enter '+' for add or '-' for subtract from existing quantity :";
		cin>>op;
		if(op=='+')
		{
			units+=qty;
		}
		else
		{
			if(units==0)
			{
				cout<<"\nStock Empty!\nCannot subtract\n\n";
			}
			else
			{
				while(units-qty<0)
				{
					cout<<"Not enough Stock Available!!\n";
					cout<<"Current Stock:"<<units<<endl;
					cout<<"Enter Appropriate Quantity:";
					cin>>qty;
				}
				units-=qty;
			}	
		}
		if(units<z)
			check_stock();
		status_check();
	}
	cout<<"New Price:(Enter -1 to retain old one):";
	cin>>cost;
	if(strcmp(nm,".")!=0)
		strcpy(pname,nm);
	if(cost!=-1)
		p_price=cost;
}

void mainmenu()
{
	stock ob,ob1;
	//customer ob2;
	system("cls");
	int choice,id;
	char found;
	do
	{
		system("cls");
		cout<<"-------->INVENTORY MANAGEMENT<--------\n\n";
		cout<<"         1.ADD an item\n";
		cout<<"         2.MODIFY an item\n";
		cout<<"         3.SEARCH an item\n";
		cout<<"         4.DELETE an item\n";
		cout<<"         5.SHOW stock details\n";
		cout<<"         6.SALE item\n";
		cout<<"         7.BACK to previous MENU\n";
		cout<<"\n       Enter your Choice :";
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				int check;
				system("cls");
				char ch;
				ofstream outfile;
				ifstream infile;
				do
				{
					outfile.open("stock.txt",ios::app|ios::binary);	
					while(1)
					{
						check=0;
						ob1.input_id();
						infile.open("stock.txt",ios::in|ios::binary);
						while(!infile.eof())
						{
							infile.read((char *)&ob,sizeof(ob));
							if(ob1.get_id()==ob.get_id())
							{
								cout<<"Duplicate Product ID is not allowed!\n";
								cout<<"Enter Unique Product ID\n";
								check=1;
								break;
							}
						}
						if(check==0)
						{
							ob1.add_item();
							outfile.write((char *)&ob1,sizeof(ob1));
							break;
						}
						else
						{
							infile.close();
						}
					}
					infile.close();
					outfile.close();
					cout<<"Do you want to insert any more:(y/n):";
					cin>>ch;	
				}while(ch=='y'||ch=='Y');
			}	break;
			case 2:
			{
				system("cls");
				found='f';
				long pos;
				fstream fio("stock.txt",ios::in|ios::out|ios::binary);
				cout<<"Enter ID of the product to modify :";
				cin>>id;
				while(!fio.eof())
				{
					pos=fio.tellg();
					fio.read((char *)&ob1,sizeof(ob1));
					if(ob1.get_id()==id)
					{
						fio.seekg(pos);
						ob1.update_item();
						fio.write((char *)&ob1,sizeof(ob1));
						found='t';
						cout<<"DATA UPDATED.\n";
						system("pause");
						fio.close();
						break;
					}
				}
				if(found=='f')
				{
					cout<<"Product ID doesn't exist!!\n";
					system("pause");
				}
			}	break;
			case 3:
			{
				system("cls");
				found='f';
				cout<<" Enter ID of the product to search : ";
				cin>>id;
				ifstream infile;
				infile.open("stock.txt",ios::in|ios::binary);
				while(!infile.eof())
				{
					infile.read((char *)&ob1,sizeof(ob1));
					if(ob1.get_id()==id)
					{
						ob1.show_stock();
						cout<<' ';
						system("pause");
						found='t';
						infile.close();
						break;
					}
				}
				if(found=='f')
				{
					cout<<" Product ID doesn't exist!!\n ";
					system("pause");
				}
			}	break;
			case 4:
			{
				system("cls");
				ifstream fio;
				fio.open("stock.txt",ios::in|ios::binary);
				ofstream file;
				file.open("temp.txt",ios::out|ios::binary);
				int id;
				char found='f',confirm='n';
				cout<<"Enter ID of the product to delete : ";
				cin>>id;
				while(!fio.eof())
				{
					if(fio.read((char *)&ob1,sizeof(ob1)))
					{
						if(ob1.get_id()==id)
						{
							ob1.show_stock();
							found='t';
							cout<<"Are you sure, you want to delete this record?(y/n)..";
							cin>>confirm;
							if(confirm=='n')
								file.write((char *)&ob1,sizeof(ob1));
						}
						else
							file.write((char *)&ob1,sizeof(ob1));
					}
				}
				if(found=='f')
					cout<<"Record not found!!\n";
				fio.close();
				file.close();
				remove("stock.txt");
				rename("temp.txt","stock.txt");
				system("pause");
			}	break;
			case 5:
			{
				system("cls");
				ifstream infile;
				infile.open("stock.txt",ios::in|ios::binary);
				while(infile.read((char *)&ob1,sizeof(ob1)))
				{
					ob1.show_stock();
					cout<<endl;
				}
				cout<<' ';
				system("pause");
				infile.close();
			}	break;
			case 6:
			{
				system("cls");
				found='f';
				quantity=0;
				tot_amt=0;
				long pos;
				char more;
				do
				{
					fstream fio("stock.txt",ios::in|ios::out|ios::binary);
					cout<<"Enter ID of the product to sale :";
					cin>>id;
					while(!fio.eof())
					{
						pos=fio.tellg();
						fio.read((char *)&ob1,sizeof(ob1));
						if(ob1.get_id()==id)
						{
							fio.seekg(pos);
							ob1.sale();
							fio.write((char *)&ob1,sizeof(ob1));
							found='t';
							cout<<"DATA UPDATED.\n";
							system("pause");
							fio.close();
							break;
						}
					}
					if(found=='f')
					{
						cout<<"\nProduct ID doesn't exist!!\n";
						system("pause");
					}
					cout<<"\nSale another product :(y/n).. ";
					cin>>more;
				}while(more=='y'||more=='Y');
				cout<<"\nTotal Quantity Purchased : "<<quantity<<endl;
				cout<<"Total Amount : "<<tot_amt<<endl;
				system("pause");
			}	break;
		}	
	}while(choice!=7);
}
void help()
{
	system("cls");
	cout<<"------->INSTRUCTIONS<-------\n\n";
	cout<<"1.Every Product should have unique PRODUCT ID\n\n";
	cout<<"2.The program will not allow duplicate PRODUCT ID\n\n";
	cout<<"3.The Program will generate a warning message followed by an action where you   can add items to a product whose units are below 50\n\n";
	cout<<"4.Make sure to keep your STOCK STATUS : SAFE to avoid dead stock\n\n";
	system("pause");
}
main()
{
	quantity=0;
	tot_amt=0;
	z=50;
	cout<<"\nThe Program will generate a warning message followed by an action where you can add items to a product whose units are below "<<z<<".\n\n";
	system("pause");
	system("cls");

	int choice;
	do
	{
		system("cls");
		cout<<"-------->INVENTORY MANAGEMENT<--------\n\n";
		cout<<"         1.MAIN MENU\n";
		cout<<"         2.INSTRUCTIONS\n";
		cout<<"         3.EXIT\n";
		cout<<"\n       Enter your choice :";
		cin>>choice;
		switch(choice)
		{
			case 1:mainmenu();
				   break;
			case 2:help();
				   break;
		    case 3:cout<<"Exit\n";
			 	   break;
			default:cout<<"INVALID ENTRY\n\n";
				   system("pause");			   					
		}		
	}while(choice!=3);

}

