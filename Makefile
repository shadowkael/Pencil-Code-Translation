# The top level Makefile

all:	
	cd Client 	&& $(MAKE)
	cd Server	&& $(MAKE)
	cd Client 	&& $(MAKE) clean
	cd Server	&& $(MAKE) clean
	@echo 
	@echo "*********************************************"
	@echo "All files Built"
	@echo "Please move to exe/ directory"
	@echo "*********************************************"
	@echo
	
