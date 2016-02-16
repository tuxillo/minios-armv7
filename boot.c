#include "boot.h"
#include "subr.h"

void kern_boot(void);

void
kern_boot(void)
{

	kprintf("miniOS arvm7 startup ...\n");

	/* Loop forever */
	for(;;);
}
