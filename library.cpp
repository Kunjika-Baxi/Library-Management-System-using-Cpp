#include<iostream>
#include<fstream>
using namespace std;
int cps,cp;
class Library 
{
   public : 
   string bname,aname;int qty,sqty,pgs;
   void get()
   {
      cout<<"\n\t-----Enter Book Details-----";
      cout<<"\nEnter Book Name : ";
      cin>>bname;
      cout<<"\nEnter Author Name : ";
      cin>>aname;
      cout<<"\nEnter Total Number of Pages : ";
      cin>>pgs;
      cout<<"\nEnter Total Copies : ";
      cin>>qty;sqty=qty;
   }
   void display()
   {
       cout<<"\n-------------------------------------\n";
       cout<<"\n\t---Details--- ";
       cout<<"\nBook Name : "<<bname;
       cout<<"\nAuthor Name : "<<aname;
       cout<<"\nPages : "<<pgs;
       cout<<"\nTotal Copies : "<<qty;
       cout<<"\n-------------------------------------\n";
   }
};
Library l;
void write()
{
    ofstream fout;
    fout.open("Library.dat",ios::app|ios::binary);
    l.get();
    fout.write((char*)&l,sizeof(l));
    fout.close();
    cout<<"\nData Added Successfully...";
}
void read()
{
    ifstream fin;
    fin.open("Library.dat",ios::in|ios::binary);
    while(fin.read((char*)&l,sizeof(l)))
    {
        l.display();
    }
    fin.close();
}
void search()
{
    fstream fin;
    int flag=0;string bookn;
    fin.open("Library.dat",ios::in|ios::binary);
    cout<<"\nEnter the Book Name : ";
    cin>>bookn;
    while(fin.read((char*)&l,sizeof(l)))
    {
        if(l.bname==bookn)
        {
            flag=1;
            cout<<"\nRecord Found";
            l.display();
            break;
        }
    }
    if(flag==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    fin.close();
}

void update()
{
    int fl=0;string bookname;char ans,cho;
    fstream f;
    f.open("Library.dat",ios::out|ios::in|ios::binary);
    cout<<"\nEnter the Book Name whose details you want to update : ";
    cin>>bookname;
    while(f.read((char*)&l,sizeof(l)))
    {
        if(l.bname==bookname)
        {
            fl=1;
            cout<<"\nRecord Found";
            cout<<"\nEnter the Updated Copies : ";cin>>cp;
            int t=f.tellp();
            l.qty=cp;
            f.seekp(t-sizeof(l));
            f.write((char*)&l,sizeof(l));
            cout<<"\nIs any Copy given to Student ? (y/n) : ";
            cin>>ans;
            if(ans=='y'||ans=='Y')
            {
                while(1)
                {
                cout<<"\nEnter Number of Copies Given to Student : ";
                cin>>cps;
                if(cps<=(l.sqty-cp))
                {
                    break;
                }
                else
                {
                    cout<<"\nEnter Valid Number of Copies";
                }
                }
                cout<<"\nDo you want to View the Record of Unavilable Copies ? (y/n) : ";
                cin>>cho;
                if(cho=='y'||cho=='Y')
                {
                    cout<<"\nTotal Copies Given to Student : "<<cps;
                    cout<<"\nNumber of Copies not Available as well as Not given to Student : "<<(l.sqty-cp-cps)<<endl;
                }

            }
            cout<<"\nData Updated Successfully.....\n";
            break;
        }
    }
    if(fl==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    f.close();
}
void delete_specific()
{
    int fl=0;string bn;
    fstream f;
    f.open("Library.dat",ios::in|ios::binary);
    ofstream fout;
    fout.open("new.dat",ios::app|ios::binary);
    cout<<"\nEnter Book Name whose data you want to delete : ";
    cin>>bn;
    while(f.read((char*)&l,sizeof(l)))
    {
        if(l.bname!=bn)
        {

            fout.write((char*)&l,sizeof(l));
        }
        else{
            fl=1;
        }
    }
    f.close();
    fout.close();
    remove("Library.dat");
    rename("new.dat","library.dat");
    cout<<"\nSuccessful...\n";

}
int main()
{
    int ch;
    remove("Library.dat");
    while(1)
    {
        cout<<"\nEnter : \n1.Add Books\n2.Display All Books\n3.Search Specific Book\n4.Update Specific Book\n5.Delete Book\n6.Exit";
        cout<<"\nEnter Your Choice : ";
        cin>>ch;
        switch(ch)
        {
            case 1:write();break;
            case 2:read();break;
            case 3:search();break;
            case 4:update();break;
            case 5:delete_specific();break;
            case 6:exit(0);break;  
            default:cout<<"\nInvalid Choice";
        }
    }
}