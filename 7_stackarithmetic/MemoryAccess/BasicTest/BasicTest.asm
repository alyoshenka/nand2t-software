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
   @10
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to local
   @LCL
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
   @21
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @22
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to arg
   @ARG
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

// pop to arg
   @ARG
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

// import number constant
   @36
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to this
   @THIS
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

// import number constant
   @42
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @45
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to that
   @THAT
   D=M // base
   @5
   D=D+A
   @R13
   M=D
   @SP
   AM=M-1
   D=M
   @R13
   A=M
   M=D // set

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

// import number constant
   @510
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// pop to temp(R5)
   @SP
   AM=M-1
   D=M
   @R11
   M=D

// local
   @LCL
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
   @5
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

// Sub
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M-D

// this
   @THIS
   D=M
   @6
   A=A+D
   D=M
   @SP
   A=M
   M=D
   @SP
   M=M+1

// this
   @THIS
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

// Sub
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M-D

// push from temp (R5)
   @R11
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
