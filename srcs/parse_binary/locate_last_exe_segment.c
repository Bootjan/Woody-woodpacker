#include "woody.h"
#include <stdint.h>
#include <elf.h>
#include <stdbool.h>

extern uint8_t*	stager_g;
extern uint8_t*	stager_end_g;

void
find_last_exe_segment(void)
{
	size_t	
}

enum {
    METHOD_LAST_PAGE_INJECT = 0,
    METHOD_EXPAND_AND_INJECT,
};

#define MAX_SH_NAMELEN 128
#define PAGE_SIZE 0x1000

typedef struct {
    char name[MAX_SH_NAMELEN];
    uint32_t *offset;
    uint32_t *size;
    int inject_method;
}	shinfo_t;

bool
payload_fits_in_current_segment(Elf64_Shdr* Sect_hdrs, uint16_t j, size_t total_payload_size)
{
	return (Sect_hdrs[j + 1].sh_addr - Sect_hdrs[j].sh_addr - Sect_hdrs[j].sh_size >= total_payload_size);
}

void
set_shinfo(shinfo_t* shinfo, char* shstr, Elf64_Shdr* Sect_hdrs)
{
	strncpy(shinfo->name, shstr + Sect_hdrs->sh_name, MAX_SH_NAMELEN - 1);
	shinfo->offset = (uint32_t *)Sect_hdrs->sh_offset;
	shinfo->size = (uint32_t *)Sect_hdrs->sh_size;
}

bool
load_last_exe_segment(file_map_t* file_map, shinfo_t* shinfo, size_t patch_size)
{
	Elf64_Ehdr*	Elf_hdr;
	Elf64_Phdr*	Prog_hdrs;
	Elf64_Shdr*	Sect_hdrs;
	char*		shstr;

	Elf_hdr = (Elf64_Ehdr *)(file_map->data);
	Prog_hdrs = (Elf64_Phdr *)((uintptr_t)file_map->data + Elf_hdr->e_phoff);
	Sect_hdrs = (Elf64_Shdr *)((uintptr_t)file_map->data + Elf_hdr->e_shoff);
	shstr = (char *)((uintptr_t)file_map->data + Sect_hdrs[Elf_hdr->e_shstrndx].sh_offset);

	uint32_t	segment_end, stager_size;
	uint16_t	i, j;
	bool		found = false;
	for (i = 0; i < Elf_hdr->e_phnum; i++)
	{
		if ((Prog_hdrs[i].p_flags & PF_X) == 0)
			continue;
		
		segment_end = Prog_hdrs[i].p_offset + Prog_hdrs[i].p_memsz;

		for (j = 0; j < Elf_hdr->e_shnum; j++)
		{
			if (Sect_hdrs[i].sh_addr + Sect_hdrs[i].sh_size == segment_end)
			{
				set_shinfo(shinfo, shstr, &(Sect_hdrs[j]));
				found = true;
				break;
			}
		}

		if (!found)
			continue;
		
		stager_size = (uintptr_t)&stager_end_g - (uintptr_t)&stager_g;
		// payload is able to fit without expanding the segment past the next page boundary
		if (payload_fits_in_current_segment(Sect_hdrs, j, patch_size + stager_size))
		{
			shinfo->inject_method = METHOD_LAST_PAGE_INJECT;
			return;
		}

		// check if it's the last section in the binary
		if (j + 1 == Elf_hdr->e_shnum)
		{
			shinfo->inject_method = METHOD_EXPAND_AND_INJECT;
			return;
		}

		// check if section can be expanded
		if ((Sect_hdrs[j].sh_addr + PAGE_SIZE) > Sect_hdrs[j + 1].sh_addr)
		{
			shinfo->inject_method = METHOD_EXPAND_AND_INJECT;
			return;
		}
	}
	return false;
}
