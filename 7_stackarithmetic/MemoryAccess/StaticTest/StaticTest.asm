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
   @RETURN_EQ
   0;JMP
(SET_FALSE)
   @false
   D=M
   @eq_val
   M=D
   @RETURN_EQ
   0;JMP
(RETURN_EQ)
   @eq_val
   D=M
   @SP
   A=M-1
   M=D
   @cmp_addr
   A=M
   0;JMP

(MAIN)

// import number constant
   @111
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @333
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @888
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to static
   @SP
   AM=M-1
   D=M
   @StaticTest.8
   M=D

// pop to static
   @SP
   AM=M-1
   D=M
   @StaticTest.3
   M=D

// pop to static
   @SP
   AM=M-1
   D=M
   @StaticTest.1
   M=D

// static
   @StaticTest.3
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// static
   @StaticTest.1
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// Sub
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M-D

// static
   @StaticTest.8
   D=M
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

(END)
@END
0;JMP
