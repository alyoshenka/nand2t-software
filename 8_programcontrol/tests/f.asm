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
(f)
    // repeat 0 times
    // initialze args to 0 (push to stack)

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
@THAT
M=D
// this=*(frame-2)
@2
D=A
@frame
D=M-D
@THIS
M=D
// arg=*(frame-3)
@3
D=A
@frame
D=M-D
@ARG
M=D
// lcl=*(frame-4)
@4
D=A
@frame
D=M-D
@LCL
M=D
// goto ret
@current_return
M;JMP

(END)
@END
0;JMP
