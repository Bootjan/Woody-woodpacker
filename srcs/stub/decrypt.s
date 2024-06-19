section	.text
	global	decrypt

decrypt:	; void	decrypt(uint8_t* bytes, uint64_t size, uint8_t key)
	xor		rcx,	rcx
	xor		al,		al
	.startLoop:
		cmp		rcx,	rsi
		je		.return
	
		mov		al,		BYTE [rdi + rcx]
		xor		al,		dl
		mov		[rdi + rcx],	al
		
		inc		rcx
		jmp		.startLoop

	.return:
		ret
