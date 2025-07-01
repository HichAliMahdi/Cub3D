# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 11:21:49 by hali-mah          #+#    #+#              #
#    Updated: 2025/07/01 19:08:36 by hali-mah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# library name
NAME = libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files && bonus and object files with object bonus
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_strcmp.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# All Rule
all: $(NAME)

# BUILD
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# CLEAN 
clean:
	$(RM) $(OBJ)

# FCLEAN
fclean: clean
	$(RM) $(NAME)

# Rebuild Rule
re: fclean $(NAME)

# Bonus BUILD
bonus:	$(OBJ) $(BONUS_OBJ)
		ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

# Avoid fname as target
.PHONY: all clean fclean re
