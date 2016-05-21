.data
.org 0x400

STEV1: .word16 2323 
STEV2: .word16 4343
STEV3: .byte -127
STEV4: .byte 6
.align 4
STEV5: .word 23456
STEV6: .word 43210

DIV: .space 1
REZ: .space 1
.align 2
MUL:  .space 2
SUM16: .space 2
.align 4
SUM: .space 4
DIF: .space 4

.data
.org 0x40001000

TAB: .byte 17,9,20,7,1

.code
.org 0

main:
     lhu r1,STEV1(r0)
     lhu r2,STEV2(r0)
     addu r3,r1,r2
     sh SUM16(r0),r3

     lb r1,STEV3(r0)
     lb r2,STEV4(r0)
     sll r3,r1,r2
     sh MUL(r0),r3

     lb r1,STEV3(r0)
     srai r2,r1,#5
     sb DIV(r0), r2

     lw r1,STEV5(r0)
     lw r2,STEV6(r0)
     addu r3,r1,r2
     sw SUM(r0),r3

     subu r3,r2,r1
     sw DIF(r0),r3

     lhi r1,0x40000000
     addui r1,r1,#0x1000     
     addui r2,r0,#10
     addui r3,r0,#0  
     addui r4,r0,#0
     Loop: sltui r5,r4,#5
           beq r5, End
           lb  r6,0x0(r1)
           sgti r7,r6,#10
           bne r7, Add 
           addui r4,r4,#1
           addui r1,r1,#1
           j Loop(r0)
           Add: 
               addui r3,r3,#1    
               addui r4,r4,#1
               addui r1,r1,#1
               j Loop(r0)
     End: 
     sb REZ(r0),r3
halt





