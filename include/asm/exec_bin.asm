[global run_binary]
run_binary:
  mov eax, [esp+4]
  call eax    ;; Once we get a ret, we come back to this.

  ;; Then we just return to caller.
  ret