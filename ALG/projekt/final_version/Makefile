# Kompilátor
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Zdroje
SRCS = main.cpp graph.cpp bridges.cpp builder.cpp

# Objektové súbory
OBJS = $(SRCS:.cpp=.o)

# Výsledný program
TARGET = main

# Defaultný cieľ
all: $(TARGET)

# Linkovanie
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Kompilácia .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Vyčistenie projektu
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
