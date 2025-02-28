# Compiler
CC = clang

# Flags for Apple Silicon (M1/M2/M3)
CFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lglfw -lcglm -lglew -framework OpenGL

# Output executable
TARGET = minecraft_clone

# Source files
SRCS = src/main.c src/window.c src/camera.c src/shader.c src/texture.c src/cube.c src/stb_image.c

# Compile
all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Clean generated files
clean:
	rm -f $(TARGET)
