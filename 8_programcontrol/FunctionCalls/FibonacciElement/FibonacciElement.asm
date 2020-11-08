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
   // initialize global stack
   @256
   D=A
   @SP
   M=D
// not sure if i should be initializing these
   @300
   D=A
   @LCL
   M=D
   @400
   D=A
   @ARG
   M=D
   @3000
   D=A
   @THIS
   M=D
   @3010
   D=A
   @THAT
   M=D

// call Sys.init 0
   // push return address, using label below
   @return-address-1-Sys.init
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1
   // save LCL, ARG, THIS, THAT
   @LCL
   D=M
   @SP
   A=M
   M=D
   @ARG
   D=M
   @SP
   AM=M+1
   M=D
   @THIS
   D=M
   @SP
   AM=M+1
   M=D
   @THAT
   D=M
   @SP
   AM=M+1
   @SP
   M=M+1
   // reposition ARG, LCL
   // arg=sp-n-5
   @SP
   D=M
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   // lcl=sp
   @SP
   D=M
   @LCL
   M=D
   // transfer control
   @Sys.init
   0;JMP

// label return address
(return-address-1-Sys.init)

// label function entry
(Main.fibonacci)
   // repeat 0 times
   // initialze args to 0 (push to stack)

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

// import number constant
   @2
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

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
   D;JLT
   @SET_FALSE
   D;JGE
   (cmp1)

// if-goto IF_TRUE
   @SP
   AM=M-1
   D=M
   @IF_TRUE
   D;JNE
   @IF_FALSE
   0;JMP

(IF_TRUE)

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

// return
   @LCL
   D=M
   @frame // lcl
   M=D

   // return address = *(lcl-5)
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
   0;JMP

(IF_FALSE)

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

// call Main.fibonacci 1
   // push return address, using label below
   @return-address-2-Main.fibonacci
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1
   // save LCL, ARG, THIS, THAT
   @LCL
   D=M
   @SP
   A=M
   M=D
   @ARG
   D=M
   @SP
   AM=M+1
   M=D
   @THIS
   D=M
   @SP
   AM=M+1
   M=D
   @THAT
   D=M
   @SP
   AM=M+1
   @SP
   M=M+1
   // reposition ARG, LCL
   // arg=sp-n-5
   @SP
   D=M
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   // lcl=sp
   @SP
   D=M
   @LCL
   M=D
   // transfer control
   @Main.fibonacci
   0;JMP

// label return address
(return-address-2-Main.fibonacci)

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

// call Main.fibonacci 1
   // push return address, using label below
   @return-address-3-Main.fibonacci
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1
   // save LCL, ARG, THIS, THAT
   @LCL
   D=M
   @SP
   A=M
   M=D
   @ARG
   D=M
   @SP
   AM=M+1
   M=D
   @THIS
   D=M
   @SP
   AM=M+1
   M=D
   @THAT
   D=M
   @SP
   AM=M+1
   @SP
   M=M+1
   // reposition ARG, LCL
   // arg=sp-n-5
   @SP
   D=M
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   // lcl=sp
   @SP
   D=M
   @LCL
   M=D
   // transfer control
   @Main.fibonacci
   0;JMP

// label return address
(return-address-3-Main.fibonacci)

// Add
   @SP
   M=M-1 // decr
   A=M // top value
   D=M
   A=A-1
   M=M+D

// return
   @LCL
   D=M
   @frame // lcl
   M=D

   // return address = *(lcl-5)
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
   0;JMP

// label function entry
(Sys.init)
   // repeat 0 times
   // initialze args to 0 (push to stack)

// import number constant
   @0
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1

// call Main.fibonacci 1
   // push return address, using label below
   @return-address-4-Main.fibonacci
   D=A
   @SP
   A=M
   M=D
   @SP
   M=M+1
   // save LCL, ARG, THIS, THAT
   @LCL
   D=M
   @SP
   A=M
   M=D
   @ARG
   D=M
   @SP
   AM=M+1
   M=D
   @THIS
   D=M
   @SP
   AM=M+1
   M=D
   @THAT
   D=M
   @SP
   AM=M+1
   @SP
   M=M+1
   // reposition ARG, LCL
   // arg=sp-n-5
   @SP
   D=M
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   D=D-1
   // lcl=sp
   @SP
   D=M
   @LCL
   M=D
   // transfer control
   @Main.fibonacci
   0;JMP

// label return address
(return-address-4-Main.fibonacci)

(WHILE)
   @WHILE
   0;JMP

(END)
    @END
    0;JMP
