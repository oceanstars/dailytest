#include "testfunc.h"
//#include "mysql.h"

testFunc::testFunc()
{

}

/*void mysql_connect()
{
    MYSQL mysql,*sock;
    MYSQL_RES *res;
    char v_sql[150];

    mysql_init(&mysql);
    sock = mysql_real_connect(&mysql,"192.168.153.128","test", "123",
                              "testDB", 3306, NULL, 0);
    if(sock==NULL)
    {
        fprintf(stderr,"Query failed (%s)\n",mysql_error(sock));
        exit(1);
    }
    mysql.reconnect= 1;

    sprintf(v_sql,"select count(1) from personinfo;");
    if(mysql_query(sock,v_sql))
    {
     fprintf(stderr,"Query failed (%s)\n",mysql_error(sock));
     exit(1);
    }
    if (!(res=mysql_store_result(sock)))
    {
      fprintf(stderr,"Couldn't get result from %s\n",
          mysql_error(sock));
      exit(1);
    }
    mysql_free_result(res);

    mysql_close(sock);
}
*/
/*#include <stdio.h>
int  * p;
void pp(int  a, int  * b);
int  main(void)
{
    int a = 1, b = 2,  c = 3;
    p = & b;
    pp(a + c, & b);
    printf("%d %d %d", a, b, * p);
    return 1;
}
void pp(int  a, int  * b)
{
    int  c = 4;
    * p = * b + c;
    a = * p - c;
    printf("%d %d %d", a, * b, * p);
}*/

/*#include <stdio.h>
int main(void)
{
    union EXAMPLE
    {
        struct { int x; int y;}  in;
        int a, b;
    } e;
    e.a = 1;
    e.b = 2;
    e.in.x = e.a * e.a;
    e.in.y = e.b + e.b;
     printf("%d %d", e.a, e.b);
    printf("%d %d", e.in.x, e.in.y);
    return 1;
}*/

/*#include <iostream>
#include <unistd.h>
#include <string>
#include <time.h>
#include <fstream>
#include <sys/time.h>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/warning.h"
#include "cppconn/metadata.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/resultset.h"
#include "cppconn/resultset_metadata.h"
#include "cppconn/statement.h"

#define N 8
using namespace std;

bool test()
{
    try
    {
        fstream ftest;
        ftest.open("D:\\cppworkspace\\qt\\t1.txt", ios_base::in|ios_base::out|ios_base::binary );
        if (!ftest.is_open())
        {
            cout << "open error " << endl;
        }
        string str1 = "hello world!\n";
        cout << str1 << endl;
        ftest.write(str1.c_str(), str1.length());
        ftest.write(str1.c_str(), str1.length()+1);
        ftest.close();
    }
    catch(exception &ex)
    {
        cout << ex.what() << endl;
        return 0;
    }
    cout << (double)1/3 << endl;
    struct timeval tvl;
    struct tm *ttm;
    char buf[100] = {0};
    snprintf(buf, 4, "%d",591);

    cout << buf << endl;
    memset(buf, 0, 100);
    cout << buf << endl;
    strncpy(buf, "helloworld",10);
    cout << buf << "  " << strlen(buf) << endl;
    buf[strlen(buf)] = '\0';
    memset(buf, 0, 100);
    strncpy(buf, "helloworld",8);
    buf[strlen(buf)] = '\0';
    cout << buf << "  " << strlen(buf) << endl;
    gettimeofday(&tvl, NULL);
    cout << "tv_sec " << tvl.tv_sec << " tv_usec " << tvl.tv_usec << endl;
    ttm = localtime(&(tvl.tv_sec));
    strftime(buf, 25, "%Y-%m-%d %H:%M:%S", ttm);
    cout << buf << endl;
    time_t tint = time(NULL);
    //ttm = localtime(&tint);
    //tint = mktime(ttm);
    tint -= 23*24*3600;
    string stime = ctime(&tint);
    cout << stime << endl;
    tint -= 180*24*3600;
    stime = ctime(&tint);
    //cout << stime << endl;

    //ttm = localtime(& tint);
    cout << stime << endl;
    string str1 = "hedfsfsddl/dfsflseddf.txt";
    string str2 = str1.substr(str1.rfind("/"));
    cout << str2 << endl;
    cout << " 'hello world'%" << endl;

    return true;
}

static sql::Driver * mysql_driver = NULL;
bool test_mysql()
{
    sql::Connection* conn;
    string host("tcp://192.168.153.128");
    string user("test");
    string pass("123");
    string database("testDB");
    string connect_method("tcp");
    if (!mysql_driver)
    {
        mysql_driver = sql::mysql::MySQL_Driver::Instance();
    }
    try
    {
        conn = mysql_driver->connect(host, user, pass);
        sql::Statement* stmt(conn->createStatement());

        stmt->execute("SHOW ENGINES");
        {
            sql::ResultSet* rset(stmt->getResultSet());
            int found = 0;
            while (rset->next()) {
                if (rset->getString("Engine") == "InnoDB" && (rset->getString("Support") == "YES" || rset->getString("Support") == "DEFAULT")) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                printf("\n#ERR: InnoDB Storage engine not available or disabled\n");
                printf("not ok\n");
                return 1;
            }
        }
        cout << "find InnoDB" << endl;
        //stmt->execute("USE " + database);
    }
    catch (sql::SQLException &e)
    {
        //printf("\n# ERR: Caught sql::SQLException at %s::%d  [%s] (%d/%s)\n", CPPCONN_FUNC, __LINE__, e.what(), e.getErrorCode(), e.getSQLState());
        printf("not ok\n");
        return 1;
    }
    return 1;
}

int main()
{
    test_mysql();


    return 1;
}*/

