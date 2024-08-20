# theta (θ)
Monolithic IA-32 kernel that acts as a graphing calculator. Notable features:
- Supports SSE
- Graphing calculator,
- Solving for `x` in any equation $ax^2 + bx + c$,
- and more!

# Motivation / "Why?"

## The processor is discontinued
The TI-84 runs on a **very** old processor (Z80) that was [discontinued](https://arstechnica.com/gadgets/2024/04/after-48-years-zilog-is-killing-the-classic-standalone-z80-microprocessor-chip/) back in April of 2024. Because
of the antiquity of the Z80, there is only 65kb of memory available to any applications. Obviously, some of this is taken up by the kernel/operating
system itself, so there's not much memory that can be used.

The latter reason is why plotting any function takes upwards of half a 
second. From my tests it took an **average of 4.37 seconds** to plot `sin(x)`!

## Features Theta has that TI-84 does not
The TI-84 does not support numbers that are bigger than $9.99\underbrace{\dots}_{\infty}9 \cdot 10^{99}$. So a number like $1\cdot10^{100}$ causes
an overflow. Theta hopes to be able to support huge numbers, hopefully
larger than $1\cdot10^{400}$, but that will come later.

Additionally, theta has access to more than 65k of memory, so plotting
functions will be way quicker.

## Learning Experience
This is my first main project with SSE, and I figured why not do it on bare
metal, to challenge myself B)
# Compiling

## Dependencies
You will need:
- An [i386-elf](https://gist.github.com/pedrominicz/93ef0510a20f990b8dc99877fd51a438) toolchain.
- GRUB development dependencies:
  - xorriso
  - mtools
  - `grub-pc-bin` (if you're booting UEFI and on Ubuntu)

## Compilation

### Building the kernel ELF
You can just run `make`. The Makefile is designed to both:
1. Compile the stub and kernel
2. Bail out (and don't continue) if either compilation of the stub or kernel
failed.
```
$ make
```

### Building an ISO file
The `build_iso.sh` file is here to build the iso. As mentioned earlier,
this is where you need the GRUB development dependencies:
```sh
# You can also do bash build_iso.sh
$ ./build_iso.sh
...
$ file theta.iso
theta.iso: ISO 9660 CD-ROM filesystem data (DOS/MBR boot sector) 'ISOIMAGE' (bootable)
```

# Running

## Emulation
For this, you'll need qemu (or other emulator - like Bochs). The flags I
personally use for development are:
```
-d int -M smm=off -monitor stdio -m 256
```

The full command would be
```
qemu-system-i386 -d int -M smm=off -monitor stdio -m 256 -cdrom theta.iso
```

## Real Hardware
What I like to do is clear out the partitions on the USB device with `cfdisk`, for example
```sh
# I boot off an NVMe drive, so this doesn't damage my system -- this
# may be different for you.
$ sudo cfdisk /dev/sda
# Here we remove all the partitions and write to disk and quit
$ sync # Just make sure the filesystem is up to date
$ dd if=theta.iso of=/dev/sda bs=4M && sync
```

Now, you should be able to boot off the USB device.
# Credit/Acknowledgements

I would like to credit [bzt](https://gitlab.com/bztsrc) for:
1. The ssfn library
2. The font provided
3. The `writestring` function.

# Contribution
To contribute to theta, all you need to do is:
1. fork the repository
2. make your changes
3. open a pull request when you're done.

That's it! I don't care if you use semantic commit messages or not.
The only thing I do ask of you is that every commit is compilable. E.g.
you can revert to a specific commit and everything will compile smoothly.

# Support
If you like my work, and would like to support me, you can donate to me.
```
XMR: 42vBH8y2qujTe5eV3PX2aXHokYrH8Qe1VeGSgRRfNvNYPXRuPFnTgjBg3eK26YPwJXEmynvXDesxw3peKYwDYkD28Mp2dFN
```


