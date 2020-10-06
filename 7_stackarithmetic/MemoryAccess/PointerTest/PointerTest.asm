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
   @3030
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to pointer(R3)
   @SP
   AM=M-1
   D=M
   @R3
   M=D

// import number constant
   @3040
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to pointer(R3)
   @SP
   AM=M-1
   D=M
   @R4
   M=D

// import number constant
   @32
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to this
   @THIS
   D=M // base
   @2
   D=D+A
   @R13
   M=D
   @SP
   AM=M-1
   D=M
   @R13
   A=M
   M=D // set

// import number constant
   @46
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to that
   @THAT
   D=M // base
   @6
   D=D+A
   @R13
   M=D
   @SP
   AM=M-1
   D=M
   @R13
   A=M
   M=D // set

// push from pointer (R3)
   @R3
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// push from pointer (R3)
   @R4
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

// this
   @THIS
   D=M
   @2
   A=A+D
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

// that
   @THAT
   D=M
   @6
   A=A+D
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
