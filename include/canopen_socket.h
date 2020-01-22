#ifndef _CANOPEN_H_
#define _CANOPEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#define FRAME_SIZE 8
#define SDO_W 1
#define SDO_R 0

#define PDO_1 0x01
#define PDO_2 0x02
#define PDO_3 0x03
#define PDO_4 0x04

class Canopen_socket 
{
 public:
  Canopen_socket(const char* ifname,bool verbose = false);

  template <typename T=uint8_t>
    uint32_t send_SDO(uint8_t nodeID, bool w, uint32_t index, T data=0)
    {
      return send_SDO(nodeID, w, (uint16_t)(index>>16), (uint8_t)index, data);
    };
  
  template <typename T=uint8_t>
  uint32_t send_SDO(uint8_t nodeID, bool w, uint16_t index, uint8_t subindex, T data=0)
  {
    m_frame.can_id  = 0x600+nodeID;
    m_frame.can_dlc = 8;
    memset( m_frame.data , 0, 8 );
    
    long unsigned i,sd = sizeof(T);//data size 

    m_frame.data[0] = !w?0x40:(0x23| ((4-sd)<<2));//1b:F 2b:B 4b:3
    m_frame.data[1] = index;
    m_frame.data[2] = index>>8;
    m_frame.data[3] = subindex;
    for(i =0; i<sd; i++)
      m_frame.data[4+i] = data>>(8*i);

    if(m_verbose)
      print_frame(m_frame);
    
    write(m_socket, &m_frame, sizeof(struct can_frame));

    recv_SDO();

    return *(uint32_t*)(m_frame.data+4);
  }

  int recv_SDO()
  { 
    int n = read(m_socket, &m_frame, sizeof(struct can_frame));
    if(m_verbose && n>0)
      print_frame(m_frame);
    
  }




  
  template <typename T, typename S>
    void send_PDO( uint8_t pdo_n, uint8_t nodeID, T data1, S data2)
    {
      send_msg(0x100*pdo_n+0x100+nodeID,data1,data2);
    };

  template <typename T, typename S>
    void send_PDO( uint8_t pdo_n, uint8_t nodeID, T data1)
    {
      send_msg(0x100*pdo_n+0x100+nodeID,data1);
    };





  
  template <typename T>
    void send_msg(uint32_t COB_ID, T data1)
    {
      m_frame.can_id  = COB_ID;
    
      long unsigned sT = sizeof(T);//data size
      m_frame.can_dlc = sT;
      memset( m_frame.data , 0, sT );
    
      for(int i =0; i<sT; i++)
	m_frame.data[i] = data1>>(8*i);
    
      write(m_socket, &m_frame, sizeof(struct can_frame));
    };

  template <typename T, typename S=uint8_t>
    void send_msg(uint32_t COB_ID, T data1, S data2)
    {
      m_frame.can_id  = COB_ID;
    
      long unsigned sT = sizeof(T);//data size
      long unsigned sS = sizeof(S);//data size 
      m_frame.can_dlc = sT+sS;
      memset( m_frame.data , 0, sT+sS );
    
      for(int i =0; i<sT; i++)
	m_frame.data[i] = data1>>(8*i);

      for(int i =0; i<sS; i++)
	m_frame.data[sT+i] = data2>>(8*i);
    
      write(m_socket, &m_frame, sizeof(struct can_frame));
    };

  void print_frame(struct can_frame m_frame);
  

  
 private:
  int m_socket;
  char m_ifname[20];

  
  struct sockaddr_can m_addr;
  struct can_frame m_frame;
  struct ifreq m_ifr;
  
  bool m_verbose;
  
};

#endif
