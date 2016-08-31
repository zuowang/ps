# Figure out app path
#g++ -g -o0 -std=c++11 test_api.cpp -o output -I/root/mxnet/ps/src -I/root/mxnet/third_party/include -L/root/mxnet/ps/lib -L/root/mxnet/third_party/lib -fsanitize=address -fno-omit-frame-pointer -lpthread -lpetuum-ml -lpetuum-ps -lyaml-cpp -lgflags -lzmq -lleveldb -lboost_thread -lboost_system
#
# export LD_LIBRARY_PATH=/root/mxnet/ps/lib:/root/mxnet/third_party/lib
#
TEST_DIR := $(shell readlink $(dir $(lastword $(MAKEFILE_LIST))) -f)
PETUUM_ROOT = $(TEST_DIR)/../../

CXXFLAGS += -g -o0 -std=c++11
INCFLAGS += -I/root/mxnet/ps/src -I/root/mxnet/third_party/include
LDFLAGS += -L/root/mxnet/ps/lib -L/root/mxnet/third_party/lib -fsanitize=address -fno-omit-frame-pointer -lpthread -lpetuum-ml -lpetuum-ps -lyaml-cpp -lgflags -lzmq -lleveldb -lboost_thread -lboost_system

TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)
TEST_HDR = $(wildcard $(TEST_DIR)/*.hpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: test_api 

test_api: $(TEST_DIR)/test_api


$(TEST_DIR)/test_api: $(TEST_OBJ) 
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(TEST_OBJ) $(LDFLAGS) -o $@

$(TEST_OBJ): %.o: %.cpp $(TEST_HDR)
	$(CXX) $(NDEBUG) $(CXXFLAGS) -Wno-unused-result $(INCFLAGS) -c $< -o $@


clean:
	-rm -rf $(TEST_OBJ)
	-rm -rf $(TEST_DIR)/test_api

.PHONY: clean test_api
