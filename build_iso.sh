#!/bin/bash
rm -rf iso/
sleep 0.1
mkdir -p iso/boot/grub
cp bin/kernel.bin iso/boot/kernel.bin
cp src/boot/grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o theta.iso iso