include system/make.inc

all: build

apps_port:
	@cd apps/porting && sh install_ported.sh all

apps_seaos:
	@cd apps/porting && sh install_ported.sh seaos-util

newhd:
	@sh tools/chd.sh

toolchain: toolchain/built

toolchain/built:
	@cd toolchain && sh install_toolchain.sh

system/skernel:
	@$(MAKE) -j2 -s -C system all

man:
	sh tools/gen_man.sh

hd.img: newhd

build: system/skernel
	@-read tmp < build_number && let tmp++ && echo $$tmp > build_number
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
	@qemu -serial stdio -smp 1 -hda hd.img -localtime -m 1024

test:
	@-sudo mkdir /tmp_t 2> /dev/null
	@sudo mount -t tmpfs -o size=2g tmpfs /tmp_t
	@cp hd.img /tmp_t/hd.img
	@qemu -serial stdio -smp 1 -hda /tmp_t/hd.img -localtime -m 1024
	@sudo umount /tmp_t
