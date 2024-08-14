# Phase 0: Basic setup
- [X] Enable SSE in boot stub.
- [X] Set up framebuffer
- [ ] Output library
  - [X] `putc`
  - [X] `puts`
  - [ ] `printf`
    - [ ] Outputting floats (very important later on)

# Phase 2: CPU / important stuff
- [ ] GDT
- [ ] IDT
  - [ ] Exceptions
- [ ] Heap
  - [ ] Get memory map from GRUB
  - [ ] `malloc`/`free`/etc...
- [ ] IRQ / device drivers
  - [ ] PS/2 keyboard
  - [ ] PS/2 mouse

# Phase 3: User applications
- [ ] Preemptive multitasking / SMP
- [ ] Code some applications 'baked' into the kernel
  - [ ] Tiny graphing calculator
  - [ ] Quadratic equation solver
- [ ] Swap to usermode / ring 3
  - [ ] Update GDT
  - [ ] Make/update TSS
- [ ] Shell
- [ ] Better GUI (this is where the mouse comes into play)
  - [ ] Windowing UI (for graphing calculator and other apps)

# Phase 4: Homebrewing Everything (probably might not be possible)
- [ ] Bootloader that
  - [ ] Loads framebuffer / sets VESA
  - [ ] Sets GDT correctly
  - [ ] Gets memory map
