#
# This file is part of the coreboot project.
#
# Copyright (C) 2009 coresystems GmbH
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
subdirs-y += loaders
subdirs-y += gnat


ifneq ($(CONFIG_BOOTBLOCK_CUSTOM),y)
bootblock-y += bootblock.c
endif

bootblock-y += prog_loaders.c
bootblock-y += prog_ops.c
bootblock-y += cbfs.c
bootblock-$(CONFIG_GENERIC_GPIO_LIB) += gpio.c
bootblock-y += libgcc.c
bootblock-$(CONFIG_GENERIC_UDELAY) += timer.c

ifeq ($(CONFIG_EARLY_CBMEM_INIT),y)
bootblock-$(CONFIG_COLLECT_TIMESTAMPS) += timestamp.c
endif

bootblock-$(CONFIG_CONSOLE_CBMEM) += cbmem_console.c
bootblock-y += delay.c
bootblock-y += memchr.c
bootblock-y += memcmp.c
bootblock-y += boot_device.c
bootblock-y += fmap.c

verstage-y += prog_loaders.c
verstage-y += prog_ops.c
verstage-y += delay.c
verstage-y += cbfs.c
verstage-y += halt.c
verstage-y += fmap.c
verstage-y += libgcc.c
verstage-y += memcmp.c
verstage-$(CONFIG_COLLECT_TIMESTAMPS) += timestamp.c
verstage-y += boot_device.c
verstage-$(CONFIG_CONSOLE_CBMEM) += cbmem_console.c

ifeq ($(MOCK_TPM),1)
libverstage-y += mocked_tlcl.c
romstage-$(CONFIG_SEPARATE_VERSTAGE) += mocked_tlcl.c
else
libverstage-$(CONFIG_TPM) += tlcl.c
libverstage-$(CONFIG_TPM2) += tpm2_marshaling.c
libverstage-$(CONFIG_TPM2) += tpm2_tlcl.c

ifeq ($(CONFIG_SEPARATE_VERSTAGE),y)
romstage-$(CONFIG_TPM) += tlcl.c
romstage-$(CONFIG_TPM2) += tpm2_marshaling.c
romstage-$(CONFIG_TPM2) += tpm2_tlcl.c
endif # CONFIG_SEPARATE_VERSTAGE

endif

verstage-$(CONFIG_GENERIC_UDELAY) += timer.c
verstage-$(CONFIG_GENERIC_GPIO_LIB) += gpio.c

romstage-y += prog_loaders.c
romstage-y += prog_ops.c
romstage-y += memchr.c
romstage-y += memcmp.c
$(foreach arch,$(ARCH_SUPPORTED),\
	    $(eval rmodules_$(arch)-y += memcmp.c) \
	    $(eval rmodules_$(arch)-y += rmodule.ld))

romstage-y += fmap.c
romstage-y += delay.c
romstage-y += cbfs.c
romstage-$(CONFIG_COMPRESS_RAMSTAGE) += lzma.c lzmadecode.c
romstage-y += libgcc.c
romstage-y += memrange.c
romstage-$(CONFIG_PRIMITIVE_MEMTEST) += primitive_memtest.c
ramstage-$(CONFIG_PRIMITIVE_MEMTEST) += primitive_memtest.c
romstage-$(CONFIG_CACHE_AS_RAM) += ramtest.c
romstage-$(CONFIG_GENERIC_GPIO_LIB) += gpio.c
ramstage-y += region_file.c
romstage-y += region_file.c
ramstage-y += romstage_handoff.c
romstage-y += romstage_handoff.c
romstage-y += romstage_stack.c
ramstage-y += romstage_stack.c
romstage-y += stack.c
ramstage-y += rtc.c

ifeq ($(CONFIG_EARLY_CBMEM_INIT),y)
romstage-$(CONFIG_COLLECT_TIMESTAMPS) += timestamp.c
romstage-$(CONFIG_CONSOLE_CBMEM) += cbmem_console.c
endif

romstage-y += compute_ip_checksum.c
ifeq ($(CONFIG_COMPILER_GCC),y)
bootblock-$(CONFIG_ARCH_BOOTBLOCK_X86_32) += gcc.c
verstage-$(CONFIG_ARCH_VERSTAGE_X86_32) += gcc.c
romstage-$(CONFIG_ARCH_ROMSTAGE_X86_32) += gcc.c
ramstage-$(CONFIG_ARCH_RAMSTAGE_X86_32) += gcc.c
smm-$(CONFIG_ARCH_RAMSTAGE_X86_32) += gcc.c
endif

romstage-$(CONFIG_GENERIC_UDELAY) += timer.c

ramstage-y += prog_loaders.c
ramstage-y += prog_ops.c
ramstage-y += hardwaremain.c
ramstage-y += selfboot.c
ramstage-y += coreboot_table.c
ramstage-y += bootmem.c
ramstage-y += fmap.c
ramstage-y += memchr.c
ramstage-y += memcmp.c
ramstage-y += malloc.c
smm-$(CONFIG_SMM_TSEG) += malloc.c
ramstage-y += delay.c
ramstage-y += fallback_boot.c
ramstage-y += compute_ip_checksum.c
ramstage-y += cbfs.c
ramstage-y += lzma.c lzmadecode.c
ramstage-y += stack.c
ramstage-y += hexstrtobin.c
ramstage-y += wrdd.c
ramstage-$(CONFIG_CONSOLE_CBMEM) += cbmem_console.c
ramstage-$(CONFIG_BOOTSPLASH) += jpeg.c
ramstage-$(CONFIG_TRACE) += trace.c
ramstage-$(CONFIG_COLLECT_TIMESTAMPS) += timestamp.c
ramstage-$(CONFIG_COVERAGE) += libgcov.c
ramstage-$(CONFIG_MAINBOARD_DO_NATIVE_VGA_INIT) += edid.c
ramstage-y += memrange.c
ramstage-$(CONFIG_COOP_MULTITASKING) += thread.c
ramstage-$(CONFIG_TIMER_QUEUE) += timer_queue.c
ramstage-$(CONFIG_GENERIC_GPIO_LIB) += gpio.c
ramstage-$(CONFIG_GENERIC_UDELAY) += timer.c
ramstage-y += b64_decode.c
ramstage-$(CONFIG_ACPI_NHLT) += nhlt.c
ramstage-$(CONFIG_TPM2) += tpm2_marshaling.c
ramstage-$(CONFIG_TPM2) += tpm2_tlcl.c

romstage-y += cbmem_common.c
romstage-y += imd_cbmem.c
romstage-y += imd.c

ramstage-y += cbmem_common.c
ramstage-y += imd_cbmem.c
ramstage-y += imd.c

postcar-y += cbmem_common.c
postcar-$(CONFIG_CONSOLE_CBMEM) += cbmem_console.c
postcar-y += imd_cbmem.c
postcar-y += imd.c
postcar-y += romstage_handoff.c

bootblock-y += hexdump.c
ramstage-y += hexdump.c
romstage-y += hexdump.c
verstage-y += hexdump.c

bootblock-$(CONFIG_REG_SCRIPT) += reg_script.c
verstage-$(CONFIG_REG_SCRIPT) += reg_script.c
romstage-$(CONFIG_REG_SCRIPT) += reg_script.c
ramstage-$(CONFIG_REG_SCRIPT) += reg_script.c

ifeq ($(CONFIG_CACHE_RELOCATED_RAMSTAGE_OUTSIDE_CBMEM),y)
ramstage-y += ext_stage_cache.c
romstage-y += ext_stage_cache.c
postcar-y += ext_stage_cache.c
else
ramstage-$(CONFIG_RELOCATABLE_RAMSTAGE) += cbmem_stage_cache.c
romstage-$(CONFIG_RELOCATABLE_RAMSTAGE) += cbmem_stage_cache.c
endif


romstage-y += boot_device.c
ramstage-y += boot_device.c

smm-y += boot_device.c
smm-y += fmap.c
smm-y += cbfs.c memcmp.c

bootblock-y += version.c
romstage-y += version.c
ramstage-y += version.c
smm-y += version.c
verstage-y += version.c
postcar-y += version.c

$(call src-to-obj,bootblock,$(dir)/version.c) : $(obj)/build.h
$(call src-to-obj,romstage,$(dir)/version.c) : $(obj)/build.h
$(call src-to-obj,ramstage,$(dir)/version.c) : $(obj)/build.h
$(call src-to-obj,smm,$(dir)/version.c) : $(obj)/build.h
$(call src-to-obj,verstage,$(dir)/version.c) : $(obj)/build.h
$(call src-to-obj,postcar,$(dir)/version.c) : $(obj)/build.h

$(call src-to-obj,bootblock,$(dir)/cbfs.c) : $(obj)/fmap_config.h
$(call src-to-obj,romstage,$(dir)/cbfs.c) : $(obj)/fmap_config.h
$(call src-to-obj,ramstage,$(dir)/cbfs.c) : $(obj)/fmap_config.h
$(call src-to-obj,smm,$(dir)/cbfs.c) : $(obj)/fmap_config.h
$(call src-to-obj,verstage,$(dir)/cbfs.c) : $(obj)/fmap_config.h
$(call src-to-obj,postcar,$(dir)/cbfs.c) : $(obj)/fmap_config.h

$(call src-to-obj,bootblock,$(dir)/fmap.c) : $(obj)/fmap_config.h
$(call src-to-obj,romstage,$(dir)/fmap.c) : $(obj)/fmap_config.h
$(call src-to-obj,ramstage,$(dir)/fmap.c) : $(obj)/fmap_config.h
$(call src-to-obj,smm,$(dir)/fmap.c) : $(obj)/fmap_config.h
$(call src-to-obj,verstage,$(dir)/fmap.c) : $(obj)/fmap_config.h
$(call src-to-obj,postcar,$(dir)/fmap.c) : $(obj)/fmap_config.h

bootblock-y += bootmode.c
romstage-y += bootmode.c
ramstage-y += bootmode.c
verstage-y += bootmode.c

bootblock-y += halt.c
romstage-y += halt.c
ramstage-y += halt.c
smm-y += halt.c

postcar-y += bootmode.c
postcar-y += boot_device.c
postcar-y += cbfs.c
postcar-y += delay.c
postcar-y += fmap.c
postcar-y += gcc.c
postcar-y += halt.c
postcar-y += libgcc.c
postcar-$(CONFIG_COMPRESS_RAMSTAGE) += lzma.c lzmadecode.c
postcar-y += memchr.c
postcar-y += memcmp.c
postcar-y += prog_loaders.c
postcar-y += prog_ops.c
postcar-y += rmodule.c
postcar-$(CONFIG_COLLECT_TIMESTAMPS) += timestamp.c

# Use program.ld for all the platforms which use C fo the bootblock.
bootblock-$(CONFIG_C_ENVIRONMENT_BOOTBLOCK) += program.ld

postcar-y += program.ld
romstage-y += program.ld
ramstage-y += program.ld
verstage-y += program.ld

ifeq ($(CONFIG_RELOCATABLE_MODULES),y)
ramstage-y += rmodule.c
romstage-$(CONFIG_RELOCATABLE_RAMSTAGE) += rmodule.c

RMODULE_LDFLAGS  := -z defs -Bsymbolic

# rmodule_link_rules is a function that should be called with:
# (1) the object name to link
# (2) the dependencies
# (3) heap size of the relocatable module
# (4) arch for which the rmodules are to be linked
# It will create the necessary Make rules to create a rmodule. The resulting
# rmdoule is named $(1).rmod
define rmodule_link
$(strip $(1)): $(strip $(2)) $$(COMPILER_RT_rmodules_$(4)) $(call src-to-obj,rmodules_$(4),src/lib/rmodule.ld) | $$(RMODTOOL)
	$$(LD_rmodules_$(4)) $$(LDFLAGS_rmodules_$(4)) $(RMODULE_LDFLAGS) -T $(call src-to-obj,rmodules_$(4),src/lib/rmodule.ld) --defsym=__heap_size=$(strip $(3)) -o $$@ --whole-archive --start-group $(filter-out %.ld,$(2)) --end-group
	$$(NM_rmodules_$(4)) -n $$@ > $$(basename $$@).map
endef

endif

$(objcbfs)/%.debug.rmod: $(objcbfs)/%.debug | $(RMODTOOL)
	$(RMODTOOL) -i $< -o $@

$(obj)/%.elf.rmod: $(obj)/%.elf | $(RMODTOOL)
	$(RMODTOOL) -i $< -o $@

ifeq ($(CONFIG_RAMSTAGE_LIBHWBASE),y)

$(call add-special-class,hw)
hw-handler = $(eval ramstage-srcs += $$(addprefix $(1),$(2)))
subdirs-y += ../../3rdparty/libhwbase

ramstage-$(CONFIG_HAVE_MONOTONIC_TIMER) += hw-time-timer.adb

endif # CONFIG_RAMSTAGE_LIBHWBASE

ifeq ($(CONFIG_GENERIC_SPD_BIN),y)
romstage-$(CONFIG_GENERIC_SPD_BIN) += spd_bin.c

LIB_SPD_BIN = $(obj)/spd.bin

LIB_SPD_DEPS = $(foreach f, $(SPD_SOURCES), src/mainboard/$(MAINBOARDDIR)/spd/$(f).spd.hex)

# Include spd ROM data
$(LIB_SPD_BIN): $(LIB_SPD_DEPS)
	for f in $(LIB_SPD_DEPS); \
	 do for c in $$(cat $$f | grep -v ^#); \
	  do printf $$(printf '\%o' 0x$$c); \
	 done; \
	done > $@

cbfs-files-$(CONFIG_GENERIC_SPD_BIN) += spd.bin
spd.bin-file := $(LIB_SPD_BIN)
spd.bin-type := spd
endif
