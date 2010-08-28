#include "multiboot.h"

#include "../../utils/flag.h"

/**Permet de stocker à une place sûre les informations passées*/
static multiboot_info_t mbi;

int init_multiboot_info(multiboot_info_t * info)
{
	/*On recopie à un emplacement sûr la structure multiboot_info (on  ne
		fait pas confiance à grub par exemple...)
		Mais on n'a pas protéger les structures vers lesquelles pointent
		quelques unes des informations de multiboot_info. A faire ?
	*/
	if(CHEK_FLAG(mbi.flags, 4) && CHEK_FLAG(mbi.flags, 5))
		return 1;
	memcpy(&mbi, info, sizeof(multiboot_info_t));
	return 0 ;
}

//Plutôt retourner une copie ?
multiboot_info_t * get_multiboot_info()
{
	return &mbi;
}

unsigned int get_mem(int mem)
{
	if(!CHEK_FLAG(mbi.flags, 0))
		return 0;
	else if( mem)
		return mbi.mem_lower;
	else
		return mbi.mem_upper;
}

uint_8 get_boot_device(unsigned int partition_level)
{
	if(!CHEK_FLAG(mbi.flags, 1))
		return 0xFF;
	else if(partition_level < 4)
	{
		//améliorer directement la structure mbi avec des champs de bits
		return EXTRACT_OCTET(mbi.boot_device, partition_level);
	}
	else
		return 0xFF;
}

char * get_cmdline()
{
	if(CHEK_FLAG(mbi.flags, 2))
		return (char *) mbi.cmdline;
	else
		return NULL;
		
}

unsigned int get_nbModules()
{
	if(CHEK_FLAG(mbi.flags, 3))
		return mbi.mods_count;
	else
		return 0;
}

multiboot_module_t * get_modules()
{
	if(CHEK_FLAG(mbi.flags, 3))
		return (multiboot_module_t *) mbi.mods_addr;
	else
		return NULL;
}

unsigned int get_mmap_length()
{
	if(CHEK_FLAG(mbi.flags, 6))
		return mbi.mmap_length;
	else 
		return 0;
}

multiboot_memory_map_t * get_mmap()
{
	if(CHEK_FLAG(mbi.flags, 6))
		return (multiboot_memory_map_t *) mbi.mmap_addr;
	else
		return NULL;
}

unsigned int get_drives_length()
{
	if(CHEK_FLAG(mbi.flags, 7))
	{
		return mbi.drives_length;
	}
	else
		return 0;
}

multiboot_drive_t * get_drive()
{
	if(CHEK_FLAG(mbi.flags, 7))
	{
		return (multiboot_drive_t *) mbi.drives_addr;
	}
	else
		return NULL;
}

void * get_config_table()
{
	if(CHEK_FLAG(mbi.flags, 8))
	{
		return (void *) mbi.config_table;
	}
	else 
		return NULL;
}
