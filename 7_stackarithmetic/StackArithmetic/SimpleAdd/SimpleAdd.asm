// initialize SP to 256
@256 // import 256
D=A // set D to 256
@SP // import SP(0)
M=D // set mem to 256
// VM segment allocation
// Local
@300
D=A
@LCL
M=D
// Argument
@400
D=A
@ARG
M=D
// This
@3000
D=A
@THIS
M=D
// That
@3010
D=A
@THAT
M=D

// initialize variables
@eq_val // value of equality check
@cmp_addr // address to return to after comparing
@true
M=-1 // set true constant
@false
M=0 // set false constant

@MAIN
0;JMP

(SET_TRUE)
   @true
   D=M
   @eq_val
   M=D
   @cmp_addr
   0;JMP
(SET_FALSE)
   @false
   D=M
   @eq_val
   M=D
   @cmp_addr
   0;JMP

(MAIN)

// import number constant
    @7
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
    @8
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// Add
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M+D
