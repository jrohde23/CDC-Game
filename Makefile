BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: vibepong.z64

$(BUILD_DIR)/vibepong.elf: $(BUILD_DIR)/main.o

vibepong.z64: N64_ROM_TITLE="VIBE PONG"
vibepong.z64: $(BUILD_DIR)/vibepong.elf

clean:
	rm -rf $(BUILD_DIR) *.z64

.PHONY: clean