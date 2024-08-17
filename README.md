# Single-Cycle-4-bit-Computer-
## Project Description
A single-cycle processor is a type of CPU design where each instruction is executed in a single clock cycle. This architecture simplifies control and instruction fetching, ensuring uniform execution time for all instructions but may result in lower efficiency due to potential idle time in some stages during each cycle.

## Block Diagram
![image](https://github.com/user-attachments/assets/b75fa92d-a3a5-4c97-8c92-cc8557d9a430)

## Components
### Datapaths
- **Register File**: Stores data temporarily during instruction execution.
- **ALU (Arithmetic & Logic Functions)**: Performs arithmetic and logic operations on data.
- **Shifter**: Changes the value on bus B, putting the result on MUX input F.

### Memory
- **Data Memory**: Holds data that the processor uses for computation or stores results.
- **Instruction Memory**: Stores the program instructions that the processor fetches and executes.

### Program Counter (PC)
Holds the address of the next instruction to be executed from memory.

### Instruction Decoder
Translates a machine language instruction into a set of control signals.

## Instruction Set
The single-cycle computer supports the following instructions:
- **NOP**: No operation
- **MOV**: Move data
- **INC**: Increment
- **ADD**: Addition
- **SUB**: Subtraction
- **DEC**: Decrement
- **AND**: Logical AND
- **OR**: Logical OR
- **XOR**: Exclusive OR
- **NOT**: Logical NOT
- **SHL**: Shift Left
- **LDI**: Load Immediate
- **ADI**: Add Immediate
- **SUBI**: Subtract Immediate
- **LD**: Load
- **ST**: Store
  
## Assembler
An assembler is used to convert low-level assembly language code into machine code. We used an ATmega32 microcontroller to convert assembly instructions into machine code, which is then stored in instruction memory.

## Full Design
![full design](https://github.com/HamadaMohamed1/Single-Cycle-4-bit-Computer-/assets/124931950/ddc877bd-6d26-44ab-a811-e84caa65e9c4)

## More details & videos :
https://www.linkedin.com/posts/hamada-mohamed-9b480b248_simplecomputer-embedded-embeddedsystems-activity-7141180587259736064-TSUw?utm_source=share&utm_medium=member_desktop

