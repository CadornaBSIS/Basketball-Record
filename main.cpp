//ADT List of players usig array of structures
#include <iostream> //Used for input and output.
#include <stdlib.h>
#include <fstream>  //This library is used for file handling.
#include <sstream>  //Used to manipulate strings as I/O streams.
#include <iomanip>  //Used in setting width of output to align them.
#include <cstring>
#define MAX 15   //MAX number is defined.
using namespace std;
typedef struct players {
   string name;
   int fga,fgm;
}REC;
//DATA STRUCTURE
typedef struct adtlist {
    REC bp[MAX];
    int last;
}LIST;
//Class definition
class MyList {
private:
    LIST L;
    bool isfull();
    bool isempty();
    int locate(string n);
    int locatePos(string n);
    double computeFGP(int a, int m);
public:
    void makenull();
    void insertSort(REC r);
    void del(string n);
    void display();
    void update(string n);//update the fga and/or fgm only given the name of the record
    void save();
    void retrieve();
};
int menu();
void MyList::insertSort(REC r){
int p,i;
if(isfull()){
    cout<<"List is full.\n";
    system("pause");
}
else {
    p = locatePos(r.name);
    for(i=L.last;i>=p;i--){
        L.bp[i+1]=L.bp[i];
    }
    L.bp[p] = r;
    L.last++;
}

}
void MyList::update(string n) {
    int p;
    if (isempty()) {
        cout << "Array is empty.";
        system("pause");
    }
    else {
        p = locate(n);
        if (p == -1) {
            cout << "Data not found.";
            system("pause");
        }
        else {
            int edit_info;
            while (true) {
                system("cls");
                cout << "Edit Mode for " << n << ":\n";
                cout << "1. Edit FGA\n";
                cout << "2. Edit FGM\n";
                cout << "3. Back to Main Menu\n";
                cout << "1 to 3 lang!: ";
                cin >> edit_info;

                switch (edit_info)
                {
                case 1:
                    cout << "Insert new FGA: ";
                    cin >> L.bp[p].fga;
                    cout << "FGA was successfully updated.";
                    system("pause");
                    break;
                case 2:
                    cout << "Insert new FGM: ";
                    cin >> L.bp[p].fgm;
                    cout << "FGM was successfully updated.";
                    system("pause");
                    break;
                case 3:
                    return;
                default:
                    cout << "Mali!, 1 to 3 lang.";
                    system("pause");
                }
            }
        }
    }
}




void MyList::del(string n)
{
int p,i;
if (isempty()){
    cout<<"Array is empty.\n";
    system("pause");
}
else {
    p=locate(n);
    if (p==-1){
        cout<<"Data not found.\n";
        system("pause");
    }
    else {
        for (i=p;i<L.last;i++){
            L.bp[i]=L.bp[i+1];
            //display();
        }
        L.last--;
        cout<<"Record was successfully deleted.\n",n;
        system("pause");
    }
}

}
bool MyList::isempty(){
  return (L.last==-1);
}
bool MyList::isfull(){
return (L.last==MAX-1);
}
int MyList::locate(string n){
int i;
for (i=0;i<=L.last;i++){
    if (n==L.bp[i].name)
        return i;
   }
return -1;//not found
}
int MyList::locatePos(string n){
int i;
for (i=0;i<=L.last;i++){
    if (n<L.bp[i].name)
        return i;
}
return i;//or return L.last+1;
}
void MyList::display(){
double fgp;
string remarks;
int i;
system("cls");
cout << setw(24) << left << "Name" << setw(19) << left << "FGA" << setw(22) << left  << "FGM" << setw(18) << left  << "FGP(%)" << setw(14) << left  << "REMARKS" << endl;
for (i=0;i<=L.last;i++){
    fgp = computeFGP(L.bp[i].fga, L.bp[i].fgm);
    remarks = fgp>50? "HIGH" : "LOW";
    cout <<i+1<<".) "<<setw(20)<<left<<L.bp[i].name<<setw(20)<<left<<L.bp[i].fga<<setw(20)<<left<<L.bp[i].fgm<<setw(20)<<setprecision(2)<<fixed<<fgp<<setw(20)<<left<<remarks<<endl;
}
system("pause");
}
double MyList::computeFGP(int a, int m){
return (double)m/a*100.0;
}
void MyList::makenull(){
L.last=-1;
}
int main(){
MyList pl;
REC pd;
string NtoDel;
pl.makenull();//initialize the list
pl.retrieve();//retrieve the data from file and insertSort to the list
while(true){
    switch(menu()){
    case 1: system("cls");cout <<"Insert Mode\n";
            cout<<"Input Name: ";getline(cin>>ws, pd.name);
            cout<<"Input FGA: ";cin >> pd.fga;
            cout<<"Input FGM: ";cin >> pd.fgm;
            pl.insertSort(pd);break;
    case 2: cout<<"Update Mode\n";cout<<"Input Name To Update: ";cin>>NtoDel;;pl.update(NtoDel);break;
    case 3: cout<<"Delete Mode\n";cout<<"Input Name: ";cin>>NtoDel;;pl.del(NtoDel);break;

    case 4: pl.display();break;
    case 5: pl.save();exit(0);
    default: cout<<"1 to 4 only.\n";system("pause");

    }

}
}
int menu(){
int op;
system("cls");
cout<<"MENU\n";
cout<<"1. Add a Record\n";
cout<<"2. Update a Record\n";
cout<<"3. Delete a Record\n";
cout<<"4. Display All Records\n";
cout<<"5. Exit\n";
cout<<endl<<"Select(1-5): ";
cin >>op;
return op;
}
void MyList::save() //This function is used to save the record into a text file.
{
    int i;

    ofstream fileptr("data2.txt"); //The file is opened.

    for(i = 0; i <= L.last; i++)  //Using a loop, the contents of the array of structures is written into a text file.
    {
        if(i == L.last)
        {
            fileptr << L.bp[i].name << endl << L.bp[i].fga  << " " << L.bp[i].fgm; //If it's the last index of the array there is no endl at the end to avoid unnecessary spaces at the end of the file.
        }
        else
        {
            fileptr << L.bp[i].name << endl << L.bp[i].fga  << " " << L.bp[i].fgm << endl;
        }
    }
    fileptr.close();   //After writing the data, the file is closed.
    system("cls");
    cout << "The records have been saved successfully!" << endl;
}

void MyList::retrieve() //This function is used to retrieve data from a text file.
{
    string firstn;  //This will be used to store the first name of a player.
    string lastn;   //This will be used to store the last name of a player(if there is any).
    ifstream fileptr("data2.txt"); //The file is opened.
    if(fileptr.is_open()) //The various operations will only run if the file is indeed open.
    {
        REC d;  //Using REC, a structure is declared.
        string line; //This will be used in handling the contents of t he file.
        int strline = 0; //This variable will be used to keep track of the current line number.
        while(getline(fileptr, line)) //The loop will run as long as there is a line to be read.
        {
            istringstream data(line); //istringstream is used to handle the strings/lines like an input stream.
            if((strline%2)==0) //If the current line number is 0 or an even number it means that the current line holds the name of the player.
            {

                data >> firstn >> lastn; //If there are two strings in the current line, they will be stored to firstn and lastn accordingly.
                if(lastn.empty())   //If lastn is empty, only the contents of firstn will be transferred to the structure.
                {
                    d.name = firstn; //This step is done to prevent errors in handling the strings in the program(specifically the delete part).
                }
                else
                {
                    d.name = firstn + " " + lastn; //If lastn is not empty, firstn, a white space, and lastn will be assigned to d.name.
                    firstn ="";lastn="";
                }
            }
            else //If the current line number is an odd number, it means that it is where the FGA and FGM are written.
            {
                data >> d.fga >> d.fgm; //The FGA and FGM are stored in the structure accordingly.
                insertSort(d);
            }

            strline++; //This value is incremented to determine the current line number.
        }
        cout << "File is read successfully." << endl; //A message is displayed after retrieving the contents of the file.
    }
    else
    {
        cout << "There is no existing record." << endl; //If there is no file, a message will appear.
    }
    fileptr.close(); //The file is closed.
    cout << endl;
    system("pause");
}
