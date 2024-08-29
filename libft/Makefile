SRC			= ft_atoi.c \
			 ft_atoll.c \
			 ft_atof.c \
			 ft_bzero.c \
			 ft_calloc.c \
			 ft_isalnum.c \
			 ft_isalpha.c \
			 ft_isspace.c \
			 ft_isascii.c \
			 ft_isdigit.c \
			 ft_isprint.c \
			 ft_memchr.c \
			 ft_memcmp.c \
			 ft_memcpy.c \
			 ft_memmove.c \
			 ft_memset.c \
			 ft_strchr.c \
			 ft_strdup.c \
			 ft_strlcat.c \
			 ft_strlcpy.c \
			 ft_strlen.c \
			 ft_strncmp.c \
			 ft_strnstr.c \
			 ft_strrchr.c \
			 ft_tolower.c \
			 ft_toupper.c \
			 ft_substr.c \
			 ft_strjoin.c \
			 ft_strtrim.c \
			 ft_split.c \
			 ft_itoa.c \
			 ft_strmapi.c \
			 ft_striteri.c \
			 ft_putchar_fd.c \
			 ft_putstr_fd.c \
			 ft_putendl_fd.c \
			 ft_putnbr_fd.c \
			 ft_abs.c

SRC_BONUS	= ft_lstnew_bonus.c \
			 ft_lstadd_front_bonus.c \
			 ft_lstsize_bonus.c \
			 ft_lstlast_bonus.c \
			 ft_lstadd_back_bonus.c \
			 ft_lstdelone_bonus.c \
			 ft_lstclear_bonus.c \
			 ft_lstiter_bonus.c \
			 ft_lstmap_bonus.c

SRC_GNL		= ${addprefix get_next_line/, get_next_line_bonus.c get_next_line_utils_bonus.c}

OBJS		= ${SRC:.c=.o}  
OBJS_BONUS	= ${SRC_BONUS:.c=.o}
OBJS_GNL	= ${SRC_GNL:.c=.o}
NAME		= libft.a       
AR			= ar rcs         
RM 			= rm -f         
CC 			= cc        

CFLAGS 		= -Wall -Wextra -Werror

.c.o: 
			${CC} ${CFLAGS} -c -o $@ $<

${NAME}: 	${OBJS} ${OBJS_GNL}
					${AR} ${NAME} ${OBJS} ${OBJS_GNL}

all:		${NAME}

.bonus : 	${OBJS} ${OBJS_GNL} ${OBJS_BONUS}
					@touch .bonus;
					${AR} ${NAME} ${OBJS} ${OBJS_GNL} ${OBJS_BONUS}

bonus : 	.bonus

clean: 
			${RM} ${OBJS} ${OBJS_GNL} ${OBJS_BONUS} 
			@${RM} .bonus

fclean: 	clean
			${RM} ${NAME}
		
re:			fclean all
.PHONY:		all clean fclean re bonus
