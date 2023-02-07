#ifndef DBCONN_H
#define DBCONN_H
#include<iostream>
#include<mysql.h>
#include"error_handler.h"

using namespace std;
MYSQL* conn;
MYSQL_ROW row;

MYSQL_RES* res;
class dbconn
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            system("cls");


        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "", "pinnacle", 3306, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            system("cls");

        }
        else
            cout << "Connection Timeout!" << mysql_errno(conn) << endl;
        system("cls");
    }
};


#endif