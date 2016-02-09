# The top level Makefile

all:	
	cd Client 	&& $(MAKE)
	cd Server	&& $(MAKE)
	@echo 
	@echo "*********************************************"
	@echo "All files Built"
	@echo "Please move to demo/exe directory"
	@echo "Execute each file to see examples in action"
	@echo "*********************************************"
	@echo
clean:
	cd Client 	&& $(MAKE) clean
	cd Server	&& $(MAKE) clean
