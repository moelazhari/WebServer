#include "connection.hpp"

int main()
{
    Connection conn(8004);
    conn.createsocket();
    return 0;
}