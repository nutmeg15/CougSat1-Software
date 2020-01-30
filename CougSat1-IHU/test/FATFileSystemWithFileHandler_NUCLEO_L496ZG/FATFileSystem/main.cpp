#include "mbed.h"
#include <cstdio>
//#include "SDBlockDevice.h"
#include "HeapBlockDevice.h"
#include <FATFileSystem.h>
#include "SatFileHandler.h"

//SDBlockDevice sd(D11, D12, D13, D10);
//FATFileSystem fs("sd");
Serial pc(SERIAL_TX, SERIAL_RX);
//HeapBlockDevice sd(2048, 256);
SatFileHandler testfs(D11, D12, D13, D10, true);

int main() {  
    pc.printf("Start \n\r");
    string testString("Hello World Big Brain");
    /*int a = testfs.sd.init();
    testfs.fs.format(&sd); //Uncomment if this is the first time running this
    testfs.fs.mount(&sd);
    pc.printf("%X \n", a);*/
    /* Checks for existing text file. This will be successful on a second run
       but not the first run. The file system must be mounted and the file must
       be written first */
    
    if (testfs.write(std::string("fuckThis"),testString))
        pc.printf("End \n");
        
    else
        pc.printf("Fail \n");
}