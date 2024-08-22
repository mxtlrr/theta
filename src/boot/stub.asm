.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, 0x00000007
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS) & 0xFFFFFFFF

.set WIDTH,  800
.set HEIGHT, 600
.set DEPTH,  32

.section .multiboot

.align 16, 0
multiboot_header:
    .long   MAGIC
    .long   FLAGS
    .long   CHECKSUM

    # aout kludge (unused)
    .long 0,0,0,0,0

    # Video mode
    .long   0       # Linear graphics please?
    .long   WIDTH   # Preferred width
    .long   HEIGHT  # Preferred height
    .long   DEPTH   # Preferred pixel depth
.section .bss
.align 16
stack_bottom:
	.skip  16384
stack_top:

.section .text
.global _start
.type _start, @function

enable_sse:
    mov %cr0, %eax
    and $0xfffb, %ax
    or $0x2, %ax
    mov %eax, %cr0
    mov %cr4, %eax
    or $0x600, %eax
    mov %eax, %cr4
    ret

_start:
	mov $stack_top, %esp
    # Enable SSE, so we can do floating point stuff
    call enable_sse

    # Still here? SSE has been enabled.
	
	# We don't want our stack tracer to go off and execute
	# random stuff, so let's set ebp to 0 so this is the
	# last place we go.
	xor %ebp, %ebp
	
	/* Multiboot */
	push %eax
	push %ebx
	call kmain

	/* exited? */
	cli
1: hlt
	jmp 1b
.size _start, . - _start
