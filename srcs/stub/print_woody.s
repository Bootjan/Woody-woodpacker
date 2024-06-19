section	.data
	FORMAT:			db	"%s%c", 0x0
	WOODY:			db	"....WOODY....", 0x10

section	.text
	global	print_woody
	extern	printf,@function

print_woody:
	push	rcx

	mov		rdi,	FORMAT
	mov		rsi,	WOODY
	mov		dl,		0xa
	mov		al,		0
	call	printf	wrt ..plt

	pop		rcx
	ret
