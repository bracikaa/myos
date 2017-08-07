.set IRQ_BASE, 0x20
.section .text
.extern _ZN9Interrupt15HandleInterruptEhj

.macro HandleException number
.global _ZN9Interrupt16HandleException\number\()Ev
_ZN9Interrupt16HandleException\number\()Ev:
  movb $\number, (interruptNum)
  jmp int_bottom
 .endm
 
 .macro HandleInterruptRequest number
.global _ZN9Interrupt26HandleInterruptRequest\number\()Ev
_ZN9Interrupt26HandleInterruptRequest\number\()Ev:
  movb $\number + IRQ_BASE, (interruptNum)
  jmp int_bottom
 .endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01


int_bottom:

  pusha
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs

  pushl %esp
  push (interruptNum)
  call _ZN9Interrupt15HandleInterruptEhj
  #addl $5, %esp
  movl %eax, %esp
  
  
  popl %gs
  popl %fs
  popl %es
  popl %ds
  popa

.global _ZN9Interrupt22IgnoreInterruptRequestEv
_ZN9Interrupt22IgnoreInterruptRequestEv:
  
  iret
  
  
.data
  interruptNum: .byte 0
  