FLAG=-Wall -Werror -fPIC
CC=g++
LIB_DIR=/usr/lib/re3
OBJ_DIR=./obj
SRC_DIR=./src
TEST_DIR=./test

$(OBJ_DIR)/libre3.so: $(OBJ_DIR)/re3.o
		$(CC) -g -shared -o $(OBJ_DIR)/libre3.so $(OBJ_DIR)/re3.o
$(OBJ_DIR)/re3.o:$(SRC_DIR)/re3.cc 	 
		g++ -g -c $(FLAG) $(SRC_DIR)/re3.cc -o $(OBJ_DIR)/re3.o
install: $(OBJ_DIR)/libre3.so
		echo "installing..."
		mkdir -p  $(LIB_DIR) && cp $(OBJ_DIR)/libre3.so $(LIB_DIR)
		echo $(LIB_DIR) >/etc/ld.so.conf.d/re3.conf	
		ldconfig	
test2:
		echo "testing"
		g++ -g -L $(LIB_DIR) $(TEST_DIR)/main.c -o $(TEST_DIR)/main -lre3	
		./$(TEST_DIR)/main <$(TEST_DIR)/test_file
clean:
		rm -rf $(OBJ_DIR)/*
clean_test:
		rm  -rf $(TEST_DIR)/main	
