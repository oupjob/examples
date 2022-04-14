ROOT_DIR = $(PWD)
BUILD_DIR = $(ROOT_DIR)/build
CXX = g++
# OBJS = ${subst $(ROOT_DIR), $(BUILD_DIR), $(shell find $(ROOT_DIR) -name "*cc" -printf "%p "  | sed 's/\.cc/.o/' )}
# SOURCES = $(shell find $(ROOD_DIR) -name "*cc" -printf "%p ")

SOURCES = $(wildcard $(ROOT_DIR)/*.cc)
OBJS = $(patsubst %.cc, %.o, $(subst $(ROOT_DIR), $(BUILD_DIR), $(SOURCES)))


all: $(OBJS)
	echo $< $?
	$(CXX) $? -o example

#$(OBJS) : $(SOURCES)
#	@echo $< $@ $^ $*
#	$(CXX) -c $< -o $@ 

$(BUILD_DIR)/%.o: %.cc
	$(CXX) -c $< -o $@

clean:
	rm $(BUILD_DIR)/*

print : $(ROOT_DIR)/*.cc
	@echo "OBJS" $(OBJS)
	@echo "SOURCES" $(SOURCES)
	@echo "@" $@
	@echo "<" $<
	@echo "^" $^
	@echo "*" $*
