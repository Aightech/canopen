#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cstdint>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "canopen_socket.h"



int
main(int argc, char** argv)
{ 

  Canopen_socket can("can0",true);

  uint16_t t = 0x1234;

  uint16_t index = (uint16_t)strtol(argv[1],NULL,16);
  uint8_t  subindex = (uint8_t)strtol(argv[2],NULL,16);

  if(argc==3)
    can.send_SDO(4, SDO_R, index, subindex);
  if(argc==6)
    {
      uint8_t s = (uint8_t)strtol(argv[3],NULL,10);
      uint8_t b = (argv[4][0]=='d')?10:16;
      printf("%d\n",s);
      if(s==1)
	can.send_SDO(4, SDO_W, index, subindex,(uint8_t)strtol(argv[5],NULL,b));
      if(s==2)
	can.send_SDO(4, SDO_W, index, subindex,(uint16_t)strtol(argv[5],NULL,b));
      if(s==4)
	can.send_SDO(4, SDO_W, index, subindex,(uint32_t)strtol(argv[5],NULL,b));
    }
    
  

	
  return 0;
}
