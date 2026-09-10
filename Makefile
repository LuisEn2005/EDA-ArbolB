CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = main.cpp ArbolB.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
