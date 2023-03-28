#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int hexToDec(string hex)
{
    int decimal;
    stringstream ss;
    ss << hex;
    ss >> std::hex >> decimal;
    return decimal;
}

int main()
{
    string hex;
    cout << "Enter a hexadecimal number: ";
    cin >> hex;
    int decimal = hexToDec(hex);
    cout << "Decimal equivalent of " << hex << " is " << decimal << endl;
    return 0;
}
