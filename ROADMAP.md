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
- [ ] Calculus stuff
  - [ ] Integrals
    - [ ] [Gauss-Kronrod](https://en.wikipedia.org/wiki/Gauss%E2%80%93Kronrod_quadrature_formula)
    - [ ] Double or even TRIPLE integrals!?
  - [ ] Derivatives
  - [ ] Limits

# Phase 4: Usability
- [ ] Shell
    - [ ] Parse buffer as a math expression
- [ ] Test if `theta` runs on real hardware
- [ ] Write some hardcoded apps to Theta (this is gonna be fun :])
  - [ ] Quadratic equation solver