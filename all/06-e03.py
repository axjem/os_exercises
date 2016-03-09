#!/usr/local/bin/python

import argparse

def get_mem():
    mem = []
    fin = open('memdata.txt', 'r')
    text = fin.read()
    for line in text.split('\n'):
        page_data = line[9:].split()
        page_data = [int(d, 16) for d in page_data]
        mem.extend(page_data)
    return mem

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('virtual_addr', type=str)
    args = parser.parse_args()

    virtual_addr = int(args.virtual_addr, 16)
    mem = get_mem()

    page_dir_base = 0x11

    pdbr = 544
    pdt_list = mem[pdbr:pdbr+32]

    page_dir_idx = virtual_addr >> 10
    page_dir_entry = pdt_list[page_dir_idx]
    page_tbl_valid = page_dir_entry >> 7
    page_tbl_base = page_dir_entry & 127

    print 'Virtual Address {}:'.format(args.virtual_addr)
    print '  --> pde index: {}   pde contents: (valid {}, pfn {})'.format(hex(page_dir_idx), hex(page_tbl_valid), hex(page_tbl_base))

    if(page_tbl_valid == 0):
        print '    --> Fault (page directory entry not valid)'
    else:
        page_tbl_entry = mem[page_tbl_base * 32 + ((virtual_addr & 1023) >> 5)]
        page_tbl_valid = page_tbl_entry >> 7
        page_tbl_base = page_tbl_entry & 127
        print '    --> pte index: {}   pte contents: (valid {}, pfn {})'.format(hex(page_dir_idx), hex(page_tbl_valid), hex(page_tbl_base))
        if(page_tbl_valid == 0):
            print '      --> Fault (page table entry not valid)'

        else:
            phys_addr = (page_tbl_base << 5) + virtual_addr & 31
            val = mem[page_tbl_base * 32 + (virtual_addr & 31)]
            print '      --> Translates to Physical Address {} --> Value: {}'.format(hex(phys_addr), hex(val))
