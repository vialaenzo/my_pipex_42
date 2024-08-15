# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eviala <eviala@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 11:41:47 by eviala            #+#    #+#              #
#    Updated: 2024/08/15 09:57:24 by eviala           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du programme
NAME = pipex
NAME_BONUS = pipex_bonus

# Dossier de sortie pour les fichiers objets
OBJ_DIR = obj/
SRCS_DIR = srcs/
SRCS_DIR_BONUS = srcs_bonus/
# Dossiers des dépendances
LIBFT_DIR = libft

# Les différentes bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a

# Headers et includes
HEADER = -I./includes \
	-I./libft/includes \

# Options de compilation
CFLAGS = -Wall -Wextra -Werror

# Commandes
CC = cc
RM = rm -rf

# Rechercher tous les fichiers .c dans le répertoire courant
SRCS = pipex.c \
	childs.c \
	ft_utils.c \
	ft_parsing.c

SRCS_BONUS = pipex_bonus.c \
	childs_bonus.c \
	ft_utils_bonus.c \
	ft_parsing_bonus.c \
	ft_free_all.c \
	here_doc.c

MAKEFLAGS += --no-print-directory
TOTAL_FILES := $(words $(SRCS))
CURRENT_INDEX := 0
TOTAL_FILES_BONUS := $(words $(SRCS_BONUS))
CURRENT_INDEX_BONUS := 0

# Conversion des fichiers source en fichiers objets
OBJS = $(addprefix ${OBJ_DIR}, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix ${OBJ_DIR}, $(SRCS_BONUS:.c=.o))

# Cibles
all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "\n"

# Compilation de la bibliothèque
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(HEADER) $(LIBFT)
	@echo "\n┗▷${BOLD}$(GREEN)『./$(NAME) Successfully created [✅]$(RESET)"

${OBJ_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES)))))
	@printf "\r🔧 $(BLUE)$(BOLD)%3d%% $(WHITE)$(BOLD)Compiling:$(WHITE)$(BOLD) ${NAME}${RESET} $(RED)$(BOLD)%-50s $(MAGENTA)[%3d/%3d]$(RESET)" $(PERCENT) "$<" $(CURRENT_INDEX) $(TOTAL_FILES)
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

bonus : $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(HEADER) $(LIBFT)
	@echo "\n┗▷${BOLD}$(GREEN)『./$(NAME_BONUS) Successfully created [✅]$(RESET)"

${OBJ_DIR}%.o: ${SRCS_DIR_BONUS}%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_INDEX_BONUS=$(shell echo $$(($(CURRENT_INDEX_BONUS)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX_BONUS) * 100 / $(TOTAL_FILES_BONUS)))))
	@printf "\r🔧 $(BLUE)$(BOLD)%3d%% $(WHITE)$(BOLD)Compiling:$(WHITE)$(BOLD) ${NAME}${RESET} $(RED)$(BOLD)%-50s $(MAGENTA)[%3d/%3d]$(RESET)" $(PERCENT) "$<" $(CURRENT_INDEX_BONUS) $(TOTAL_FILES_BONUS)
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@


# Nettoyage des fichiers objets
clean:
	@echo "$(BOLD) [ 🗑️ ] $(YELLOW)$(REVERSED)Cleaning up$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null 2>&1
	@$(RM) -r $(OBJ_DIR) > /dev/null 2>&1
	@$(RM) -r $(OBJ_DIR_BONUS) > /dev/null 2>&1
	@echo "┗▷$(YELLOW)『$(ITALIC)./$(SRCS_DIR)'s$(RESET)$(YELLOW) object files cleaned』$(RESET)"

# Nettoyage complet
fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@$(RM) $(NAME) > /dev/null 2>&1
	@$(RM) $(NAME_BONUS) > /dev/null 2>&1
	@echo "┗▷$(YELLOW)『$(ITALIC)./$(NAME)'s$(RESET)$(YELLOW) cleaned』$(RESET)"

# Recompiler entièrement
re: fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus

# ... (le reste du Makefile reste inchangé)
.SILENT:
# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[0;37m
RESET := \033[0m
BOLD := \033[1m
UNDERLINE := \033[4m
REVERSED := \033[7m
ITALIC := \033[3m
