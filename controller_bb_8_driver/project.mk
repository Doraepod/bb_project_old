
PROJECT_MODULES = 	src/lld_control.c	\
					src/lld_encoder.c	\
					src/odometry.c		\
					src/wheel_control.c
				  
PROJECT_TESTS   =	tests/test_lld_control.c	\
					tests/test_lld_encoder.c	\
					tests/test_odometry.c		\
					tests/test_frequency.c
				  		
PROJECT_CSRC    = src/main.c src/common.c src/debug.c \
					$(PROJECT_MODULES) $(PROJECT_TESTS)

PROJECT_INCDIR	= include tests $(ROSINC)

PROJECT_LIBS	= -lm

PROJECT_OPTS	= -specs=nosys.specs

