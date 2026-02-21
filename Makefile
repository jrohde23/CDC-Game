# Manually define the toolchain path for the Libdragon container
N64_INST=/n64_toolchain
BUILD_DIR=build

include $(N64_INST)/include/n64.mk

all: vibepong.z64

$(BUILD_DIR)/vibepong.elf: $(BUILD_DIR)/main.o

# This creates the final ROM file
vibepong.z64: N64_ROM_TITLE="VIBE PONG"
vibepong.z64: $(BUILD_DIR)/vibepong.elf

clean:
	rm -rf $(BUILD_DIR) *.z64

.PHONY: clean