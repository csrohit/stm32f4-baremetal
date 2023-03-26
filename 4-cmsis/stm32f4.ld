ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx):    ORIGIN = 0x08000000,    LENGTH =256K
    SRAM(rwx):    ORIGIN = 0x20000000,    LENGTH =64K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    /* The startup code into "FLASH" Rom type memory */
    .isr_vector :
    { 
        . = ALIGN(4);
        KEEP(*(.isr_vector)) /* Startup code */
        . = ALIGN(4);
    } >FLASH

    /* The program code and other data into "FLASH" Rom type memory */
    .text :
    {
        . = ALIGN(4);
        *(.text)           /* .text sections (code) */
        *(.text*)          /* .text* sections (code) */
        . = ALIGN(4);
    } >FLASH

    _la_data = LOADADDR(.data);

    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss :
    {
        _sbss = .;
        *(.bss SORT(.bss.*) COMMON)
        . = ALIGN(4);
        _ebss = .;
        
        . = ALIGN(4);
        _end = .;
    }> SRAM
}
