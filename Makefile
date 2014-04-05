SRC= mainAlex.cpp
OBJ= ${SRC:.cpp=.o}
d_OBJ= ${SRC:.cpp=_d.o}
p_OBJ= ${SRC:.cpp=_p.o}
CXX	 = g++
LFLAGS   = -lm
#IMPLFLAGS= -DCLAUSE=$(CLAUSE) -DCHOOSE=$(CHOOSE) -DVERBOSE=$(VERBOSE) -DINIT_SORT=$(INIT_SORT) -DINTERACT=$(INTERACT)
CXXFLAGS = $(IMPLFLAGS) -Wall -Wextra -s -O2 -std=c++11
CXXDEBUGFLAGS = $(IMPLFLAGS) -Wall -Wextra -O0 -g -std=c++11
CXXPROFILEFLAGS = $(IMPLFLAGS) -DVERBOSE=0 -Wall -Wextra -g -O2 -fno-inline -std=c++11

all : release
      
release: $(OBJ) $(HDR) 
	${CXX} $(CXXFLAGS) -o $@ $(OBJ) $(LFLAGS)  $(LIB);

debug: $(d_OBJ) $(HDR) 
	${CXX} $(CXXDEBUGFLAGS) -o $@ $(d_OBJ) $(LFLAGS)  $(LIB);

clean: 
	rm -f $(OBJ) $(d_OBJ) $(p_OBJ)

destroy: clean
	rm -f release debug profile

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
     
%_p.o: %.cpp
	$(CXX) $(CXXPROFILEFLAGS) -c $< -o $@

%_d.o: %.cpp
	$(CXX) $(CXXDEBUGFLAGS) -c $< -o $@
