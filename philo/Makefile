# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/11 06:09:32 by aechafii          #+#    #+#              #
#    Updated: 2022/10/07 16:04:07 by aechafii         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =  	parser.c		\
		philo.c 		\
		philos_func0.c	\
		philos_func1.c	
		
HEADER = include/*.h

OBJ = $(addprefix obj/, $(SRC:.c=.o))

CC = cc

CFLAGS = -Wall -Werror -Wextra -I include 

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
	@ $(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "\n\033[90;1;4mPHILO\033[0m \033[1;32mCOMPLETE!\033[0m\n"
		
obj/%.o : src/%.c $(HEADER)
	@mkdir -p obj
	@ printf "\033[1;36mCreating  ⥱\033[0m   📁 \033[1;92m"
	@ echo "$(notdir $@)" 
	@$(CC) $(CFLAGS) -c $< -o $@
	@ printf "\033[0m"

clean:
		@rm -rf $(OBJ)
		@echo "\n\033[1;34mOBJECT FILES\033[0m \033[1;32mCLEANED!\033[0m\n"

fclean: clean
		@rm -rf $(NAME) 
		@echo "\033[90;1;4mPHILO\033[0m \033[34;1mEXECUTABLE\033[0m \033[1;31mREMOVED! \n \033[0m"


re: fclean all
