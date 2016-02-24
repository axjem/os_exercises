# lab0 SPOC思考题

## 个人思考题

---

能否读懂ucore中的AT&T格式的X86-32汇编语言？请列出你不理解的汇编语言。
- [x]  

>  http://www.imada.sdu.dk/Courses/DM18/Litteratur/IntelnATT.htm
>  inb一般应用程序用不到的指令等。

虽然学过计算机原理和x86汇编（根据THU-CS的课程设置），但对ucore中涉及的哪些硬件设计或功能细节不够了解？
- [x]  

> 中断寄存器和非通用寄存器等。


哪些困难（请分优先级）会阻碍你自主完成lab实验？
- [x]  

>   

如何把一个在gdb中或执行过程中出现的物理/线性地址与你写的代码源码位置对应起来？
- [x]  

> 1. 在gdb中通过break加行号得到物理地址，list加*物理地址得到行号。
> 2. 用nm, objdump工具可以看到

了解函数调用栈对lab实验有何帮助？
- [x]  

> 除了错可以调试 
> 对于函数的调用过程和程序的运行过程有更好的理解。
> 便于调试以及检查。 

你希望从lab中学到什么知识？
- [x]  

>   

---

## 小组讨论题

---

搭建好实验环境，请描述碰到的困难和解决的过程。
- [x]  

> 困难：在virtualbox中设置虚拟机的时候找不到Linux的64位选项。
> 解决：需要通过BIOS设置将电脑的虚拟化功能打开（本电脑LenovoY480的VT功能是锁的，需要打开）。
> 开始时选择了UBUNTU 32位，不能启动，后来换成64位就能顺利运行

熟悉基本的git命令行操作命令，从github上
的 http://www.github.com/chyyuu/ucore_lab 下载
ucore lab实验
- [x]  

> clone 仓库 
> gitclone http://www.github.com/chyyuu/ucore_lab

尝试用qemu+gdb（or ECLIPSE-CDT）调试lab1
- [x]   

> 清除文件夹：make clean 
> 编译lab1：make 
> 调出debug命令行：make debug

对于如下的代码段，请说明”：“后面的数字是什么含义
```
 /* Gate descriptors for interrupts and traps */
 struct gatedesc {
    unsigned gd_off_15_0 : 16;        // low 16 bits of offset in segment
    unsigned gd_ss : 16;            // segment selector
    unsigned gd_args : 5;            // # args, 0 for interrupt/trap gates
    unsigned gd_rsv1 : 3;            // reserved(should be zero I guess)
    unsigned gd_type : 4;            // type(STS_{TG,IG32,TG32})
    unsigned gd_s : 1;                // must be 0 (system)
    unsigned gd_dpl : 2;            // descriptor(meaning new) privilege level
    unsigned gd_p : 1;                // Present
    unsigned gd_off_31_16 : 16;        // high bits of offset in segment
 };
 ```

- [x]  

> 每一个filed(域，成员变量)在struct(结构)中所占的位数; 也称“位域”，用于表示这个成员变量占多少位(bit)。

对于如下的代码段，
```
#define SETGATE(gate, istrap, sel, off, dpl) {            \
    (gate).gd_off_15_0 = (uint32_t)(off) & 0xffff;        \
    (gate).gd_ss = (sel);                                \
    (gate).gd_args = 0;                                    \
    (gate).gd_rsv1 = 0;                                    \
    (gate).gd_type = (istrap) ? STS_TG32 : STS_IG32;    \
    (gate).gd_s = 0;                                    \
    (gate).gd_dpl = (dpl);                                \
    (gate).gd_p = 1;                                    \
    (gate).gd_off_31_16 = (uint32_t)(off) >> 16;        \
}
```
如果在其他代码段中有如下语句，
```
unsigned intr;
intr=8;
SETGATE(intr, 0,1,2,3);
```
请问执行上述指令后， intr的值是多少？

- [x]  0x10002

> https://github.com/chyyuu/ucore_lab/blob/master/related_info/lab0/lab0_ex3.c

请分析 [list.h](https://github.com/chyyuu/ucore_lab/blob/master/labcodes/lab2/libs/list.h)内容中大致的含义，并能include这个文件，利用其结构和功能编写一个数据结构链表操作的小C程序
- [x]  

> 

---

## 开放思考题

---

是否愿意挑战大实验（大实验内容来源于你的想法或老师列好的题目，需要与老师协商确定，需完成基本lab，但可不参加闭卷考试），如果有，可直接给老师email或课后面谈。
- [x]  

>  

## v9-cpu相关题目
---

### 提前准备
```
sudo apt-get install hexedit
cd YOUR v9-cpu DIR
git pull 
cd YOUR os_course_spoc_exercise DIR
git pull 
```

分析和实验funcall.c，需要完成的内容包括： 
-[X]

 - 修改代码，可正常显示小组两位同学的学号（用字符串）  
 ```
    ret = write(1, "2012011308 2012011308", 22);
 ```
 - 生成funcall.c的汇编码，理解其实现并给汇编码写注释
   - 查看文件./build-funcall.sh可见： ./xc -s -Iroot/lib root/usr/funcall.c >funcall.txt
   - 说明：运行./build-funcall.sh后，得到文件funcall.txt，里面包含的就是汇编代码
   ```
    root/usr/funcall.c  1: #include <u.h>
    root/lib/u.h  1: // u.h
    root/lib/u.h  2: 
    root/lib/u.h  3: // instruction set
    root/lib/u.h  4: enum {
    root/lib/u.h  5:   HALT,ENT ,LEV ,JMP ,JMPI,JSR ,JSRA,LEA ,LEAG,CYC ,MCPY,MCMP,MCHR,MSET, // system
    root/lib/u.h  6:   LL  ,LLS ,LLH ,LLC ,LLB ,LLD ,LLF ,LG  ,LGS ,LGH ,LGC ,LGB ,LGD ,LGF , // load a
    root/lib/u.h  7:   LX  ,LXS ,LXH ,LXC ,LXB ,LXD ,LXF ,LI  ,LHI ,LIF ,
    root/lib/u.h  8:   LBL ,LBLS,LBLH,LBLC,LBLB,LBLD,LBLF,LBG ,LBGS,LBGH,LBGC,LBGB,LBGD,LBGF, // load b
    root/lib/u.h  9:   LBX ,LBXS,LBXH,LBXC,LBXB,LBXD,LBXF,LBI ,LBHI,LBIF,LBA ,LBAD,
    root/lib/u.h  10:   SL  ,SLH ,SLB ,SLD ,SLF ,SG  ,SGH ,SGB ,SGD ,SGF ,                     // store
    root/lib/u.h  11:   SX  ,SXH ,SXB ,SXD ,SXF ,
    root/lib/u.h  12:   ADDF,SUBF,MULF,DIVF,                                                   // arithmetic
    root/lib/u.h  13:   ADD ,ADDI,ADDL,SUB ,SUBI,SUBL,MUL ,MULI,MULL,DIV ,DIVI,DIVL,
    root/lib/u.h  14:   DVU ,DVUI,DVUL,MOD ,MODI,MODL,MDU ,MDUI,MDUL,AND ,ANDI,ANDL,
    root/lib/u.h  15:   OR  ,ORI ,ORL ,XOR ,XORI,XORL,SHL ,SHLI,SHLL,SHR ,SHRI,SHRL,
    root/lib/u.h  16:   SRU ,SRUI,SRUL,EQ  ,EQF ,NE  ,NEF ,LT  ,LTU ,LTF ,GE  ,GEU ,GEF ,      // logical
    root/lib/u.h  17:   BZ  ,BZF ,BNZ ,BNZF,BE  ,BEF ,BNE ,BNEF,BLT ,BLTU,BLTF,BGE ,BGEU,BGEF, // conditional
    root/lib/u.h  18:   CID ,CUD ,CDI ,CDU ,                                                   // conversion
    root/lib/u.h  19:   CLI ,STI ,RTI ,BIN ,BOUT,NOP ,SSP ,PSHA,PSHI,PSHF,PSHB,POPB,POPF,POPA, // misc
    root/lib/u.h  20:   IVEC,PDIR,SPAG,TIME,LVAD,TRAP,LUSP,SUSP,LCL ,LCA ,PSHC,POPC,MSIZ,
    root/lib/u.h  21:   PSHG,POPG,NET1,NET2,NET3,NET4,NET5,NET6,NET7,NET8,NET9,
    root/lib/u.h  22:   POW ,ATN2,FABS,ATAN,LOG ,LOGT,EXP ,FLOR,CEIL,HYPO,SIN ,COS ,TAN ,ASIN, // math
    root/lib/u.h  23:   ACOS,SINH,COSH,TANH,SQRT,FMOD,
    root/lib/u.h  24:   IDLE
    root/lib/u.h  25: 
    };
    root/lib/u.h  26: 
    root/lib/u.h  27: // system calls
    root/lib/u.h  28: enum {
     root/lib/u.h  29:   S_fork=1, S_exit,   S_wait,   S_pipe,   S_write,  S_read,   S_close,  S_kill,
     root/lib/u.h  30:   S_exec,   S_open,   S_mknod,  S_unlink, S_fstat,  S_link,   S_mkdir,  S_chdir,
     root/lib/u.h  31:   S_dup2,   S_getpid, S_sbrk,   S_sleep,  S_uptime, S_lseek,  S_mount,  S_umount,
     root/lib/u.h  32:   S_socket, S_bind,   S_listen, S_poll,   S_accept, S_connect, 
     root/lib/u.h  33: 
    };
    root/lib/u.h  34: 
    root/lib/u.h  35: typedef unsigned char uchar;
    root/lib/u.h  36: typedef unsigned short ushort;
    root/lib/u.h  37: typedef unsigned int uint;
    root/lib/u.h  38: 
    root/usr/funcall.c  2: int ret;
    root/usr/funcall.c  3: out(port, val)
    root/usr/funcall.c  4: {
     root/usr/funcall.c  5:   asm(LL,8);   // load register a with port
     00000000  0000080e  LL    0x8 (D 8)     // a = *(sp+8)
     root/usr/funcall.c  6:   asm(LBL,16); // load register b with val
     00000004  00001026  LBL   0x10 (D 16)   // b = *(sp+16)
     root/usr/funcall.c  7:   asm(BOUT);   // output byte to console
     00000008  0000009a  BOUT                // a = write(a, &b, 1);
     root/usr/funcall.c  8: 
    }
    root/usr/funcall.c  9: 
    root/usr/funcall.c  10: int write(int f, char *s, int n)
    0000000c  00000002  LEV   0x0 (D 0)      // pc = *sp, sp += 8
    root/usr/funcall.c  11: {
     root/usr/funcall.c  12:   int i;
     root/usr/funcall.c  13:   ret = 1;
     00000010  fffff801  ENT   0xfffffff8 (D -8)    // sp -= 8
     00000014  00000123  LI    0x1 (D 1)            // a = 1
     00000018  00000045  SG    0x0 (D 0)            // *(pc+0) = a    // &ret = (pc+0)
     root/usr/funcall.c  14:   i=n;
     0000001c  0000200e  LL    0x20 (D 32)          // a = *(sp+32)   // 存放参数n
     00000020  00000440  SL    0x4 (D 4)            // *(sp+4) = a    // 存放i
     root/usr/funcall.c  15:   while (i--)
     00000024  00000003  JMP   <fwd>
     root/usr/funcall.c  16:     out(f, *s++);
     00000028  0000180e  LL    0x18 (D 24)          // a = *(sp+24)   // 字符串地址++
     0000002c  ffffff57  SUBI  0xffffffff (D -1)    // a += 1
     00000030  00001840  SL    0x18 (D 24)          // *(sp+24) = a
     00000034  ffffff1f  LXC   0xffffffff (D -1)    // a = 物理地址为-1的内存里的char 
     00000038  0000009d  PSHA                       // push a         // char
     0000003c  0000180e  LL    0x18 (D 24)          // a = *(sp+24)
     00000040  0000009d  PSHA                       // push a
     00000044  ffffb805  JSR   0xffffffb8 (TO 0x0)  // *sp=pc, sp -= 8; jump to 0x0
     00000048  00001001  ENT   0x10 (D 16)          // sp += 16
     root/usr/funcall.c  17:   return i;
     0000004c  0000040e  LL    0x4 (D 4)            // a = *(sp+4)    // i --
     00000050  00000157  SUBI  0x1 (D 1)            // a -= 1
     00000054  00000440  SL    0x4 (D 4)            // *(sp+4) = a
     00000058  00000154  ADDI  0x1 (D 1)            // a += 1
     0000005c  00000086  BNZ   <fwd>                // a != 0，跳回去..
     00000060  0000040e  LL    0x4 (D 4)            // a = *(sp+4)    // a其实就是返回值。。
     00000064  00000802  LEV   0x8 (D 8)            // pc = pop(), sp += 8+8
     root/usr/funcall.c  18: }  
     root/usr/funcall.c  19: 
     root/usr/funcall.c  20: main()
     00000068  00000802  LEV   0x8 (D 8)            // pc = *sp, sp += 8+8
    root/usr/funcall.c  21: {
     root/usr/funcall.c  22: 
     root/usr/funcall.c  23:   //Change S1/S2 ID to your student ID, and change 12 to new str length
     root/usr/funcall.c  24:   ret = write(1, "2012011308 2012011308", 22);
     0000006c  0000169e  PSHI  0x16 (D 22)          // push 22
     00000070  00000008  LEAG  0xq0 (D 0)           // a = pc
     00000074  0000009d  PSHA                       // push a --> push pc
     00000078  0000019e  PSHI  0x1 (D 1)            // push 1
     0000007c  ffff9005  JSR   0xffffff90 (TO 0x10) // push pc; jump to write
     00000080  00001801  ENT   0x18 (D 24)          // sp += 24
     00000084  00000045  SG    0x0 (D 0)            // *(pc+0) = a
     root/usr/funcall.c  25:   asm(HALT);
     00000088  00000000  HALT
     root/usr/funcall.c  26: 
    }
    root/usr/funcall.c  27: 
    0000008c  00000002  LEV   0x0 (D 0)
     </fwd>
    }
   ```
  
 - 尝试用xem的简单调试功能单步调试代码  
   ```
   ./xem -g funcall
   ```


 - 回答如下问题：
   - funcall中的堆栈有多大？是内核态堆栈还是用户态堆栈
      - 不知道，咋算？
      - 不知道
   - funcall中的全局变量ret放在内存中何处？如何对它寻址？
      - 不知道，pc+0是？ 
   - funcall中的字符串放在内存中何处？如何对它寻址？
      - 0x90
      - 传参的时候有字符串的首地址，参数压栈。直接利用地址可得。
   - 局部变量i在内存中的何处？如何对它寻址？
      - 0x07bfffdc (sp+4)
      - 栈偏移
   - 当前系统是处于中断使能状态吗？
      - ?
   - funcall中的函数参数是如何传递的？函数返回值是如何传递的？
      - 压栈
      - 用寄存器a传递
   - 分析并说明funcall执行文件的格式和内容  
      - 先是文件头信息hdr，然后是代码段，最后是数据段

分析和实验os0.c，需要完成的内容包括： 
-[X]

 - 生成os0.c的汇编码，理解其实现并给汇编码写注释
 - 尝试用xem的简单调试功能单步调试代码
 - 回答如下问题：
   - 何处设置的中断使能？   
   - 系统何时处于中断屏蔽状态？
   - 如果系统处于中断屏蔽状态，如何让其中断使能？
   - 系统产生中断后，CPU会做哪些事情？（在没有软件帮助的情况下）
   - CPU执行RTI指令的具体完成工作是哪些？

[HARD]分析和实验os1/os3.c，需要完成的内容包括： 
-[X]
 
 - os1中的task1和task2的堆栈的起始和终止地址是什么？
 - os1是如何实现任务切换的？
 - os3中的task1和task2的堆栈的起始和终止地址是什么？
 - os3是如何实现任务切换的？
 - os3的用户态task能够破坏内核态的系统吗？
