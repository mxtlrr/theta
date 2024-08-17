extern exception_handler
%macro isr_err_stub 1
isr_stub_%+%1:
	;; The error code has already been pushed to the stack
	;; when the interrupt is raised, so all we need to do is
	;; push the ISR number
	push byte %1
	jmp isr_stub
  iret 
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
	push byte 0		;; Empty error code
	push %1	;; Push the ISR number to the stack
	jmp isr_stub
  iret
%endmacro

isr_stub:
	pusha ;; Push all general purpose registers

	cld		;; ABI requires DF clear on function entry.
	call exception_handler

	popa
	add esp, 8
	iret

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
  dd isr_stub_%+i
%assign i i+1 
%endrep


;; Like the ISRs, we need to do the same thing for the IRQs.
;; Instead of just halting, we want to eventually go and handle it,
;; when I write handlers for the IRQs.

;; Parameter one is the IRQ number itself,
;; and parameter two is the IRQ number + 32
%macro IRQ 2
irq_stub_%1:
	push byte 0		;; No error code (obviously)
	push byte %2	;; This is the IRQ
	jmp irq_stub
%endmacro

IRQ 0,  32
IRQ 1,  33
IRQ 2,  34
IRQ 3,  35
IRQ 4,  36
IRQ 5,  37
IRQ 6,  38
IRQ 7,  39
IRQ 8,  40
IRQ 9,  41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

extern irq_handler		;; see isr.c
irq_stub:
	pusha ;; Push all general purpose registers
	
	cld		;; ABI requires DF clear on function entry.
	call irq_handler
	popa

	add esp, 8
	iret

;; Stub table -- prevents repeated code
global irq_stub_table
irq_stub_table:
%assign j 0
%rep 15
	dd irq_stub_%+j
%assign j j+1
%endrep

