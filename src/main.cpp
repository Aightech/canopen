#include "socket.h"
#include <iostream>

void usage(char** argv)
{
    printf("usage: \n\t%s ifname 0xindex 0xsub [ size base data ]\n", argv[0]);
    printf("\n\tArg:\tifname  : CAN interface name\n");
    printf("\t\t0xindex : Object register index\n");
    printf("\t\t0xsub   : Object register subindex\n");
    printf("\t\tsize : Data size (number of bytes)\n");
    printf("\t\tbase : Numerical base of the value passed.\n");
    printf("\t\tdata : Value to write.\n");
    printf("\n\tEx:\tTo read register 0x1000:2 of node 4 on \"can0\": \n\t\t%s can0 4 1000 2\n", argv[0]);
    printf("\n\t\tTo write in register 0x2000:F of node 3 the value 0x1234 on \"can0\": \n\t\t%s can0 3 2000 F 2 x 1234\n", argv[0]);
}

int main(int argc, char** argv)
{
    printf("#### CANopen SDO sender ####\n");
    if (argc == 5 || argc == 8) {

        uint8_t i = 1;
        char* ifname = argv[i++];
        uint8_t node = (uint8_t)strtol(argv[i++], NULL, 16);
        uint16_t index = (uint16_t)strtol(argv[i++], NULL, 16);
        uint8_t subindex = (uint8_t)strtol(argv[i++], NULL, 16);

        printf("Opening CAN socket on inteface : ");
        CANopen::Socket can(ifname, true);
        if (argc == 5)
            can.send(CANopen::SDOOutboundRead(node, index, subindex));
        else {
            uint8_t s = (uint8_t)strtol(argv[i++], NULL, 10); //size of the data to send
            uint8_t b = (argv[i++][0] == 'd') ? 10 : 16; //base of the value writen
            char* v = argv[i++];
	    
	    CANopen::Payload p;
            if (s == 1) {
                int8_t data = (uint32_t)strtol(v, NULL, b);
		p << data;
	    }	    
            if (s == 2) {
                int16_t data = (uint32_t)strtol(v, NULL, b);
		p << data;
	    }
	    if (s == 4) {
	      
                int32_t data = (uint32_t)strtol(v, NULL, b);
		p << data;
            }

	    

	    
	    //Use the methode value to acces the value of the payload
	    /*p.value<uint16_t>(2) = 0x6789;
	    std::cout << "The second block of 2byte is equale to (uint16_t):  " << std::hex << p.value<uint16_t>(2) << std::endl;
	    */

	    CANopen::SDOOutboundWrite msg = CANopen::SDOOutboundWrite(node, index, subindex, p);

	    
	    std::cout  << "payload sent: " << p << std::endl;
	    std::cout  << "Message  sent: " << msg.to_string() << std::endl;
	    
	    can.send(std::move(msg));
	    
	      
	      
            
	      }
    } else
      usage(argv);

    return 0;
}
