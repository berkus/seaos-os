include system/make.inc

all: build

apps_port:
	@cd apps/porting && sh install_ported.sh all

apps_seaos:
	@cd apps/porting && sh install_ported.sh seaos-util

newhd:
	@zsh tools/chd.sh

toolchain: toolchain/built

toolchain/built:
	@cd toolchain && sh install_toolchain.sh

system/skernel:
	@PATH=$$PATH:/usr/local/cross/bin $(MAKE) -j2 -s -C system all

man:
	sh tools/gen_man.sh

hd.img: newhd

build: system/skernel
	@sh tools/inc_build.sh
	@echo -n "build: "
	@cat build_number
	@echo updating hd image...
	@sh tools/open_hdimage.sh
	@sudo mkdir -p /mnt-seaos/sys/modules-${KERNEL_VERSION}/
	@sudo cp -rf system/drivers/built/* /mnt-seaos/sys/modules-${KERNEL_VERSION}/
	@sudo cp -rf system/initrd.img /mnt-seaos/sys/initrd
	@sudo cp -rf system/skernel /mnt-seaos/sys/kernel
	@rm system/skernel
	@sh tools/close_hdimage.sh

clean:
	@make -s -C system clean
	@rm hd.img hd2.img

test_t:
	@qemu-system-i386 -serial stdio -smp 1 -drive file=hd.img,if=ide  -localtime -m 1024 -boot=disk

test:
	@-sudo mkdir /tmp_t 2> /dev/null
	@sudo mount -t tmpfs -o size=2g tmpfs /tmp_t
	@cp hd.img /tmp_t/hd.img
	@qemu-system-i386 -serial stdio -smp 1 -drive file=/tmp_t/hd.img,if=ide,cache=unsafe,media=disk -localtime -m 1024 -boot a
	@sudo umount /tmp_t
