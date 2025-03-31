# ─── Build Settings ──────────────────────────────
ARTIFACTS = AircraftProcess RadarSystem ComputerSystem OperatorConsole DataDisplay

PLATFORM ?= aarch64le
BUILD_PROFILE ?= debug
CONFIG_NAME ?= $(PLATFORM)-$(BUILD_PROFILE)
OUTPUT_DIR = build/$(CONFIG_NAME)

CC = qcc -Vgcc_nto$(PLATFORM)
CXX = q++ -Vgcc_nto$(PLATFORM)_cxx
LD = $(CC)

CCFLAGS_release += -O2
CCFLAGS_debug += -g -O0 -fno-builtin
CCFLAGS_all += -Wall -fmessage-length=0
CCFLAGS_all += $(CCFLAGS_$(BUILD_PROFILE))

LDFLAGS_all +=
LIBS_all += -lm

INCLUDES += -Isrc
SHARED_SRC = src/SharedMemory.cpp

# ─── Build Rules ─────────────────────────────────

all: $(ARTIFACTS)

$(ARTIFACTS):
	@mkdir -p $(OUTPUT_DIR)
	$(CXX) $(CCFLAGS_all) $(INCLUDES) src/$@.cpp $(SHARED_SRC) -o $(OUTPUT_DIR)/$@ $(LDFLAGS_all) $(LIBS_all)

clean:
	rm -rf build/

rebuild: clean all

.PHONY: all clean rebuild $(ARTIFACTS)
