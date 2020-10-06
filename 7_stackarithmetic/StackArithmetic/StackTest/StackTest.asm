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
   @17
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @17
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// Eq
   @cmp1
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JEQ
   @SET_FALSE
   D;JNE
   (cmp1)

// import number constant
   @17
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @16
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// Eq
   @cmp2
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JEQ
   @SET_FALSE
   D;JNE
   (cmp2)

// import number constant
   @16
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @17
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// Eq
   @cmp3
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JEQ
   @SET_FALSE
   D;JNE
   (cmp3)

// import number constant
   @892
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @891
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

   @cmp4
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JLT
   @SET_FALSE
   D;JGE
   (cmp4)

// import number constant
   @891
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @892
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

   @cmp5
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JLT
   @SET_FALSE
   D;JGE
   (cmp5)

// import number constant
   @891
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @891
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

   @cmp6
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JLT
   @SET_FALSE
   D;JGE
   (cmp6)

// import number constant
   @32767
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @32766
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

   @cmp7
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JGT
   @SET_FALSE
   D;JLE
   (cmp7)

// import number constant
   @32766
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @32767
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

   @cmp8
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JGT
   @SET_FALSE
   D;JLE
   (cmp8)

// import number constant
   @32766
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @32766
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

   @cmp9
   D=A
   @cmp_addr
   M=D // save return address
   // sub
   @SP
   M=M-1 // decr
   A=M
   D=M // top value
   A=A-1
   MD=M-D // sub, result in MD
   // check against 0
   @SET_TRUE
   D;JGT
   @SET_FALSE
   D;JLE
   (cmp9)

// import number constant
   @57
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @31
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// import number constant
   @53
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

// import number constant
   @112
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// Sub
   @SP
   M=M-1 // decr
   A=M-1 // top value
   D=M
   A=A-1
   M=D-M

// Neg
   @SP // go to stack pointer
   A=M-1 // go to top value of stack
   M=-M // negate value

// And
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M&D

// import number constant
   @82
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// Or
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M|D

// Not
   @SP
   A=M-1
   M=!M

(END)
@END
0;JMP
