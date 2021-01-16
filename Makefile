CXXFLAGS=-std=c++11

INSTALL_FILES=\
	regex-parser 
	
all : $(INSTALL_FILES)

clean :
	rm -f *.o
	rm -f $(INSTALL_FILES)

test : $(INSTALL_FILES)
	./regex-parser
	
regex-parser : main.o RegexParser.o
	$(CXX) -o $@ $^
	
