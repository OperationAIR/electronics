
MEMORY
{
  /* Define each memory region */
  Flash (rx) : ORIGIN = 0x0, LENGTH = 0x10000 /* 64K bytes */
  RAM_IAP (rwx) : ORIGIN = 0x10000000, LENGTH = 0x0020 /* 32 bytes */
  RAM_main (rwx) : ORIGIN = 0x10000020, LENGTH = 0x1FE0 /* 8K-32 bytes */
  RAM_USB (rwx) : ORIGIN = 0x20004000, LENGTH = 0x800 /* 2K bytes */


}

/* Define a symbol for the top of each memory region */
__top_Flash = 0x0 + 0xC000;
__top_RAM_main      = ORIGIN(RAM_main)      + LENGTH(RAM_main);
__top_RAM_USB       = ORIGIN(RAM_USB)       + LENGTH(RAM_USB);

