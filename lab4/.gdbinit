target remote localhost:1234
symbol-file /home/scorcery/lab2022/lab4/lab4/bootloader/bootloader.elf
add-symbol-file /home/scorcery/lab2022/lab4/lab4/kernel/kMain.elf
add-symbol-file /home/scorcery/lab2022/lab4/lab4/app/uMain.elf
b fork
si
watch current
watch pcb[1].state
watch pcb[2].state
watch pcb[3].state
watch pcb[4].state
watch pcb[5].state

layout split
