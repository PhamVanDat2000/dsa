/* Note: 
    * You change anything in this answer 
    * such that your implementation must have BusSystem class with method query.
    * This query method should return the output of each instruction
*/
#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;
class BusSystem
{

public:
    string query(string instruction)
    {
        // TODO: Your implementation
        return "-1";
    }
};

int main()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;
    cout << bs->query("CS 50 2134") << endl;
    return 0;
}