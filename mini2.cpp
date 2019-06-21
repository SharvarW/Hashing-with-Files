/* 
# MINIPROJECT : FILE HANDLING WITH LINEAR HASHING
# ---------------------------------------------------
# PROJECT TEAM :
# 
#	SONIKA ADGAONKAR 	SE(A) - 01
#	YASHASHREE SURYAWANSHI 	SE(A) - 69
#	OJASWINI TANK 		SE(A) - 70
#	SHARVARI WAGH 		SE(A) - 73
# --------------------------------------------------
*/

#include<iostream>		//header files
#include<string.h>
#include<fstream>
using namespace std;

class student
{
	public :
		int iRoll_no;
		char cName[20];
		student()
		{
			iRoll_no=0;
			strcpy(cName," ");
		}
		void getdata()
		{
			cout<<"\n Enter Name of student : ";
			cin>>cName;
			cout<<"\n Enter Roll No. of student : ";
			cin>>iRoll_no;
		}
		void display(int i)
		{
			cout<<"\n "<<i<<"\t\t"<<iRoll_no<<"\t\t"<<cName;
		}
};

int hash(int iKey)
{
	return iKey%20;
}

int main()
{
	student s,p;
	int iOption,i,iKey,iFlag,iCount=1;
	char filename[50];
	char cChoice;
	long lPos,lFpos;
	fstream f;
	cout<<"\n=======================================\n";
	cout<<"\n 1. Create new file \n 2. Use existing file \n Enter your Choice : ";
	cin>>iOption;
	cout<<"\n=======================================\n";
	if(iOption==1)
	{
		cout<<"\n Enter filename : ";
		cin>>filename;
		f.open(filename,ios::out | ios::binary);
		for(i=0;i<20;i++)
		f.write((char*)&s,sizeof(s));
		f.close();
	}
	if(iOption==2)
	{
		cout<<"\n Enter filename : ";
		cin>>filename;
	}
	f.open(filename,ios::in | ios::out | ios::binary);
	do
	{
	here:	cout<<"\n============================\n";
		cout<<"\n\t  MENU";
		cout<<"\n============================\n";
		cout<<"\n 1. Insert \n 2. Display \n 3. Modify \n 4. Search \n 5. Delete \n 6. Exit";
		cout<<"\n============================\n";
		cout<<" \n Enter your choice : ";
		cin>>iOption;
		cout<<"\n============================\n";
		switch(iOption)
		{
			case 1 :
					iFlag=0;
					iCount=0;
					s.getdata();
					lPos=hash(s.iRoll_no);
					lPos=lPos*sizeof(s);
					f.seekg(lPos);
					while(1)
					{
						f.read((char*)&p,sizeof(p));
						if(p.iRoll_no==0)
						{
							f.seekp(lPos);
							f.write((char*)&s,sizeof(s));
							iFlag=1;
							break;
						}
						else
						lPos=(lPos+sizeof(s))%480;
						iCount++;
						if(iCount==20)
						break;
					}
					if(iFlag==1)
					cout<<"\n Insertion Successful.";
					else
					cout<<"\n Insertion failed.";
					break;
			case 2 :
					f.seekg(0,ios::beg);
					cout<<"\n Index\t\tRoll-no\t\tName\n";
					for(i=0;i<20;i++)
					{
						f.read((char*)&p,sizeof(p));
						p.display(i);
					}
					break;
			case 3 :
					iFlag=0;
					iCount=0;
					cout<<"\n Enter Roll No. whose data is to be modified : ";
					cin>>iKey;
					lPos=hash(iKey);
					lPos=lPos*sizeof(s);
					f.seekg(lPos);
					f.read((char*)&p,sizeof(p));
					while(1)
					{
						if(p.iRoll_no==iKey)
						{
							f.seekp(lPos);
							cout<<"\n------Enter new data--------\n";
							cout<<"\n Enter new Name : ";
							cin>>s.cName;
							s.iRoll_no=p.iRoll_no;
							f.write((char*)&s,sizeof(s));
							iFlag=1;
							break;
						}
						else
						lPos=(lPos+sizeof(s))%480;
						f.read((char*)&p,sizeof(p));
						if(iCount==20)
						break;
					}
					if(iFlag==1)
					cout<<"\n Data modified successfully.";
					else
					{
						cout<<"\n Data not found";
						f.close();
						f.open(filename,ios::in | ios::out | ios::binary);
					}
					break;
			case 4 :
					iFlag=0;
					iCount=0;
					cout<<"\n Enter Roll no. whose data is to be searched : ";
					cin>>iKey;
					lPos=hash(iKey);
					lPos=lPos*sizeof(s);
					f.seekg(lPos);
					f.read((char*)&p,sizeof(p));
					while(1)
					{
						if(p.iRoll_no==iKey)
						{
							f.seekg(lPos);
							cout<<"\n Name : "<<p.cName;
							iFlag=1;
							break;
						}
						else
						lPos=(lPos+sizeof(s))%480;
						f.read((char*)&p,sizeof(p));
						if(iCount==20)
						break;
					}
					if(iFlag==0)
					{
						cout<<"\n Data not found.";
						f.close();
						f.open(filename,ios::in | ios::out | ios::binary);
					}
					break;
			case 5 :
					iFlag=0;
					iCount=0;
					cout<<"\n Enter Roll No. whose data is to be deleted : ";
					cin>>iKey;
					lPos=hash(iKey);
					lPos=lPos*sizeof(s);
					f.seekg(lPos);
					f.read((char*)&p,sizeof(p));
					while(1)
					{
						if(p.iRoll_no==iKey)
						{
							f.seekp(lPos);
							s.iRoll_no=0;
							strcpy(s.cName," ");
							f.write((char*)&s,sizeof(s));
							iFlag=1;
							break;
						}
						else
						lPos=(lPos+sizeof(s))%480;
						f.read((char*)&p,sizeof(p));
						if(iCount==20)
						break;
					}
					if(iFlag==1)
					cout<<"\n Data deleted successfully.";
					else
					{
						cout<<"\n Data not found";
						f.close();
						f.open(filename,ios::in | ios::out | ios::binary);
					}
					break;
			default:	cout<<"\nINVALID CHOICE!!!";
					goto here;
		}
	}while(iOption!=5);
	return 0;
	f.close();
}



