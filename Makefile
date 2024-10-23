# Makefile do kompilacji programu generującego nieskierowany graf

# Kompilator
CXX = g++

# Flagi kompilacji
CXXFLAGS = -Wall -Wextra -std=c++11

# Nazwa docelowego pliku wykonywalnego
TARGET = random_graph

# Pliki źródłowe
SRCS = main.cpp random_graph.cpp tsp.cpp

# Pliki obiektowe
OBJS = $(SRCS:.cpp=.o)

# Reguła domyślna (kompilacja)
all: $(TARGET)

# Reguła do budowania pliku wykonywalnego
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reguła do budowania plików obiektowych
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Reguła do czyszczenia (usuwania plików obiektowych i wykonywalnych)
clean:
	rm -f $(OBJS) $(TARGET)

# Reguła do uruchamiania programu
run: $(TARGET)
	./$(TARGET)
