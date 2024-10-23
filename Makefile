# Nazwa pliku wykonywalnego
TARGET = run

# Kompilator
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Nazwa pliku źródłowego
SRCS = main.cpp

# Domyślny cel: kompilacja
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Usuwanie pliku wykonywalnego
clean:
	rm -f $(TARGET)

# Usuwanie pliku wykonywalnego i wszystkich plików tymczasowych
cleanall: clean
	rm -f *.o
