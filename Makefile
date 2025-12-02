CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pthread -I.
LDFLAGS = -pthread

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

SERVER_TARGET = server
CLIENT_TARGET = client

SERVER_OBJS = $(OBJ_DIR)/Server.o $(OBJ_DIR)/MessageHandler.o $(OBJ_DIR)/server_main.o
CLIENT_OBJS = $(OBJ_DIR)/Client.o $(OBJ_DIR)/MessageHandler.o $(OBJ_DIR)/client_main.o

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Server built successfully!"

$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Client built successfully!"

$(OBJ_DIR)/Server.o: $(SRC_DIR)/Server.cpp $(INCLUDE_DIR)/Server.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Client.o: $(SRC_DIR)/Client.cpp $(INCLUDE_DIR)/Client.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/MessageHandler.o: $(SRC_DIR)/MessageHandler.cpp $(INCLUDE_DIR)/MessageHandler.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/server_main.o: server_main.cpp $(INCLUDE_DIR)/Server.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/client_main.o: client_main.cpp $(INCLUDE_DIR)/Client.h $(INCLUDE_DIR)/MessageHandler.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(SERVER_TARGET) $(CLIENT_TARGET)
	@echo "Clean completed!"

rebuild: clean all

.PHONY: all clean rebuild
