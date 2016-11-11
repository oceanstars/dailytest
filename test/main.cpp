#include <iostream>
#include <algorithm>
#include <iterator>
#include <sys/time.h>
#include <vector>
#include <unistd.h>
using namespace std;
string chartemp("");
//字符串中反斜杠和引号之前添加转义字符\  tt
void replaceAllChange(string& ss)
{
    for (size_t i=0;i<ss.size();i++)
    {
        if (ss[i]=='\\') {
            ss.insert(i,string("\\"));
            i++;
        }
        else if(ss[i] == '\"')
        {
            ss.insert(i, string("\\"));
            i++;
        }
    }
}
int main()
{
    chartemp = "\\\"\"helloworld\"\"\"hello\\\\\\test\\\\";
    cout << chartemp << endl;
    replaceAllChange(chartemp);
    cout << chartemp << endl;
    struct timeval mtimeval;
    struct tm * mtm;
    char buf[15] = {0};
    cout << sizeof(buf) << endl;
    gettimeofday(&mtimeval, NULL);
    long timet = 15048087;
    //mtm = localtime(&(mtimeval.tv_sec));
    mtm = localtime(&timet);
    strftime(buf,15, "%Y%m%d%H%M%S", mtm);
    cout << buf << " " << mtimeval.tv_usec << endl;
    sleep(10);
    gettimeofday(&mtimeval, NULL);
    mtm = localtime(&(mtimeval.tv_sec));
    cout << "tt" << mtm->tm_hour << mtm->tm_min << mtm->tm_sec << endl;
    strftime(buf,15, "%Y%m%d%H%M%S", mtm);
    cout << buf << " " << mtimeval.tv_usec << endl;
    vector<int> my_vec;
    my_vec.push_back(12);
    my_vec.push_back(32);
    my_vec.push_back(54);
    copy(my_vec.begin(), my_vec.end(), ostream_iterator<int>(cout, "\n"));
    return 1;
}
