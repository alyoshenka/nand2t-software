// initialize SP to 256
@256 // import 256
D=A // set D to 256
@SP // import SP(0)
M=D // set mem to 256

// initialize variables
@cur_func // current function, NO reset
@line_num // line function couter, DOES reset
@eq_val // value of equality check
@push_val // the pushed value
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
   D=D-M // sub
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
   D=D-M // subtract
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
   D=D-M // subtract
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

(PUSH)
   @push_val
   D=M // set register D to number
   @SP // get stack value as address
   A=M // go to addres (top of stack)
   M=D // set top of stack to number
   @SP // get SP address
   M=M+1 // increment stack pointer
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

(POP)
   @cur_func
   M=M+1 // increment
   @MAIN
   0;JMP // return control to main

// main function loop
(MAIN)
   @line_num
   M=0 // reset line counter

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

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

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @2
   D=A // store address as value
   @push_val
   M=D // set value

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

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

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
   @NEG
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @2
   D=A // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @2
   D=A // store address as value
   @push_val
   M=D // set value

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
   @EQ
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @2
   D=A // store address as value
   @push_val
   M=D // set value

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
   @GT
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @2
   D=A // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

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
   @LT
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

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
   @AND
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

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
   @OR
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=A // store address as value
   @push_val
   M=D // set value

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
   @NOT
   D;JEQ

   @line_num
   M=M+1 // increment

   @END
   0;JMP // finish 

(END)
   @END
   0;JMP
