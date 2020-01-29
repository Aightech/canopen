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
### Methods
#### PDO 
```cpp
void set_PDO<N,R/W>(uint8_t ID); // Set the R/W PDO numero N.
```
```cpp
void send_PDO<N>(uint8_t ID, T data); // Send the data of type T (anytype) with the PDO N.
```
```cpp
void recv(T& data); // Receive the data of type T (anytype).
```


#### SDO
```cpp
void send_SDO(uint8_t ID, uint16_t index, uint8_t sub, T data); // Send the data of type T (anytype) with a SDO message at index:sub.
```
#### NMT
```cpp
void send_NMT(uint16_t msg); // Send a NMT message.
```

