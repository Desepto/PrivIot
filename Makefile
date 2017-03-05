.PHONY: clean All

All:
	@echo "----------Building project:[ PrivIot - Debug ]----------"
	@"$(MAKE)" -f  "PrivIot.mk"
clean:
	@echo "----------Cleaning project:[ PrivIot - Debug ]----------"
	@"$(MAKE)" -f  "PrivIot.mk" clean
