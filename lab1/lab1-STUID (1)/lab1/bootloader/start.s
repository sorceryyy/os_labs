/* Protected Mode Hello World */
	.code16
	.global start
	start:
			movw %cs,%ax
			movw %ax,%ds
			movw %ax,%es
			movw %ax,%ss

			cli                             #关闭中断
			inb $0x92,%al
			orb $0x02,%al															
			outb %al, $0x92      #启动A20总线

    
			data32 addr32 lgdt gdtDesc      #加载GDTR
																			#启动保护模式
    
			movl %cr0,%eax								  #设置CR0的PE位（第0位）为1
			orl $0x01, %eax
			movl %eax,%cr0

			data32 ljmp $0x08, $start32     #长跳转切换至保护模式

	.code32
	start32:
		movw $0x10,%ax
		movw %ax,%ds
		movw %ax,%es
		movw %ax,%fs
		movw %ax,%ss
		movw $0x18,%ax                             #初始化DS ES FS GS SS 初始化栈顶指针ESP
		movw %ax,%gs
		movl $0x8000,%eax
		movl %eax,%esp


		jmp bootMain

 loop:
		jmp loop

 message:
	 .string "Hello, World!\n\0"

 displayStr:
	 movl 4(%esp), %ebx
	 movl 8(%esp), %ecx
	 movl $((80*5+0)*2), %edi
	 movb $0x0c, %ah
 nextChar:
	 movb (%ebx), %al
	 movw %ax, %gs:(%edi)
	 addl $2, %edi
	 incl %ebx
	 loopnz nextChar # loopnz decrease ecx by 1
	 ret

 gdt:
		 .word  0,0                     #GDT第一个表项必须为空
		 .byte  0,0,0,0 
		 .word  0xffff,0x0                         #代码段描述符
		 .byte  0x0,0x9a,0xcf,0x0
        
		 .word  0xffff,0x0                         #数据段描述符
		 .byte  0x0,0x92,0xcf,0x0
        
		 .word  0xffff,0x8000                         #视频段描述符
		 .byte  0x0b,0x92,0xcf,0x0

		 

 gdtDesc:
		 .word (gdtDesc - gdt -1)				#limit
		 .long gdt											#base


