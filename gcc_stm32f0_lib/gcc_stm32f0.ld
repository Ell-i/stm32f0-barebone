MEMORY
{
    /* STM32F051 */
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x00010000 /* 64 Kbytes */
    RAM (rwx) :  ORIGIN = 0x20000000, LENGTH = 0x00002000 /* 8 Kbyte */
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        KEEP(*(.after_vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : AT (ADDR(.text) + SIZEOF(.text))
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > RAM

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM
}
