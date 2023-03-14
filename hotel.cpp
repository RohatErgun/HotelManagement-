
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<cstdio>


class Hotel
{
  private:
  int roomNo;
  char name[20];
  char lname[20];
  char adress[50];
  char phone[15];
  int date;
  double cost;
  
  public:
  void main_menu(); //menu
  void customer_detials();//personal details about customer
  void book(); //book a room
  void record(); //record of the custemer 
  void issued_room(); //display the issued room
  void edit(); // edit customer detials

  int  check(int); //check if room avaible
  void modify_Rec(int); // modify  record
  void delete_Rec(int); // delete record
};

int Hotel::check(int room)
{
  int flag=0;
  std::ifstream fin("Record.dat",std::ios::in);
  while(!fin.eof())
  {
    fin.read((char*)this,sizeof(Hotel));

    if(roomNo == room)
    {
      flag = 1;
      break;
    }
  }
  fin.close();
  return(flag);
}

void Hotel::modify_Rec(int room)
{
  system("clear");
  int pos,flag=0; // position 
  std::fstream file("Record.dat",std::ios::in|std::ios::out|std::ios::binary);
    while(!file.eof())
    {
      pos = file.tellg();
      file.read((char*)this,sizeof(Hotel));
      if(roomNo = room)
      {
        std::cout <<"    "<< "Enter New Details" << "    " << std::endl;
        std::cout <<"\nNew Name: " ; std::cin >>name;
        std::cout <<"\nNew Last Name: " ; std::cin >>lname;
        std::cout <<"\nNew Adress: " ; std::cin >>adress;
        std::cout <<"\nNew Phone: " ; std::cin >>phone;
        std::cout <<"\nEdit days of stay: " ; std::cin >>date;
        cost = date*100 ;
        std::cout<< "\nThe new edited fare for customer:  " << cost << std::endl;

        file.seekg(pos);
        file.write((char*)this,sizeof(Hotel));
        std::cout <<"Record of the customer succsesfully modified " << std::endl;
        flag = 1;
        break;
      }
    }
    if(flag==0)
    {
        std::cout <<"\nRoom no is not found or room is already empty" << std::endl;
        file.close();
    }
}

void Hotel::delete_Rec(int room)
{
  system("clear");
 int flag=0;
 char Dchoice;
 std::ifstream fin("Record.dat",std::ios::in);
 std::ofstream fout("Temporary.dat",std::ios::out);
      while(!fin.eof())
      {
        fin.read((char*)this,sizeof(Hotel));
        if(roomNo == room)
        {
          std::cout << "\nPesonal details of Customer" <<std::endl;
          std::cout << "\nName and Surname: "<<name << lname << std::endl;
          std::cout << "\nAdress: "<< adress << std::endl;
          std::cout << "\nPhone Number: "<<phone << std::endl;
          std::cout << "\nTotal Cost: "<< cost << std::endl;

          std::cout << "Do you want to delete the customer record" << std::endl;
          std::cout << "y.(Yes) || n.(NO)" << std::endl;
          std::cin >> Dchoice;

          if(Dchoice == 'n')
          {
           fout.write((char*)this,sizeof(Hotel));
           flag=1;
           break;
          }
          else 
          {
            fout.write((char*)this,sizeof(Hotel));
          }
          
          fin.close();
          fout.close();
          if(flag==0)
          {
            std::cout << "Sorry room no not found" << std::endl;
          }
          else{
            remove("Record.dat");
            rename("Temporary.dat","Record.dat");
          }
          
        }
      }

}

int main(void)
{ 
  Hotel hotel;
  hotel.main_menu();  
  
  return 0;
}

void Hotel::main_menu()
{
  system("clear");
  std::cout << " ----------------------" << std::endl;
  std::cout << " |WELCOME TO MAIN MENU| " << std::endl;
  std::cout << " ----------------------" << std::endl;
  int choice;
  std::cout << "\n1.Book a room "<< "\n2.Display the customer record " << "\n3.Display the issued room "<< "\n4.Edit the cutomer details"<<"\n5.Exit the screen" << std::endl;
  std::cin >> choice ;
  switch(choice)
  {
    case 1:
    book();
    break;

    case 2:
    record();
    break;

    case 3:
    issued_room();
    break;

    case 4:
    edit();
    break;

    case 5:
    std::cout << "'\nExiting from main menu..." << std::endl;
    return;
  }
}

void Hotel::customer_detials()
{
  system("clear");
  std::cout << "Please enter the personal detials " << std::endl;
  
  std::cout << "\nEnter your name : " ; 
  std::cin >> name;
  std::cout << "\nEnter your last name : " ; 
  std::cin >> lname;
  std::cout << "\nEnter your adress: " ; 
  std::cin >> adress;
  std::cout << "\nEnter your phone number: " ; 
  std::cin >> phone;

  std::cout << "\n!Reminder daily cost of the hotel is 100 Euro per day " <<std::endl;
  std::cout << " Press any key to continue " <<std::endl;
  getchar();

  std::cout << "\nEnter the number of days to checkout: " ; 
  std::cin >> date;

  cost = date*100;
  std::cout << "Customer :" << name << lname << " Cost of total payment: " << cost <<"(Euro)"<< std::endl;
  std::cout << " " << std::endl;
  int refill;
  std::cout << "\n1.Refill the customer details\n0.Exit from the app" << std::endl;
  std::cin >> refill;
  switch(refill)
  {
    case 1:
    getchar();
    main();
    case 2:
    getchar();
    return;
  }
 }
 
void Hotel::book()
 {
  system("clear");
  int room,flag;
  std::ofstream fout("Record.dat",std::ios::app);

  std::cout << "\nWelcome to booking page" << std::endl;

  std::cout << "\nEnter room no:  ";
  std::cin >> room;

  flag = check(room);
  if(flag)
  {
   std::cout << "Sorry this room already booked! " << std::endl;
  }
  else
  {
    roomNo = room;
    customer_detials();

    fout.write((char*)this,sizeof(Hotel));
    std::cout << "\nRoom is successfully booked" << std::endl;
  }
  std::cout << "Please press ant key to continue " << std::endl;
  getchar();
  fout.close();
 }

 void Hotel::record() //customer record
 {
  system("clear");

  std::ifstream fin("Record.dat",std::ios::in);
  int room,flag;
  std::cout << "Enter the room no: "; std::cin >>room;
  while(!fin.eof()) //inline bool
  {
   fin.read((char*)this,sizeof(Hotel));
   if(roomNo == room)
   {
      system("clear");
      //printing customer detials
      std::cout << "\nCustomer Details" << std::endl;
      std::cout << "\nRoom no: " << roomNo << std::endl; 
      std::cout << "\nName and surname: " << name << lname <<std::endl; 
      std::cout << "\nAdress: " << adress << std::endl; 
      std::cout << "\nPhone number: " << phone << std::endl;
      std::cout << "\nDays stay in and the Total fare: "
      << date << cost << std::endl;
      flag = 1;
   }
  }
  if(flag ==0)
  {
    system("clear");
      std::cout << "Sorry room no not found or already booked" << std::endl;
      std::cout <<"Please enter any key to continue " << std::endl;
      getchar();
      fin.close();
  }
 }

void Hotel::issued_room()
{
  system("clear");
   std::ifstream fin("Record.dat",std::ios::in);
   
   std::cout << "\nList of all the rooms issued " <<std::endl;
   while(!fin.eof())
   {
    fin.read((char*)this,sizeof(Hotel));
    std::cout << "\nRoom no: " << roomNo << std::endl;
    std::cout << "\nName and last name: " << name << lname <<std::endl;
    std::cout << "\nAdress: " << adress <<std::endl;
    std::cout << "\nDays stay in and the Total fare: "
      << date << cost << std::endl;
         std::cout << " " << std::endl;
   }
   std::cout <<"Press any key to continue" << std::endl;
   getchar();
   fin.close();
}

void Hotel::edit()
{
  system("clear");
  int Echoice,room;
  std::cout <<"    "<< "WELCOME TO EDITING  MENU " << "    "<<std::endl;
  std::cout << "\nEnter room no: " ; std::cin >> room;

  std::cout << " " << std::endl;
  std::cout << "1.For Modify Customer Record || 2.Delete Customer Record" << std::endl;
  std::cin >> Echoice;
  system("clear");
  
  
  switch(Echoice)
  {
    case 1: 
    std::cout << "Editing customer rec" << std::endl;
    modify_Rec(room);
    break;

    case 2:
    std::cout << "Deleting customer account" << std::endl;
    delete_Rec(room);
    break;

    default:
    main();
  }
  std::cout << "Press any key to continue" << std::endl;
  getchar();
}