#include "kernel.h"


struct gdt_entry{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[5];
struct gdt_ptr gp; 

void set_descriptor(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran){
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;
}

void init_gdt(){
    // init gdt 
    gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gp.base = (unsigned int)&gdt;

    // Your gdt must be set at address 
    // 0x00000800;

    print_k(WHITE, "INIT GDT", (char *)VIDEO, active_screen);
    // null descriptor
    set_descriptor(0, 0, 0, 0, 0);
    // kernel code segment
    set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // data segment
    set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // user mode code segment
    set_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xAF);
    // user mode data segment
    set_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    // let the processor know about it by calling gdt_flush
    gdt_flush();
}