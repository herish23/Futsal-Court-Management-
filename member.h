#define _CRT_SECURE_NO_WARNINGS
#ifndef MEMBER_H
#define MEMBER_H
#include<iostream>

#include"dbconn.h"
#include"clocking.h"
#include"fstream"
#include"iomanip"
#include"error_handler.h"

using namespace std;
class member {

private:

    clocking select2;
    int a[11][11] = {
  {1,1,1,1,1,1,1,0,1,0,1},{1,0,0,0,0,0,1,0,1,0,1},
  {1,0,1,1,1,0,1,0,1,1,0},{1,0,1,1,1,0,1,0,0,0,0},
  {1,0,1,1,1,0,1,0,1,1,1},{1,0,0,0,0,0,1,0,0,0,1},
  {1,1,1,1,1,1,1,0,1,1,1},{0,0,0,0,0,0,0,0,0,1,1},
  {1,1,0,0,1,1,1,0,0,1,0},{0,0,1,0,1,1,0,0,0,1,0},
  {1,1,1,1,1,0,0,1,1,1,1}
    };
    error_handler hdl;
    string booking_test;
   
public:


    void checking();
    void pos();
    void court_checker(string);
    void check_time(string court_id,string);
    void court_book(string id);
    void payment(string member_id, string booking_id);
    void Renew_Membership(string member_id);
    void MemberPortal(string member_id);
    void points_redeem_gold_calc(string, string);
    void points_redeem_plat_calc(string, string);
    void printPixels(int Board[11][11], string member_id);
    void invoice(string booking_id, string payment_id);
    void invoice_membership(string,string );
    

    




};
void member::Renew_Membership(string member_id)
{


    string array[2] = { "PLATINUM","GOLD" };
    int qstate;
    string findbookingid_query = "SELECT mem_type FROM member_table where mem_id like '" + member_id + "'";
    const char* q = findbookingid_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {

        while ((row = mysql_fetch_row(res)))
        {

            if (row[0] == array[0])
            {
                //update member_table set mem_points = mem_points - '1000' where mem_id like '" + member_id + "'"
                cout << "Renewing for 1 year";
                string update_query = "update member_table set mem_end_date = '" + select2.platex1 + "'";





            }
            else if (row[0] == array[1])
            {

                cout << "Renewing for 6months";
                string update_query = "update member_table set mem_end_date = '" + select2.goldex1 + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    cout << "done";
                }
            }
            else
            {
                cout << "Server down!";
            }

        }
    }

}

void member::MemberPortal(string member_id)
{
    system("color 0B");
    string user = member_id;
    int portal_opt;
    cout << "Hey " + member_id;
    cout << "\n1.Book a court";
    cout << "\n2.Check booking details";
    cout << "\n3.Exit\n";
    hdl.directory(4);
    cin >> portal_opt;
    switch (portal_opt)
    {
    case 1:
        court_checker(user);
        break;

    case 2:
    {
        int qstate;
        string book_details = "select booking_table.mem_id, booking_table.booking_id, payment_table.payment_date, booking_table.court_id, booking_table.start_time, booking_table.end_time from booking_table JOIN payment_table on booking_table.booking_id = payment_table.booking_id where payment_table.payment_date = '" + select2.tommorow + "' and mem_id = '" + member_id + "'";
        const char* q = book_details.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        if (!qstate)
        {
            if (mysql_num_rows(res) <= 0)
            {
                cout << "No bookings done\n";
                system("PAUSE");
                system("cls");
                MemberPortal(member_id);
                
            }
            if ((row = mysql_fetch_row(res)))
            {
                cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
                printf("| %-10s | %-20s | %-40s | %-13s | %-15s | %-15s |\n", "MemberID", "BookingID", "Payment Date", "CourtID", "StartTime", "EndTime");
                printf("| %-10s | %-20s | %-40s | %-13s | %-15s | %-15s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);

                printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }

    }

    

    case 3:
        hdl.exit_msg();
        break;

    default:
        cout << "trial";
        break;

    }
}



void member::invoice(string booking_id, string payment_id)
{
    int qstate;
    string select_query = "select booking_table.mem_id , booking_table.start_time ,booking_table.end_time , payment_table.amount from payment_table JOIN booking_table on booking_table.booking_id = payment_table.booking_id WHERE payment_table.booking_id = '" + booking_id + "'";
    const char* qn = select_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {

            string d0 = row[0]; //memid
            string d1 = row[1]; //start_time
            string d2 = row[2]; //end_time
            string d3 = row[3]; //amount
            string name = payment_id + ".txt";
            ofstream file(name);
            int duration = stoi(row[2]) - stoi(row[1]);
            file << setw(15) << "\t\t\t  Receipt";
            file << "\n\nPayment id :" << payment_id;
            file << "\n\nMemberId :" << d0;
            file << "\n\nDate:" << select2.time1;
            file << "\n\n\n------------------------------------------------------------------";
            file << setw(10) << "\n BookingID   |" << setw(10) << " StartTime   |" << setw(10) << "EndTime      |" << setw(10) << " Duration    |" << setw(10) << " Amount  |";
            file << "\n------------------------------------------------------------------\n";
            file << setw(10) << booking_id << setw(12) << d1 << setw(14) << d2 << setw(14) << duration << setw(14) << d3;


            for (int i = 0; i < 10; i++)
            {
                file << "\n";
                file << setw(14) << "|" << setw(14) << "|" << setw(14) << "|" << setw(14) << "|" << setw(10) << "|";
            }
            file << "\n------------------------------------------------------------------";
            file.close();
            printPixels(a, row[0]);
        }



    }


}

// do formatting after amount
void member::invoice_membership(string register_id,string payment_id)
{
    int qstate;
    string select_query = "select member_table.mem_start_date, member_table.mem_end_date, registration_table.mem_id, registration_table.mem_type, payment_table.amount from payment_table JOIN registration_table on registration_table.register_id = payment_table.register_id JOIN member_table ON member_table.mem_id = registration_table.mem_id where registration_table.register_id = '" + register_id + "'";
    const char* qn = select_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {
           
            string d0 = row[0]; //start_date
            string d1 = row[1]; //end_date
            string d2 = row[2]; //mem_id
            string d3 = row[3]; //mem_type
            string d4 = row[4]; //mem_amount
            string name = register_id + "_membership.txt";
            ofstream file(name);
            //int duration = stoi(row[2]) - stoi(row[1]);
            file << setw(15) << "\t\t\t  Receipt";
            file << "\n\nPayment id :" << payment_id;
            file << "\n\nMemberId :" << d2;
            file << "\n\nDate:" << select2.time1;
            file << "\n\n\n------------------------------------------------------------------";
            file << setw(10) << "\n Membership   |" << setw(10) << " StartDate   |" << setw(10) << "EndDate      |" << setw(10) << " Amount |";
            file << "\n------------------------------------------------------------------\n";
            file << setw(13) << d3 << setw(13) << d0 << setw(13) << d1 << setw(14) << d4 << setw(14);


            for (int i = 0; i < 10; i++)
            {
                file << "\n";
                file << setw(14) << "|" << setw(14) << "|" << setw(14) << "|" << setw(14) << "|";
            }
            file << "\n------------------------------------------------------------------";
            file.close();
            
            printPixels(a, d2);
        }
    }


}                  



   
    
    




void member::printPixels(int Board[11][11],string member_id)
{

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++)  cout << ((Board[i][j] == 0) ? "  " : "\xDB\xDB");
        cout << endl;
    }
    system("PAUSE");
    system("cls");
    MemberPortal(member_id);
    
    
    
    
   




}

void member::points_redeem_plat_calc(string member_id, string booking_id)
{
    int qstate;

    double price_p;
    price_p = 0.7 * 100;

    string findbyname_query = "select MAX(NO) from payment_table";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    string payment_id;
    int temp_points;
    while (!qstate)
    {
        if ((row = mysql_fetch_row(res)))
        {
            int temp = stoi(row[0]) + 1;
            payment_id = "P" + to_string(temp);
            

        }
        break;
    }
    string memberpoints_query = "select mem_points from member_table where mem_id = '" + member_id + "'";
    const char* q = memberpoints_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {

        res = mysql_store_result(conn);
        if ((row = mysql_fetch_row(res)))
        {
            if (stoi(row[0]) >= 1000)
            {
                int opt;
                cout << row[0] << " available points" << endl;
                cout << "Do you want to redeem it";
                cout << "\n1. Redeem";
                cout << "\n2. Save\n";
                cin >> opt;
                if (opt == 1)
                {
                    temp_points =  stoi(row[0]) -1000;
                    cout << "A complimentary court for an hour will be given for 1000 points";
                    string updatepoints_query = "update member_table set mem_points = '" + to_string(temp_points) + "' where mem_id = '" + member_id + "'";
                    const char* q = updatepoints_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    if (!qstate)
                    {
                        string insert_query = "insert into payment_table(payment_id, booking_id , amount , payment_date ) values ('" + payment_id + "','" + booking_id + "','0','" + select2.tommorow + "')";
                        const char* q = insert_query.c_str();

                        qstate = mysql_query(conn, q);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {
                            cout << "\nEnjoy your complimentary game! VAMOS";
                            MemberPortal(member_id);
                        }
                    }
                }
                else if (opt == 2)
                {
                payment:
                    int qstate = 0;
                    string points_query = "insert into payment_table(payment_id, booking_id , amount,payment_date) values ('" + payment_id + "','" + booking_id + "','" + to_string(price_p) + "','" + select2.tommorow + "')";
                    const char* qbz = points_query.c_str();
                    qstate = mysql_query(conn, qbz);
                    res = mysql_store_result(conn);
                    if (!qstate)
                    {

                        temp_points = stoi(row[0]) + 100;
                        string update_query = "UPDATE member_table SET mem_points = '" + to_string(temp_points) + "' WHERE EXISTS (SELECT * FROM booking_table WHERE booking_table.mem_id = member_table.mem_id AND mem_id = '" + member_id + "')";
                        const char* q7 = update_query.c_str();
                        qstate = mysql_query(conn, q7);
                        res = mysql_store_result(conn);

                        if (!qstate)
                        {



                            cout << "Succesfully booked\n\n";
                            
                            invoice(booking_id,payment_id);






                        }
                        else
                        {
                            cout << "Server error";
                        }



                    }
                    else
                    {
                        cout << "Server down";
                    }


                }


            }
            else
            {
                goto payment;
            }
        }
    }


}




void member::points_redeem_gold_calc(string member_id, string booking_id)
{
    int qstate;

    double price_p;
    price_p = 0.8 * 100;
    string findbyname_query = "select MAX(NO) from payment_table";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    string payment_id;
    while (!qstate)
    {
        if ((row = mysql_fetch_row(res)))
        {
            int temp = stoi(row[0]) + 1;
            payment_id = "p" + to_string(temp);
            break;

        }

    }
    string memberpoints_query = "select mem_points from member_table where mem_id = '" + member_id + "'";
    const char* q = memberpoints_query.c_str();
    qstate = mysql_query(conn, q);
    int temp_points;
    if (!qstate)
    {

        res = mysql_store_result(conn);
        if ((row = mysql_fetch_row(res)))
        {
            if (stoi(row[0]) >= 1000)
            {
                int opt;
                cout << row[0] << " available points" << endl;
                cout << "Do you want to redeem it";
                cout << "\n1. Redeem";
                cout << "\n2. Save\n";
                cin >> opt;
                if (opt == 1)
                {
                    
                    temp_points = 1000 - stoi(row[0]);

                    cout << "A complimentary court for an hour will be given for 1000 points";
                    string updatepoints_query = "update member_table set mem_points = '" + to_string(temp_points) + "' where mem_id = '" + member_id + "'";
                    const char* q = updatepoints_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    if (!qstate)
                    {
                        string insert_query = "insert into payment_table(payment_id, booking_id , amount,payment_date) values ('" + payment_id + "','" + booking_id + "','0','" + select2.tommorow + "')";
                        const char* q = insert_query.c_str();

                        qstate = mysql_query(conn, q);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {
                            cout << "\nEnjoy your complimentary game! VAMOS";
                        }
                    }
                }
                else if (opt == 2)
                {
                payment:
                    string payment_query = "insert into payment_table(payment_id, booking_id , amount,payment_date) values ('" + payment_id + "','" + booking_id + "','" + to_string(price_p) + "','" + select2.tommorow + "')";
                    const char* q1 = payment_query.c_str();
                    qstate = mysql_query(conn, q1);
                    res = mysql_store_result(conn);

                    if (!qstate)
                    {

                        temp_points = stoi(row[0]) + 70;

                        string update_query = "UPDATE member_table SET mem_points  = '" + to_string(temp_points) + "' WHERE EXISTS (SELECT * FROM booking_table WHERE booking_table.mem_id = member_table.mem_id AND mem_id = '" + member_id + "')";
                        const char* q = update_query.c_str();
                        qstate = mysql_query(conn, q);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {



                            cout << "Succesfully booked\n\n";
                            
                            invoice(booking_id,payment_id);


                        }
                        else
                        {
                            cout << "Server error";
                        }



                    }
                    else
                    {
                        cout << "Server down";
                    }


                }


            }
            else
            {
                goto payment;
            }
        }
    }

}






//need editing
void member::court_checker(string id)
{
    system("color 0E");
    int qstate;
    string avail = "A";   
    int size;    
    string findbycourt_query = "SELECT COUNT(court_id) from court_table; ";
    const char* qn = findbycourt_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        if ((row = mysql_fetch_row(res)))
        {
            size = stoi(row[0]);
        }
    }

    string* array2 = new string[size];
   

    

    string findbycort_query = "SELECT court_id from court_table";
    const char* qz = findbycort_query.c_str();
    qstate = mysql_query(conn, qz);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        for (int i = 0; i <size; i++)
        {
            if ((row = mysql_fetch_row(res)))
            {
                array2[i] = row[0];
                

            }
        }
        
    }
    

    cout << "Courts available\n\n";
    for(int i = 0; i<size;i++)
    {
        cout << "--------------------------\n";
        //SELECT booking_table.court_id,time_table.start_time , time_table.end_time FROM time_table,booking_table WHERE NOT EXISTS(SELECT * FROM booking_table WHERE time_table.time_stamp = booking_table.time_stamp and court_id = 'c2' and booking_date = '2023-01-09')group by start_time asc having (time_table.start_time > '10:00:00');
       
        string findbycourt_query = "SELECT time_table.start_time , time_table.end_time FROM time_table,payment_table WHERE NOT EXISTS(SELECT * FROM booking_table,payment_table WHERE time_table.time_stamp = booking_table.time_stamp and court_id = '" + array2[i] + "' and booking_table.booking_id = payment_table.booking_id and payment_table.payment_date = '" + select2.tommorow + "') group by start_time asc having (time_table.start_time > '" + select2.time1 + "')";
        const char* qn = findbycourt_query.c_str();
        qstate = mysql_query(conn, qn);

        if (!qstate)
        {
            res = mysql_store_result(conn);

            while ((row = mysql_fetch_row(res)))
            {

                cout << array2[i];
                cout << "|   " << row[0] << "|   " << row[1] << endl;





            }
            cout << "--------------------------\n";

        }
       
    }

    delete[] array2;

    
    court_book(id);
   
    
    
   



}




void member::pos()
{
    cout << "=========================================================" << endl;
    cout << "|                  COURTS POSITIONS                     |" << endl;
    cout << "|\t--------\t" << "--------\t" << "--------\t|" << endl;
    cout << "|\t|      |\t" << "|      |\t" << "|      |\t|" << endl;
    cout << "|\t|  C1  |\t" << "|  C2  |\t" << "|  C3  |\t|" << endl;
    cout << "|\t|      |\t" << "|      |\t" << "|      |\t|" << endl;
    cout << "|\t--------\t" << "--------\t" << "--------\t|" << endl;
    cout << "-->                                                   -->" << endl;
    cout << "|\t--------\t" << "--------\t" << "--------\t|" << endl;
    cout << "|\t|      |\t" << "|      |\t" << "|      |\t|" << endl;
    cout << "|\t|  C4  |\t" << "|  C5  |\t" << "|  C6  |\t|" << endl;
    cout << "|\t|      |\t" << "|      |\t" << "|      |\t|" << endl;
    cout << "|\t--------\t" << "--------\t" << "--------\t|" << endl;
    cout << "|                                                       |";
    cout << "\n=========================================================" << endl;

}
//disable




void member::court_book(string id)
{
reg:


    int qstate;
    //court_checker();
    string findbyname_query = "select MAX(NO) from booking_table";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    string book_id;
    while (!qstate)
    {
        if ((row = mysql_fetch_row(res)))
        {
            int temp = stoi(row[0]) + 1;
            book_id = "B" + to_string(temp);
            break;

        }

    }
    int duration = 1;;
    string court_id, time;
    int end_time;
    string end_time2;
    cout << "Choose your court";
    cin >> court_id;
    //check_time(court_id,id);
    cout << "\nChoose your time (eg 10:00:00) ";
    cin >> time;
    
    
    
    end_time = stoi(time) + duration;
    end_time2 = to_string(end_time) + ":00:00";
    string findbytime_query = "select time_stamp from time_table where start_time like '%" + time + "%' and end_time like '%" + end_time2 + "%'";
    const char* q = findbytime_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {
           
            
            string insert_booking_query = "insert into booking_table(booking_id ,court_id, mem_id, start_time,end_time,time_stamp) values ('" + book_id + "','" + court_id + "','" + id + "','" + time + "','" + end_time2 + "','" + row[0] + "')";
            const char* q = insert_booking_query.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);
            if (!qstate)
            {
               
                payment(id, book_id);

            }

        }

    }
   




}


void member::payment(string member_id, string booking_id)
{
    
    int qstate;
    string array[2];

    string mem_type = "SELECT mem_type from registration_table group by mem_type order by mem_type desc";
    const char* z = mem_type.c_str();
    qstate = mysql_query(conn, z);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        for(int i = 0 ; i<2;i++)
        {
            if ((row = mysql_fetch_row(res)))
            {
                array[i] = row[0];
            }
        }
    }

    string findbookingid_query = "SELECT  registration_table.mem_type FROM registration_table JOIN booking_table ON registration_table.mem_id = booking_table.mem_id WHERE registration_table.mem_id = '" + member_id + "' group by registration_table.mem_id";
    const char* q = findbookingid_query.c_str();
    qstate = mysql_query(conn, q);
    
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {

            if (row[0] == array[0])
            {

               
                points_redeem_plat_calc(member_id, booking_id);

            }
            else if (row[0] == array[1])
            {

                points_redeem_gold_calc(member_id, booking_id);
            }
            

        }
    }
    
}

#endif