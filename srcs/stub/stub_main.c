#include <stdint.h>
#include <aio.h>

#define ENCRYPTION_KEY 103

typedef void* function_t;

void	print_woody(void);
void	decrypt(uint8_t* bytes, size_t size, uint8_t key);
void	call_entrypoint(function_t	entrypoint);

typedef struct {
	function_t	entrypoint;
	uint64_t*	exe_start;
	size_t		size;
}	sample_info_t;

int
main(void)
{
	sample_info_t	info = { 0 };
	uint64_t*	encrypted_bytes = locate_encrypted_bytes(&info);
	if (!encrypted_bytes)
		return (print_error(), 1);
	print_woody();
	decrypt(encrypted_bytes, info.size, ENCRYPTION_KEY);
	call_entrypoint(info.entrypoint);
}
