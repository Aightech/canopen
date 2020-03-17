# canopen

## Information
- **Brief**: Canopen object able to send command through a CAN interface using the UNIX socket.
- **Languages**: C++
- **Libraries**: 
- **Note**: /
- **Compatibility**:

| Ubuntu           | Window10         | MacOS            |
|:----------------:|:----------------:|:----------------:|
|:heavy_check_mark:|:grey_question:|:grey_question:   |


## Building
### Ubuntu
#### Steps
- Clone the repository and go inside.
```bash
git clone https://gitlab-dev.isir.upmc.fr/devillard/canopen.git && cd canpen
```
- Create a build directory and go inside.
- Configure the project.
- Build the project.
```bash
mkdir build && cd build && cmake .. && cmake --build .
```

#### Testing
##### Install can tools
```bash
sudo apt install can-utilis
```

##### Setup a virtual CAN bus
```bash
sudo ip link add dev vcan0 type vcan && ip link set up vcan0
```

##### Listen to the CAN bus
```bash
candump vcan0
```



## Canopen program
The executable file canopen enable you to send SDO message to a CAN bus.
### usage: 
	./canopen ifname 0xindex 0xsub [ size base data ]

	Arg:	ifname  : CAN interface name
		0xindex : Object register index
		0xsub   : Object register subindex
		size : Data size (number of bytes)
		base : Numerical base of the value passed.
		data : Value to write.

	Ex:	To read register 0x1000:2 of node 4 on "can0": 
		./canopen can0 4 1000 2

		To write in register 0x2000:F of node 3 the value 0x1234 on "can0": 
		./canopen can0 3 2000 F 2 x 1234



