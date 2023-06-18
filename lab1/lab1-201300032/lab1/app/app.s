.code32

.global start
start:
	pushl $13
	pushl $message
	call displayStr2
loop:
	jmp loop

message:
	.string "Hello, World!\n\0"

displayStr2:
	movl 4(%esp), %ebx
	movl 8(%esp), %ecx
	movl $((80*5+0)*2), %edi
	movb $0x0c, %ah
nextChar2:
	movb (%ebx), %al
	movw %ax, %gs:(%edi)
	addl $2, %edi
	incl %ebx
	loopnz nextChar2 # loopnz decrease ecx by 1
	ret
