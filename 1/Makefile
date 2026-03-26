CXX = g++
CXXFLAGS = -g

TARGET = build/debug.out

OBJS = build/rect.o build/barrel.o build/matrix.o build/myString.o

TEST = tests
SRC = src


$(TARGET): $(OBJS) src/lab1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


build/%.o: src/%.cpp src/%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


debug: $(TARGET)
	lldb $(TARGET)
	

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f build/*.o $(TARGET)


checkmem: clean
	$(MAKE) $(TARGET) CXXFLAGS="$(CXXFLAGS) -fsanitize=address -fno-omit-frame-pointer"
	./$(TARGET)

test_basic: $(TEST)/test_rect_basic_methods.cpp src/rect.cpp
	$(CXX) $(CXXFLAGS) -o tests/test_basic $^
	./tests/test_basic
	@echo "Код возврата: $$?"

test_properties: tests/test_rect_properties.cpp src/rect.cpp
	$(CXX) $(CXXFLAGS) -o tests/test_properties $^
	./tests/test_properties
	@echo "Код возврата: $$?"

test_operations: tests/test_rect_operations.cpp src/rect.cpp
	$(CXX) $(CXXFLAGS) -o tests/test_operations $^
	./tests/test_operations
	@echo "Код возврата: $$?"

test_bounding: tests/test_bounding_rect.cpp src/rect.cpp
	$(CXX) $(CXXFLAGS) -o tests/test_bounding $^
	./tests/test_bounding
	@echo "Код возврата: $$?"

test: test_basic test_properties test_operations test_bounding
	@echo "Все тесты Rect пройдены успешно!"




.PHONY: debug run clean

