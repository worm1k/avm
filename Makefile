#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochayche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/05 19:07:36 by ochayche          #+#    #+#              #
#    Updated: 2017/06/30 19:42:48 by vdoroshy         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC       = g++
CFLAGS   = -Wall -Wextra  -std=c++11
BIN_NAME = avm

#********* -OBJ
OBJ_DIR  = .obj
OBJ      = $(subst .cpp,.o,$(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRC)))

#********* -SRC
SRC_DIR  = src
SRC      = $(addprefix $(SRC_DIR)/, $(SRC_NAME))

SRC_NAME =              main.cpp \
                        Lexer.cpp \
                        LerserException.cpp \
                        Machine.cpp \
                        MachineException.cpp \
                        OperandFactory.cpp \
                        Parser.cpp \
# add .cpp file ---->

################################################################################
#	RULES
################################################################################

.PHONY: all clean fclean re

all: $(BIN_NAME)

$(BIN_NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(BIN_NAME)
		@echo "\033[33m'$(BIN_NAME)' compiling done.\033[0m"

$(OBJ_DIR)/Machine.o: $(SRC_DIR)/Operand.hpp $(SRC_DIR)/Operand.tpp $(SRC_DIR)/Machine.cpp
		$(CC) -c $(CFLAGS) src/Machine.cpp -o $@

$(OBJ_DIR)/OperandFactory.o: $(SRC_DIR)/Operand.hpp $(SRC_DIR)/Operand.tpp $(SRC_DIR)/OperandFactory.cpp
		$(CC) -c $(CFLAGS) src/OperandFactory.cpp -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
		$(CC) -c $(CFLAGS) $? -o $@

$(OBJ_DIR):
		mkdir $(OBJ_DIR)

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(BIN_NAME)

re: fclean all