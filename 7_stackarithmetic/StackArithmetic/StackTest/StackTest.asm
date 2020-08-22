@256
D=A
@SP
M=D

// EQ

// equality compare value
@eq_val // setup
// equality function (true)
(IS_EQ)
   @eq_val // get value
   M=-1 // true
   @AFTER_EQ // post set function
   0;JMP
// equality function (false)
(NOT_EQ)
   @eq_val // get value
   M=0 // false
   @AFTER_EQ // post set function
   0;JMP
// setup function
(BEFORE_EQ)
   @SP // go to stack pointer
   M=M-1 // decrement value
   A=M // go to top of stack
   D=M // store value in D
   M=0 // clear value
   @SP // go to stack pointer
   A=M-1 // go to next value
   D=D-M // subtract
   @IS_EQ // set dest for true
   D;JEQ // jump if 0
   @NOT_EQ // set dest for false
   D;JNE // jump if not 0
// cleanup function
(AFTER_EQ) // after set value
   @eq_val // load return val
   D=M // store val
   @SP // go to stack pointer
   A=M-1 // go to top value
   M=D; // set value

// import number constant
@17
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@17
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

@BEFORE_EQ // equality check function
0;JMP

// import number constant
@17
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@16
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

@BEFORE_EQ // equality check function
0;JMP

// import number constant
@16
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@17
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

@BEFORE_EQ // equality check function
0;JMP

// import number constant
@892
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@891
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer



// import number constant
@891
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@892
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer



// import number constant
@891
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@891
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer



// import number constant
@32767
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@32766
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer



// import number constant
@32766
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@32767
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer



// import number constant
@32766
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@32766
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer



// import number constant
@57
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@31
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

// import number constant
@53
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

@SP
M=M-1
A=M
D=M
A=A-1
D=D+M
M=D
A=A+1
M=0

// import number constant
@112
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

@SP
M=M-1
A=M
D=M
A=A-1
D=D-M
M=D
A=A+1
M=0

@SP
A=M-1
M=-M

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M&D
@SP
M=M+1

// import number constant
@82
D=A // set register D to number
@SP // get stack value as address
A=M // go to addres (top of stack)
M=D // set top of stack to number
@SP // get SP address
M=M+1 // increment stack pointer

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M|D
@SP
M=M+1

@SP
A=M-1
M=!M
(END)
   @END
   0;JMP
