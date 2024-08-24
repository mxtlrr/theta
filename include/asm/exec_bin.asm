%macro clear_regs 0
  xor ebx, ebx
  xor ecx, ecx
  xor edx, edx
  xor edi, edi
  xor esi, esi
%endmacro

[global run_binary]
run_binary:
  mov eax, [esp+4]

  ;; Clear registers before use.
  clear_regs
  
  call eax    ;; Once we get a ret, we come back to this.

  ;; Then we just return to caller.
  ret