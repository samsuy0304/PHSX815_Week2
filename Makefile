# C++ compiler
CXX = g++ 

# necessary compiler flags for using ROOT (root.cern.ch) - remove these if you're not using root
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTGLIBS     = $(shell root-config --glibs)

# Paths to the folders with the necessary header files for compilation (these are all for matplotlib-cpp library)
CXX += -I/Users/christopherrogan/GitHub/matplotlib-cpp/
CXX += -I/usr/local/Cellar/python\@3.9/3.9.1_6/Frameworks/Python.framework/Versions/3.9/include/python3.9/
CXX += -I/usr/local/lib/python3.9/site-packages/numpy/core/include

# Path to the folder with the Python shared library (for matplotliib-cpp)
GLIBS =  -L/usr/local/Cellar/python\@3.9/3.9.1_6/Frameworks/Python.framework/Versions/3.9/lib/
# Flag to let the compiler know which shared library to use (for matplotlib-cpp)
GLIBS += -lpython3.9
# ROOT shared library flags
GLIBS += $(filter-out -stdlib=libc++ -pthread , $(ROOTGLIBS))

# some compiler flags
CXXFLAGS = -std=c++11
# ROOT flags
CXXFLAGS += -fPIC $(filter-out -stdlib=libc++ -pthread , $(ROOTCFLAGS))

# location of source code
SRCDIR = ./src/

#location of header files
INCLUDEDIR = ./include/

CXX += -I$(INCLUDEDIR)

# location of object files (from compiled library files)
OUTOBJ = ./obj/

CC_FILES := $(wildcard src/*.cc)
HH_FILES := $(wildcard include/*.hh)
OBJ_FILES := $(addprefix $(OUTOBJ),$(notdir $(CC_FILES:.cc=.o)))

# targets to make
all: CoinToss.x CoinAnalysis.x CookieTimer.x CookieAnalysis.x

# recipe for building CoinToss.x
CoinToss.x:  $(SRCDIR)CoinToss.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o CoinToss.x $(OUTOBJ)/*.o $(GLIBS) $ $<
	touch CoinToss.x

# recipe for building CoinAnalysis.x
CoinAnalysis.x:  $(SRCDIR)CoinAnalysis.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o CoinAnalysis.x $(OUTOBJ)/*.o $(GLIBS) $ $<
	touch CoinAnalysis.x

# recipe for building CookieTimer.x
CookieTimer.x:  $(SRCDIR)CookieTimer.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o CookieTimer.x $(OUTOBJ)/*.o $(GLIBS) $ $<
	touch CookieTimer.x

# recipe for building CookieAnalysis.x
CookieAnalysis.x:  $(SRCDIR)CookieAnalysis.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o CookieAnalysis.x $(OUTOBJ)/*.o $(GLIBS) $ $<
	touch CookieAnalysis.x

$(OUTOBJ)%.o: src/%.cc include/%.hh
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean-up target (make clean)
clean:
	rm -f *.x
	rm -rf *.dSYM
	rm -f $(OUTOBJ)*.o
