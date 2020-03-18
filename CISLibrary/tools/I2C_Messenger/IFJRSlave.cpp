#include "IFJRSlave.h"

void IFJRSlave::recieveBinary()
{
    bool found = false;

    TransferProtocol BinRec;
    while (!found)
    {
        int result = slaveBoard->receive();

        if (result == I2CSlave::WriteAddressed)
        {
            slaveBoard->read((char*)&BinRec, sizeof (TransferProtocol));
            found = true;
        }
    }
    processBinary(BinRec);
}

void IFJRSlave::processBinary(TransferProtocol dataInfo)
{
    bool found = false;

    TransferProtocol ProtocolRecieved;

}