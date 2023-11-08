include config.mk


.DEFAULT_GOAL:= all

all: snakeEffect.hex
	$(shell mkdir ../Build)
	$(shell avr-size snakeEffect.hex > BinaryReport.txt)
	$(shell mv	BinaryReport.txt ../Build/)
	$(shell mv snakeEffect.hex ../Build/)
	$(shell mv snakeEffect.elf ../Build/)
	@echo "files Generated successfully in Build Directory"

.PHONY: snakeEffect.hex
snakeEffect.hex : snakeEffect.elf
	@$(OBJCPY) -O ihex $< $@
	@echo ".hex file created.."

.PHONY: snakeEffect.elf
snakeEffect.elf: main.o ../lib/DIO_program.c ../lib/PORT_program.c
	@$(MAKE) -C ../lib/
	@$(CC) -mmcu=$(MCU) $(CFLAGS) $^ -o $@
	@echo ".elf file created.."

#../lib/libDIO.a: ../lib/Makefile
#	$(shell cd ../lib/ && make all)
#	$(make) -c ../lib/
#	@echo "Static library generated successfully.."

%.o: %.c
	@$(CC) $(CFLAGS) -c -mmcu=$(MCU) $< -o $@
	@echo "object file generated successfully.."

.PHONY: clean_obj
clean_obj:
	@rm -f *.o
	@echo "All object files removed.."

.PHONY: clean_all
clean_all:
	@rm -f *.o *.elf *.hex
	@echo "All generated files and libraries removed.."
