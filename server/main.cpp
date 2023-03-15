#include "connection.hpp"
int main()
{
    Connection conn(8004);
    conn.createsocket();
    // std::cout << MAX_POLL_CONNECTIONS << std::endl;
    return 0;
}