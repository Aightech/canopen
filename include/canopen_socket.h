#ifndef _CANOPEN_H_
#define _CANOPEN_H_
/*!
 * \file canopen_socket.h
 * \brief Canopen object able to send command through a CAN interface using the UNIX socket.
 * \author Alexis Devillard
 * \version 1.0
 */

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

#define R_PDO 0x00
#define T_PDO 0x01

#define PDO_1 0x01
#define PDO_2 0x02
#define PDO_3 0x03
#define PDO_4 0x04

#define SDO_COBID 0x600
#define SDO_FRAME_SIZE 8


#define NMT_START 0x0001
#define NMT_STOP  0x0002
#define NMT_PREOP 0x0080
#define NMT_RESET_NODE 0x0082
#define NMT_RESET_COMM 0x0081




/*! \class Canopen_socket
 * \brief Canopen object able to send command through a CAN interface using the UNIX socket.
 */
class Canopen_socket 
{
 public:
  
  /*!
   *  \brief Constructor
   *  \param ifname : Name of the can interface ex:"can0"
   *  \param verbose : Display the different message sent.
   */
  Canopen_socket(const char* ifname,bool verbose = false);
  
  /*!
   *  \brief Constructor
   *  \param ifname : Name of the can interface ex:"can0"
   *  \param COBID : Filtering only frame with this ID.
   *  \param verbose : Display the different message sent.
   */
 Canopen_socket(const char* ifname, uint32_t COBID, bool verbose = false) :
  Canopen_socket(ifname, verbose)
      {
	m_rfilter[0].can_id=COBID;
	m_rfilter[0].can_mask = CAN_SFF_MASK;
	setsockopt(m_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &m_rfilter, sizeof(m_rfilter));
      };


  /*!
   *  \brief templated function to send SDO message with different kind of data type (uint8_t, uint16_t ...)
   *  \param nodeID : ID of the destination node. [0-127] 
   *  \param w : Set to SDO_W or SDO_R to respectively write or read a parameter.
   *  \param index : Register index with the format (unit32_t):0x|(uint16_t)index|(uint8_t)00| (uint16_t)subindex| 
   *  \param data : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <typename T=uint8_t>
    uint32_t
    send_SDO(uint8_t nodeID, bool w, uint32_t index, T data=0)
    {
      return send_SDO(nodeID, w, (uint16_t)(index>>16), (uint8_t)index, data);
    };

  /*!
   *  \brief templated function to send SDO message with different kind of data type (uint8_t, uint16_t ...)
   *  \param nodeID : ID of the destination node. [0-127] 
   *  \param w : Set to SDO_W or SDO_R to respectively write or read a parameter.
   *  \param index : Register index.
   *  \param subindex : Register subindex.
   *  \param data : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <typename T=uint8_t>
    uint32_t
    send_SDO(uint8_t nodeID, bool w, uint16_t index, uint8_t subindex, T data=0)
    {
      m_frame.can_id  = SDO_COBID+nodeID;
      m_frame.can_dlc = SDO_FRAME_SIZE;
      memset( m_frame.data , 0, SDO_FRAME_SIZE);

      //filled up the frame
      long unsigned i,sd = sizeof(T);//data size 
      m_frame.data[0] = !w?0x40:(0x23| ((4-sd)<<2));//1b:F 2b:B 4b:3
      m_frame.data[1] = index;
      m_frame.data[2] = index>>8;
      m_frame.data[3] = subindex;
      for(i =0; i<sd; i++)
	m_frame.data[4+i] = data>>(8*i);

      if(m_verbose)
	print_frame(m_frame);

      //send frame
      write(m_socket, &m_frame, sizeof(struct can_frame));

      //recv frame
      int n = read(m_socket, &m_frame, sizeof(struct can_frame));
      if(m_verbose)
	{
	  if(n<0)
	    printf("CAN socket: nothing to read\n");
	  else if (n < sizeof(struct can_frame))
	    fprintf(stderr, "read: incomplete CAN frame\n");
	  print_frame(m_frame);
	}

      //return the value stored in the frame data slot
      return *(uint32_t*)(m_frame.data+4);
    };


  template <uint8_t N, uint8_t U=R_PDO>
  void
    set_PDO(uint8_t nodeID)
  {
    if(U==R_PDO)
      send_SDO(nodeID , SDO_W, 0x1400+N-1, 1, 0x04000100+N*0x100+nodeID);
    else
      send_SDO(nodeID , SDO_W, 0x1800+N-1, 1, 0x04000080+N*0x100+nodeID);
    
  };



  
  /*!
   *  \brief templated function to send PDO1 message with different kind of data type (uint8_t, uint16_t ...)
   *  \param N : Number of the PDO.
   *  \param T : Data type.
   *  \param nodeID : ID of the destination node. [0-127] 
   *  \param data1 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <uint8_t N, typename T> void send_PDO(uint8_t nodeID, T data1)
  {
    send_PDO(N,nodeID,data1);
  };
    /*!
   *  \brief templated function to send PDO1 message with different kind of data type (uint8_t, uint16_t ...)
   *  \param N : Number of the PDO.
   *  \param T : Data type.
   *  \param nodeID : ID of the destination node. [0-127] 
   *  \param data1 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <uint8_t N, typename T, typename S> void send_PDO(uint8_t nodeID, T data1, S data2)
  {
    send_PDO(N,nodeID,data1,data2);
  };



  
  /*!
   *  \brief templated function to send PDO message with different kind of data type (uint8_t, uint16_t ...)
   *  \param T : Data type.
   *  \param pdo_n : Number of the PDO to send 
   *  \param nodeID : ID of the destination node. [0-127] 
   *  \param data1 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <typename T>
    void
    send_PDO( uint8_t pdo_n, uint8_t nodeID, T data1)
  {
    send_msg(0x100*pdo_n+0x100+nodeID,data1);
  };
  /*!
   *  \brief templated function to send PDO message with different kind of data type (uint8_t, uint16_t ...)
   *  \param T : Data type.
   *  \param S : Data type.
   *  \param pdo_n : Number of the PDO to send 
   *  \param nodeID : ID of the destination node. [0-127] 
   *  \param data1 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   *  \param data2 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <typename T, typename S>
    void
    send_PDO( uint8_t pdo_n, uint8_t nodeID, T data1, S data2)
  {
    send_msg(0x100*pdo_n+0x100+nodeID,data1,data2);
  };


   /*!
   *  \brief templated function to send NMT CAN message.
   *  \param msg : NMT message to send. 
   */
  void send_NMT(uint16_t msg)
  {
    send_msg((uint32_t)0,msg);
  }





  /*!
   *  \brief templated function to send CAN message.
   *  \param T : Data type.
   *  \param nodeID : COBID of the messae to send 
   *  \param data1 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <typename T>
    void
    send_msg(uint32_t COB_ID, T data1)
    {
      send_msg(COB_ID, data1, 0, 1);
    };

  /*!
   *  \brief templated function to send CAN message.
   *  \param T : Data type.
   *  \param S : Data type.
   *  \param nodeID : COBID of the messae to send 
   *  \param data1 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   *  \param data2 : The data to write, can be any data type. (uint8_t, uint16_t ...)
   */
  template <typename T, typename S=uint8_t>
    void
    send_msg(uint32_t COB_ID, T data1, S data2, uint8_t nb_data=2)
    {
      m_frame.can_id  = COB_ID;
    
      long unsigned sT = sizeof(T);//data size
      long unsigned sS = (nb_data==2)?sizeof(S):0;//data size 
      m_frame.can_dlc = sT+sS;
      memset( m_frame.data , 0, sT+sS );
    
      for(int i =0; i<sT; i++)
	m_frame.data[i] = data1>>(8*i);

      for(int i =0; i<sS; i++)
	m_frame.data[sT+i] = data2>>(8*i);
    
      write(m_socket, &m_frame, sizeof(struct can_frame));
    };

  

  /*!
   *  \brief Function  to print SDO message.
   *  \param frame :CAN frame to print
   */
  void
    print_frame(struct can_frame frame);
  

  
 private:
  
  int m_socket; /*!< Can socket */
  char m_ifname[20];  /*!< CAN interface name*/

  struct can_filter m_rfilter[0];
  
  struct sockaddr_can m_addr;  /*!< CAN address*/
  struct can_frame m_frame;  /*!< CAN frame*/
  struct ifreq m_ifr;  /*!< CAN interface*/
  
  bool m_verbose; /*!< Verbose mode*/
  
};

#endif
