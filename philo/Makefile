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

FLAGS = -I libft/head -I head -I . -lreadline

DEBUG_FLAGS = -g3 -fsanitize=address

SRC =	philo.c\
		ft_atoi.c\
		check_args.c\
		philo_eating.c\
		philo_thiking.c

BONUS_SRC =

DEPENDS	:=	$(addprefix obj/,$(SRC:.c=.d)) $(addprefix obj/,${BONUS_SRC:.c=.d})

OBJ = $(addprefix obj/,$(SRC:.c=.o))

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all : create_obj_folder
	$(MAKE) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(DEBUG_FLAGS) -o $(NAME)

bonus : create_obj_folder .bonus

.bonus : $(OBJ) $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(FLAGS) -o $(NAME)

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile
	cc $(DEBUG_FLAGS) -Werror -Wall -Wextra -c $< -MD -I head -o $@

debug :
	$(CC) $(OBJ) $(FLAGS) $(DEBUG_FLAGS) -o debug$(NAME)

run : all
	./a.out

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM

fclean : clean
	@$(RM) $(NAME)
	@$(RM) .main .bonus

re : fclean
	@$(MAKE) all

.PHONY : all lib run re clean fclean bonus create_obj_folder leaks

leaks:	all
	echo "{" > valgrind_ignore_leaks.txt
	echo "    leak readline" >> valgrind_ignore_leaks.txt
	echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "    ..." >> valgrind_ignore_leaks.txt
	echo "    fun:readline" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	echo "{" >> valgrind_ignore_leaks.txt
	echo "    leak add_history" >> valgrind_ignore_leaks.txt
	echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "    ..." >> valgrind_ignore_leaks.txt
	echo "    fun:add_history" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full\
	    --show-leak-kinds=all --track-origins=yes --verbose\
	    --show-mismatched-frees=yes --read-var-info=yes ./${NAME}

-include $(DEPENDS)
