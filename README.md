# MIPS_ARC
This is MIPS pipeline Simulator very basic for detecting Hazards and proposing solution using data/operand forwarding method..


Sample Input

#Input are all in register format

#Registers are availble from 0-32

#Instruction supported are General Instruction except BEQ, JNZ

#Last Instruction should be either BRK or HLT to stop giving input

#Copy the inputs and paste in Consol as direct input is not being fetch now


ADD 2 3 4

SUB 5 2 4

MUL 5 5 6

HLT

Sample Output 

INSTRUCTION DEST_REG SRC1_REG SRC2_REG

========Insterted Input============

0 ADD R2 R3 R4

1 SUB R5 R2 R4

2 MUL R5 R5 R6



======Hazards and its solution===========


RAW Conflict between ADD R2 R3 R4 and SUB R5 R2 R4

Data Fowrarding: ADD R2 L3[R3] R4

RAW Conflict between SUB R5 R2 R4 and MUL R5 R5 R6

Data Fowrarding: SUB R5 L3[R2] R4

WAW Conflict between SUB R5 R2 R4 and MUL R5 R5 R6


=========Pipeline Structure=================

1 2 3 4 5 

0 1 2 3 4 5 

0 0 1 2 3 4 5 
