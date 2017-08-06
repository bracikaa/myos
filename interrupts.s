.set IRQ_BASE, 0x20
.section .text
.extern _ZN10Interrupt15handleInterruptEhj

.macro HandleException number
.global _ZN10Interrupt16handleException\number\()Ev
  movb $\number, (interruptNum)
  jmp int_bottom
 .endm
 
 .macro HandleInterruptRequest number
.global _ZN10Interrupt26handleInterruptRequest\number\()Ev
  movb $\numbers + IRQ_BASE, (interruptNum)
  jmp int_bottom
 .endm

HandleException 0x00
HandleException 0x01


int_bottom:

  pusha
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs

  pushl %esp
  push (interruptNum)
  call _ZN10Interrupts15handleInterruptEhj
  #addl $5, %esp
  movl %eax, %esp
  
  
  popl %gs
  popl %fs
  popl %es
  popl %ds
  popa

  iret
  
  
.data
  interruptNum: .byte 0
  