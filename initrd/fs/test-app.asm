;; This is a test COFF binary that will be
;; executed on Theta. It raises INT 0x3 (breakpoint),
;; which should call an interrupt handler
section .text
global _start

_start:
  int 0x3
  jmp $
