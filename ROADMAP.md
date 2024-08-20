# Phase 0: Basic setup
- [X] Enable SSE in boot stub.
- [X] Set up framebuffer
- [X] Output library
  - [X] `putc`
  - [X] `puts`
  - [X] `printf`
    - [X] Outputting floats (very important later on)

# Phase 2: CPU / important stuff
- [X] GDT
- [X] IDT
  - [X] Exceptions
- [X] Heap
  - [X] Get memory map from GRUB
  - [X] `malloc`/`free`/etc...
- [X] IRQ / device drivers
  - [X] PIT timer
  - [X] PS/2 keyboard

# Phase 3: Math library
- [X] `exp()` function
- [X] `pow()` function
- [ ] Trig functions (Taylor series)
    - [X] `sin(x)`
    - [ ] `cos(x)`
    - [ ] `tan(x)`
- [X] Square root approximation -- [Heron's method](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Heron's_method)
- [ ] Imaginary numbers (!!)
- [X] `abs(x)`

# Phase 4: Usability
- [ ]  [Cooperative multitasking](https://wiki.osdev.org/Cooperative_Multitasking)
- [ ] Code applications into kernel
    - [ ] Graphing calcaulator
    - [ ] Quadratic equation solver
- [ ] GUI library
    - [ ] Shapes (triangle, rectangles, circles)
    - [ ] Windows
        - [ ] Kill signal
        - [ ] Resize signal
    - [ ] PS/2 mouse (REQUIRED)

# Phase 5: Homebrewing
- [ ] Own bootloader
    - [ ] Get mmap from BIOS
    - [ ] Set up VESA (800x600x32), pass structure to kernel
- [ ] Write PSF driver (sorry SSFN!)
