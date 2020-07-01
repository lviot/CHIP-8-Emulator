include sources.mk

T_NAME	=	unit_tests

TESTS	=	$(SRCS)					\
			./tests/test_opcode.c

T_OBJS	= 	$(TESTS:.c=.o)

LDFLAGS	+=	-lcriterion