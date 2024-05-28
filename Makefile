# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by ysabik            #+#    #+#              #
#    Updated: 2024/05/28 14:51:49 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CCXX				= c++
CXXFLAGS			= -Werror -Wall -Wextra -std=c++98 -g
NAME				= ircserv
NAME_BONUS			= ircbot
INCLUDES			= inc -I inc/server -I inc/server/bases -I inc/server/commands
INCLUDES_BONUS		= inc -I inc/bot -I inc/bot/bases -I inc/bot/commands
SRC_FILES			= \
						src/server/bases/Client.cpp \
						src/server/bases/Server.cpp \
						src/server/bases/Channel.cpp \
						src/server/bases/Command.cpp \
						src/server/bases/CommandManager.cpp \
						src/server/commands/InviteCommand.cpp \
						src/server/commands/JoinCommand.cpp \
						src/server/commands/KickCommand.cpp \
						src/server/commands/ListCommand.cpp \
						src/server/commands/ModeCommand.cpp \
						src/server/commands/NamesCommand.cpp \
						src/server/commands/NickCommand.cpp \
						src/server/commands/PartCommand.cpp \
						src/server/commands/PassCommand.cpp \
						src/server/commands/PingCommand.cpp \
						src/server/commands/PongCommand.cpp \
						src/server/commands/PrivCommand.cpp \
						src/server/commands/QuitCommand.cpp \
						src/server/commands/TopicCommand.cpp \
						src/server/commands/UserCommand.cpp \
						src/server/main.cpp \
						src/server/parsing.cpp \
						src/utils.cpp
SRC_FILES_BONUS		= \
						src/bot/bases/Bot.cpp \
						src/bot/bases/CommandResponse.cpp \
						src/bot/bases/curlRequest.cpp \
						src/bot/bases/Executor.cpp \
						src/bot/bases/ExecutorManager.cpp \
						src/bot/bases/NumericResponse.cpp \
						src/bot/bases/Response.cpp \
						src/bot/commands/FactExecutor.cpp \
						src/bot/commands/HelpExecutor.cpp \
						src/bot/commands/JoinExecutor.cpp \
						src/bot/commands/JokeExecutor.cpp \
						src/bot/commands/PartExecutor.cpp \
						src/bot/commands/PingBotCommand.cpp \
						src/bot/commands/PingExecutor.cpp \
						src/bot/commands/PongBotCommand.cpp \
						src/bot/commands/PongExecutor.cpp \
						src/bot/commands/PrivBotCommand.cpp \
						src/bot/commands/QuitExecutor.cpp \
						src/bot/commands/QuoteExecutor.cpp \
						src/bot/commands/SayExecutor.cpp \
						src/bot/main.cpp \
						src/bot/parsing.cpp \
						src/utils.cpp

BUILD_FOLDER		= build

C_RESET				= \033[0m
C_BOLD				= \033[1m
C_DIM				= \033[2m
C_UNDERLINE			= \033[4m
C_BLINK				= \033[5m
C_BLACK				= \033[30m
C_RED				= \033[31m
C_GREEN				= \033[32m
C_YELLOW			= \033[33m
C_BLUE				= \033[34m
C_MAGENTA			= \033[35m
C_CYAN				= \033[36m
C_WHITE				= \033[37m

OBJ_FILES			= $(SRC_FILES:.cpp=.o)
OBJ_FILES_BONUS		= $(SRC_FILES_BONUS:.cpp=.o)
BUILD_FILES			= $(addprefix $(BUILD_FOLDER)/, $(OBJ_FILES))
BUILD_FILES_BONUS	= $(addprefix $(BUILD_FOLDER)/, $(OBJ_FILES_BONUS))

TO_COMPILE			= 0

all : $(NAME)

$(NAME) : $(BUILD_FILES)
	@echo ""
	@echo -n "  > $(C_YELLOW)$(C_BOLD)./$(NAME)$(C_RESET):  $(C_DIM)"
	$(CCXX) $(CXXFLAGS) -o $(NAME) $(BUILD_FILES) -I $(INCLUDES)
	@echo "$(C_RESET)"
	@echo ""
	@echo -n "$(C_BOLD)$(C_MAGENTA)>$(C_BLUE)>$(C_CYAN)>$(C_GREEN)"
	@echo -n " Compilation success ! "
	@echo "$(C_CYAN)<$(C_BLUE)<$(C_MAGENTA)<$(C_RESET)"
	@echo ""

m_line_break :
	@echo ""

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(BUILD_FILES_BONUS)
	@echo ""
	@echo -n "  > $(C_YELLOW)$(C_BOLD)./$(NAME_BONUS)$(C_RESET):  $(C_DIM)"
	$(CCXX) $(CXXFLAGS) -o $(NAME_BONUS) $(BUILD_FILES_BONUS) -I $(INCLUDES_BONUS)
	@echo "$(C_RESET)"
	@echo ""
	@echo -n "$(C_BOLD)$(C_MAGENTA)>$(C_BLUE)>$(C_CYAN)>$(C_GREEN)"
	@echo -n " Compilation success ! "
	@echo "$(C_CYAN)<$(C_BLUE)<$(C_MAGENTA)<$(C_RESET)"
	@echo ""

$(BUILD_FOLDER)/%.o : %.cpp
	@if [ $(TO_COMPILE) -eq 0 ] ; then \
		echo -n "$(C_CYAN)$(C_BOLD)$(C_UNDERLINE)" ; \
		echo "Compiling $(C_YELLOW)./$(if $(findstring bonus, $(MAKECMDGOALS)),$(NAME_BONUS),$(NAME))$(C_CYAN)... :$(C_RESET)" ; \
		echo "" ; \
	fi
	@$(eval TO_COMPILE := 1)
	@echo -n "  - $(C_GREEN)$<$(C_RESET):  $(C_DIM)"
	@mkdir -p $(@D)
	$(CCXX) $(CXXFLAGS) -c $< -o $@ -I $(if $(findstring bonus, $(MAKECMDGOALS)),$(INCLUDES_BONUS),$(INCLUDES))
	@echo -n "$(C_RESET)"

define del =
	@echo -n "$(C_RED)$(C_BOLD)$(C_UNDERLINE)"
	@echo "Deleting files... :$(C_RESET)$(C_RED)"
	@\
	l=-1 ; \
	for file in $(1) ; do \
		if [ $${#file} -gt $$l ] ; then \
			l=$${#file} ; \
		fi ; \
	done ; \
	cols=$$((64 / $$l)) ; \
	i=0 ; \
	for file in $(1) ; do \
		if [ $$i -eq 0 ] ; then \
			echo -n "    " ; \
		fi ; \
		if [ "$$file" = "./$(NAME)" ] ; then \
			printf "$(C_YELLOW)%-$$((l))s  $(C_RED)" "$$file" ; \
		elif [ "$$file" = "./$(NAME_BONUS)" ] ; then \
			printf "$(C_YELLOW)%-$$((l))s  $(C_RED)" "$$file" ; \
		else \
			printf "%-$$((l))s  " "$$file" ; \
		fi ; \
		if [ $$i -gt $$cols ] ; then \
			echo "" ; \
			i=-1; \
		fi ; \
		i=$$(($$i + 1)); \
	done ; \
	if [ $$i -ne -1 ] ; then \
		echo "" ; \
	fi
	@echo "$(C_RESET)"
endef

clean :
	$(call del, "$(BUILD_FOLDER)" $(BUILD_FILES) $(BUILD_FILES_BONUS))
	@rm -rf $(BUILD_FILES) $(BUILD_FOLDER) $(BUILD_FILES_BONUS)

fclean :
	$(call del, "./$(NAME)" "./$(NAME_BONUS)" "$(BUILD_FOLDER)" $(BUILD_FILES) $(BUILD_FILES_BONUS))
	@rm -rf $(NAME) $(NAME_BONUS) $(BUILD_FILES) $(BUILD_FILES_BONUS) $(BUILD_FOLDER)

re : fclean m_line_break all

re_bonus : clean m_line_break bonus

.PHONY : all bonus clean fclean re re_bonus
