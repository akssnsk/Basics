SUBDIRS = Cpp Tasks
 
.PHONY: subdirs $(SUBDIRS)
 
subdirs: $(SUBDIRS)
 
$(SUBDIRS):
	$(MAKE) -C $@
  
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done


#Dependency example   
#foo: baz

