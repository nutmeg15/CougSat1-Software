#include "IFJRSlave.h"

/**
 */
void IFJRSlave::checkCommand(int8_t command)
{
    if (command == sendBinary)
    {
        recieveBinary();
    }
    else if (command == reprogram)
    {
        reProgram();
    }
}

void IFJRSlave::recieveBinary()
{
    bool found = false;

    TransferProtocol *BinRec;
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

void IFJRSlave::processBinary(TransferProtocol *dataInfo)
{
    bool found = false;

    //Not sure what datatype to use for a binary file, so going to use int for now?
    int binaryArray[PACKET_MAX_SIZE/4];


    uint32_t bytes_received = 0;

    while (dataInfo-> bytes_total > bytes_received)    
    {
        int result = slaveBoard->receive();
        if (result == I2CSlave::WriteAddressed)
        {
            slaveBoard->read((char*)&binaryArray, sizeof(PACKET_MAX_SIZE));
            bytes_received += sizeof(binaryArray);

            //Filesystems ***** CHANGE THIS *******
            BinaryFile << binaryArray;
        }
    }    
}

void IFJRSlave::reProgram()
{
    bool found = false;

    uint8_t subsystem, major, minor, patch;

    while (!found)
    {
        int result = slaveBoard->receive();
        if (result == I2CSlave::WriteAddressed)
        {
            slaveBoard->read((char*)&subsystem, sizeof (uint8_t));
            slaveBoard->read((char*)&major, sizeof (uint8_t));
            slaveBoard->read((char*)&minor, sizeof (uint8_t));
            slaveBoard->read((char*)&patch, sizeof (uint8_t));
        }

    }

    //Filesystems ***** CHANGE THIS *******
    //Find correct file from binary titled major.minor.patch and flash subsystem 
}