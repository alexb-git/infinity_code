###############################################################################
# By Roma Tarasenko HRD1												      #
# makefile for watch dog.													  #
# run: "make shared" for compile shared library, what_dog app and a test app. #
# run: "make debbug" for compiling all the above for debbuging  			  #
###############################################################################
c_files  = wdfuncs.c dlist.c scheduler.c task.c	uid.c pqueue.c sortedlist.c semV.c
OBJ_DIR  = objects
LIB_NAME = libwd.so
OBJ      = $(patsubst %.c, %.o, $(c_files))
GC       = gcc -std=c89 -ansi -Wall -pedantic -Werror -DNDEBUG -D_GNU_SOURCE
GD       = gcc -std=c89 -ansi -Wall -pedantic -Werror -D_DEBUG -g -D_GNU_SOURCE

shared:  $(OBJ_DIR) shared_lib cp_lib test wd_shared

debbug: a.out wd.out

a.out:  wd_test.c $(c_files)
	$(GD) $^  -o $@ -lpthread -ldl

wd.out: watch_dog.c $(c_files)
	$(GD) $^   -o $@ -lpthread -ldl

$(OBJ_DIR):
	mkdir $@

$(wd_dir):
	mkdir $@

# -fPIC position independent code
%.o: %.c
	$(GC) -fPIC -c $^ -o ./$(OBJ_DIR)/$@

shared_lib: ./$(OBJ_DIR)/$(OBJ)
	$(GC) -shared -o $(LIB_NAME) $(addprefix $(OBJ_DIR)/, $(OBJ))

cp_lib: shared_lib
	sudo cp  ./$(LIB_NAME) /usr/lib/

# lwd.so (watch dog library)
# -ldl dynamic linker
test: $(c_files)
	$(GC) wd_test.c -lwd -lpthread -ldl -D_GNU_SOURCE

wd_shared: test $(c_files)
	$(GC) watch_dog.c -lwd -lpthread -o wd.out -D_GNU_SOURCE

clean:
	rm -f *.out
	sudo rm -f /usr/lib/libwd.so
	rm -r $(OBJ_DIR)
