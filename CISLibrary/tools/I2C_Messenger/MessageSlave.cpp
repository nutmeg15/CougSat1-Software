#include "MessageSlave.h"

MessageSlave::MessageSlave(PinName sda, PinName scl, int boardAddress)
{
    this->slaveBoard = new I2CSlave(sda, scl);
    slaveBoard->address = boardAddress;
}

MessageSlave::~MessageSlave()
{
    delete this->slaveBoard;
}

/**
 * @brief Looks for a command packet and is what should
 * be running constantly. Reroutes to the right data type
 * 
 * @return int8_t
 */
int8_t MessageSlave::WriteAddressed()
{
    bool found = false;
    int8_t command;

    while (!found)
    {
        int result = slaveBoard->receive();

        if (result == I2CSlave::WriteAddressed)
        {
            slaveBoard->read((char*)&command, sizeof(int8_t));
            found = true;
        }
    }
    
    return command;
}