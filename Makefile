OBJS = DynPipe.o 
dynpipe: $(OBJS)
	g++ -o dynpipe $(OBJS)
DynPipe.o: 
	g++ -c DynPipe.cpp
clean:
	rm -f core dynpipe $(OBJS)

