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

// argument
   @ARG
   D=M
   @1
   A=A+D
   D=M
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
   @0
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to that
   @THAT
   D=M // base
   @0
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
   @1
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to that
   @THAT
   D=M // base
   @1
   D=D+A
   @R13
   M=D
   @SP
   AM=M-1
   D=M
   @R13
   A=M
   M=D // set

// argument
   @ARG
   D=M
   @0
   A=A+D
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @2
   D=A
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

// pop to arg
   @ARG
   D=M // base
   @0
   D=D+A
   @R13
   M=D
   @SP
   AM=M-1
   D=M
   @R13
   A=M
   M=D // set
(MAIN_LOOP_START)

// argument
   @ARG
   D=M
   @0
   A=A+D
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1
// if-goto COMPUTE_ELEMENT
@SP
AM=M-1
D=M
@COMPUTE_ELEMENT
D;JNE
@END_PROGRAM
0;JMP
(COMPUTE_ELEMENT)

// that
   @THAT
   D=M
   @0
   A=A+D
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// that
   @THAT
   D=M
   @1
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

// pop to that
   @THAT
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

// push from pointer (R3)
   @R4
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @1
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

// pop to pointer(R3)
   @SP
   AM=M-1
   D=M
   @R4
   M=D

// argument
   @ARG
   D=M
   @0
   A=A+D
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @1
   D=A
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

// pop to arg
   @ARG
   D=M // base
   @0
   D=D+A
   @R13
   M=D
   @SP
   AM=M-1
   D=M
   @R13
   A=M
   M=D // set
@MAIN_LOOP_START
0;JMP
(END_PROGRAM)

(END)
@END
0;JMP
