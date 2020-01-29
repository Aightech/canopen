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
*** Methods
|  PDO  | SDO | NMT |
|---|---|---|
| `set_PDO<N,R/W>(ID)` | `send_SDO(ID,index,sub,data)` | `send_NMT(mode)` | 
| `send_PDO<N>(ID,data)` | | |
| `recv(&data)` |  | |