EXS=$(shell find ./ -type d -name "ex*")

default:
	@echo "\"make pdf\" to build all exercises and mitschrift"

.PHONY: force

pdf: $(EXS) mitschrift

$(EXS) mitschrift : force
	$(MAKE) -C $@