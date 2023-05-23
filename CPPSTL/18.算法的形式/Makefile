# 指定编译器
CXX=g++

# 指定编译选项
CXXFLAGS=-std=c++17 -Wall -g

# 指定目标文件
TARGET=a

# 指定依赖的源文件
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp test_stl.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
