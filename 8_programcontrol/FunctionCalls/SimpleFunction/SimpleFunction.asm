// initialize variables
@eq_val // value of equality check
@cmp_addr // address to return to after comparing
@true
M=-1 // set true constant
@false
M=0 // set false constant
@frame // frame variable
@current_return

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
// label function entry
(SimpleFunction.test)
   // repeat 2 times
   // initialze args to 0 (push to stack)
   @SP
   A=M
   M=0
   @SP
   M=M+1
   @SP
   A=M
   M=0
   @SP
   M=M+1

// push from local
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

// push from local
   @LCL
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

// Not
   @SP
   A=M-1
   M=!M

// push from argument
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

// Add
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M+D

// push from argument
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

// return
@LCL
D=M
@frame // lcl
M=D
// ret = *(lcl-5)
@5
D=A
@frame
D=M-D
A=D
D=M
@current_return // ret
M=D
// *arg=pop() reposition return value
@SP
AM=M-1
D=M
@ARG
A=M
M=D
// sp=arg+1
@ARG
D=M+1
@SP
M=D
// that=*(frame-1)
@frame
D=M-1
A=D
D=M
@THAT
M=D
// this=*(frame-2)
@2
D=A
@frame
D=M-D
A=D
D=M
@THIS
M=D
// arg=*(frame-3)
@3
D=A
@frame
D=M-D
A=D
D=M
@ARG
M=D
// lcl=*(frame-4)
@4
D=A
@frame
D=M-D
A=D
D=M
@LCL
M=D
// goto ret
@current_return
M;JMP

(END)
@END
0;JMP
