# sudo apt-get install g++ binutils libc6-dev-i386
CPPPARAMETERS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-leading-underscore -fno-exceptions
ASSEMBLERPARAMETERS = --32
LINKERPARAMETERS = -melf_i386

parts = loader.o gdt.o kernel.o port.o idt.o interrupts.o

%.o: %.cpp
	g++ $(CPPPARAMETERS) -o $@ -c $<
	
%.o: %.s
	as $(ASSEMBLERPARAMETERS) -o $@ $<
	
mykernel.bin: linker.ld $(parts)
	ld $(LINKERPARAMETERS) -T $< -o $@ $(parts)
	
boot: mykernel.bin
	sudo cp $< /boot/mykernel.bin
	
mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot/
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo ' multiboot  /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo ' boot ' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
	
run: mykernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "MyOperatingSystem" &

.PHONY: clean
clean: 
	rm -f $(parts) mykernel.bin mykernel.iso