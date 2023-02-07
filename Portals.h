#ifndef PORTAL_H
#define PORTAL_H
#include<iostream>
#include"dbconn.h"
#include"error_handler.h"
#include"clocking.h"
#include"member.h"
#include<string>
#include"clocking.h"

//pre booking option (By day)
using namespace std;

class Portals {
private :
    error_handler handle;
    clocking clock;
   
    member opt;
    string name, ic, address, phone, pwd, id;
   
    
public :
    void MainPortal();
    void login_menu();
	void AdminPortal();
	void StaffPortal(string);
	void MemberPortal(string);
    void Renew_Membership(string);
    void checking(string);
    void Register();
    void adminLogin();
    void staffLogin();
    void memberLogin();
    void reset_pwd();
    void a_forgot_pwd();
    void s_forgot_pwd();
    void m_forgot_pwd();
    void Retry();
    void report();
    void daily_report();
    void check_time(string);

    void AdminRegistration();

    void StaffRegistration();
    
    void monthly_report();
    void memberRegistration();
    void sales_calc(string);

    void ic_vld(string id);
    
};

void Portals::sales_calc(string month)
{
    system("cls");
    int qstate;
    //= '" + to_string(month) + "'
    string courts_calc = "select booking_table.court_id , COUNT(booking_table.booking_id) from booking_table JOIN court_table on booking_table.court_id = court_table.court_id JOIN payment_table on booking_table.booking_id = payment_table.booking_id where MONTH(payment_table.payment_date)= '" + (month)+"' Group by court_id; ";
    const char* q = courts_calc.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        cout << "Frequncy of court booked as per month  " << month << endl;
        cout << "-------------------------------------\n";
        printf("| %-10s | %-20s |\n", "Court ID", "Total Bookings");

        cout << "-------------------------------------\n";
        while ((row = mysql_fetch_row(res)))
        {
            //mode of court 

           
            printf("| %-10s | %-20s |\n", row[0], row[1]);
        }

            printf("-------------------------------------\n");

            //mode of slots
            string courts_calc = "select booking_table.start_time , booking_table.end_time,time_table.time_stamp , COUNT(booking_table.booking_id) from booking_table JOIN payment_table on booking_table.booking_id = payment_table.booking_id JOIN time_table on time_table.time_stamp = booking_table.time_stamp where MONTH(payment_table.payment_date)= '" + (month)+"' Group by time_stamp order by COUNT(booking_table.booking_id) desc;";
            const char* q = courts_calc.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);

            if (!qstate)
            {
                cout << "\n\nFrequency fo Times Booked  " << endl;
                cout << "----------------------------------------------------------------------\n";
                printf("| %-20s | %-20s |%-10s |%-10s |\n", "Time Stamp", "Start Time", "End time", "Booked");
                cout << "----------------------------------------------------------------------\n";
                while ((row = mysql_fetch_row(res)))
                {
                   

                   
                    
                    printf("| %-20s | %-20s |%-10s |%-10s |\n", row[2], row[0], row[1], row[3]);

                   
                }
                printf("-----------------------------------------------------------------------\n");
            }
            string perc = "SELECT SUM(amount) AS CURRENT,MONTH(payment_table.payment_date),YEAR(payment_table.payment_date), ROUND(SUM(amount) * 100/(SELECT SUM(AMOUNT) FROM payment_table),2) as 'Percentage of Difference' From payment_table group by MONTH(payment_table.payment_date),YEAR(payment_table.payment_date) ORDER BY YEAR(payment_table.payment_date) DESC;";
            const char* qz = perc.c_str();
            qstate = mysql_query(conn, qz);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                cout << "\n\nSales Difference  " << endl;
                cout << "--------------------------------------------------------------------------------------\n";
                printf("| %-20s | %-20s |%-10s |%-25s |\n", "Year", "Month", "Sales", "Percentage difference");
                cout << "----------------------------------------------------------------------\n";
                while ((row = mysql_fetch_row(res)))
                {




                    printf("| %-20s | %-20s |%-10s |%-25s |\n", row[2], row[1], row[0], row[3]);


                }
                printf("---------------------------------------------------------------------------------------\n");

                cout << "Back to main menu\n";
                system("PAUSE");
                AdminPortal();
            }
           
        
    }

}


void Portals::report()
{
    ret:
    system("cls");
    cout << "1. Display monthly reports\n";
    cout << "2. View by date\n";
    
    int opt;
    cin >> opt;
    switch (opt)
    {

    case 1:
    {
        monthly_report();
        break;
    }
    case 2:
        daily_report();
        break;


    default:
        goto ret;
        break;
    }
}


void Portals::monthly_report()
{
    x:
    system("cls");
    int month;
    int qstate;
    cout << "[1] January   [4] April  [7] July       [10] October" << endl;
    cout << "[2] February  [5] May    [8] August     [11] November" << endl;
    cout << "[3] March     [6] May    [9] September  [12] December" << endl;
    cout << "\n Choose a month by inputing [1] - [12] -> ";
    cin >> month ;
    // validation for month entered
    if (month >= 1 || month < 10)
    {
        string sub = "0";
        month = month + stoi(sub);
    }

    string select_query = "select MONTH(payment_date) as Month, payment_table.booking_id,payment_table.register_id ,payment_table.amount from payment_table where MONTH(payment_table.payment_date) = '" + to_string(month)+"'group by register_id,booking_id ";
    const char* q = select_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {

        if (mysql_num_rows(res) <= 0)
        {
            g:
            int optl;
            system("cls");
            cout << "No data available";
            cout << "\n1. Research for different month";
            cout << "\n2. Back to Admin Portal";
            cin >> optl;
            switch (optl)
            {
            case 1:
                goto x;

            case 2:
                AdminPortal();

            default:
                handle.invalid_option();
                goto g;
            }
        }
        cout << "--------------------------------------------------------\n";
        printf("| %-10s | %-10s | %-13s |%-10s |\n", "Month", "Bookings","Registers", "Amount");
        while ((row = mysql_fetch_row(res)))
        {
            
           
            printf("| %-10s | %-10s | %-13s |%-10s |\n", row[0],row[1], row[2], row[3]);
            

            
            //cout << row[0] << "|" << row[1] << "|" << row[2] << endl;
            
        }
        
        printf("-------------------------------------------------------\n");
        cout << "Total";
        
        string select_query = "select SUM(payment_table.amount) from payment_table where MONTH(payment_table.payment_date) = '" + to_string(month) + "'";
        const char* q = select_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        if (!qstate)
        {
            while ((row = mysql_fetch_row(res)))
            {
                printf("%-15s  %-18s  |%-10s |\n", "", "", row[0]);
                
            }
            printf("-------------------------------------------------------\n");
        }
        int iko;
        cout << "\n1. Show more details";
        cout << "\n2. Search for another month";
        cout << "\n3. Admin Portal";
        cin >> iko;
        switch (iko)
        {
        case 1:
            sales_calc(to_string(month));
            break;

        case 2:
            goto x;
            break;

        case 3:
            AdminPortal();
            break;

        }

    }
}


void Portals::daily_report()
{
    x:
    int qstate;
    string ddate;
    cout << "Enter date of sales to be searched (yyyy-mm-dd)\n";
    cin >> ddate;
    string select_query = "select payment_table.payment_date, payment_table.booking_id,payment_table.register_id, payment_table.amount from  payment_table where payment_table.payment_date = '" + ddate + "'";
    const char* q = select_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {

        if (mysql_num_rows(res) <= 0)
        {
        g:
            int optl;
            system("cls");
            cout << "No data available";
            t:
            cout << "\n1. Re-search another day";
            cout << "\n2. Back to Admin Portal";
            cin >> optl;
            switch (optl)
            {
            case 1:
                goto x;

            case 2:
                AdminPortal();

            default:
                handle.invalid_option();
                goto g;
            }
        }
        cout << "-------------------------------------------------------\n";
        printf("| %-10s | %-10s | %-13s |%-10s |\n", "Date", "Bookings", "Registers", "Amount");
        while ((row = mysql_fetch_row(res)))
        {



            printf("| %-10s | %-10s | %-13s |%-10s |\n", row[0], row[1], row[2], row[3]);


            //cout << row[0] << "|" << row[1] << "|" << row[2] << endl;

        }

        printf("-------------------------------------------------------\n");
        cout << "Total";
        string select_query = "select SUM(payment_table.amount) from payment_table where(payment_table.payment_date) = '" + ddate + "'";
        const char* q = select_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        if (!qstate)
        {
            while ((row = mysql_fetch_row(res)))
            {
                printf("%-15s  %-18s  |%-10s |\n", "", "", row[0]);

            }
            printf("-------------------------------------------------------\n");
           
            goto t;
        }
        cout << "\nBack to main menu\n";
        system("PAUSE");
        AdminPortal();
    }
}

//STEP1 
void Portals::MainPortal()
{
    dbconn::ConnectionFunction();

    cout<<"Date   :" <<setw(10)<<clock.tommorow;
    cout <<"\nTime   :" <<setw(10)<< clock.time1;
    int menu_item = 0;
    cout << "\n\nH23 FUTSAL MANAGEMENT SYSTEM";
    cout << "\n1. Login";
    cout << "\n2. Register";
    cout << "\n3. Forgot password";
    cout << "\n4. Exit";
    handle.directory(1);
    cin >> menu_item;


    switch (menu_item)
    {

    case 1: 
    {

        login_menu();
        break;
    }


    case 2: {
        Register();
        break;
    }

    case 3: {
        reset_pwd();
        break;
    }

    case 4: {
        system("cls");
        cout << "See you";
        return;

    default:
        handle.invalid_option();
        MainPortal();
    }


    }





    return;
}
// STEP 2
void Portals::login_menu()
{


    system("cls");
    int login_opt;
    cout << "Login";
    cout << "\n1. Admin";
    cout << "\n2. Staff";
    cout << "\n3. Member";
    cout << "\n4. Main menu\n";
    cout << "\nPlease select a login menu";
    handle.directory(1);
    cin >> login_opt;

    switch (login_opt)
    {

    case 1:
        system("cls");
        adminLogin();
        break;


    case 2:
        system("cls");
        staffLogin();
        break;


    case 3:
        system("cls");
        memberLogin();
        break;



    case 4:

        MainPortal();
        break;

    default:
        handle.invalid_option();
        login_menu();
        break;


    }



}


void Portals::adminLogin()
{
    system("color 0C");
    system("cls");
    int astate;
    Portals admin;
    //control the input length
    cout << "Hi admin!" << endl;
    cout << "Please enter your id\n";

    cin >> admin.id;
    cout << "Please enter your password\n";
    int ch, chr =0;
 
  do
  {
   ch = _getch();

   if (ch == 13 || ch == ' ')
   {
    break;
   }
   if ((ch == 8 || ch == 127) && !admin.pwd.empty())
   {
    std::cout << "\b \b";
    admin.pwd.erase(admin.pwd.size() - 1);
    chr--;
   }
   else
   {
    admin.pwd += ch;
    std::cout << "*";
    chr++;
   }
  } while (ch != 13 || ch != ' ');



    string finduser_query = "select * from admin_table where admin_id like BINARY '%" + admin.id + "%' and admin_pwd like BINARY '%" + admin.pwd + "%' ";
    const char* qn = finduser_query.c_str();
    astate = mysql_query(conn, qn);
    res = mysql_store_result(conn);


    do
        if ((row = mysql_fetch_row(res)))
        {
            cout << "\nLogin success\n\n";
            system("cls");
            AdminPortal();

        }
        else
        {
        retry:
            int login_retry_menu;
            cout << "\nWrong id or password\n";
            cout << "1. Retry\n";
            cout << "2. Login menu\n";
            cin >> login_retry_menu;
            switch (login_retry_menu)
            {
            case 1:

                system("cls");
                adminLogin();
                break;

            case 2:

                login_menu();
                break;

            default:
                cout << "Invalid option";
                goto retry;
                break;

            }


        }
    while (astate);




}


void Portals::staffLogin()
{
    system("color 0D");
    system("cls");
    Portals staff;
    int qstate;

    cout << "Hi staff" << endl;
    cout << "Please enter your id\n";
    cin >> staff.id;
    cout << "Please enter your password\n";
    int ch, chr = 0;

    do
    {
        ch = _getch();

        if (ch == 13 || ch == ' ')
        {
            break;
        }
        if ((ch == 8 || ch == 127) && !staff.pwd.empty())
        {
            std::cout << "\b \b";
            staff.pwd.erase(staff.pwd.size() - 1);
            chr--;
        }
        else
        {
            staff.pwd += ch;
            std::cout << "*";
            chr++;
        }
    } while (ch != 13 || ch != ' ');

    string findbyid_query = "select * from staff_table where staff_id like BINARY '%" + staff.id + "%' and staff_pwd like BINARY '%" + staff.pwd + "%' ";
    const char* qn = findbyid_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);

    do
        if ((row = mysql_fetch_row(res)))
        {
            cout << "\nLogin success\n\n";
            system("cls");
            StaffPortal(staff.id);

        }
        else
        {

            int login_retry_menu;
            cout << "\nWrong id or password\n";
            cout << "1. Retry\n";
            cout << "2. Login menu\n";
            cin >> login_retry_menu;
            switch (login_retry_menu)
            {
            case 1:

                system("cls");
                staffLogin();
                break;

            case 2:

                login_menu();
                break;

            default:
                cout << "Invalid option";
                staffLogin();
                break;

            }


        }
    while (qstate);


}



void Portals::memberLogin()
{
    system("color 0B");
    system("cls");
    Portals member;

    int qstate;
    cout << "Hi Member" << endl;
    cout << "Please enter your id\n";
    cin >> member.id;
    cout << "Please enter your password\n";
    int ch, chr = 0;

    do
    {
        ch = _getch();

        if (ch == 13 || ch == ' ')
        {
            break;
        }
        if ((ch == 8 || ch == 127) && !member.pwd.empty())
        {
            std::cout << "\b \b";
            member.pwd.erase(member.pwd.size() - 1);
            chr--;
        }
        else
        {
            member.pwd += ch;
            std::cout << "*";
            chr++;
        }
    } while (ch != 13 || ch != ' ');

    string findbyid_query = "select * from member_table where mem_id like BINARY'%" + member.id + "%' and mem_pwd like BINARY '%" + member.pwd + "%' ";
    const char* qn = findbyid_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);

    do

        if ((row = mysql_fetch_row(res)))
        {
            cout << "\nLogin success\n\n";
            system("cls");
            opt.MemberPortal(member.id);

        }
        else
        {

            int login_retry_menu;
            cout << "\nWrong id or password\n";
            cout << "1. Retry\n";
            cout << "2. Login menu\n";
            cin >> login_retry_menu;
            switch (login_retry_menu)
            {
            case 1:

                system("cls");
                memberLogin();
                break;

            case 2:

                login_menu();
                break;

            default:
                handle.invalid_option();
                memberLogin();
                break;

            }


        }while (qstate);


}

void Portals::Register()
{

    int reg_opt;
    system("cls");
    cout << "Registration Menu\n";
    cout << "1. Admin" << endl;
    cout << "2. Staff" << endl;
    cout << "3. Member" << endl;
    cout << "4. Back to Main" << endl;
    handle.directory(1);
    cout << "Please enter a selction:";
    cin >> reg_opt;

    system("cls");
    switch (reg_opt)
    {
    case 1:
        cout << "Welcome to Admin Registration Portal";
        AdminRegistration();
        break;

    case 2:
        cout << "Welcome to Staff Registration Portal";
        StaffRegistration();
        break;

    case 3:
        cout << "Welcome to Member Registration Portal";
        memberRegistration();
        break;


    case 4:
        system("cls");
        MainPortal();
        break;



    default:
        handle.invalid_option();
        Register();
        break;

    }

}

void Portals::reset_pwd()
{

    int opt;
    system("cls");

    cout << "PASSWORD RESET MENU";
    cout << "\n1. Admin Reset";
    cout << "\n2. Staff reset";
    cout << "\n3. Member reset\n";
    cin >> opt;
    switch (opt)
    {

    case 1:
    {

        a_forgot_pwd();
        system("cls");
        break;
    }


    case 2: {
        s_forgot_pwd();
        break;
    }

    case 3: {
        m_forgot_pwd();
        break;
    }

    default:
    {
        handle.invalid_option();
        MainPortal();
    }


    }








    return;
}














void Portals::AdminPortal()
{
    ret:
    system("color08");
    int portal_opt;
    system("cls");
    
    cout << "What are you up to";
    cout << "\n1. Add Court";
    cout << "\n2. Delete staff records";
    cout << "\n3. View Sales Report";
    cout << "\n4. Main menu";
    cout << "\n5. Exit";
    handle.directory(2);
    cin >> portal_opt;
    switch (portal_opt)
    {
        case 1:
        {
        retry:
            int qstate;
            string court_id, court_num, avail;
            cin.ignore(1, '\n');
            cout << "\nEnter Court Id: ";
            getline(cin, court_id);
            cout << "Enter Court Number: ";
            cin >> court_num;
            cout << "Enter Availability: ";
            cin >> avail;
            string findbyname_query = "select * from court_table where court_id = '" + court_id + "' and court_num = '" + court_num + "' ";
            const char* qn = findbyname_query.c_str();
            qstate = mysql_query(conn, qn);




            if (!qstate)
            {
                res = mysql_store_result(conn);

                if (res->row_count == 1)
                {
                    cout << "Court Id has been taken please retry ";
                    goto retry;
                }

                else
                {
                    string insert_query = "insert into court_table(court_id, court_num , court_avail) values ('" + court_id + "','" + court_num + "','" + avail + "')";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                
                    if (!qstate)
                    {
                    
                        int ch;
                        cout << "Added court -> " << court_id;
                        Retry();
                        

                    }
                    else
                    {
                        cout << "Server disconnected" << endl;
                        goto retry;
                    }
                }

            }
        }
        break;


        case 2:

        {
            int qstate;
            
           
            retry1:
                system("cls");
                cout << "Enter staff id to be deleted\n";
                cin >> id;
                string findbyid_query = "select * from staff_table where staff_id = '" + id + "'";
                const char* qn = findbyid_query.c_str();
                qstate = mysql_query(conn, qn);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    if (mysql_num_rows(res) <= 0)
                    {

                        cout << "No staffs as " << id << endl << endl;

                        cout << "Going back to admin portal\n";
                        system("PAUSE");
                        AdminPortal();
                    }

                    while (row = mysql_fetch_row(res))
                    {

                        

                        system("cls");
                        cout << "-------------------------------------------------------------------------------------------------------------------------\n";
                        printf("| %-10s | %-20s | %-30s | %-30s | %-15s |\n", "Staff Name", "Staff ID", "Identification Card", "Address", "Phone");
                        printf("| %-10s | %-20s | %-30s | %-30s | %-15s |\n", row[1], row[0], row[2], row[3], row[4]);

                        printf("-------------------------------------------------------------------------------------------------------------------------\n");

                        string crack;
                        cout << "Confirm deleting the staff by typing DONE\n";
                        cin >> crack;
                        if (crack == "DONE")
                        {
                            string findbyid_query = "delete from staff_table where staff_id = '" + id + "'";
                            const char* qn = findbyid_query.c_str();
                            qstate = mysql_query(conn, qn);
                            res = mysql_store_result(conn);
                            if (!qstate)
                            {


                                int op;
                                cout << "Deleted staff " + id << endl;
                            retry4:
                                cout << "\Where would you like to go";
                                cout << "\n\n\n1. Back to portal ";
                                cout << "\n2. Back to main";
                                cout << "\n3. Exit";
                                cin >> op;
                                switch (op)
                                {
                                case 1:
                                    AdminPortal();
                                    break;
                                case 2:
                                    MainPortal();

                                case 3:
                                    cout << "Exiting program\n";
                                    system("PAUSE");

                                default:
                                    handle.invalid_option();
                                    goto retry4;

                                }



                            }
                        }
                        else
                        {
                            
                            int red;
                            handle.invalid_details(7);
                            system("PAUSE");
                        y:
                            cout << "Press 1 to exit or 2 to retry";
                            cin >> red;
                            if (red == 1)
                            {
                                AdminPortal();
                            }
                            else if (red == 2)
                            {
                                goto retry1;
                            }
                            else
                            {
                                handle.invalid_option();
                                goto y;
                                break;
                            }
                            
                        }





                    }

                }
                else
                {
                    handle.server_down();
                }

            
            
        }
        break;



        case 3:
        {
            report();
        }
        break;

        case 4:
        {
           MainPortal();
        }
        break;

        case 5:
        {
            cout << "Exiting program";
            return;
        }
        break;

        default:
        {
            handle.invalid_option();
            system("PAUSE");
            goto ret;
        }
        break;

    }
}
void Portals::Retry()
{
ret:
    cout << "\n\nWhere to next";
    int ch;
    cout << "\n1. Admin portal";
    cout << "\n2. Main menu";
    cout << "\n3. Exit";

    cin >> ch;
    switch (ch)
    {
    case 1:
        AdminPortal();
        break;

    

    case 2:
        cout << "Logging out";
        MainPortal();

        break;

    case 3:
        cout << "Exiting program";
        return;
        break;

    default:
        handle.invalid_option();
        system("PAUSE");
        goto ret;

    }
}
void Portals::StaffPortal(string staff_id)
{
    system("color 0D");
    int portal_opt;
    cout << "Hey " + staff_id;

    cout << "\n1. Find member";
    cout << "\n2. Search courts";
    cout << "\n3. Back to main";
    handle.directory(3);
    cin >> portal_opt;
    switch (portal_opt)
    {
    case 1:
        checking(staff_id);
        break;


    case 2:
    {
        
             
        check_time(staff_id);
        break;
    }

    case 3:
        MainPortal();
        break;

    default:
        cout << "trial";

    }
}


void Portals::check_time(string staff_id)
{
    int qstate;
x:
    string court_id;
    cout << "Enter court id to be searched\n";
    cin >> court_id;
    string findbycourt_query = "select court_id from court_table where court_id = '" + court_id + "'";
    const char* q = findbycourt_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if(!qstate)
    {
        if (mysql_num_rows(res) <= 0)
        {
        gg:
           
            handle.invalid_details(4);
            system("PAUSE");
            system("cls");
            cout << "1. Retry with different court_id\n";
            cout << "2. Back to portal\n";
            handle.directory(4);
            int opt;
            cin >> opt;
            if (opt == 1)
            {

                goto x;
            }
            else if (opt == 2)
            {
                system("cls");
                StaffPortal(staff_id);
            }
            else
            {
                handle.invalid_option();
                goto gg;
            }
            

            
        }

        else
        {
            string findbycourt_query = "SELECT time_table.start_time , time_table.end_time FROM time_table,payment_table WHERE NOT EXISTS(SELECT * FROM booking_table,payment_table WHERE time_table.time_stamp = booking_table.time_stamp and court_id = '" + court_id + "' and booking_table.booking_id = payment_table.booking_id and payment_table.payment_date = '" + clock.tommorow + "') group by start_time asc having (time_table.start_time > '" + clock.time1 + "')";
            const char* q = findbycourt_query.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);
            if (!qstate)
            {


                while ((row = mysql_fetch_row(res)))

                {
                    if (mysql_num_rows(res) <= 0)
                    {
                        cout << "No timeslots available\n";

                        system("PAUSE");
                        system("cls");
                        cout << endl;
                    xy:
                        cout << "1. Retry with different court_id\n";
                        cout << "2. Back to portal\n";
                        int opt;
                        cin >> opt;
                        if (opt == 1)
                        {

                            goto x;
                        }
                        else if (opt == 2)
                        {
                            system("cls");
                            StaffPortal(staff_id);
                        }
                        else
                        {
                            handle.invalid_option();
                            goto xy;
                        }
                    }


                    else
                    {

                        cout << row[0] << "-" << row[1] << endl;

                    }


                }
                cout << endl;
                goto xy;



            }
        }
    }



}




void Portals::checking(string staff_id)
{
retx:
    string member_id;
    cout << "Enter Member id to be searched\n";
    cin >> member_id;
    int qstate;
    
    string findbyid_query = "select* from member_table JOIN registration_table on member_table.mem_id = registration_table.mem_id where member_table.mem_id = '" + member_id + "'";
    const char* qn = findbyid_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {


        if ((row = mysql_fetch_row(res)))
        {


            system("cls");
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            printf("| %-10s | %-20s | %-40s | %-13s | %-15s | %-15s | %-10s | %-10s |\n", "Name", "Identification Card", "Address", "Phone", "Member since", "Member till", "Points", "Membership");
            printf("| %-10s | %-20s | %-40s | %-13s | %-15s | %-15s | %-10s | %-10s |\n", row[1], row[2], row[3], row[4], row[6], row[7], row[8], row[12]);

            printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
           
            string d1 = row[7];
            string d2 = row[6];
            string date_query = "select(DATEDIFF('" + d1 + "','" + d2 + "')) ,mem_id from member_table where member_table.mem_id = '" + member_id + "'";
            const char* qn = date_query.c_str();
            qstate = mysql_query(conn, qn);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                while ((row = mysql_fetch_row(res)))
                {
                    
                    cout << "Membership expires in " << row[0] << " days";
                }
            }

            int retry_ii;
            cout << "\n1. Re-Search ";
            cout << "\n2. Exit to staff portal\n";
            cin >> retry_ii;

            if (retry_ii == 1)
            {
                goto retx;
            }
            else if (retry_ii == 2)
            {
                system("cls");
                StaffPortal(staff_id);
            }
            else
            {
                handle.invalid_option();
            }
            



        }
        else if (mysql_num_rows(res) <= 0)
        {
            int retry_i;
            handle.invalid_details(4);

            cout << "\n1. Retry ";
            cout << "\n2. Exit to staff portal\n";
            cin >> retry_i;

            if (retry_i == 1)
            {
                system("cls");
                goto retx;
            }
            else if (retry_i == 2)
            {
                system("cls");
                StaffPortal(staff_id);
            }
            else
            {
                handle.invalid_option();
            }
        }
       
    }
    

}

void Portals::a_forgot_pwd()
{
    Portals admin_pwd;
    int qstate;
retry:
    cout << "Enter your AdminID/Name/Phone Number\n";
    cin >> admin_pwd.id;
    string finduser_query = "select * from admin_table where admin_id = '" + admin_pwd.id + "' or admin_name = '" + admin_pwd.id + "'or  admin_phone = '" + admin_pwd.id + "' ";
    const char* qn = finduser_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);

    if (!qstate)
    {
        if (mysql_num_rows(res) <= 0)
        {
       
            
            
            cout << "Invalid Admin Details\n";                      
            system("PAUSE");
            MainPortal();

            
        }
        if ((row = mysql_fetch_row(res)))
        {
        p:

            cout << "Enter  Password consisting 8 characters:\n ";
            cin >> admin_pwd.pwd;
            if (admin_pwd.pwd.length() != 8)
            {
                handle.invalid_details(5);
                goto p;

            }
            
            string updatepwd_query = "update admin_table set admin_pwd = '" + admin_pwd.pwd + "' where admin_id = '" + admin_pwd.id + "' or admin_name = '" + admin_pwd.id + "'or  admin_phone = '" + admin_pwd.id + "'";
            const char* qn = updatepwd_query.c_str();
            qstate = mysql_query(conn, qn);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                cout << "Succesfully changed password\n";
                system("PAUSE");
                MainPortal();
            }
        }
        else
        {
            ret :
            int min;
            handle.invalid_details(6);
            system("PAUSE");
            system("cls");
            cout << "1.Retry\n";
            cout << "2.Reset menu\n";
            cout << "3.Main menu\n";
            cin >> min;
            switch (min)
            {
            case 1:
                goto retry;
                break;

            case 2:
                reset_pwd();
                break;

            case 3:
                MainPortal();
                break;

            default:
                handle.invalid_option();
                system("cls");
                goto ret;
                break;

            }


        }

        //string updatepoints_query = "update member_table set mem_points = mem_points - '1000' where mem_id like '" + member_id + "'";

    }
    

}

void Portals::s_forgot_pwd()
{
    Portals staff_pwd;
    int qstate;
retry:
    cout << "Enter your Staff ID/Name/Phone Number\n";
    cin >> staff_pwd.id;
    string finduser_query = "select * from staff_table where staff_id = '" + staff_pwd.id + "' or admin_name = '" + staff_pwd.id + "'or  admin_phone = '" + staff_pwd.id + "' ";
    const char* qn = finduser_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        if (mysql_num_rows(res) <= 0)
        {



            cout << "Invalid Staff DEtails\n";
            system("PAUSE");
            MainPortal();


        }
        if ((row = mysql_fetch_row(res)))
        {
        p:

            cout << "Enter  Password consisting 8 characters:\n ";
            cin>> staff_pwd.pwd;
            if (staff_pwd.pwd.length() != 8)
            {
                handle.invalid_details(5);
                goto p;

            }
            string updatepwd_query = "update staff_table set staff_pwd = '" + staff_pwd.pwd + "' mem_id = '" + staff_pwd.id + "' or mem_name = '" + staff_pwd.id + "'or  mem_phone = '" + staff_pwd.id + "'";
            const char* qn = updatepwd_query.c_str();
            qstate = mysql_query(conn, qn);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                cout << "Succesfully changed password\n";
                system("PAUSE");
                MainPortal();
            }

        }
        else
        {
            ret:
            int min;
            handle.invalid_details(6);
            system("PAUSE");
            system("cls");
            cout << "1.Retry\n";
            cout << "2.Reset menu\n";
            cout << "3.Main menu\n";
            cin >> min;
            switch (min)
            {
            case 1:
                goto retry;
                break;

            case 2:
                reset_pwd();
                break;

            case 3:
                MainPortal();
                break;

            default:
                handle.invalid_option();
                system("cls");
                goto ret;
                break;

            }


        }
        //string updatepoints_query = "update member_table set mem_points = mem_points - '1000' where mem_id like '" + member_id + "'";


    }
}


void Portals::m_forgot_pwd()
{
    Portals member_pwd;
    int qstate;
retry:
    cout << "Enter your Member ID/Name/Phone Number\n";
    cin >> member_pwd.id;
    string finduser_query = "select * from member_table where mem_id = '" + member_pwd.id + "' or mem_name = '" + member_pwd.id + "'or  mem_phone = '" + member_pwd.id + "' ";
    const char* qn = finduser_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        if (mysql_num_rows(res) <= 0)
        {



            cout << "Invalid Member Details\n";
            system("PAUSE");
            MainPortal();


        }
        if ((row = mysql_fetch_row(res)))
        {
        p:

            cout << "Enter  Password consisting 8 characters:\n ";
            cin>> member_pwd.pwd;
            if (member_pwd.pwd.length() != 8)
            {
                handle.invalid_details(5);
                goto p;

            }
            string updatepwd_query = "update member_table set mem_pwd = '" + member_pwd.pwd + "' where mem_id = '" + member_pwd.id + "' or mem_name = '" + member_pwd.id + "'or  mem_phone = '" + member_pwd.id + "'";
            const char* qn = updatepwd_query.c_str();
            qstate = mysql_query(conn, qn);
            res = mysql_store_result(conn);

            if (!qstate)
            {
                cout << "Succesfully changed password\n";
                system("PAUSE");
                MainPortal();
            }




        }
        else
        {
            ret :
            int min;
            handle.invalid_details(6);
            system("PAUSE");
            system("cls");
            cout << "1.Retry\n";
            cout << "2.Reset menu\n";
            cout << "3.Main menu\n";
            cin >> min;
            switch (min)
            {
            case 1:
                goto retry;
                break;

            case 2:
                reset_pwd();
                break;

            case 3:
                MainPortal();
                break;

            default:
                handle.invalid_option();
                system("cls");
                goto ret;
                break;

            }


        }
        //string updatepoints_query = "update member_table set mem_points = mem_points - '1000' where mem_id like '" + member_id + "'";


    }
}


void Portals::ic_vld(string id)
{
    if (stoi(id) < 12)
    {
        
    }
}



//registration
void Portals::AdminRegistration()
{
   
    Portals admin;
    int qstate;
    cin.ignore(1, '\n');//ignores line or whitespace
    cout << "\nEnter Name :\n ";
    getline(cin, admin.name);
id:
    cout << "Enter Identification Card Number (022345678910) :\n ";
    getline(cin, admin.ic);
    
        
        for (int i = 0; i < admin.ic.length(); i++)
        {
            if (!isdigit(admin.ic[i])|| admin.ic.length()<12 || admin.ic.length() > 12)
            {
                handle.invalid_details(1);
                goto id;
            }

        }
        
    
    
    cout << "Enter Admin Address:\n ";
    getline(cin, admin.address);
ph:
    cout << "Enter Admin Phone No (0123456789) :\n ";
    getline(cin, admin.phone);
    for (int i = 0; i < admin.phone.length(); i++)
    {
        if (!isdigit(admin.phone[i])|| admin.phone.length()<10 || admin.phone.length() > 11)
        {
            handle.invalid_details(2);
            goto ph;
        }

    }

retry:
    cout << "Enter a admin id :\n ";
    getline(cin, admin.id);
    string findbyname_query = "select * from admin_table where admin_id = '" + admin.id + "'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
   


    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            handle.invalid_details(3);
            goto retry;
        }
        else
        {

           
            p:
            cout << "Enter Member Password consisting 8 characters:\n ";
            getline(cin, admin.pwd);
            if (admin.pwd.length() != 8)
            {
                handle.invalid_details(5);
                goto p;

            }
            string insert_query = "insert into admin_table (admin_name, admin_ic, admin_address, admin_phone, admin_id, admin_pwd) values ('" + admin.name + "','" + admin.ic + "','" + admin.address + "','" + admin.phone + "','" + admin.id + "','" + admin.pwd + "')";
            const char* q = insert_query.c_str();
            qstate = mysql_query(conn, q);


            if (!qstate)
            {
                
                cout << "---------------------------\n";
                cout << "Registered successfully";
                cout << "\n---------------------------\n";
                cout << "Proceed to login screen\n";
                system("PAUSE");
                adminLogin();




            }
            else
            {
                cout << "Connection failed" << endl;
                goto retry;
            }

        }
    }
}



void Portals::StaffRegistration()
{
    int qstate;
    Portals staff;
    cin.ignore(1, '\n');
    cout << "\nEnter Staff Name: ";
    getline(cin, staff.name);
id:
    cout << "Enter Identification Card Number: ";
    getline(cin, staff.ic);
    for (int i = 0; i < staff.ic.length(); i++)
    {
        if (!isdigit(staff.ic[i]) || staff.ic.length() < 12 || staff.ic.length() > 12)
        {
            handle.invalid_details(1);
            goto id;
        }

    }
    cout << "Enter Staff Address: ";
    getline(cin, staff.address);
ph:
    cout << "Enter Staff Phone No: ";
    getline(cin, staff.phone);
    for (int i = 0; i < staff.phone.length(); i++)
    {
        if (!isdigit(staff.phone[i]) || staff.phone.length()<10 || staff.phone.length() >11)
        {
            handle.invalid_details(2);
            goto ph;
        }

    }



retry:
    cout << "Enter a Staff id  : ";
    getline(cin, staff.id);
    string findbyname_query = "select * from staff_table where staff_id = '" + staff.id + "'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    



    if (!qstate)
    {
        res = mysql_store_result(conn);


       
        if (res->row_count == 1)
        {
            handle.invalid_details(3);
            goto retry;
        }
        else
        {
            p:

            cout << "Enter  Password consisting 8 characters:\n ";
            getline(cin, staff.pwd);
            if (staff.pwd.length() != 8)
            {
                handle.invalid_details(5);
                goto p;

            }
            string insert_query = "insert into staff_table (staff_name, staff_ic, staff_address, staff_phone, staff_id, staff_pwd) values ('" + staff.name + "','" + staff.ic + "','" + staff.address + "','" + staff.phone + "','" + staff.id + "','" + staff.pwd + "')";
            const char* q = insert_query.c_str();
            qstate = mysql_query(conn, q);



            if (!qstate)
            {
                cout << "---------------------------\n";
                cout << "Registered successfully";
                cout << "\n---------------------------\n";
                cout << "Proceed to login screen \n";
                system("PAUSE");
                staffLogin();

                    
            }
            else
            {
                cout << "Connection failed" << endl;
                goto retry;
            }
        }

    }


}




void Portals::memberRegistration()
{

    clocking type;
    string member_type1 = "PLATINUM";
    string member_type2 = "GOLD";
    cout << "\n\nPricings\n";

    cout << "---------------------------------------------------------------------------------------\n";
    printf("| %-30s | %-50s |\n", "Membership Plan ", "PLATINUM");
    printf("| %-30s | %-50s |\n", "Perks", "**Gain 30% discount for each booking");
    printf("| %-30s | %-50s |\n", "     ", "**100points per booking");
    printf("| %-30s | %-50s |\n", "Price", "RM500/annum");
    cout << endl;
    printf("| %-30s | %-50s |\n", "Membership Plan ", "GOLD");
    printf("| %-30s | %-50s |\n", "Perks", "**Gain 20% discount for each booking");
    printf("| %-30s | %-50s |\n", "     ", "**70points per booking");
    printf("| %-30s | %-50s |\n", "Price", "RM350/annum");
    printf("---------------------------------------------------------------------------------------\n");
    int qstate;
    Portals member;
    int membership_opt;
    cout << "Choose a member plan\n";
    cout << "1. Platinum\n";//1 year membership with discount of 30%
    cout << "2. Gold\n   "; // 6 months of membership with discount of 20%
    cin >> membership_opt;
    system("cls");

    cin.ignore(1, '\n');
    cout << "Enter Member Name: \n ";
    getline(cin, member.name);
id:
    cout << "Enter Identification Card Number:\n ";
    getline(cin, member.ic);
    for (int i = 0; i < member.ic.length(); i++)
    {
        if (!isdigit(member.ic[i]) || member.ic.length() < 12 || member.ic.length() > 12)
        {
            handle.invalid_details(1);
            goto id;
        }

    }
    cout << "Enter Member Address:\n ";
    getline(cin, member.address);
ph:
    cout << "Enter Member Phone No:\n ";
    getline(cin, member.phone);
    for (int i = 0; i < member.phone.length(); i++)
    {
        if (!isdigit(member.phone[i]) || (member.phone.length() < 10 || member.phone.length() > 11))
        {
            handle.invalid_details(2);
            goto ph;
        }

    }


retry:
    cout << "Enter a Member id:\n";
    getline(cin, member.id);
    string findbyname_query = "select * from member_table where mem_id = '" + member.id + "'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    




    if (!qstate)
    {
        res = mysql_store_result(conn);

        if (res->row_count == 1)
        {
            handle.invalid_details(3);
            goto retry;
        }

        else
        {
            p:
            cout << "Enter Member Password consisting 8 characters:\n ";
            getline(cin, member.pwd);
            if (member.pwd.length() != 8)
            {
                handle.invalid_details(5);
                goto p;

            }
            



            if (membership_opt == 1)
            {

                string insert_query = "insert into member_table(mem_name, mem_ic, mem_address, mem_phone, mem_id, mem_pwd,mem_start_date,mem_end_date) values ('" + member.name + "','" + member.ic + "','" + member.address + "','" + member.phone + "','" + member.id + "','" + member.pwd + "','" + type.tommorow + "','" + type.plat + "')";
                const char* q = insert_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    cout << "\n---------------------------\n";
                    cout << "Registered successfully";
                    cout << "\n---------------------------\n";

                    cout << "You are a Platinum Member till  " << type.plat;
                    cout << "\nYour total will be RM 500 " << member.name;
                   
                   
                    string insert_query = "select mem_id , mem_pwd , mem_end_date from member_table where mem_id = '" + member.id + "'";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    if (!qstate)                    
                    {
                        while ((row = mysql_fetch_row(res)))
                        {
                            cout << "\n\n----------------------------------------------------------------------\n";
                            printf("| %-20s | %-20s | %-20s |\n", "Member ID", "Member Password", "End Date");
                            printf("| %-20s | %-20s | %-20s |\n", row[0], row[1], row[2]);

                            printf("----------------------------------------------------------------------\n");




                            string findbyname_query = "select MAX(NO) from registration_table";
                            const char* qn = findbyname_query.c_str();
                            qstate = mysql_query(conn, qn);
                            res = mysql_store_result(conn);
                            string reg_id;
                            while (!qstate)
                            {
                                if ((row = mysql_fetch_row(res)))
                                {
                                    int temp = stoi(row[0]) + 1;
                                    reg_id = "R" + to_string(temp);
                                    string insert_query = "insert into registration_table(register_id, mem_id , mem_type) values ('" + reg_id + "' , '" + member.id + "', '" + member_type1 + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {

                                        string findbyname_query = "select MAX(NO) from payment_table";
                                        const char* qn = findbyname_query.c_str();
                                        qstate = mysql_query(conn, qn);
                                        res = mysql_store_result(conn);
                                        string payment_id;
                                        if(!qstate)
                                        {
                                            if ((row = mysql_fetch_row(res)))
                                            {
                                                int temp_p = stoi(row[0]) + 1;
                                                payment_id = "P" + to_string(temp_p);
                                                string insert_query = "insert into payment_table(payment_id,register_id, amount,payment_date) values ('" + payment_id + "' , '" + reg_id + "', '500', '" + clock.tommorow + "')";
                                                const char* q = insert_query.c_str();
                                                qstate = mysql_query(conn, q);
                                                res = mysql_store_result(conn);
                                                if (!qstate)
                                                {
                                                    opt.invoice_membership(reg_id,payment_id);
                                                    cout << "Proceeding to login";
                                                    memberLogin();
                                                    
                                                    //cout << "\n\nProceed to login screen\n";
                                                    //system("PAUSE");
                                                    //memberLogin();
                                                }
                                            }
                                        }
                                        
                                    }
                                    

                                }
                                break;
                            }
                           

                            
                            



                           
                        }
                    }
                }
                else
                {
                    cout << "Connection lost";
                }
                //cout << "\n\t\t\t\t\t\tTotal will be RM 500";



            }

            else if (membership_opt == 2)
            {
                string member_type1 = "GOLD";
                string insert_query = "insert into member_table(mem_name, mem_ic, mem_address, mem_phone, mem_id, mem_pwd,mem_start_date,mem_end_date) values ('" + member.name + "','" + member.ic + "','" + member.address + "','" + member.phone + "','" + member.id + "','" + member.pwd + "','" + type.tommorow + "','" + type.gold + "')";
                const char* q = insert_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    cout << "\n---------------------------\n";
                    cout << "Registered successfully";
                    cout << "\n---------------------------\n";

                    cout << "You are a GOLD Member till " << type.gold;
                    cout << "\nYour total will be RM 350 " << member.name;


                    string insert_query = "select mem_id , mem_pwd , mem_end_date from member_table where mem_id = '" + member.id + "'";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    if (!qstate)
                    {
                        while ((row = mysql_fetch_row(res)))
                        {
                            cout << "\n\n----------------------------------------------------------------------\n";
                            printf("| %-20s | %-20s | %-20s |\n", "Member ID", "Member Password", "End Date");
                            printf("| %-20s | %-20s | %-20s |\n", row[0], row[1], row[2]);

                            printf("----------------------------------------------------------------------\n");



                            string findbyname_query = "select MAX(NO) from registration_table";
                            const char* qn = findbyname_query.c_str();
                            qstate = mysql_query(conn, qn);
                            res = mysql_store_result(conn);
                            string reg_id;
                            while (!qstate)
                            {
                                if ((row = mysql_fetch_row(res)))
                                {
                                    int temp = stoi(row[0]) + 1;
                                    reg_id = "R" + to_string(temp);
                                    string insert_query = "insert into registration_table(register_id, mem_id , mem_type) values ('" + reg_id + "' , '" + member.id + "', '" + member_type2 + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {

                                        string findbyname_query = "select MAX(NO) from payment_table";
                                        const char* qn = findbyname_query.c_str();
                                        qstate = mysql_query(conn, qn);
                                        res = mysql_store_result(conn);
                                        string payment_id;
                                        if (!qstate)
                                        {
                                            if ((row = mysql_fetch_row(res)))
                                            {
                                                int temp_q = stoi(row[0]) + 1;
                                                payment_id = "P" + to_string(temp_q);
                                                string insert_query = "insert into payment_table(payment_id, register_id, amount,payment_date) values ('" + payment_id + "' , '" + reg_id + "', '350', '" + clock.tommorow + "')";
                                                const char* q = insert_query.c_str();
                                                qstate = mysql_query(conn, q);
                                                res = mysql_store_result(conn);
                                                if (!qstate)
                                                {
                                                    opt.invoice_membership(reg_id, payment_id);
                                                    system("PAUSE");
                                                    cout << "Proceeding to login";
                                                    memberLogin();
                                                }
                                            }
                                        }

                                    }


                                }
                                break;
                            }
                        }
                    }
                }

                else
                {
                    cout << "Connection lost";
                }
            }



        }

    }


}


#endif