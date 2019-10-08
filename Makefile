##
## Makefile for  in /home/mex/rendu/tek2/c++/cpp_indie_studio
##
## Made by Mex
## Login   <maximilien.oteifeh-pfennig@epitech.eu>
##
## Started on  Mon May  1 17:45:08 2017 Mex
## Last update Sun Jun 18 22:38:44 2017 Anthony
##

CC		= g++

INDIR		= includes/

ENTITYDIR	= Entity/

GAMEPHASEDIR	= GamePhase/

POWERUPDIR	= PowerUp/

OBJECTSDIR	= Objects/

SRCDIR		= sources/

NAME		= gantelet

SRC		= main.cpp \
		  $(SRCDIR)Core.cpp \
		  $(SRCDIR)$(GAMEPHASEDIR)Intro.cpp \
		  $(SRCDIR)$(GAMEPHASEDIR)MainMenu.cpp \
		  $(SRCDIR)$(GAMEPHASEDIR)SelectCharacter.cpp \
		  $(SRCDIR)$(GAMEPHASEDIR)InGame.cpp \
		  $(SRCDIR)Errors.cpp \
		  $(SRCDIR)FPSBenchmark.cpp \
		  $(SRCDIR)ScoreManager.cpp \
		  $(SRCDIR)EventReceiver.cpp \
		  $(SRCDIR)SoundEventReceiver.cpp \
		  $(SRCDIR)ThreadPool.cpp \
		  $(SRCDIR)Map.cpp \
		  $(SRCDIR)Room.cpp \
		  $(SRCDIR)MouseEvent.cpp \
		  $(SRCDIR)KeySelector.cpp \
		  $(SRCDIR)$(ENTITYDIR)Elf.cpp \
		  $(SRCDIR)$(ENTITYDIR)Warrior.cpp \
		  $(SRCDIR)$(ENTITYDIR)Wizard.cpp \
		  $(SRCDIR)$(ENTITYDIR)Valkyrie.cpp \
		  $(SRCDIR)$(ENTITYDIR)Monster.cpp \
		  $(SRCDIR)Player.cpp \
		  $(SRCDIR)MeshManager.cpp \

OBJS		= $(SRC:.cpp=.o)

IRKLANGDIR	= lib/irrklang/

LIB		= -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lpthread

OPT		= -L"/usr/lib" lib/irrklang/bin/linux-gcc-64/libIrrKlang.so #"/usr/lib" -L lib/irrKlang-64bit-1.5.0/libIrrKlang.so

CXXFLAGS        += -W -Wall -Wextra -Werror -std=c++11 -I $(INDIR) -I $(INDIR)$(ENTITYDIR) -I $(INDIR)$(GAMEPHASEDIR) -I $(INDIR)$(POWERUPDIR) -I $(INDIR)$(OBJECTSDIR) -I $(IRKLANGDIR)include

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LIB) $(CXXFLAGS) $(OPT)

install:
		./lib/install.sh

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
