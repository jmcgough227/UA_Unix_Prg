# man page generation

# compress man page (can still be viewed)
src2srcml.1.gz : src2srcml.1
	gzip -f src2srcml.1

# create man page
src2srcml.1 : src2srcml.xml
	docbook2x-man src2srcml.xml

# view man page
viewman :
	man -l src2srcml.1.gz

# clean generated man and info pages
clean :
	rm -f src2srcml.1 src2srcml.1.gz
