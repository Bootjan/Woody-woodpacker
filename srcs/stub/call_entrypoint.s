section	.text
	global	call_entrypoint

call_entrypoint:	; int	call_entrypoint(void (*f)())
	call	rdi
	ret
