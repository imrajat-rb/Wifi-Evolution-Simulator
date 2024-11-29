# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall
OPTFLAGS = -O3
DEBUGFLAGS = -g -O0
SHARED_FLAGS = -fPIC

# Directories
OBJDIR = obj
BINDIR = bin

# Target names
TARGET_DEBUG = $(BINDIR)/ques2_debug
TARGET_OPTIMIZED = $(BINDIR)/ques2_optimized

# Source and object files
SRCS = AccessPointModule.h ChannelModule.h main.cpp UserModule.h
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Default target: build everything
all: $(TARGET_DEBUG) $(TARGET_OPTIMIZED)

# Compile optimized version
$(TARGET_OPTIMIZED): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -o $@ $^

# Compile debug version
$(TARGET_DEBUG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $@ $^

# Compile object files for regular builds
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
