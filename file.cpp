#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<string>
using namespace std;

string record;


//*************************____ [  START ] clerk __________ ******************
class clerk
{
public:
    string id;
    string name;
    void setData();
    void getData();
    void pack();
    void unpack();
    void insert();
    void search(string key);
    void update(string key);
    void deleteD(string key);
    void display();
};

void clerk::setData()
{
    cout << "Enter ID" << endl;
    cin >> id;
    cout << "Enter Name" << endl;
    cin >> name;
}
void clerk::getData()
{
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "_______________________" << endl;
}
void clerk::pack()
{
    record = id + "|" + name + "#\n";
}
void clerk::unpack()
{
    int pos;

    pos = record.find("|");
    id = record.substr(0, pos);

    record = record.substr(pos + 1);
    pos = record.find("#");
    name = record.substr(0, pos);
}

void clerk::insert()
{
    fstream file;
    file.open("clerk.txt", ios::out | ios::app);
    setData();
    pack();
    file << record;
    file.close();
}
void clerk::display()
{
    fstream file;
    file.open("clerk.txt", ios::in);
    while (getline(file, record))
    {
        unpack();
        getData();
    }
    file.close();
}
void clerk::search(string key)
{
    int pos = -1;
    int count = 0;
    fstream file;
    file.open("clerk.txt", ios::in);

    while (!file.eof())
    {
        getline(file, record);
        count++;
        if (file.fail()) break;
        unpack();
        if (id == key)
        {
            pos = count;
            break;
        }
    }
    file.close();

    if (pos == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at postion " << pos << endl;
        getData();
    }
}

void clerk::update(string key)
{
    fstream in_file;
    fstream out_file;
    in_file.open("clerk.txt", ios::in);
    out_file.open("temp.txt", ios::out);

    while (getline(in_file, record))
    {
        unpack();
        if (key == id)
        {
            setData();
        }
        pack();
        out_file << record;
    }
    in_file.close();
    out_file.close();

    remove("clerk.txt");
    rename("temp.txt", "clerk.txt");
}

void clerk::deleteD(string key)
{
    fstream in_file;
    fstream out_file;
    in_file.open("clerk.txt", ios::in);
    out_file.open("temp.txt", ios::out);

    while (getline(in_file, record))
    {
        unpack();
        if (key == id)
        {
            continue;
        }
        pack();
        out_file << record;
    }
    in_file.close();
    out_file.close();

    remove("clerk.txt");
    rename("temp.txt", "clerk.txt");
}
//*************************____ [  END ] clerk __________ ******************

//*************************____ [  START ] contact __________ ******************
class contact
{
private:
    string c_id;
    string c_name;
    string address;
    float number;
    string clr_ID;
public:
    void setData();
    void getData();
    void pack();
    void unpack();
    void insert();
    void search(string key);
    void update(string key);
    void deleteD(string key);
    void display();
};

void contact::setData()
{
    cout << "Enter ID" << endl;
    cin >> c_id;
    cout << "Enter Name" << endl;
    cin >> c_name;
    cout << "Enter ADDRESS" << endl;
    cin >> address;
    cout << "Enter number" << endl;
    cin >> number;
    cout << "Enter clerk ID" << endl;
    cin >> clr_ID;
}
void contact::getData()
{
    cout << "ID: " << c_id << endl;
    cout << "Name: " << c_name << endl;
    cout << "Address: " << address << endl;
    cout << "number: " << number << endl;
    cout << "clerk ID: " << clr_ID << endl;
    cout << "_______________________" << endl;
}
void contact::pack()
{
    record = c_id + "|" + c_name + "|" + address + "|" + to_string(number) + "|" + clr_ID + "#\n";
}
void contact::unpack()
{
    int pos;

    pos = record.find("|");
    c_id = record.substr(0, pos);

    record = record.substr(pos + 1);
    pos = record.find("|");
    c_name = record.substr(0, pos);

    record = record.substr(pos + 1);
    pos = record.find("|");
    address = record.substr(0, pos);

    record = record.substr(pos + 1);
    pos = record.find("|");
    number = stof(record.substr(0, pos));

    record = record.substr(pos + 1);
    pos = record.find("#");
    clr_ID = record.substr(0, pos);
}

void contact::insert()
{
    fstream file, file1;
    clerk obj;
    file.open("contact.txt", ios::out | ios::app);
    file1.open("clerk.txt", ios::in);
    setData();
    bool clerkExists = false;


    while (getline(file1, record))
    {
        obj.unpack();
        if (obj.id == clr_ID)
        {
            clerkExists = true;
            break;
        }
    }

    if (clerkExists) {
        pack();
        file << record;
        cout << "contact added successfully." << endl;
    } else {
        cout << "clerk not found!" << endl;
    }

    file.close();
    file1.close();
}

void contact::display()
{
    fstream file;
    file.open("contact.txt", ios::in);
    while (getline(file, record))
    {
        unpack();
        getData();
    }
    file.close();
}
void contact::search(string key)
{
    int pos = -1;
    int count = 0;
    fstream file;
    file.open("contact.txt", ios::in);

    while (!file.eof())
    {
        getline(file, record);
        count++;
        if (file.fail()) break;
        unpack();
        if (c_id == key)
        {
            pos = count;
            break;
        }
    }
    file.close();

    if (pos == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at postion " << pos << endl;
        getData();
    }
}

void contact::update(string key)
{
    fstream in_file, out_file;
    in_file.open("contact.txt", ios::in);
    out_file.open("temp.txt", ios::out);

    bool updated = false;
    while (getline(in_file, record))
    {
        unpack();
        if (key == c_id)
        {
            setData(); // تحديث البيانات
            updated = true;
        }
        pack();
        out_file << record;
    }

    in_file.close();
    out_file.close();

    if (updated) {
        remove("contact.txt");
        rename("temp.txt", "contact.txt");
        cout << "contact updated successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "contact not found!" << endl;
    }
}

void contact::deleteD(string key)
{
    fstream in_file, out_file;
    in_file.open("contact.txt", ios::in);
    out_file.open("temp.txt", ios::out);

    bool deleted = false;
    while (getline(in_file, record))
    {
        unpack();
        if (key != c_id) {
            pack();
            out_file << record;
        } else {
            deleted = true;
        }
    }

    in_file.close();
    out_file.close();

    if (deleted) {
        remove("contact.txt");
        rename("temp.txt", "contact.txt");
        cout << "contact deleted successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "contact not found!" << endl;
    }
}

//*************************____ [  END ] contact __________ ******************


//*************************________ [  START ] job _________ *****************
class job
{
    private:
    string j_id;
    string j_name;
    string j_address;
    double salary;
    string clr_ID;
    string con_ID;
public:
    void setData();
    void getData();
    void pack();
    void unpack();
    void insert();
    void search(string key);
    void update(string key);
    void deleteD(string key);
    void display();
};

void job::setData()
{
    cout << "Enter ID" << endl;
    cin >> j_id;
    cout << "Enter Name" << endl;
    cin >> j_name;
    cout << "Enter ADDRESS" << endl;
    cin >> j_address;
    cout << "Enter salary" << endl;
    cin >> salary;
    cout << "Enter clerk ID" << endl;
    cin >> clr_ID;
     cout << "Enter contact ID" << endl;
    cin >> con_ID;
}
void job::getData()
{
    cout << "Job ID: " << j_id << endl;
    cout << "Job Name: " << j_name << endl;
    cout << "Job Address: " << j_address << endl;
    cout << "salary: " << salary << endl;
    cout << "clerk ID: " << clr_ID << endl;
    cout << "contact ID: " << con_ID << endl;
    cout << "_______________________" << endl;
}
void job::pack()
{
    record = j_id + "|" + j_name + "|" + j_address + "|" + to_string(salary) + "|" + clr_ID + con_ID + "#\n";
}
void job::unpack()
{
    int pos;

    pos = record.find("|");
    j_id = record.substr(0, pos);

    record = record.substr(pos + 1);
    pos = record.find("|");
    j_name = record.substr(0, pos);

    record = record.substr(pos + 1);
    pos = record.find("|");
    j_address = record.substr(0, pos);

    record = record.substr(pos + 1);
    pos = record.find("|");

    record = record.substr(pos + 1);
    pos = record.find("#");
    clr_ID = record.substr(0, pos);
}

void job::insert()
{
    fstream file, file1;
    clerk obj;
    file.open("contact.txt", ios::out | ios::app);
    file1.open("clerk.txt", ios::in);
    setData();
    bool clerkExists = false;


    while (getline(file1, record))
    {
        obj.unpack();
        if (obj.id == clr_ID)
        {
            clerkExists = true;
            break;
        }
    }

    if (clerkExists) {
        pack();
        file << record;
        cout << "contact added successfully." << endl;
    } else {
        cout << "clerk not found!" << endl;
    }

    file.close();
    file1.close();
}

void job::display()
{
    fstream file;
    file.open("job.txt", ios::in);
    while (getline(file, record))
    {
        unpack();
        getData();
    }
    file.close();
}
void job::search(string key)
{
    int pos = -1;
    int count = 0;
    fstream file;
    file.open("job.txt", ios::in);

    while (!file.eof())
    {
        getline(file, record);
        count++;
        if (file.fail()) break;
        unpack();
        if (j_id == key)
        {
            pos = count;
            break;
        }
    }
    file.close();

    if (pos == -1)
    {
        cout << "Not found" << endl;
    }
    else
    {
        cout << "Found at postion " << pos << endl;
        getData();
    }
}

void job::update(string key)
{
    fstream in_file, out_file;
    in_file.open("job.txt", ios::in);
    out_file.open("temp.txt", ios::out);

    bool updated = false;
    while (getline(in_file, record))
    {
        unpack();
        if (key == j_id)
        {
            setData(); // تحديث البيانات
            updated = true;
        }
        pack();
        out_file << record;
    }

    in_file.close();
    out_file.close();

    if (updated) {
        remove("job.txt");
        rename("temp.txt", "job.txt");
        cout << "job updated successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "job not found!" << endl;
    }
}

void job::deleteD(string key)
{
    fstream in_file, out_file;
    in_file.open("job.txt", ios::in);
    out_file.open("temp.txt", ios::out);

    bool deleted = false;
    while (getline(in_file, record))
    {
        unpack();
        if (key != j_id) {
            pack();
            out_file << record;
        } else {
            deleted = true;
        }
    }

    in_file.close();
    out_file.close();

    if (deleted) {
        remove("job.txt");
        rename("temp.txt", "job.txt");
        cout << "job deleted successfully." << endl;
    } else {
        remove("temp.txt");
        cout << "job not found!" << endl;
    }
}

//*************************________ [  END ] job _________ *****************/
//declartion function "introduction"
void introduction();
int main()
{
    system("color 72");
    clerk clr; 
    contact con;
    job jo;
    char ch, chPass;
    introduction();
    string key;
    int option;
again: //لو اليوزر دخل قيمة غلط للname وال password ارجع تاني للصفحة الرئيسية
    string pass = "", username;
    cout << "Enter Your Username" << endl;
    cin >> username;
    cout << "Enter Your Password" << endl;
    chPass = _getch();
    while (chPass != '\r') //لو اليوزر دخل قيمة للباسوورد ومسابهوش فاضي
    {
        pass += chPass; //زود char كل مرة
        cout << "*";  //اطبع * عشان الباسوورد
        chPass = _getch(); //caling للفنكشن اللي هتخلينا ندخل الباسوورد
    }


    if (pass == "123456" && username == "contact")
    {
        system("cls"); //clear screen 
    home: //home scope
        cout << "1- clerk" << endl;
        cout << "2- contact" << endl;
        cout << "3- job" << endl;
        cout << "4- exit" << endl;
        cout << "\t\t\tEnter Your option" << endl;
        cin >> option;
    }
    else
    {
        system("cls");
        cout << "Incorrect Password Or Username" << endl;
        goto again;
    }
    if (option == 1)
    {
        goto D; //clerk scope
    }
    else if (option == 2)
    {
        goto S; //contact scope
    }
    else if (option == 3)
    {
        goto J; //job scope
    }
     else if (option == 4)
        exit(0);

    else
    {

        system("cls");
        cout << "Incorrect Option" << endl;
        goto home;
    }

D: //scope clerk
    do
    {
        system("cls");
        cout << "1- Insert" << endl;
        cout << "2- Search" << endl;
        cout << "3- Update" << endl;
        cout << "4- Delete" << endl;
        cout << "5- Display" << endl;
        cout << "6- back" << endl;
        int choice;
        cout << "\n\t\t Enter your choice " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            clr.insert();
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            clr.search(key);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            clr.update(key);
            break;
        }

        case 4:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            clr.deleteD(key);
            break;
        }

        case 5:
        {
            system("cls");
            clr.display();
            break;
        }
        case 6:
        {
            system("cls");
            goto home;
            break;
        }
        default:
        {
            system("cls");
            cout << "invalid choice" << endl;

        }
        }

        cout << "\n \t &&&&&&&&&&&&&&&&&&&&&& To return to a menu Enter (y,Y)" << endl;
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

S: //scope contact
    do
    {
        system("cls");
        cout << "1- Insert" << endl;
        cout << "2- Search" << endl;
        cout << "3- Update" << endl;
        cout << "4- Delete" << endl;
        cout << "5- Display" << endl;
        cout << "6- back" << endl;
        int choice;
        cout << "\n\t\t Enter your choice " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            con.insert();
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            con.search(key);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            con.update(key);
            break;
        }

        case 4:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            con.deleteD(key);
            break;
        }

        case 5:
        {
            system("cls");
            con.display();
            break;
        }
        case 6:
        {
            system("cls");

            goto home;
            break;
        }
        default:
        {
            system("cls");
            cout << "invalid choice" << endl;

        }
        }

        cout << "\n \t &&&&&&&&&&&&&&&&&&&&&& To return to a menu Enter (y,Y)" << endl;
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');


    J: //scope job
      do
    {
        system("cls");
        cout << "1- Insert" << endl;
        cout << "2- Search" << endl;
        cout << "3- Update" << endl;
        cout << "4- Delete" << endl;
        cout << "5- Display" << endl;
        cout << "6- back" << endl;
        int choice;
        cout << "\n\t\t Enter your choice " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            jo.insert();
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            jo.search(key);
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            jo.update(key);
            break;
        }

        case 4:
        {
            system("cls");
            cout << "Enter Key" << endl;
            cin >> key;
            jo.deleteD(key);
            break;
        }

        case 5:
        {
            system("cls");
            jo.display();
            break;
        }
        case 6:
        {
            system("cls");

            goto home;
            break;
        }
        default:
        {
            system("cls");
            cout << "invalid choice" << endl;

        }
        }

        cout << "\n \t &&&&&&&&&&&&&&&&&&&&&& To return to a menu Enter (y,Y)" << endl;
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

    return 0;


}



//definition function "introduction"
void introduction() //print the home screen
{
    cout << "\n\n\t\t contact system \2\n\n\n" << endl;

}

