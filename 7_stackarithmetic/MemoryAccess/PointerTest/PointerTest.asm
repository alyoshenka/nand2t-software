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
@cur_func // current function, NO reset
@line_num // line function couter, DOES reset
@eq_val // value of equality check
@pp_val // the pushed/popped value
@pp_addr // the address of the pushed/popped value
@true
M=-1 // set true constant
@false
M=0 // set false constant

@MAIN
0;JMP // start program

(ADD)
   @SP // go to stack pointer
   M=M-1 // decrement stack
   A=M // go to top of stack
   D=M // store top value
   A=A-1 // get address of next value
   D=D+M // add
   M=D // store
   A=A+1 // get top value
   M=0 // clear
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(SUB)
   @SP // go to stack pointer
   M=M-1 // decrement stack
   A=M // go to top of stack
   D=M // store top value
   A=A-1 // get address of next value
   D=M-D // sub
   M=D // store
   A=A+1 // get top value
   M=0 // clear
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(NEG)
   @SP // go to stack pointer
   A=M-1 // go to top value of stack
   M=-M // negate value
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(EQ)
   @SP // go to stack pointer
   M=M-1 // decrement value
   A=M // go to top of stack
   D=M // store value in D
   M=0 // clear value
   @SP // go to stack pointer
   A=M-1 // go to next value
   D=D-M // subtract
   @TRUE // set dest for true
   D;JEQ // jump if 0
   @FALSE // set dest for false
   D;JNE // jump if not 0
(TRUE)
   @true
   D=M // get true value
   @eq_val
   M=D // store value
   @AFTER_SET
   0;JMP // return control
(FALSE)
   @false
   D=M // get false value
   @eq_val
   M=D // store value
   @AFTER_SET
   0;JMP // return control
(AFTER_SET)
   @eq_val
   D=M // take value
   @SP // go to stack pointer
   A=M-1 // go to top value
   M=D; // set value
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(GT)
   @SP // go to stack pointer
   M=M-1 // decrement value
   A=M // go to top of stack
   D=M // store value in D
   M=0 // clear value
   @SP // go to stack pointer
   A=M-1 // go to next value
   D=M-D // subtract
   @TRUE // set dest for true
   D;JGT // jump if 0
   @FALSE // set dest for false
   D;JLE // jump if not 0
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(LT)
   @SP // go to stack pointer
   M=M-1 // decrement value
   A=M // go to top of stack
   D=M // store value in D
   M=0 // clear value
   @SP // go to stack pointer
   A=M-1 // go to next value
   D=M-D // subtract
   @TRUE // set dest for true
   D;JLT // jump if 0
   @FALSE // set dest for false
   D;JGE // jump if not 0
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(AND)
   @SP // go to stack pointer
   M=M-1 // decrement value to get first number
   A=M // go to stack
   D=M // store first number
   @SP // go to stack pointer
   M=M-1 // decrement value
   @SP // go to stack pointer
   A=M // go to stack
   M=M&D // calculate value
   @SP // go to stack pointer
   M=M+1 // increment value;
   A=M // go to top of stack
   M=0 // clear value
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(OR)
   @SP // go to stack pointer
   M=M-1 // decrement value to get first number
   A=M // go to stack
   D=M // store first number
   @SP // go to stack pointer
   M=M-1 // decrement value
   @SP // go to stack pointer
   A=M // go to stack
   M=M|D // calculate value
   @SP // go to stack pointer
   M=M+1 // increment value
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(NOT)
   @SP // go to stack pointer
   A=M-1 // go to top value of stack
   M=!M // bitwise negation
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

// push the value at pp_val to the stack
// (assumes pp_val has been set)
(PUSH)
   @pp_val
   D=M // store value
   @SP
   A=M // go to top of stack
   M=D // set value
   @SP
   M=M+1 // incr
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

// pop from stack to pp_addr
// (assumes pp_addr has been set)
(POP)
   @SP
   M=M-1 // decr
   A=M // top of stack
   D=M // top value
   M=0 // clear
   @pp_addr
   A=M // new address
   M=D // set value
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

// main function loop
(MAIN)
   @line_num
   M=0 // reset line counter

   @3030 // import number constant
   D=A
   @pp_val
   M=D // set
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @THIS
   D=A
   @0 // import number constant
   D=D+A // add offset
   @pp_addr
   M=D // set value
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @POP
   D;JEQ

   @line_num
   M=M+1 // increment

   @3040 // import number constant
   D=A
   @pp_val
   M=D // set
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @THIS
   D=A
   @1 // import number constant
   D=D+A // add offset
   @pp_addr
   M=D // set value
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @POP
   D;JEQ

   @line_num
   M=M+1 // increment

   @32 // import number constant
   D=A
   @pp_val
   M=D // set
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

    @THIS
   D=M // base of segment
   @2 // import index
   D=D+A // calc RAM address
   @pp_addr
   M=D // set address
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @POP
   D;JEQ

   @line_num
   M=M+1 // increment

   @46 // import number constant
   D=A
   @pp_val
   M=D // set
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

    @THAT
   D=M // base of segment
   @6 // import index
   D=D+A // calc RAM address
   @pp_addr
   M=D // set address
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @POP
   D;JEQ

   @line_num
   M=M+1 // increment

   @THIS
   D=A // store address
   @0 // import index
   A=D+A // offset from base
   D=M // save val
   @pp_val
   M=D // set val
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @THIS
   D=A // store address
   @1 // import index
   A=D+A // offset from base
   D=M // save val
   @pp_val
   M=D // set val
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @ADD
   D;JEQ

   @line_num
   M=M+1 // increment

   @THIS
   D=M // store argument base
   @2 // import index
   A=D+A // offset from base
   D=M // save val
   @pp_val
   M=D // set val
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @SUB
   D;JEQ

   @line_num
   M=M+1 // increment

   @THAT
   D=M // store argument base
   @6 // import index
   A=D+A // offset from base
   D=M // save val
   @pp_val
   M=D // set val
   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @ADD
   D;JEQ

   @line_num
   M=M+1 // increment

   @END
   0;JMP // finish 

(END)
   @END
   0;JMP
