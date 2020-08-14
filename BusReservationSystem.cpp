#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>
#include<algorithm>
#include<map>
#include<ctime>

using namespace std;

///*******************************************FUNCTION TO FIND PATH BETWEEN TWO CITIES USING DIJKSTRA**************************************************///

void  get_path(string s,string d,std::vector<string>&t);                                ///function to get path s and d

///*****************************************************************************************************************************************************///

namespace persons{                                                                      ///person class member function taking input/output
    int valid_input(int,int,int);                                                       /// number input function
    void exit();                                                                        /// exit function to get out of programme
}

///************************************************************BUS NAMESPACE****************************************************************************///
namespace bus{																		    ///namespace for bus class and its function
    int stoi(std::string s){                                                            ///Normal function to convert string to integer
        int mul=1,count=0;
        for(int i=s.size()-1;i>=0;i--){
            count+=mul*(s[i]-48);
            mul*=10;
        }
        return count;
    }

///************************************************************ BUS CLASS *****************************************************************************///
class Bus {

	std::string  id_num;							    								///Bus_id number
	std::string origin;                                                                 ///Starting city
	std::string destination;                                                            ///destination city
	std::string arrival_time;                                                           ///Arrival time of the bus
	std::string departure_time;                                                         ///Departure time of bus
	int available_seats;						    									///Available seats
	int reserved_seats;								    								///reserved seats



public:
    static int total_seats;                                                             ///static variable to save total seats
    static void show_total_seats();                                                     ///function showing total seats
    std::vector<int> vec_seats;                                                         ///vector for saving total bus seats which are reserved
	void update_timing(std::string s1);                                                 ///function for admin to update timing of bus
    Bus(int x);                                                                         ///normal constructor with integral argument
	Bus();                                                                              ///main constructor function
    Bus(std::string id,std::string ori,std::string dest,std::string dept_time,std::string arr_time,int avail_seats,int reserve_seats,std::vector<bool>v);

    Bus(const Bus &b,std::string ori,std::string dest,std::string Date );               ///copy constructor with some other arguments

	void show();                                                                        ///function showing structure of bus
	std::string valid_time();                                                           ///function taking valid time as input from user/admin
	std::string get_bus_id()const;                                                      ///const member function to access private variable bus_id
	std::string get_origin( )const;                                                     ///const member function to access private variable origin
	std::string get_destination()const;                                                 ///const member function to access private variable destinaiton
	std::string get_departure_time()const;                                              ///const member function to access private variable departure_time
	std::string get_arrival_time()const;                                                ///const member function to access private variable arrival_time
	int get_available_seats()const;                                                     ///const member function to access private variable available_seats
    std::string date_valid();                                                           ///function taking valid date from user/admin as input
    ///void search_bus();                                                               ///function finding whether given bus is present or not
    void load_buses();                                                                  ///Taking all data of buses from csv file to vector of buses at the time of starting of programme
    void out_buses();                                                                   ///Giving all buses data from programme to csv file at the time of end of programme
    int is_id(std::string s);                                                           ///Function finding whether bus with given id exists or not
    void print_all_buses(vector<std::string>p,std::string date);                        ///Function printing all buses of path in vector p
    std::string make_id(std::string a,std::string b,std::string c);                     ///Returns bus id provided source,destination and date
    bool reserve_a_seat(int index,int k);                                               ///function reserves k seats in bus index at i in vector of buses
    void show_bus_admin(std::string src,std::string dest,std::string date);             ///shows buses to admin according to given inputs
    void get_bus_details_admin();                                                       ///Takes valid input from admin to show him desired buses
    std::string Enter_city();                                                           ///Takes valid city name input from user/admin


///There is no need to make a separate destructor for this class because all memory used is static(compile time)  so will be freed as soon as class objects goes out of their scope using default destructor of compiler *///


};
///*****************************************CLASS ENDS AND DEFINITION OF ITS FUNCTION STARTS************************************************************///


///**************************************VECTOR OF BUSES(VB) KEEPS ALL DATA OF BUSES PRESENT IN CSV ****************************************************///

std::vector<Bus>vb;                                                                     ///vector storing data of all running buses


///***************************************FUNCTION TO LOAD DATA FROM CSV FILE TO VEVTOR OF BUSES*********************************************************///

    void Bus::load_buses(){                                                             ///Function is loading all the data from a csv file(bus_data.csv)
        std::ifstream u;                                                                ///input file stream object u in std namespace
        u.open("bus_data.csv");                                                         ///opening file bus_data.csv
         Bus *temp;                                                                     ///Making a temporary pointer to object of Bus type
        temp=this;                                                                      ///Assigning temp address of current object on which member function is called

        while(u.good()){                                                                ///Extracting data until file is not empty
        getline(u,temp->id_num,',');                                                    ///Assigning value from file to id of current object
        getline(u,temp->origin,',');                                                    ///Assigning value from file to origin of current object
        getline(u,temp->destination,',');                                               ///Assigning value from file to destination of current object
        getline(u,temp->arrival_time,',');                                              ///Assigning value from file to arrival_time of current object
        getline(u,temp->departure_time,',');                                            ///Assigning value from file to departure_time of current object
        std::string x;
        getline(u,x,',');
        temp->available_seats=stoi(x);                                                  ///Assigning value from file to available_seats of current object by converting into integer
        getline(u,x,',');
        temp->reserved_seats=stoi(x);                                                   ///Assigning value from file to reserved_seats of current object by converting that into integer
        getline(u,x,',');
        temp->total_seats=40;

        for(int i=0;i<39;i++){                                                          ///Assigning value from file to seats of current object seats into vector of seats
         getline(u,x,',');
         temp->vec_seats[i]=stoi(x);                                                    ///Converting seat number into integer and saving in current temporary object
        }
          getline(u,x,'\n');
         temp->vec_seats[39]=stoi(x);
        vb.push_back(*temp);                                                            ///Pusing temporary bus object into vector of buses(vb)
    }

    u.close();                                                                          ///Closing the file bus_data.csv
     vb.erase(vb.begin()+vb.size()-1);                                                  ///Deletes the last element of vector of buses which is accessed twice
    }


 ///***************************************************FUNCTION TO OUTPUT TOTAL SEATS IN A BUS*********************************************************///
    void Bus::show_total_seats(){
        std::cout<<"TOTAL SEATS IN THIS BUS IS: "<<40<<"\n";                            ///function returns the total number of seats in Bus
    }

///**************************************ADMIN CAN USE THIS FUNCTION TO CHANGE TIMING OF SOME BUS ****************************************************///
    void Bus::update_timing(std::string s1){

		departure_time=s1;
		cout<<"\n\tBUS TIMING CHANGED SUCCESSFULLY";                                    ///Funcion to update the timing of bus by admin
	}

///********************************************CONSTRUCTOR WITH NO INITIALISATION WITH ARGUMENT INT X*************************************************///

     Bus::Bus(int x){                                                                   ///Constructor with integral value which just initialises all seats of bus

        for(int i=0;i<39;i++){
            vec_seats.push_back(0);                                                     ///Gives vector a size of 40
        }
    }

///**********************************************MAIN CONSTRUCTOR TAKING ALL INPUTS********************************************************************///

	Bus::Bus(){                                                                         ///Main constructor takes every details of bus as input

	    std::cout<<"\n\tENTER ORIGIN CITY: ";
	    origin=Enter_city();                                                            ///Taking valid source city as input

	    std::cout<<"\n\tENTER DESTINATION CITY: ";
	    destination=Enter_city();                                                       ///Taking valid destination city as input

		std::cout<<"\n\tENTER ARRIVAL TIME IN 'HH:MM AM' OR 'HH:MM PM' FORMAT : ";      ///Taking arrival time of bus as input
		std::string t1=valid_time();

		std::cout<<"\n\tENTER DEPARTURE TIME IN 'HH:MM AM' OR 'HH:MM PM' FORMAT : ";    ///Taking departure time of bus as input
		std::string t2=valid_time();

		std::string date;
		std::cout<<"\n\tENTER DATE: ";                                                  ///Taking date of travel of bus as input
		date=date_valid();
        std::string num;                                                                ///Constructing a unique bus id
        num+=origin[0];
        num+=origin[1];
        num+=destination[0];
        num+=destination[1];
        num+=date;
		id_num=num;                                                                     ///assigning the value of id to variable id_num
		arrival_time=t1;                                                                ///assigning the value of arrival time to variable arrival_time
		departure_time=t2;                                                              ///assigning the value of departure time to variable departure_time
		reserved_seats=0;                                                               ///Initializing number of reserved seats from zero
		available_seats=total_seats;                                                    ///Initializing number of available seats with total_seats
		total_seats=40;                                                                 ///Initializing total seats with 40
		for(int i=0;i<40;i++){
            vec_seats.push_back(0);                                                     ///Initializing all seats of bus as empty(0)
		}

	}


///********************************************************CONSTRUCTOR TAKING ALL INPUT AS ARGUMENT****************************************************///
	Bus::Bus(std::string id,std::string ori,std::string dest,std::string dept_time,std::string arr_time,int avail_seats,int reserve_seats,std::vector<bool>v){
        id_num=id;                                                                      ///initializing id_num of bus
        origin=ori;                                                                     ///Initializing origin or source city
        destination=dest;                                                               ///Initializing destination city of bus
        departure_time=dept_time;                                                       ///Initializing departure time of bus
        arrival_time=arr_time;                                                          ///Initializing arrival time of bus
        available_seats=avail_seats;                                                    ///Initializing number of available seats in bus
        reserve_seats=reserve_seats;                                                    ///Initializing number of reserved seats in bus
        total_seats=40;
        for(int i=0;i<40;i++){
            vec_seats.push_back(v[i]);                                                  ///Initializing vector of buses according to vector passed as argument
        }
	}

///***********************************************COPY CONSTRUCTOR WITH SOME ONTER ARGUMENTS TOO*****************************************************////
	Bus::Bus(const Bus &b,std::string ori,std::string dest,std::string Date ){
         std::string s;                                                                 ///Constructing unique bus id
         s+=ori[0];s+=ori[1];
         s+=dest[0];s+=dest[1];
         s+=Date;

         id_num=s;                                                                      ///Assigning the value of new unique id
         origin=b.origin;                                                               ///Assigning the value of origin same as that of b
         destination=b.destination;                                                     ///Assigning the value of destination same as that of b
         arrival_time=b.arrival_time;                                                   ///Assigning the value of arrival time same as that of b
         departure_time=b.departure_time;                                               ///assigning the value of departure time same as that of b
         reserved_seats=0;                                                              ///Initializing reserved seats with zero
		available_seats=total_seats;                                                    ///Initializing available seats with total seats
		 total_seats=40;                                                                ///Total seats =40
		for(int i=0;i<40;i++){
            vec_seats.push_back(0);                                                     ///Initializing vector of seats with all empty
		}
    }


///*******************************************SHOW FUNCTION TO PRINT ALL DETAILS OF BUS *****************************************************************///
    void Bus::show(){
        std::cout<<"\n\t"<<origin<<"  ->  "<<destination<<"\n\n";
	    for(int i=0;i<4;i++){
            cout<<"\t";
            if(i==0)
            std::cout<<"ARRIVAL TIME : "<<arrival_time;				                    ///showing arrival time
            if(i==1)
            std::cout<<"DEPARTURE TIME : "<<departure_time;                             ///showing departure  time
            if(i==2)
            std::cout<<"TOTAL SEATS : "<<40;		                                    ///shows total seats
            if(i==3)
            std::cout<<"AVAILABLE SEATS : "<<available_seats;		                    ///shows available seats
            if(i==1)
                cout<<"\t\t";
            else
                cout<<"\t\t\t";
            for(int j=0;j<10;j++){                                                      ///Showing total structure of bus
                if(vec_seats[10*i+j]==0){std::cout<<"  [A]  ";}                         ///Showing 'A' for available seats
                else {std::cout<<"  [N]  ";}                                            ///Showing 'N' for reserved seats
            }
            		    ///shows reserved seats
            std::cout<<"\n\n";
	    }
        cout<<"\n\t********************************************************************************************************************\n";
	}

///**************************************VALID TIME FUNCTION TO TAKE TAKE VALID TIME INPUT FROM USER/ADMIN**********************************************///

	std::string Bus::valid_time(){                                                          ///Function taking valid time as input
		std::string s;
		std::cin>>std::ws;
		std::getline(std::cin,s);
		try{
		if(s.size()!=8){
			throw "\n\tINVALID TIME FORMAT...";											///throws error if input time is invalid
		}
		if(s[0]>1+'0'){
			throw "\n\tINVALID TIME FORMAT...";
		}
		if(s[2]!=':'){
			throw "\n\tINVALID TIME FORMAT...";
		}
		if(s[6]!='A' && s[6]!='P'){
			throw "\n\tINVALID TIME FORMAT...";
		}
		if(s[7]!='M'){
			throw "\n\tINVALID TIME FORMAT...";
		}
	}
		catch(const char *ss){
			std::cerr <<ss<<std::endl;											        ///cout if time format is incorrect
			std::cout<<"\n\tPLEASE REENTER ENTER DEPARTURE TIME IN 'HH:MM AM' OR 'HH:MM PM' FORMAT : ";

			 s=valid_time();
		}
		return s;
	}

	std::string Bus::get_bus_id()const{                                                     ///getter function to get bus_id
        return id_num;                                                                      ///returns bus id of current bus for which member functon is called
	}

	std::string Bus::get_origin()const{                                                    ///getter function to get origin
        return origin;                                                                      ///Returns origin of bus
	}

	std::string Bus::get_destination()const{                                                ///getter function to get destination
        return destination;                                                                 ///Returns destination of bus
	}

	std::string Bus::get_departure_time()const{                                             ///getter function to get departure_time
        return departure_time;                                                              ///returns departure time of bus
	};

	std::string Bus::get_arrival_time()const{                                               ///getter function to get arrival_time
        return arrival_time;                                                                ///Returns arrival time of bus
	}

	int Bus::get_available_seats()const{                                                    ///getter function to get number of available seats
        return available_seats;                                                             ///Returns number of available seats
	}



///******************************************UTILITY FUNCTION TO CHECK THE VALIDITY OF DATE ENTERED BY USER OR ADMIN************************************///

	std::string Bus::date_valid(){                                                          ///Takes valid date as input from user/admin
            std::cin.ignore();
            std::string str;std::cin>>str;
            time_t timer;
            tm * time;
            const int BASE_YEAR = 1900;
            std::time(&timer);
            time = localtime(&timer);
            int y=time->tm_year+1900;
            int m=time->tm_mon+1;
            int d=time->tm_mday;
    try{

        if(y>stoi(str.substr(6,4))||(y==stoi(str.substr(6,4)) && m>stoi(str.substr(3,2)) )||(y==stoi(str.substr(6,4)) && m==stoi(str.substr(3,2)) &&d>stoi(str.substr(0,2)) ) ){
            throw"\tPLEASE ENTER A VALID FUTURE DATE : ";                                                            ///Throws error if entered date is not possible
        }

        else{
        if(str.size()!=10){

             throw "\tENTER VALID DATE IN FOLLOWING FORMAT DD/MM/YYYY: ";                                           ///Throws error if entered date is not in valid format
        }
        else{
            std::string s1;
            s1.push_back(str[0]);
            s1.push_back(str[1]);
           // int d = std::stoi(s1);
           int d=(s1[0]-48)*10+(s1[1]-48);


            std::string s2;
            s2.push_back(str[3]);
            s2.push_back(str[4]);
            //int m = stoi(s2);
             int m=(s2[0]-48)*10+(s2[1]-48);                                                                        /// converting string to integer
            std::string s3;
            s3.push_back(str[6]);
            s3.push_back(str[7]);
            s3.push_back(str[8]);
            s3.push_back(str[9]);
         //   int y = stoi(s3);
                  int y=(s3[0]-48)*1000+(s3[1]-48)*100+(s3[2]-48)*10+(s3[3]-48);                                    /// checking the validity of date
                if(str[2] == '/' && str[5] == '/'){
                    if(m==2 && d>=1 && d<=29 && y>=2017 && y<=2018){

                    }
                    else{


                        if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12 && d<=31 && d>=1 && y>=2017 && y<=2018){

                        }
                        else {

                            if(m==2 || m==4 || m==6 || m==9 || m==11 && d<=30 && d>=1 && y>=2017 && y<=2018){

                            }
                            else throw "\tENTER VALID DATE IN FOLLOWING FORMAT DD/MM/YYYY: ";                       /// will throw an exception if the date is in wrong format
                        }
                    }
                }
                else{
                    throw "\tENTER VALID DATE IN FOLLOWING FORMAT DD/MM/YYYY:";                                     /// will throw an exception if the date is in wrong format
                }
            }
        }
    }

    catch (const char *s){

        std::cout<<"\n"<<s;
        str=date_valid();
    }
    return str;
}


///**********************FUNCTION CHEKS WHETHER BUS OF THIS PARTICULAR ID EXITS OR NOT AND RETURNS INDEX IN VECTOR OF BUSES***************************///

int  Bus::is_id(std::string s){                                                                 ///Returns whether bus of given id exits or not
    for(int i=0;i<vb.size();i++){
        if(vb[i].get_bus_id()==s){
            return i;                                                                           ///Returns index of bus if it exists
            break;
        }
    }
    return -1;                                                                                  ///Returns -1 if bus does not exists
}


///*****************************************GIVES ID OF BUS USING SOURCE AND DESTINATION AND DATE OF BUS************************************************///

 std::string Bus::make_id(std::string a,std::string b,std::string c){                           ///Returns the id of bus using source,destination and date as argument
        string p;
        p+=a[0];
        p+=a[1];
        p+=b[0];
        p+=b[1];
        p+=c;
        return p;                                                                               ///Returns id of bus with given parameters
    }


///************************************************STATIC VARIABLE TOTAL NUMBER OF SEATS IN BUS**********************************************************///

int Bus::total_seats=40;                                                                        ///Initializes static variable  total seats with 40


///******************************************TAKES INPUT FROM ADMIN AND CALLS FUNCTION SHOW_BUS_ADMIN****************************************************///

void Bus::get_bus_details_admin(){                                                              ///Takes input from admin regarding desired bus
    system("cls");
    cout<<"\n\n\n\tPLEASE ENTER BUS DETAILS:";
    cout<<"\n\n\t****************************************************************************************************************************************\n\n";
    string s,d,dt;
    cout<<"\n";
	cout<<"\tENTER SOURCE CITY: ";                                                              ///Takes source city as input from admin
	s=Enter_city();
	cout<<"\n\tENTER DESTINATION CITY: ";                                                       ///Takes destination city as input
	d=Enter_city();
	cout<<"\n\tENTER DATE : ";                                                                  ///Takes valid Date as input from admin
	bus::Bus b(7);
    dt=b.bus::Bus::date_valid();
    cout<<"\n";
    show_bus_admin(s,d,dt);                                                                     ///Calls show_bus_admin function with these details to show all buses
}


///************************************FUNCTION CALLS COPY CONSTRUCTOR TO MAKE ALL BUSES OF PARTICULAR DATE*********************************************///

void utilityCreate(std::string Date){                                                           ///Function creates the instances of all bus for date of argument
    for(int i=0;i<34;i++){
        Bus b(vb[i],vb[i].get_origin(),vb[i].get_destination(),Date);                           ///It creates 34 new buses using copy constructor
        vb.push_back(b);
    }
}


///*************************************************PRINT ALL BUSES OF ONE PATH OF ONE DATE**************************************************************///

void Bus::print_all_buses(vector<std::string>p ,std::string date){                              ///Function prints status of all buses in path p ad date -date
    cout<<"\n\t**************************************************************************************************************************\n";
    for(int i=0;i<p.size()-1;i++){
    vb[vb[0].Bus::is_id(vb[0].Bus::make_id(p[i],p[i+1],date))].show();                          ///Calls show function for each pair of city in path
    cout<<"\n";
    }
}


///*******************************************RESERVES OR DERESERVE A SEAT BY K VALUE OF INDEX'TH BUS IN VT*********************************************///

 bool Bus::reserve_a_seat(int index,int k){                                                      ///Reserve k seats in bus indexed at i position
     bool x=1;
        if(vb[index].reserved_seats+k<=40){                                                      ///Checks if bus is already not filled completely
                vb[index].reserved_seats+=k;                                                     ///Update the value of reserved seats accordingly
                vb[index].available_seats-=k;                                                    ///Update the value of available seats accordingly
                    int i=0;
        while(vb[index].vec_seats[i]){i++;}
                if(k==1)vb[index].vec_seats[i]=1;                                                 ///k=1 for booking ticket
                else{                                                                             ///k=-1 for cancel ticket
                vb[0].vec_seats[0]=0;                                                            ///Marks those seats as filled
                }
        }
        else{
            return 0;
        }

    }

///************************************************SHOWS ALL BUSES OF ONE ROUTE TO ADMIN AND CAN MODIFY**************************************************///

    void Bus::show_bus_admin(std::string src,std::string dest,std::string date){                 ///Shows bus on request of admin
    //    v//b[vb[0].is_id(vb[0].make_id(src,dest,date))];
        system("cls");
        cout<<"\n\n\n\tYOU SEARCHED FOR BUSES FROM "<<src<<" TO "<<dest<<" ON DATE "<<date<<"\n";
        cout<<"\n\t****************************************************************************************************************************************\n\n";
        if(src==dest){                                                                          ///Checks if source and destination are same
            cout<<"\n\tSORRY BOTH SOURCE AND DESTINATION CITY CAN'T BE SAME ";                  /// Can't show buses in this condition to displays message
            for(int i=0;i<1000000000;i++){

            }
            system("cls");
            get_bus_details_admin();                                                            ///Calls function to take all input again
        }
        else{
             if(vb[0].is_id(make_id("Delhi","Jaipur",date))==-1){                               ///Checks if buses of this date exists in database or not
                utilityCreate(date);                                                            ///creates buses if buses doesn't exist
             }
            std::vector<std::string>temp;
            get_path(src,dest,temp);                                                            ///Takes the path from src to dest in temp vector

            for(int i=0;i<temp.size()-1;i++){
                int index=vb[0].is_id(vb[0].make_id(temp[i],temp[i+1],date));
                cout<<"\t"<<i+1<<": "<<temp[i]<<" -> "<<temp[i+1]<<"\n\n";                      ///Prints all buses in path and their availability
                cout<<"\t"<<"AVAILABLE SEATS :"<<vb[index].available_seats<<"\n\n\n";
            }

            cout<<"\n\tPRESS ANY BUS NO. TO CHANGE DETAILS: ";
            cout<<"\n\n\tPRESS 9 TO GO BACK TO HOME PAGE: \n\n";

        int n = persons::valid_input(1,temp.size()-1,9);                                        ///Takes valid input as per the given options
        if(n==9){                                                                               ///Exit status returns
                system("cls");
            return;
        }

        system("cls");

        int index=vb[0].is_id(vb[0].make_id(temp[n-1],temp[n],date));                           ///Finds index of bus selected by admin
            cout<<"\n\n";
            cout<<"\tSTATUS OF BUS FROM "<<vb[index].get_origin()<<" TO "<<vb[index].get_destination()<<" ON "<<date<<" : \n\n";
            cout<<"\n\t"<<vb[index].get_origin()<<"  ->  "<<vb[index].get_destination()<<"\n\n";
            cout<<"\n\t********************************************************************************************************************\n\n";

	    for(int i=0;i<4;i++){
            cout<<"\t";
            if(i==0)
            std::cout<<"ARRIVAL TIME : "<<vb[index].get_arrival_time();				            ///showing arrival time
            if(i==1)
            std::cout<<"DEPARTURE TIME : "<<vb[index].get_departure_time();                     ///showing departure  time
            if(i==2)
            std::cout<<"TOTAL SEATS : "<<40;		                                            ///shows total seats
            if(i==3)
            std::cout<<"AVAILABLE SEATS : "<<vb[index].get_available_seats();		            ///shows available seats
            if(i==1)
                cout<<"\t\t";
            else
                cout<<"\t\t\t";
            for(int j=0;j<10;j++){                                                              ///Showing total structure of bus
                if(vb[index].vec_seats[10*i+j]==0){std::cout<<"  [_]  ";}                       /// shows ' [_] ' for available seats
                else {std::cout<<"  [N]  ";}                                                    /// shows ' [N] ' for reserved seats
            }
            		    ///shows reserved seats
            std::cout<<"\n\n";
	    }
        cout<<"\n\t********************************************************************************************************************\n";



          cout<<"\n";
          cout<<"\n\tPRESS 1 TO CHANGE TIME OF THIS BUS:";
          cout<<"\n\n\tPRESS 2 TO RESERVE SOME SEATS : ";
          cout<<"\n\n\tPRESS 3 TO GO TO HOME PAGE \n\n:";

            int x = persons::valid_input(1,2,3);                                                ///Takes valid input as per the options given
            if(x==1){                                                                           ///If admin wants to change time of this bus
            system("cls");
            cout<<"\n\n";
            cout<<"\tSTATUS OF BUS FROM "<<vb[index].get_origin()<<" TO "<<vb[index].get_destination()<<" ON "<<date<<" : \n\n";
            cout<<"\n\t"<<vb[index].get_origin()<<"  ->  "<<vb[index].get_destination()<<"\n\n";
            cout<<"\n\t********************************************************************************************************************\n\n";

          string s1;
          cout<<"\n\tOLD DEPARTURE TIME : "<<vb[index].get_departure_time();
          cout<<"\n\n\tENTER DEPARTURE TIME :";
          s1=valid_time();                                                                      ///Takes new valid departure time as input

            vb[index].update_timing(s1);
            for(int i=0;i<1000000000;i++){

            }
            system("cls");
            return;
          }
            if(x==2){                                                                           ///If admin wants to book some seats
              system("cls");
            cout<<"\n\n";
            cout<<"\tSTATUS OF BUS FROM "<<vb[index].get_origin()<<" TO "<<vb[index].get_destination()<<" ON "<<date<<" : \n\n";
            cout<<"\n\t"<<vb[index].get_origin()<<"  ->  "<<vb[index].get_destination()<<"\n\n";
            cout<<"\n\t********************************************************************************************************************\n\n";

            cout<<"\n\tENTER NUMBER OF SEATS TO BE RESERVE : ";
            int n,m;
            cin>>n;                                                                           ///Number of seats admin wants to book
            if(n>vb[index].available_seats){
                cout<<"\n\n\tSORRY ONLY "<<vb[index].available_seats<<" SEATS ARE AVAILABLE"; ///If lesser number of seats are available than required
                for(int i=0;i<1000000000;i++){

                }
            }
            else{
            cout<<"\n\n\tENTER FIRST SEAT NO.: ";                                             ///Takes number of seat to be booked by admin
            cin>>m;
            int count=0;
              if(m>40 ||m<=0){
                cout<<"\n\n\tSORRY THERE IS NO SUCH SEAT";                                     ///Prints message if no such seat exist in bus
                count++;
              }
              else if( vb[index].vec_seats[m-1]==1){
                cout<<"\n\n\tSORRY THIS SEAT IS ALREADY BOOKED";                              ///Prints message if seat is already booked for some other user
                count++;
              }
              else{
                    vb[index].vec_seats[m-1]=1;
              }
            for(int i=1;i<n+count;i++){
                cout<<"\n\n\tENTER NEXT SEAT NO.: ";                                           ///Takes number of seat to be booked by admin
                cin>>m;
                 if(m>40||m<=0 ){
                cout<<"\n\n\tSORRY THERE IS NO SUCH SEAT";                                     ///Prints message if no such seat exist in bus
                count++;
              }
              else if( vb[index].vec_seats[m-1]==1){
                cout<<"\n\n\tSORRY THIS SEAT IS ALREADY BOOKED";                               ///Prints message if seat is already booked for some other user
                count++;
              }
                else{
                vb[index].vec_seats[m-1]=1;
                }
            }
            vb[index].reserved_seats+=n-count;
            vb[index].available_seats-=n-count;
            cout<<"\n\n\tCONGRATS SEATS HAS BEEN RESERVED SUCCESSFULLY ";                      ///Prints message after all seats have been booked
            for(int i=0;i<1000000000;i++){

            }
            system("cls");
            return ;
          }
          system("cls");
          return;
        }


          if(x==3){
                  system("cls");
                  return ;
          }
        }

    }
///**********************************************************TAKES VALID NAME OF CITY AS INPUT***********************************************************///

string Bus::Enter_city(){                                                                       ///Takes valid city name as input
     string s;
    cin>>s;
    try{
        if(s=="Delhi" ||s=="Mumbai" || s=="Calcutta" || s=="Bangalore" ||s=="Pune" || s=="Hyderabad" || s=="Chennai" ||s=="Ahmedabad" ||s=="Jaipur" || s=="Goa" ||s=="Bhopal" || s=="Kanpur" || s=="Jodhpur"){
            return s;
        }
        else{
            throw "PLEASE ENTER VALID CITY NAME : ";                                            ///Prints message until entered city doesn't belong to any of the above cities
        }
    }
    catch(const char*ss){                                                                       ///Throws error if entered city name is not correct
        cout<<"\n\t"<<ss;
        s=Enter_city();
    }

 }

///*****************************************************OUTPUT ALL BUS DATA FROM VECTOR TO CSV FILE *****************************************************///

void Bus::out_buses(){                                                                          ///Puts all bus data from program to csv file
    ofstream u;                                                                                 ///Output stream object u
    u.open("bus_data.csv",ios::trunc);                                                          ///Over write bus_data.csv file by the bus data of program
   // u<<"First Name,Last Name,Username,Password,Mobile Number,Email ID\n";
  // cout<<"vb_size="<<vb.size()<<"\n";
    for(int i=0;i<vb.size();i++){                                                               ///Writes the data of whole vector in csv file
        u<<vb[i].id_num<<","<<vb[i].origin<<","<<vb[i].destination<<","<<vb[i].arrival_time<<","<<vb[i].departure_time<<","<<vb[i].available_seats<<","<<vb[i].reserved_seats<<","<<vb[i].total_seats<<",";
        for(int j=0;j<39;j++){
            u<<vb[i].vec_seats[j]<<",";
        }
          u<<vb[i].vec_seats[39]<<"\n";
    }


}

};


///****************************************************************** BUS NAMESPACE ENDS ************************************************************///


namespace ticket{

class Ticket{                                                                                   ///Ticket class
    std::string username;                                                                       ///Keeps the username of user
    std::string ticket_no;                                                                      ///Keeps Unique ticket id
    std::string date;                                                                           ///Date of travel
    std::string origin;                                                                         ///Keeps city of origin
    std::string destination;                                                                    ///Destination city
    std::string depart_time;                                                                    ///Departure time
    std::string arive_time;                                                                     ///Arrival time
public:

    Ticket(std::string user,std::string date,std::string depart,std::string arive,std::vector<std::string>p);
                                                                                                ///Constructor with everything as argument
    Ticket(int x);
    void cancel_Ticket(std::string s,std::string d,std::string date,int k );                    ///function for cancelling ticket
    Ticket book_Ticket(std::string user,std::string date,std::string depart,std::string arive,std::vector<std::string>p);
                                                                                                ///Function for booking ticket
    void show();                                                                                ///Function for showing ticket
    void load_tickets();                                                                        ///Function for loading all tickets from database to program
    void out_tickets();                                                                         ///function for upoading data from program to database
    bool update_seats(std::vector<std::string>p,std::string date,int k);                        ///update k seats according to booking or cancelling
    void show_all_bookings(std::string user);                                                   ///Show all bookings of user
    std::string get_origin()const;                                                              /// getter function to get origin city
    std::string get_destination()const;                                                         ///getter function to get destination city
    std::string get_date()const;                                                                ///getter function to get date of travel


};
///**********************************************CLASS DEFINITION ENDS AND DEFINITION OF ITS MEMBER FUNCTION STARTS****************************************************///

    std::vector<Ticket>vt;                                                                      ///Load data from database for program

///****************************************************LOAD TICKET FUNCTION TO LOAD TICKET DATA FROM DATABASE**********************************************///

    void Ticket::load_tickets(){                                                                ///function to load ticket database in vector of tickets
        std::ifstream u;                                                                        ///input file stream object u
        u.open("ticket_data.csv");                                                              ///Opening file ticket_data.csv
        while(u.good()){                                                                        ///taking input until file is checked completely
        getline(u,this->username,',');                                                          ///Taking username and assigning it to current object
        getline(u,this->ticket_no,',');                                                         ///Taking ticket_id and assigning it to current object's ticket_no
        getline(u,this->origin,',');                                                            ///Taking origin and assigning it to current object's origin
        getline(u,this->destination,',');                                                       ///Taking destination and assigning it to current object's destination
        getline(u,this->depart_time,',');                                                       ///Taking departure time and assigning it to current object's departure_time
        getline(u,this->arive_time,',');                                                        ///Taking arrival time and assigning it to current object's arrival time
        getline(u,this->date,'\n');                                                             ///Taking date and assigning it to current object's date

        vt.push_back(*this);                                                                    ///Pushing current object into vector of tickets
    }
    u.close();                                                                                  ///closes file

    vt.erase(vt.begin()+vt.size()-1);                                                           ///Erases last element of vector as it is copied twice

    }

    std::string Ticket::get_origin()const{                                                      ///Constant getter function to get origin
        return origin;                                                                          ///Returns origin city
    }
    std::string Ticket::get_destination()const{                                                 ///constant getter function to get destination city
        return destination;                                                                     ///Returns destination city
    }
    std::string Ticket::get_date()const{                                                        ///constant getter function to get date of travel
        return date;                                                                            ///returns date of travel
    }

    Ticket::Ticket(std::string user,std::string dat,std::string depart,std::string arive ,std::vector<std::string>p ){
                                                                                                ///Function initializes ticket and returns it
        username=user;                                                                          ///Assign the value of username
        origin=p[0];                                                                            ///Assign the value of origin
        destination=p[p.size()-1];                                                              ///assign the value destination city
        depart_time=depart;                                                                     ///Assign the value of departure time
        arive_time=arive;                                                                       ///Assign the value of arrival time
        string x;                                                                               ///creates unique ticket id
        x+=user[0];
        x+=p[0][0];
        x+=p[p.size()-1][0];
        x+=dat[0];x+=dat[1];
        x+=dat[3];x+=dat[4];
        x+=dat[9];
        ticket_no=x;                                                                            ///Assign the ticket id
        date=dat;                                                                               ///assign the date of travel to Date of  ticket
    }

 ///***********************************************TICKET CONSTRUCTOR WITH NO INITIAIZATION**************************************************************///

    Ticket::Ticket(int x){
       ticket_no="-1";
                                                                                                ///Constructor with no initialization
    }

 ///****************************************************BOOK TICKET FUNCTION TO BOOK TICKET**************************************************************///

    Ticket Ticket::book_Ticket(std::string user,std::string date,std::string depart,std::string arive,vector<string>p){
                                                                                                ///Book ticket function to book ticket
        Ticket t(user,date,depart, arive,p);                                                    ///Calls ticket constructor to create ticket
        if(update_seats(p,date,1)){                                                           ///update seats by increasing 1 reserved
        vt.push_back(t);                                                                        ///Pushes constructed ticket into vector of ticket
        return t;
        }                                                                                     ///Returns constructed ticket
        else{
           return  Ticket(-1);
        }

    }

///****************************************************CANCEL TICKET FUNCTION TO CANCEL TICKET************************************************************///

    void Ticket::cancel_Ticket(std::string s,std::string d,std::string date,int k){             ///cancel ticket function to cancel ticket
        vector<string> temp;                                                                    ///temporary vector to store min path between s&d
            get_path( s, d,temp);                                                               ///updates path in temp vector
            update_seats(temp,date,-1);                                                         ///updates seats in all buses

        vt.erase(vt.begin()+k);                                                                 ///Delete ticket from vector of tickets
    }

 ///******************************************UPDATE SEAT FUNCTION CALLED BY BOOK/CANCEL TICKET******************************************************///

    bool Ticket::update_seats(std::vector<std::string>p,std::string date,int k){                ///update seats function to update seats in  bus
        bool possibility=1;
        int x;
        for(int i=0;i<p.size()-1;i++){
                x=i;
            if(bus::vb[0].reserve_a_seat(bus::vb[0].is_id(bus::vb[0].make_id(p[i],p[i+1],date)),k));
            else{
                    possibility=0;                                                              ///If reservation is not possible
                break;
            }
        }
        if(possibility==1){
            return 1;
        }
        else{
            for(int i=x;i>0;i--){
                bus::vb[0].reserve_a_seat(bus::vb[0].is_id(bus::vb[0].make_id(p[i],p[i+1],date)),-1*k);
            }
            return 0;
        }
    }

///*********************************************************SHOW FUNCTION TO PRINT TICKET***************************************************************///

    void Ticket::show(){                                                                        ///show function to print ticket
        if(ticket_no=="-1"){
            cout<<"\n\n\n";
            cout<<"\tYOUR TICKET DETAILS:\n";
            cout<<"\n    *************************************************************************************************************************************************************\n";
            cout<<"\n";
            cout<<"\n\n\t SORRY FOR THE INCONVENIENCE BUT DUE TO UNAVAILABILITY OF SEATS WE CAN'T CONFIRM YOUR TICKET ";
            for(int i=0;i<1000000000;i++){for(int k=0;k<2;k++){}}
            system("cls");
            return;
        }else{
        cout<<"\n\n\n";
        cout<<"\tYOUR TICKET DETAILS:\n";
        cout<<"\n    *************************************************************************************************************************************************************\n";
        cout<<"\n";
         std::cout<<"\tUSER NAME : "<<username<<"\n\n";                                         ///Prints username of user
         std::cout<<"\tTICKET NO. : "<<ticket_no<<"\n\n";                                       ///Prints ticket no of ticket
         std::cout<<"\tORIGIN : "<<origin<<"\n\n";                                              ///Prints origin city of path in ticket
         std::cout<<"\tDESTINATION : "<<destination<<"\n\n";                                    ///Prints destination city of path in ticket
         std::cout<<"\tDEPARTURE TIME : "<<depart_time<<"\n\n";                                 ///Prints departure time
         std::cout<<"\tARRIVAL TIME : "<<arive_time<<"\n\n";                                    ///prints arrival time
         std::cout<<"\tTHANK YOU FOR BOOKING WITH US,PRESS ANY KEY TO CONTINUE..... \n";
         getch();
         system("cls");
        }
    }

 ///***********************************************SHOW ALL BOOKINGS FUNCTION OF THIS USER*************************************************************///

    void Ticket::show_all_bookings(std::string user){                                           ///shows booking history of this user
        system("cls");
        vector<int>t;
        cout<<"\n\n\n";
        cout<<"\tBOOKING HISTORY \n";
        cout<<"\n    *************************************************************************************************************************************************************\n";
        cout<<"\n";
        for(int i=0;i<vt.size();i++){
            if(vt[i].username==user){                                                           ///searches for bookings for this user in vector of tickets
                t.push_back(i);
                cout<<"\t"<<t.size()<<"    DOJ : "<<vt[i].date<<"\n\n";
                cout<<"\t     "<<vt[i].origin <<" -> "<<vt[i].destination<<"\n\n";
                cout<<"\t******************************************************\n\n";

            }

        }
        if(t.size()==0){                                                                        ///Prints if no tickets have been booked yet by user
            cout<<"\tYOU HAVEN'T BOOKED ANY TICKET YET ";
            for(int i=0;i<1000000000;i++){                                                      ///displays the output for some time


            }
            cout<<"\n\n";
            system("cls");                                                                      ///clears screen
            return;
        }
        else{

        cout<<"\t1. CANCEL ANY BOOKING \n\n";
        cout<<"\t2. TO EXIT TO MAIN MENU \n\n";
        int x = persons::valid_input(1,1,2);                                                    ///Takes valid input as per given options
        if(x==1){
        cout<<"\n\n\n\tENTER TICKET INDEX TO CANCEL TICKET ";
        cout<<"\n\n\tENTER 9 TO GO TO HOMEPAGE ";
        cout<<"\n\n";
       int n=persons::valid_input(1,t.size(),9);                                                ///takes valid input as per given options
       if(n==9){
            system("cls");
        return;
       }
       else{
        vt[0].cancel_Ticket(vt[t[n-1]].get_origin(),vt[t[n-1]].get_destination(),vt[t[n-1]].get_date(),t[n-1]);
                                                                                                 ///calling cancel ticket function to cancel ticket
        cout<<"\n\n\tCONGRATS TICKET HAS BEEN CANCELLED ";
        for(int i=0;i<1000000000;i++){

        }
        system("cls");
        show_all_bookings(user);                                                                ///show booking function to show all bookings of user
       }

        }

        else{
            system("cls");                                                                      ///clears screen
            return;
        }


        }
    }

///*******************************************OUT TICKET FUNCTION TO OUTPUT ALL DATA FROM VECTOR OF TICKETS TO CSV FILE**********************************///

    void Ticket::out_tickets(){                                                                 ///gives program data into database
        ofstream a;                                                                             ///output file stream object a;
        a.open("ticket_data.csv",ios::trunc);                                                   ///open ticket_data.csv file and over write it
          //cout<<"vt_size="<<vt.size()<<"\n";
        //a<<"Username,ticket_no,bus_id_no,origin,destination,depart_time,arive_time";
        for(int i=0;i<vt.size();i++){                                                           ///Sends data of whole vector
           a<<vt[i].username<<","<<vt[i].ticket_no<<","<<vt[i].origin<<","<<vt[i].destination<<","<<vt[i].depart_time<<","<<vt[i].arive_time<<","<<vt[i].date<<"\n";
        }
    }
};


///***********************************************LOAD ALL DATA INSIDE A VECTOR*************************************************************///

    void load_data(){                                                                           ///load all data of bus as well as ticket
        bus::Bus b(5);
        b.load_buses();
        ticket::Ticket t(5);
        t.load_tickets();
    }

///***********************************************MIMIMUM DISTANCE USING DIJKSTRA WITH MAPS**************************************************///

vector<int>parent(13,-1);

///***************************************************DIJKSTRA TO FIND MINIMUM DISTANCE*******************************************************///

int mindist(vector<int >dist,vector<bool>sptset){                                       ///function returns index with minimum distance from source
	int min_index,min=INT_MAX;
	for(int i=0;i<13;i++){
		if(sptset[i]==0 && dist[i]<min){
			min=dist[i];
			min_index=i;
		}
	}
	return min_index;                                                                  ///returning index
}

///**************************************************DIJKSTRA FUNCTION TO FIND MINIMUM *****************************************************************///

int dijkstra(int src,int dest,vector<vector<int> > &dist){                             ///dijkstra function to find minimum path between source and destination
	vector<bool>sptset(13,0);
	//	sptset[src]=1;
	vector<int>dfs(13,INT_MAX);                                                        ///initializes every node vertex to infinite
	dfs[src]=0;
	for(int i=0;i<12;i++){
		int u=mindist(dfs,sptset);
		sptset[u]=1;
		for(int j=0;j<13;j++){
			if(dfs[j]>dfs[u]+dist[u][j] && dist[u][j]!=0 && dfs[u]!=INT_MAX && sptset[j]==0){///update distance from source if lesser is found
				dfs[j]=dfs[u]+dist[u][j];
				parent[j]=u;                                                              ///update the parent vector
			}
		}
	}
	return dfs[dest];                                                                    ///returns minimum distance from source to destination
}


///**********************************************GET PATH FUNCTION TO FIND MIN PATH USING DIJKSTRA *****************************************************///

    void get_path(string src,string dest,vector<string>&path_vec){                      ///updates path between src & dest in path_vec vector
    int total_cities=20;
	map<string,int> mp;
	map<int,string> mp1;
	vector<vector<int> >dist(13,vector<int>(13,0));

	enum cities{                                                                        ///Enumeraion of cities in database
		Delhi=0,Mumbai,Calcutta ,Bangalore,Pune,Hyderabad,Chennai,Ahmedabad,Jaipur,Goa,Bhopal,Kanpur,Jodhpur
	};
	mp["Delhi"]=0;						mp1[0]="Delhi";                                 ///maps of all cities with number as keys
	mp["Mumbai"]=1;						mp1[1]="Mumbai";
	mp["Calcutta"]=2;					mp1[2]="Calcutta";
	mp["Bangalore"]=3;					mp1[3]="Bangalore";
	mp["Pune"]=4;						mp1[4]="Pune";
	mp["Hyderabad"]=5;					mp1[5]="Hyderabad";
	mp["Chennai"]=6;					mp1[6]="Chennai";
	mp["Ahmedabad"]=7;					mp1[7]="Ahmedabad";
	mp["Jaipur"]=8;						mp1[8]="Jaipur";
	mp["Goa"]=9;						mp1[9]="Goa";
	mp["Bhopal"]=10;					mp1[10]="Bhopal";
	mp["Kanpur"]=11;					mp1[11]="Kanpur";
	mp["Jodhpur"]=12;					mp1[12]="Jodhpur";


	dist[Delhi][Jaipur]=275;				dist[Jaipur][Delhi]=275;                    ///connected cities
	dist[Jaipur][Ahmedabad]=677;			dist[Ahmedabad][Jaipur]=677;
	dist[Ahmedabad][Mumbai]=524;			dist[Mumbai][Ahmedabad]=524;
	dist[Mumbai][Pune]=150;					dist[Pune][Mumbai]=150;
	dist[Pune][Goa]=448;					dist[Goa][Pune]=448;
	dist[Goa][Bangalore]=560;				dist[Bangalore][Goa]=560;
	dist[Bangalore][Chennai]=346;           dist[Chennai][Bangalore]=346;
	dist[Chennai][Hyderabad]=628;			dist[Hyderabad][Chennai]=628;
	dist[Hyderabad][Bhopal]=850;			dist[Bhopal][Hyderabad]=850;
	dist[Bhopal][Kanpur]=582;				dist[Kanpur][Bhopal]=582;
	dist[Kanpur][Delhi]=488;				dist[Delhi][Kanpur]=488;
	dist[Hyderabad][Pune]=561;				dist[Pune][Hyderabad]=561;
	dist[Ahmedabad][Bhopal]=583;			dist[Bhopal][Ahmedabad]=583;
	dist[Jaipur][Bhopal]=623;				dist[Bhopal][Jaipur]=623;
	dist[Jaipur][Jodhpur]=337;				dist[Jodhpur][Jaipur]=337;
	dist[Calcutta][Kanpur]=1003;            dist[Kanpur][Calcutta]=1003;
    dist[Hyderabad][Calcutta]=1490;         dist[Calcutta][Hyderabad]=1490;



	parent[mp[src]]=mp[src];                                                            ///making parent of src to src
    dijkstra(mp[src],mp[dest],dist);
	int j=mp[dest];
	vector<int>path;
	while(j!=mp[src]){                                                                  /// function to print path using parent vector
		path.push_back(j);
		j=parent[j];
	}

	//cout<<"Minimum attainable path would be:\n";
	//cout<<src;
	path_vec.push_back(src);
	reverse(path.begin(),path.end());
	for(int i=0;i<path.size();i++){
		//cout<<" -> "<<mp1[(path[i])];
		path_vec.push_back(mp1[(path[i])]);                                             ///Saves min path in path_vec vector
	}
}


///**************************************_PATH FUNCTION TO TAKE I/P FROM USER AND BOOK MIN PATH BUS FO USER *********************************************///
void _path(string user){
    system("cls");
    cout<<"\n\n\n";
    cout<<"\tBOOK TICKET\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    int total_cities=20;
	map<string,int> mp;
	map<int,string> mp1;
	vector<vector<int> >dist(13,vector<int>(13,0));                                     ///Adjacency matrix of cities

	enum cities{                                                                        ///Enum of cities
		Delhi=0,Mumbai,Calcutta ,Bangalore,Pune,Hyderabad,Chennai,Ahmedabad,Jaipur,Goa,Bhopal,Kanpur,Jodhpur
	};
	mp["Delhi"]=0;						mp1[0]="Delhi";                                 ///map of all cities in database with index as key
	mp["Mumbai"]=1;						mp1[1]="Mumbai";
	mp["Calcutta"]=2;					mp1[2]="Calcutta";
	mp["Bangalore"]=3;					mp1[3]="Bangalore";
	mp["Pune"]=4;						mp1[4]="Pune";
	mp["Hyderabad"]=5;					mp1[5]="Hyderabad";
	mp["Chennai"]=6;					mp1[6]="Chennai";
	mp["Ahmedabad"]=7;					mp1[7]="Ahmedabad";
	mp["Jaipur"]=8;						mp1[8]="Jaipur";
	mp["Goa"]=9;						mp1[9]="Goa";
	mp["Bhopal"]=10;					mp1[10]="Bhopal";
	mp["Kanpur"]=11;					mp1[11]="Kanpur";
	mp["Jodhpur"]=12;					mp1[12]="Jodhpur";


	dist[Delhi][Jaipur]=275;				dist[Jaipur][Delhi]=275;                    ///connected cities in database
	dist[Jaipur][Ahmedabad]=677;			dist[Ahmedabad][Jaipur]=677;
	dist[Ahmedabad][Mumbai]=524;			dist[Mumbai][Ahmedabad]=524;
	dist[Mumbai][Pune]=150;					dist[Pune][Mumbai]=150;
	dist[Pune][Goa]=448;					dist[Goa][Pune]=448;
	dist[Goa][Bangalore]=560;				dist[Bangalore][Goa]=560;
	dist[Bangalore][Chennai]=346;           dist[Chennai][Bangalore]=346;
	dist[Chennai][Hyderabad]=628;			dist[Hyderabad][Chennai]=628;
	dist[Hyderabad][Bhopal]=850;			dist[Bhopal][Hyderabad]=850;
	dist[Bhopal][Kanpur]=582;				dist[Kanpur][Bhopal]=582;
	dist[Kanpur][Delhi]=488;				dist[Delhi][Kanpur]=488;
	dist[Hyderabad][Pune]=561;				dist[Pune][Hyderabad]=561;
	dist[Ahmedabad][Bhopal]=583;			dist[Bhopal][Ahmedabad]=583;
	dist[Jaipur][Bhopal]=623;				dist[Bhopal][Jaipur]=623;
	dist[Jaipur][Jodhpur]=337;				dist[Jodhpur][Jaipur]=337;
    dist[Calcutta][Kanpur]=1003;            dist[Kanpur][Calcutta]=1003;
    dist[Hyderabad][Calcutta]=1490;         dist[Calcutta][Hyderabad]=1490;


    string src,dest,date;
	cout<<"\tENTER YOUR STARTING POINT: ";                                          ///taking source as input
	src=bus::vb[0].bus::Bus::Enter_city();
	cout<<"\n\tENTER YOUR DESTINATION POINT: ";                                     ///taking destination as input
	dest=bus::vb[0].bus::Bus::Enter_city();
	cout<<"\n\tENTER DATE OF TRAVEL: ";                                             ///taking date of travel as input
	bus::Bus b(7);
    date=b.bus::Bus::date_valid();

    system("cls");
    cout<<"\n\n\n";
    cout<<"\tYOU SEARCHED FOR " <<src <<" TO "<<dest<<" ON "<<date<<" \n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    if(src==dest){
        cout<<"\tSORRY, SOURCE AND DESTINATION SHOULD BE DISTINCT ";                ///Prints message if source and destination are same
        for(int i=0;i<1000000000;i++){

        }
        system("cls");                                                              ///clears screen
        return ;
    }else{
	parent[mp[src]]=mp[src];                                                        ///making parent of source=source
	int z = dijkstra(mp[src],mp[dest],dist);                                        ///calling dijksta to find minimum path

	cout<<"\tTOTAL MINIMUM DISTANCE : "<<z <<" KM \n\n";                            ///showing minimum distance
	cout<<"\tTOTAL FARE : Rs. "<<z*1.5<<" /- \n";                                   ///showing estimated minimum fare

	int j=mp[dest];
	vector<int>path;
	while(j!=mp[src]){                                                              ///reverse function to print path
		path.push_back(j);
		j=parent[j];
	}
	vector<string>path_vec;                                                         ///path_vec vector to save path
	//cout<<"Minimum attainable path would be:\n";
	//cout<<src;
	path_vec.push_back(src);
	reverse(path.begin(),path.end());                                               ///STL algorithm to reverse contents of path vector
	for(int i=0;i<path.size();i++){
		//cout<<" -> "<<mp1[(path[i])];
		path_vec.push_back(mp1[(path[i])]);                                         ///pushes cities in path_vec vector
	}
	string id;
	id+=path_vec[0][0];                                                             ///creates id of bus accordingly src,dest and date
	id+=path_vec[0][1];
	id+=path_vec[path_vec.size()-1][0];
	id+=path_vec[path_vec.size()-1][1];
	id+=date;
	if(b.bus::Bus::is_id(id)!=-1){
	}
	else{
        bus::utilityCreate(date);                                                    ///creates buses if already doesn't exist
	}
	cout<<"\n\tPATH : ";
	cout<<src;
	for(int i=1;i<path_vec.size();i++){
        cout<<"  ->  "<<path_vec[i];                                                 ///prints path
	}
    cout<<"\n";
    bus::vb[0].bus::Bus::print_all_buses(path_vec,date);


    cout<<"\n";
    cout<<"\t1. CONFIRM BOOKING\n\n";

    cout<<"\t2. CHANGE JOURNEY DETAILS\n\n";

    cout<<"\t3. HOMEPAGE\n\n";
    int n = persons::valid_input(1,2,3);                                            ///Takes valid input as per options
    if(n==1){
            system("cls");
            cout<<"\n";
            string x=bus::vb[bus::vb[0].is_id(bus::vb[0].make_id(path_vec[0],path_vec[1],date))].get_departure_time();
            string y=bus::vb[bus::vb[0].is_id(bus::vb[0].make_id(path_vec[path_vec.size()-2],path_vec[path_vec.size()-1],date))].get_arrival_time();
            ticket::vt[0].book_Ticket(user,date,x,y,path_vec).show();
            return;
    }
    if(n==2){
        system("cls");                                                              ///clears screen
        _path(user);                                                                ///call same function again

    }
    if(n==3){
            system("cls");                                                          ///clears screen
    return;

        }
    }
}


///****************************************************OUT ALL DATA OF VECTORS INSIDE CSV FILES**************************************************///

void out_data(){                                                                ///calls all data sending function
    bus::Bus b(5);
    b.out_buses();
    ticket::Ticket t(5);
    t.out_tickets();
}


///******************************************************************Persons Namespace starts here*******************************************************////
namespace persons{

void load_data();                                /// This function calls two functions to load data from csv files to vector
void start(string s="");                         /// This is a function which will be called by main to start the program it is the main homepage
void out_data();                                 /// This function calls two functions to unload data back to csv files
void show_message(string s);                     /// This is a function to show any message for few seconds and than continue the flow of the program
void exit();                                     /// This functions is called when a user/admin wants to exit the program
int valid_input(int s,int e,int exit);           /// This function checks if the input is between s and e or exit and returns the value. It will call itself till user/admin enters valid input
string get_password();                           /// This functions gets password and returns it
string get_username(bool b = 0);                 /// This functions gets username and retuens it, it also ensures that username conatins only alphanumeric characters
string get_email();                              /// This function takes correct email ID from the user and returns the string, it ensures that the entered email is in correct format
string get_mobile();                             /// This function takes correct mobile number from the user and returns it
string get_name();                               /// This function takes correct name and returns it
bool username_isavailable(string &s);            /// This function returns true if username is available i.e. username not present already
bool username_isValid(string &s);                /// This function checks the validity of the username


//// person class
class person{
protected:
    string username,password;                   /// This variables are inherited by user as well as admin
public:
    enum t{U,A};                                /// Type user or type admin
    t type;
    person(string u="",string p="",t ua=U);     /// constructor for person class
    virtual bool login(int &index){}            /// Virtual function to login
    virtual void homepage(int index){}          /// Virtual function to direct to homepage
    virtual void logout(){}                     /// This is a vitual funtion to logout
};
void get_credentials(person::t ua);             /// This function takes username and password both for user login as well as admin login


/// user class inherited from person class
class user:public person{
    string fname,lname,email,mobile;            /// this details are only required for the user and not for admin, namely , First Name, Last name, email ID, mobile number
public:
    user(string u="",string p="",t ua=U);       /// constructor for user class
    void change_details(int &index);            /// This function allows user to change his/her details
    void logout();                              /// This function is called when a user wants to logout
    bool login(int &index);                     /// This function is called for user login
    void homepage(int index);                   /// This function directs to user homepage
    void friend load_users();                   /// This function loads data from users.csv to vector users, which is used every where in the program
    bool operator == (user &compar);            /// This operator overloading is used to just compare username and password
    bool friend operator == (string un,user u); /// This operator overloading is used to just compare username
    void friend signup();                       /// This function is called for user signup
    void friend out_users();                    /// This function send data back to users.csv
};

/// admin class inherited from person class
class admin:public person{
    string employeeID;                          /// This is employee id given by company to every admin
public:
    admin(string u="",string p="",t ua=A);      /// constructor for admin class
    bool login(int &index);                     /// This function is called when admin wants to login
    void homepage(int index);                   /// This function directs to admin homepage
    void logout();                              /// This function is called when admin wants to logout
    void friend load_admins();                  /// This function loads complete data of admins.csv to vector admins, which is used further in the entire code
    bool operator == (admin &compar);           /// This operator overloading is used to just compare username and password
    void friend out_admins();                   /// This function unloads data back to admins.csv file
};
///classes to throw error
/// if entered value is invalid while selecting an option then exception thrown is of following type
class invalid_input{
    string s;
public:
    invalid_input(string w):s(w){}             /// constructor for invalid_input
    void print(){cout<<s<<"\n";}               /// function to print the string
};

///*****************if user/admin enters wrong username/password i.e not present in the vector the exception thrown is of below type****************************
class invalid_credential{
public:
    string s;
    invalid_credential(string w):s(w){}
    void print(){cout<<s<<"\n";}
};

/// ********************************if a user enters invalid mobile number than exception throws is of below type***************************************//
class invalid_mobile{
    string s;
public:
    invalid_mobile(){
        s = "\n\tPLEASE ENTER VALID MOBILE NUMBER : ";
    }
    void print(){
        cout<<s;
    }
};

/// if user enters invalid email id than exception thrown is of below type
class invalid_email{
    string s;
public:
    invalid_email(){
        s = "\n\tPLEASE ENTER VALID EMAIL ID : ";
    }
    void print(){
        cout<<s;
    }
};

/// if entered name is invalid than exception thrown is of below type
class invalid_name{
    string s;
public:
    invalid_name(){
        s = "\n\tNAME MUST ONLY CONTAIN ALPHABET : ";
    }
    void print(){
        cout<<s;
    }
};

/// if a user/admin enters invalid username than exception thrown is of below type
class invalid_username{
    string s;
public:
    invalid_username(string w):s(w){}
    void print(){
        cout<<s;
    }
};

///vectors to store complete data
vector<user>users;                          /// this vector stores complete data of users
vector<admin>admins;                        /// this vector stores complete data of amins

/// Below is the declaration of friend functions which has to be done outside class
void load_users();
void load_admins();
void out_users();
void out_admins();
void signup();
bool operator == (string ua,user u);
}
///Namespace Persons ends here


///*************************************************** Functions to get data and also send data  **************************************************************


/// Below three functions are used to load data from csv file
void persons::load_data(){
    load_users();
    load_admins();
}


/// Function to get data from users.csv file into vector users which is used throughout the program
void persons::load_users(){
    ifstream u;
    u.open("users.csv");                     /// users.csv is the file from which data is imported
    user *temp;                              /// temporary pointer which will point to the space where all data will be saved in one loop and finally it will be added to vector "users"
    temp = new user;                         /// assigning memory to the pointer
    int i=0;
    while(u.good()){
        getline(u,temp->fname,',');         /// this will take data and assign it to fname, it will read data till it finds ','
        getline(u,temp->lname,',');         /// assigns data to lname, it will also read till it find ','
        getline(u,temp->username,',');      /// assign to username
        getline(u,temp->password,',');      /// assigns to password
        getline(u,temp->mobile,',');        /// assigns to mobile
        getline(u,temp->email,'\n');        /// assigns to email and this will take input till it finds '\n' i.e. end of the line
        temp->type = person::U;             /// every user must have value of type variable as U
        /// below if else ensures that first line is not included in the vector as it just contains headings
        if(i)
            users.push_back(*temp);
        else
            i++;
    }
    u.close();                               /// closes file users.csv which was opened to take input
    delete temp;                             /// deletes that space alloted to temp pointer
    users.erase(users.begin()+users.size()-1);
}


/// Function to get data from admins.csv into vector admins which can be used throughout the program
void persons::load_admins(){
    ifstream a;
    a.open("admins.csv");                   /// data is imported from admins.csv
    admin *temp;                            /// pointer temp to temporary save data
    temp = new admin;                       /// space given to temp
    int i=0;
    while(a.good()){
        getline(a,temp->username,',');      ///assigns value to username it will read data till it finds ','
        getline(a,temp->password,',');      ///assigns value to password
        getline(a,temp->employeeID,'\n');   /// assigns value to employeeID , this will take data till it finds next line character '\n'
        temp->type = person::A;             /// assigns type as A
                                            /// below if else ensures that first line is not added to vector admins
        if(i)
            admins.push_back(*temp);
        else
            i++;
    }
    a.close();                              /// close file admins.csv
    delete temp;                            /// delete space given to temp pointer
    admins.erase(admins.begin()+admins.size()-1);
}

                                            /// Below function calls two function to send data back to csv file
void persons::out_data(){
    out_users();                            /// function to export data of users
    out_admins();                           /// function to export data of admins
}

void persons::out_users(){
    ofstream u;
    u.open("users.csv",ios::trunc);         /// here ios::trunc is used to overwrite the data present in the file "users.csv" and open is used to open the file

    u<<"First Name,Last Name,Username,Password,Mobile Number,Email ID\n";
                                            /// First line contains heading
    for(int i=0;i<users.size();i++){
        u<<users[i].fname<<","<<users[i].lname<<","<<users[i].username<<","<<users[i].password<<","<<users[i].mobile<<","<<users[i].email<<"\n";
    }
    u.close();                              /// closes file "users.csv"
}

void persons::out_admins(){
    ofstream a;
    a.open("admins.csv",ios::trunc);        /// opens file "admins.csv"
    a<<"Username,Password,EmployeeID\n";
    for(int i=0;i<admins.size();i++){
        a<<admins[i].username<<","<<admins[i].password<<","<<admins[i].employeeID<<"\n";
    }
    a.close();                              /// closes file "adins.csv"
}



///************************************************** Other Functions of namespace persons which are not in any class *********************************************************************

/// start function is the beginner it is called just after data is imported in vectors
void persons::start(string s){              /// argument taken here will be displayed on the top mainly used when this function is recalled with a message to be shown
    cout<<"\n\n\n";
    cout<<"\tBUS RESERVATION SYSTEM\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    if(s.size()){
        cout<<s;
    }
    /// Below are the options provided
    cout<<"\t1. USER LOGIN\n\n";
    cout<<"\t2. USER SIGNUP\n\n";
    cout<<"\t3. ADMIN LOGIN\n\n";
    cout<<"\t9. EXIT\n\n";
    int n = valid_input(1,3,9);         /// this function only takes valid input and returns the number, here valid input will be considered from 1 to 3 and also 9
    if(n==1){
        system("cls");
        try{
            get_credentials(person::U); ///this function gets credentials from user i.e username and password, argument passed here is of enum t which indicates this is a user
        }
        catch(invalid_credential i){
            system("cls");
            start(i.s);                 /// here starting given as argument is the exception thrown by get_credential function
        }
    }
    if(n==2){
        system("cls");
        signup();                       /// function to get details of user for signup
    }
    if(n==3){
        system("cls");
        try{
            get_credentials(person::A); /// same as that was for n==1 but argument passed here indicates that it is admin who is entering details
        }
        catch(invalid_credential i){
            system("cls");
            start(i.s);                 /// recalling function start if invalid credentials are entered
        }
    }
    if(n==9){
        exit();                         /// function to exit
    }
}

/// Below is the function called to exit the program it just contains a message and doesn't  disturb the flow
void persons::exit(){
    system("cls");
    cout<<"\n\n\n";
    cout<<"\tBUS RESERVATION SYSTEM\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    cout<<"\tTHANK YOU FOR USING OUR SERVICES\n\n";
}

void persons::get_credentials(person::t ua){
    string u,p;
    cout<<"\n\n\n";
    cout<<"\tBUS RESERVATION SYSTEM\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    cout<<"\tUSERNAME : ";
    u=get_username();               /// function to get username and return valid string
    cout<<"\n";
    cout<<"\tPASSWORD : ";
    p =get_password();              /// function to get password
    person *per;                    /// pointer of class person
    if(ua==person::U)
        per = new user(u,p);        /// it will point to user
    if(ua==person::A)
        per = new admin(u,p);       /// it will point to admin
    int index;
    /// as login is virtual function it ensures that correct function is called, it returns true if username and password is present in that list and it also assigns index with the index in the vector that corresponds to this username and password
    if(per->login(index)){
        system("cls");
        per->homepage(index);       /// homepage is also virtual function and ensures that the correct homepage function is called
        return ;
    }
    else
        throw invalid_credential("\tINVALID CREDENTIALS, PLEASE TRY AGAIN\n\n");    /// throws exception if no username and password dosen't match with the data
}

/// Function for user signup
void persons::signup(){
    cout<<"\n\n\n";
    cout<<"\tBUS RESERVATION SYSTEM\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    cout<<"\tENTER FOLLOWING DETAILS\n\n";
    user *temp;                                                                 /// temporary pointer created
    temp = new user;                                                            /// space assigned to the pointer this data will be later added to the vector
    /// There are corresponding functions made to get valid data and returns it which will be called upon need
    cout<<"\tFIRST NAME : ";
    temp->fname=get_name();
    cout<<"\n";
    cout<<"\tLAST NAME : ";
    temp->lname=get_name();
    cout<<"\n";
    cout<<"\tUSERNAME : ";
    temp->username = get_username(1);
    cout<<"\n";
    cout<<"\tPASSWORD : ";
    temp->password = get_password();
    cout<<"\n\n";
    cout<<"\tMOBILE NUMBER : ";
    temp->mobile=get_mobile();
    cout<<"\n";
    cout<<"\tEMAIL ID : ";
    temp->email=get_email();
    users.push_back(*temp);
    delete temp;            /// delete space given to temp
    system("cls");
    start("\tSIGNED UP SUCCESSFULLY, PRESS 1 TO LOGIN\n\n");                                    /// calling start function again with the message passed in the argument
}

///Below are some 6 functions to check upon the validity
string persons::get_name(){
    try{
        string s;
        cin>>ws;
        getline(cin,s);
        /// this function ensures that name must not contain any space any must not contain any special character or number
        for(int i=0;i<s.size();i++){
            if((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z')){}
            else
                throw invalid_name();
        }
        return s;
    }
    catch(invalid_name i){
        i.print();
        return get_name();
    }
}

/// This function ensures that the mobile number is of 10 digits any only contains numbers
string persons::get_mobile(){
    try{
        string s;
        cin>>ws;
        getline(cin,s);
                                        /// below condition checks if entered data contains only 10 digits
        if(s.size()!=10){
            throw invalid_mobile();     /// if not 10 digits than it throws exception, thus directly goes to catch statement
        }
                                        /// below loop checks if every character is a number
        for(int i=0;i<10;i++){
            if(s[i]>='0' && s[i]<='9'){}
            else{
                throw invalid_mobile();
            }
        }
        return s;
    }
                                        /// throws exception of type invalid_mobile
    catch(invalid_mobile i){
        i.print();
        return get_mobile();
    }
}

                                            /// This function ensures that the email entered contains a username character '@' and a domain name in the order mentioned here
string persons::get_email(){
    try{
        string s;
        cin>>ws;
        getline(cin,s);
        int d=0,a=0;                    /// value of a will be increased if it finds character '@' and it string contains '.' than value of d is increased
        for(int i=0;i<s.size();i++){
            if(s[i]=='@')
                a++;
            if(s[i]=='.' && a==1)
                d++;
            if(s[i]==' ')
                throw invalid_email();
        }
                                        /// email must contain exactly one '@' and atleast one '.' after '@'
        if(a==1 && d>=1)
            return s;
        else
            throw invalid_email();
    }
                                        /// throws exception of class invalid_email
    catch(invalid_email i){
        i.print();
        return get_email();             /// function is called again if the username entered is invalid
    }
}

                                            /// This function returns string which is the password entered by the user/admin
string persons::get_password(){
    string pass ="";
    char ch;
    ch = _getch();
    while(ch != 13){                    ///character 13 is enter

            if(ch!=8){
                pass.push_back(ch);
                cout << '*';
            }
                ch = _getch();

    }
    return pass;
}

                                            /// Function to get_username
string persons::get_username(bool b){       /// takes argument 0 or 1 if argument is 0 it doesn't checks the availability of the username,
    try{                                    /// case of login and if argument is 1 it checks if username is available, case of signup
        string u;
        cin>>ws;
        getline(cin,u);
        if(username_isValid(u)){
            if(b){
                if(username_isavailable(u))
                    return u;
            }
            else{
                return u;
            }
        }
    }
    catch(invalid_username i){
        i.print();
        return get_username();              /// recalls itself if entered invalid username
    }
}

                                            /// Function returns true if username is valid i.e. it contains only alphanumeric characters and size is less than 30
bool persons::username_isValid(string &username){
                                            /// if more than 30 characters are entered than directly exception is thrown
	if(username.size()>30){
		throw invalid_username("\n\tUSERNAME CAN HAVE MAXIMUM 30 CHARACTERS : ");
		return 0 ;
	}
                                            /// else it checks if only alphanumeric characters are entered or not
	else{
		for(int i=0;i<username.size();i++){
			if( isalnum ( username[i] ) == 0 ){
                throw invalid_username("\n\tUSERNAME CAN ONLY HAVE ALPHABETS OR NUMBERS : ");
				return 0 ;
			}
		}
		return 1 ;                          /// returns 1 if exception is not thrown till the end
	}
}


                                            /// Below function returns true if username is available i.e. not present in the vector
bool persons::username_isavailable(string &username){
    for(int i=0;i<users.size();i++){
        if(username == users[i]){
            throw invalid_username("\n\tUSERNAME IS NOT AVAILABLE : ");
            return false;
        }
    }
    return true;
}

                                            /// below function returns true if string ua passed as argument is equal to the the username of object u
bool persons::operator == (string ua,user u){
    return ua==u.username;
}

                                            /// Below function return valid number which will be used for selecting a option here valid input would be from s to e and also exit
int persons::valid_input(int s,int e,int exit){
                                            /// it throws exception of class valid_input
    try{
        cout<<"\tSELECT ONE OPTION : ";
        string a;
        cin>>ws;
        getline(cin,a);                     /// this would take input as string
        if(a.size()>=2)                     /// if length of string is greater than or equal to 2 than it directly throws exception
            throw invalid_input("\n\tPLEASE ENTER VALID INPUT\n");
                                            /// if it satisfies the below condition than it directly return the value else throws exception
        if((a[0]-'0'>=s && a[0]-'0'<=e) || a[0]-'0'==exit){
            int n = a[0]-'0';
            return n;
        }
        throw invalid_input("\n\tPLEASE ENTER VALID INPUT\n");
    }
    catch(invalid_input v){
        v.print();
        return valid_input(s,e,exit);       /// if exception is thrown than the function is called again
    }
}

                                            /// Below function shows any message given as argument and than waits for few seconds and than continues the flow of the program
void persons::show_message(string s){
    cout<<"\n\n\n";
    cout<<"\tCHANGE DETAILS\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    cout<<s;
                                            /// Below loop creates a pause for few seconds
    for(int i=0;i<100000;i++){
        for(int i=0;i<9000;i++){

        }
    }
    system("cls");                          /// clears screen
}



///************************************************************ Constructors ******************************************************************************
                                            /// constructor for person class
persons::person::person(string u,string p,t ua){
    username = u;
    password = p;
    type = ua;
}
                                            /// constructor for user class it takes argument and directly calls constructor of person class
persons::user::user(string u,string p,t ua):person(u,p,ua){}

                                            /// constructor for admin class, it takes argument and directly calls constructor of person class
persons::admin::admin(string u,string p,t ua):person(u,p,ua){}


///****************************************************** Functions of user class *************************************************************************
/// function which checks if username and password matches with that present in the vector and also assigns corresponding index to index variable
bool persons::user::login(int &index){
    user *temp = static_cast<user*>(this);   /// static cast of this pointer which would be pointer of person class
                                            /// loop to check compare with the data in users vector
    for(int i=0;i<users.size();i++){
        if(*temp==users[i]){                ///*temp == users[i] implies *temp.operator == (user[i]), it returns true if username and password matches
            index = i;
            return true;                    /// if match is found than it returns true
        }
    }
    return false;                           /// it will reach here it true is not returned which indicates that no data with this username and password is present
}

//operator overloading
bool persons::user::operator==(user &compar){
    return username==compar.username && password==compar.password;      /// returns true if username and password both matches
}

/// homepage for user, it takes argument index which is the index of the user logged in, in the vector users
void persons::user::homepage(int index){
    user *temp = &users[index];             /// pointer to the logged in user thus every change is done directly in the vector usres
    cout<<"\n\n\n";
    cout<<"\tWELCOME, "<<temp->fname<<"\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
                                            /// below are the functions which can be access by the user
    cout<<"\t1. BOOK TICKETS\n\n";
    cout<<"\t2. VIEW BOOKING HISTORY\n\n";
    cout<<"\t3. CANCEL BOOKING\n\n";
    cout<<"\t4. CHANGE DETAILS\n\n";
    cout<<"\t5. LOGOUT\n\n";
    cout<<"\t9. EXIT\n\n";
    int n = valid_input(1,5,9);             /// here valid input would be 1 to 5 and 9, valid_input function is explained earlier
    if(n==1){
        _path(username);                    /// this is the function which will takes some details from user and directly books ticket for him , also username is passed as argument to keep track of which user has booked the ticket
        this->homepage(index);              /// after user has booked ticket he is returned back to homepage
    }
    if(n==2){
        ticket::vt[0].ticket::Ticket::show_all_bookings(username);  /// function call to show all previous booking of this user
        this->homepage(index);              /// after the function is exited user is directed back to homepage
    }
    if(n==3){
        ticket::vt[0].ticket::Ticket::show_all_bookings(username);  /// same function is called as was called for seeing booking history as first user will select which ticket to be cancelled
        this->homepage(index);              /// after exiting the above function user is directed back to homepage
    }
    if(n==4){
        system("cls");
        temp->change_details(index);        /// function to change details of the user
    }
    if(n==5){
        this->logout();                     /// function to logout
    }
    if(n==9){
        exit();                             /// function to exit the program
    }
}

                                            /// Function called to change any details of the user
void persons::user::change_details(int &index){
    cout<<"\n\n\n";
    cout<<"\tCHANGE DETAILS\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    /// below are the details which can be changes by user, username cannot be changed once set during signup
    cout<<"\t1. PASSWORD\n\n";
    cout<<"\t2. FIRST NAME\n\n";
    cout<<"\t3. LAST NAME\n\n";
    cout<<"\t4. MOBILE NUMBER\n\n";
    cout<<"\t5. EMAIL ID\n\n";
    cout<<"\t6. HOME\n\n";
    int n = valid_input(1,6,9);            /// here valid input is 1 to 6 and 9
    if(n==1){
        cout<<"\n\n\tPASSWORD : ";
        password = get_password();         /// function that takes password from the user and returns password
        system("cls");
        show_message("\tPASSWORD CHANGED SUCCESSFULLY! PLEASE WAIT\n\n");   /// argument passed will be shown for few seconds only
        change_details(index);             ///same function is called so if user needs to change some more details he can do so
    }
    if(n==2){
        cout<<"\n\n\tFIRST NAME : ";
        fname=get_name();
        system("cls");
        show_message("\tFIRST NAME CHANGED SUCCESSFULLY! PLEASE WAIT\n\n");     /// argument passed will be shown for few seconds
        change_details(index);
    }
    if(n==3){
        cout<<"\n\n\tLAST NAME : ";
        lname=get_name();
        system("cls");
        show_message("\tLAST NAME CHANGED SUCCESSFULLY! PLEASE WAIT\n\n");
        change_details(index);
    }
    if(n==4){
        cout<<"\n\n\tMOBILE NUMBER : ";
        mobile=get_mobile();
        system("cls");
        show_message("\tMOBILE NUMBER CHANGED SUCCESSFULLY! PLEASE WAIT\n\n");
        change_details(index);
    }
    if(n==5){
        cout<<"\n\n\tEMAIL : ";
        email=get_email();
        system("cls");
        show_message("\tEMAIL CHANGED SUCCESSFULLY! PLEASE WAIT\n\n");
        change_details(index);
    }
    if(n==6){
        system("cls");
        homepage(index);
    }
}

                                        /// Below function is called if user wants to logout
void persons::user::logout(){
    system("cls");
    cout<<"\n\n\n";
    cout<<"\tBUS RESERVATION SYSTEM\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    /// shows below message for a while and than calls function start again, from where he can exit or log in again
    cout<<"\tLOGGED OUT SUCCESSFULLY! PLEASE WAIT\n";
    for(int i=0;i<100000;i++){
        for(int j=0;j<7000;j++){

        }
    }
    system("cls");
    persons::start();
}

////****************************************************** Functions of admin class ************************************************************************
/// function that returns true if username and password matches with the data present in the vector admins
bool persons::admin::login(int &index){
    admin *temp = static_cast<admin*>(this);    /// static cast pointer this which would be pointer to person class
    for(int i=0;i<admins.size();i++){
        if(*temp==admins[i]){                   /// *temp == admins[i] is same as *temp.operator == (admins[i])
            index=i;
            return true;
        }
    }
    return false;                               /// reached here as because there would be no data that matches with the given username and password
}

/// function that returns true if username and password both matches
bool persons::admin::operator==(admin &compar){
    return username==compar.username && password==compar.password;
}

/// admin homepage
void persons::admin::homepage(int index){
    admin *temp = &admins[index];               /// pointer to object admin in the vector admins who has just logged in
    cout<<"\n\n\n";
    cout<<"\tWELCOME, "<<temp->employeeID<<"\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
                                                /// Below features can be access by the admin
    cout<<"\t1. SEARCH FOR BUS\n\n";
    cout<<"\t2. LOGOUT\n\n";
    cout<<"\t9. EXIT\n\n";
    int n = valid_input(1,2,9);                 ///here valid input would be 1 to 2 and 9
    if(n==1){
        bus::vb[0].bus::Bus::get_bus_details_admin();   /// direct call to a function that will get some details from admin and shows him the list of desired bus
        this->homepage(index);                  /// after exiting the function he is redirected to admin homepage
    }
    if(n==2){
        this->logout();                         /// function logout is called
    }
    if(n==9){
        exit();                                 /// function exit is called
    }
}

/// logout function, called when admin wants to logout
void persons::admin::logout(){
    system("cls");
    cout<<"\n\n\n";
    cout<<"\tBUS RESERVATION SYSTEM\n";
    cout<<"\n    *************************************************************************************************************************************************************\n";
    cout<<"\n";
    /// displays below message for few seconds and then calls that start function so he can login again to exit the program
    cout<<"\tLOGGED OUT SUCCESSFULLY! PLEASE WAIT\n";
    for(int i=0;i<100000;i++){
        for(int j=0;j<7000;j++){

        }
    }
    system("cls");                                      /// clears the screen
    persons::start();
}





int main(){
    load_data();                                        /// load data of buses and ticket from csv files
    persons::load_data();                               /// load data of users and admins from csv files
    persons::start();                                   /// called at the beginning, just after importing data
    persons::out_data();                                /// exports data of users and admins back to csv files
    out_data();                                         /// exports data of buses and tickets back to csv files
    return 0;
}
