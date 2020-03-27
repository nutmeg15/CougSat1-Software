/********************************************************************************
 * Copyright (c) 2019 by Cougs in Space - Washington State University           *
 * Cougs in Space website: cis.vcea.wsu.edu                                     *
 *                                                                              *
 * This file is a part of flight and/or ground software for Cougs in Space's    *
 * satellites. This file is proprietary and confidential.                       *
 * Unauthorized copying of this file, via any medium is strictly prohibited.    *
 *******************************************************************************/

/**
 * @file MessageSlave.h
 * @authors Darren Cheatham, Meghna Dutta
 * @date 16 March 2020
 * @brief Wrapper for I2C Message Protocol
 */

#include <I2C.h>
#include <mbed.h>
#include "Protocol.h"



class MessageSlave 
{

protected:
/**
 * @brief the actual slave itself
 */
  I2CSlave *slaveBoard;


  /**
   * CHANGE THIS TO FUNCTION POINTER
   * @brief Recieves a message with a small amount of data
   * 
   * @param command defines what kind of data will be sent
   */

  virtual void* GetPacket(int8_t command) = 0;  

public:

  /**
   * @brief Construct a new Message Slave object
   *
   * @param sda SDA port
   * @param scl SCL port
   */
  MessageSlave(PinName sda, PinName scl, int boardAddress);


  /**
   * @brief Destructor for Message Slave object
   */ 
  ~MessageSlave();

  
  /**
 * @brief Recieve sent message command id
 * 
 * @return int8_t
 */
  int8_t WriteAddressed();
};