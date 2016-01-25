#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace std;

/*
    Amazon intern interview:

    Given a flat file CSV, which denotes an Organization Structure as so:

    employee_id, first_name, last_name, reports_to

    mfly, Marty, McFly, jblogs
    jblogs, Joe, Blogs, rboss
    nmuller, Nicolas, Muller, jblogs
    rboss, Robert, Boss, . from: 1point3acres.com/bbs 
    trice, Travis, Rice, rboss

    Print out a result of directs as such:
    1. Robert Boss (rboss)
        2. Joe Blogs (jblogs)
            3. Nicolas Muller (nmuller)
            3. Marty McFly (mfly)
        2. Travice Rice (trice)

*/

class Solution
{
public:
    Solution(string file)
    {
        ifstream in(file);
        string line = "null";
        while (getline(in, line))
        {
            istringstream tmp(line);
            vector<string> data(4, "");
            for (int i = 0; ; ++i)
            {
                if (!getline(tmp, data[i], ',')) break;
                trimSpaces(data[i]);
            }
            incharge[data[3]].push_back(data[0]);
            employee *em = new employee(data[1] + ' ' + data[2], data[0], data[3]);
            stuff[data[0]] = em;
        }
        in.close();
    }
    ~Solution()
    {
        for (auto &pair : stuff)
            delete pair.second;
    }
    void print(ostream &out)
    {
        for (string &boss : incharge[""])
            dfs (boss, 1, out);
    }

private:
    void trimSpaces(string &str)
    {
        size_t front = 0, back = str.size() - 1;
        while (isspace(str[front])) ++front;
        while (isspace(str[back])) --back;
        str = str.substr(front, back - front + 1);
    }

    void dfs(string cur, int level, ostream &out)
    {
        for (int i = 0; i < level - 1; ++i)
            out << '\t';
        out << level << ". " << stuff[cur]->name << " " << "(" << cur << ")\n";

        for (string &nxt : incharge[cur])
            dfs (nxt, level + 1, out);
    }
private:
    struct employee
    {
        string name;
        string id;
        string reports_to;
        employee(string n, string i, string r): name(n), id(i), reports_to(r){}
    };
    unordered_map<string, vector<string>> incharge;
    unordered_map<string, employee*> stuff;
};

int main() 
{
    Solution so("21.in");  
    so.print(cout);  
    return 0;
}
