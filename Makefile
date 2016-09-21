CXX=g++
BUILD=build
DEPEND=depend
CFLAGS=-g --std=c++11

SRCS=$(wildcard *.cc)
HEADER=$(wildcard *.h)
OBJS=$(patsubst %.cc, ./$(BUILD)/%.o, $(SRCS))
DPD=$(patsubst %.cc, ./$(DEPEND)/%.d, $(SRCS))


all:test

test:$(OBJS)
	g++ $(OBJS) $(LIBS) $(CFLAGS) -o $@

$(BUILD)/%.o:
	@if [ ! -d $(BUILD) ]; then mkdir ${BUILD};fi
	g++ $(INCLUDE) $< $(CFLAGS) -c -o $@

$(DEPEND)/%.d:%.cc
	@if [ ! -d $(DEPEND) ]; then mkdir ${DEPEND};fi; \
    rm -f $@; \
    g++ -MM $(INCLUDE) $< > $@.$$$$;\
    sed 's,\($*\)\.o[ :]*,$(BUILD)/\1.o $@:,g' < $@.$$$$ >$@; \
    rm -f $@.$$$$;

-include $(DPD)

clean:
	rm test $(BUILD)/*.o $(DEPEND)/*.d

rebuild:clean all
