
apps_port:
	@cd apps/porting && sh install_ported.sh all

apps_seaos:
	@cd apps/porting && sh install_ported.sh seaos-util

newhd:
	@sh tools/chd.sh

toolchain:
	@cd toolchain && sh install_toolchain.sh

system/skernel:
	@make -s -C system all

hd.img: newhd

build: system/skernel hd.img
	@echo updating hd image...
	@sh tools/open_hdimage.sh
	@sudo cp -rf system/drivers/built/* /mnt/sys/modules/
	@sudo cp -rf system/initrd.img /mnt/sys/initrd
	@sudo cp -rf system/skernel /mnt/sys/kernel
	@sh tools/close_hdimage.sh

clean:
	@make -s -C system clean
	@rm hd.img hd2.img
