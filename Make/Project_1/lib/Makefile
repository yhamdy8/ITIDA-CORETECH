include config.mk


.DEFAULT_GOAL:= all

all: libDIO.a

.PHONY:libDIO.a
libDIO.a: PORT_program.o DIO_program.o
	@$(AR) rcs $@ $^
	@echo "Static library created with object files.. "

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "object files created.."

.PHONY:clean_obj
clean_obj:
	@rm -f *.o
	@echo "All object files removed.."

.PHONY:clean_lib
clean_lib:
	@rm -f *.a
	@echo "All Static library files removed.."

.PHONY:clean_all
clean_all:
	@rm -f *.o *.a
	@echo "All generated files and libraries removed.."