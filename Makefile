NVCC = nvcc
TARGET = image_processor

SRC = \
src/main.cpp \
src/image_utils.cpp \
src/image_kernels.cu

INCLUDE = -Iinclude

CFLAGS = -std=c++17

all:
	$(NVCC) $(SRC) \
	$(INCLUDE) \
	$(CFLAGS) \
	-o $(TARGET)

clean:
	rm -f $(TARGET)