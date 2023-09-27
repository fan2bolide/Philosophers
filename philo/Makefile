# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/03/01 18:39:18 by alevra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Werror -Wextra -I head -pthread #-fsanitize=thread -g3

DEBUG_FLAGS = -g3

SRC =	main.c\
		ft_atoi.c\
		philo_eating.c\
		philo_sleeping.c\
		time.c\
		philo_print.c\
		philo_monitoring.c\
		ft_usleep.c\
		philo.c\
		init_threads.c

DEPENDS	:=	$(addprefix obj/,$(SRC:.c=.d)) $(addprefix obj/,${BONUS_SRC:.c=.d})

OBJ = $(addprefix obj/,$(SRC:.c=.o))

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all : create_obj_folder
	$(MAKE) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME)

bonus : create_obj_folder .bonus

.bonus : $(OBJ) $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(FLAGS) -o $(NAME)

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile
	cc $(FLAGS) -c $< -MD -o $@

debug :
	$(CC) $(OBJ) $(FLAGS) $(DEBUG_FLAGS) -o debug$(NAME)

run : all
	./philo 5 650 200 200 8

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM

fclean : clean
	@$(RM) $(NAME)
	@$(RM) .main .bonus

re : fclean
	@$(MAKE) all

.PHONY : all lib run re clean fclean bonus create_obj_folder

-include $(DEPENDS)
