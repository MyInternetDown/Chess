CXX = g++-11
CXXFLAGS = -std=c++20 -Wall -g -MMD
SOURCES = $(filter-out window.cc graphicsdisplay.cc, $(wildcard *.cc))
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chessGame

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean tests
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)
