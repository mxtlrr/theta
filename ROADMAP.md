# Phase 0: Basic setup
- [X] Enable SSE in boot stub.
    - [X] Check if SSE enabled
- [X] Set up framebuffer
- [X] Output library
  - [X] `putc`
  - [X] `puts`
  - [X] `printf`
    - [X] Outputting floats (very important later on)

# Phase 2: CPU / important stuff
- [X] GDT
- [ ] IDT
  - [X] Exceptions
  - [ ] Better ISR handler
    - [X] Dump registers
    - [X] Dump descriptor values
    - [ ] Get SSE registers
    - [ ] Get opcodes of fault
    - [ ] Stack trace
- [X] Heap
  - [X] Get memory map from GRUB
  - [X] `malloc`/`free`/etc...
- [X] IRQ / device drivers
  - [X] PIT timer
  - [X] PS/2 keyboard

# Phase 3: Math library
- [X] `exp()` function
- [X] `pow()` function
- [X] Trig functions
    - [X] `sin(x)`
    - [X] `cos(x)`
    - [X] `tan(x)`
- [X] Square root approximation -- [Heron's method](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Heron's_method)
- [ ] Imaginary numbers (!!)
- [X] `abs(x)`

# Phase 4: Usability
- [ ] More syscalls
    - [X] SYS\_WRITE
    - [X] SYS\_READ
    - [ ] Some syscalls for framebuffer control
        - [X] FB\_PLOTPIXEL
        - [X] FB\_SETCOLOR
    - [ ] Somehow get math functions from kernel to be able to be called from applications.
- [X] Initrd
    - [X] Load initrd as a module to GRUB
    - [X] Read files (flat binary) from initrd
- [ ] Shell
    - [X] Check if command buffer is file, if so execute
    - [ ] If not command buffer, parse as a math expression
- [ ] Test if `theta` runs on real hardware

# Phase 5: Apps
- [ ] Quadratic Equation Solver
- [ ] Graphing Calculator
    - [ ] Support linear/quadratic functions
    - [ ] Support trig functions

