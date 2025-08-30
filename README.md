# Machina
## an assembly subset
----

### syntax

#### registers

- al imm8
- cl imm8
- dl imm8
- bl imm8
- ah imm8
- ch imm8
- dh imm8
- bh imm8

#### 16 bit registers

- ax imm16
- cx imm16
- dx imm16
- bx imm16
- sp imm16
- bp imm16
- si imm16
- di imm16

#### 16 bit interrupts

- i10 video services
- i13 disk services
- i14 serial port services
- i15 misc system services
- i16 keyboard services
- i17 printer services
- i19 bootstrap loader
- i1A system clock/timer
- i20 terminate program (dos)
- i21 dos api
- i1C Times tick (~18.2/sec)


#### example

<img width="387" height="209" alt="Screenshot 2025-08-30 at 17 40 54" src="https://github.com/user-attachments/assets/47267588-f74c-40db-b6e0-2e92ee6a55f1" />



``` bash
make
./build/machina buidl/test build/out
qemu-system-i386 build/out
```


<img width="1197" height="602" alt="Screenshot 2025-08-30 at 17 45 02" src="https://github.com/user-attachments/assets/37d732a5-7466-4c76-b371-00fbaef3f973" />

