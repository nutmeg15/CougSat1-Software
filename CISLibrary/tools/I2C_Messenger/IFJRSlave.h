/********************************************************************************
 * Copyright (c) 2019 by Cougs in Space - Washington State University           *
 * Cougs in Space website: cis.vcea.wsu.edu                                     *
 *                                                                              *
 * This file is a part of flight and/or ground software for Cougs in Space's    *
 * satellites. This file is proprietary and confidential.                       *
 * Unauthorized copying of this file, via any medium is strictly prohibited.    *
 *******************************************************************************/

/**
 * @file IFJRSlave.h
 * @author  Darren Cheatham, Meghna Dutta
 * @date 16 March 2020
 * @brief IFJR derivation of Wrapper for I2C Message Protocol
 */


#include "MessageSlave.h"
#include <fstream>

class IFJRSlave : public MessageSlave
{
private:
    IFJRSlave(): MessageSlave(I2C_SDA, I2C_SCL, IFJR){};
    

    /**
     * @brief Something for filesystems to decide on, but
     * outputing recieved binaries to a file for now
     * 
     */
    fstream BinaryFile;
    
    void recieveBinary();
    void processBinary(TransferProtocol *);

    void reProgram();

public:
    void checkCommand(int8_t command);
    
};