# theta
Theta is a small OS whose only purpose is to act like
a calculator.

# Compiling

## Dependencies
- i386-elf-*
- nasm
- grub-pc-bin (if you're on Ubuntu)
- xorriso

Then just run `make`.

## Running
```
qemu-system-i386 -m 256 -cdrom theta.iso
```

# Credit
This kernel uses `ssfn` code. Adapted from [mmlv](https://github.com/mxtlr/mmlv)