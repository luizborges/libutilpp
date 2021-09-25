CC              = g++
DLIB_DIR_H      = /var/www/shared
DLIB_DIR        = $(DLIB_DIR_H)/dlibs
DLIB_DIR_LPATH  = $(foreach dir,$(DLIB_DIR),   -L$(dir)) # add prefix to all dir
DLIB_DIR_H_IPATH= $(foreach dir,$(DLIB_DIR_H), -I$(dir)) # add prefix to all dir
DLIB_DIR_RPATH  = $(foreach dir,$(DLIB_DIR),   -Wl,-rpath=$(dir)) # add prefix to all dir
DLIB_NAME       = #-lerror -lstackTracer# insert here all dynamics libraries in DLIB_DIR_H you want to use
# old -lclientOutput_strMap -lroute_easy -lclientInput_manager -lcookie_manager
# OLD -LIBCOMMON = -lerror -lmemoryManager -lstackTracer -lfileUtil -larrayList_noSync -lmap_ArrayList_noSync -labstractFactoryCommon
CFLAGS          = -Wall -Wextra -g -Ofast -DNDEBUG -Wno-variadic-macros -fPIC -Wl,--export-dynamic -std=c++17# Werror transforms warning in error
DLIB_STD        = -lm -lpthread #-lfcgi -lgc
DLIB            = $(DLIB_STD) $(DLIB_NAME)
COMPILER_FLAGS  = $(CFLAGS) #$(DLIB_DIR_LPATH) $(DLIB_DIR_H_IPATH) use $(DLIB_DIR_LPATH) $(DLIB_DIR_H_IPATH) when the library is not in global environment
LINK_FLAGS      = $(COMPILER_FLAGS) #$(DLIB_DIR_RPATH) # use -Wl,-rpath= when the library is not in global environment
LINK_DLIB       = $(LINK_FLAGS) -shared -Wl,-soname,$(LIB)
################################################
# PATHS TO EXPORT LIBRARY TO BE GLOBAL IN SYSTEM
################################################
DLIB_DIR_H_GLOBAL = /usr/local/include
DLIB_DIR_GLOBAL   = /usr/local/lib
################################################
# INCLUDE LIBRARIES OF THE LIBRARY
################################################
FILE        = file/file.cpp
ERROR       = error/error.cpp
LIBC_STDIO  = libc/stdio.cpp
LIBC_STDLIB = libc/stdlib.cpp
LIBC_STRING = libc/string.cpp
STR	    = str/str.cpp str/str_global.cpp
GLOBAL	    = global/global.cpp
################################################
# END
################################################

C_SRC_LIB       = 
C_SRC_MAIN      = 
C_SRC           = $(FILE) $(ERROR) $(LIBC_STDIO) $(LIBC_STDLIB) $(LIBC_STRING) $(STR) $(GLOBAL)
C_OBJ_ORI       = $(C_SRC:.cpp=.o)
C_SRC_NAME_ONLY = $(notdir $(C_SRC))
C_OBJ_NAME_ONLY = $(C_SRC_NAME_ONLY:.cpp=.o)
C_OBJ_DIR       = objs/
C_OBJ           = $(addprefix $(C_OBJ_DIR), $(C_OBJ_NAME_ONLY))
C_LIB_H         = util.hpp # $(C_SRC_LIB:.cpp=.h)
LIB             = $(LIB_NAME_ONLY).1.0.0   # lib$(C_SRC_LIB:.cpp=.so)
LIB_NAME_ONLY   = libutilpp.so
EXE             = exe

ARG1       = #-q input.dat
ARG2       = #-o output.dat
ARG3       = #-i list_log_files.dat
ARG4       = #-d date.dat
ARG5       = #-e str_end_block.dat

#run: linker
#	$(info $nrun: $(EXE))
#	./$(EXE) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5)


# use this option to create a global library.
# with this option you can use the library like a default library in the system
# you can use the library like any default dynamic library (ex: #include <pthread.h>)
# the library is put in default directories of the system, this could change
# from a system to another.
# see the directory for lib.so and the header file.
# the command to update cache of default libraries could change from a system to anoter.
glib: cscrean clean_glib linker_lib export_glib_header export_glib 
	$(info $nDynamic Library created with success: $(LIB) $nDynamic Library Header exported with success: $(C_LIB_H)$nFramework Library exported with success.$nTo use Framework CWEB: #include <$(C_LIB_H)>)
# can use to print: $(info your_text) $(warning your_text) or $(error your_text) # for new/break line use: $nYour_text - ex: my_text_line1 $nmy_text_line2
# use this option to create a local library.
# with this option you will must add the following options to use the library:
# compile timer:
# -IPATH_TO_LIBRARY_HEADER_FILE_H and -LPATH_TO_LIBRARY_OBJECT_FILE_SO
# linker timer:
# -Wl,-rpath=PATH_TO_LIBRARY_OBJECT_FILE_SO
# where:
# PATH_TO_LIBRARY_OBJECT_FILE_SO = path where is library object (ex: libfoo.so).
# example: /home/borges/shared/dlibs
# PATH_TO_LIBRARY_HEADER_FILE_H = path where is the library's header file (ex: foo.h)
# example:  /home/borges/shared/headers
lib: cscrean clean_lib linker_lib export_lib export_lib_header
	$(info $nDynamic Library created with success: $(LIB) $nDynamic Library Header exported with success: $(C_LIB_H)$nFramework Library exported with success.$nTo use Framework CWEB: #include <headers/$(C_LIB_H)>)
# can use to print: $(info your_text) $(warning your_text) or $(error your_text) # for new/break line use: $nYour_text - ex: my_text_line1 $nmy_text_line2
# old printed texted messager console	
#	$(info $nDynamic Library created with success: $(LIB) $nDynamic Library Header exported with success: $(C_LIB_H)$nTo direct use: #include <headers/$(C_LIB_H)> $nFramework Library exported with success.$nTo use Framework CWEB: #include <headers/$(C_LIB_H)>)
# can use to print: $(info your_text) $(warning your_text) or $(error your_text) # for new/break line use: $nYour_text - ex: my_text_line1 $nmy_text_line2

linker_lib:  $(C_SRC:.cpp=.o) mv_c_obj
	$(info $nlinkier objects to produce: $(LIB))
	$(CC) $(LINK_DLIB) $(C_OBJ) -o $(LIB) $(DLIB)

linker: cscrean clean add_c_src_main $(C_SRC:.cpp=.o) $(C_SRC_MAIN:.cpp=.o) mv_c_obj
	$(info $nlinker objects to produce: $(EXE))
	$(CC) $(LINK_FLAGS) $(C_OBJ) -o $(EXE) $(DLIB)

$(C_SRC:.cpp=.o): %.o : %.cpp
	$(info $ncompile: $<)
	$(CC) $(COMPILER_FLAGS) -c $< -o $@ $(DLIB)


$(C_SRC_MAIN:.cpp=.o): %.o : %.cpp
	$(info compile: $<)
	$(CC) $(COMPILER_FLAGS) -c $< -o $@ $(DLIB)
	
export_lib:
	$(info $nexport lib and lib_header:)
	sudo cp $(LIB) $(DLIB_DIR)/

export_lib_header:
	sudo cp $(C_LIB_H) $(DLIB_DIR_H)/headers/

export_glib_header:
	$(info $nexport global lib header:)
	sudo cp $(C_LIB_H) $(DLIB_DIR_H_GLOBAL)/

export_glib:
	$(info $nexport global lib:)
	sudo cp $(LIB) $(DLIB_DIR_GLOBAL)/
	sudo ldconfig $(DLIB_DIR_GLOBAL)
	sudo ln -s $(DLIB_DIR_GLOBAL)/$(LIB) $(DLIB_DIR_GLOBAL)/$(LIB_NAME_ONLY)


mv_c_obj: 
	$(info $nmoving files to obj_dir)
	mv $(C_OBJ_ORI) $(C_OBJ_DIR)

# only in C_SRC variable is necessary to concatenate whit C_SRC_MAIN, all others just loading them again
add_c_src_main:
	$(info add files from C_SRC_MAIN to global compile variables)
	$(eval C_SRC += $(C_SRC_MAIN))
	$(info new makefile variable: C_SRC = $(C_SRC))
	$(eval C_OBJ_ORI = $(C_SRC:.cpp=.o))
	$(info new makefile variable: C_OBJ_ORI = $(C_OBJ_ORI))
	$(eval C_SRC_NAME_ONLY = $(notdir $(C_SRC)))
	$(info new makefile variable: C_SRC_NAME_ONLY = $(C_SRC_NAME_ONLY))
	$(eval C_OBJ_NAME_ONLY = $(C_SRC_NAME_ONLY:.cpp=.o))
	$(info new makefile variable: C_OBJ_NAME_ONLY = $(C_OBJ_NAME_ONLY))
	$(eval C_OBJ = $(addprefix $(C_OBJ_DIR), $(C_OBJ_NAME_ONLY)))
	$(info new makefile variable: C_OBJ = $(C_OBJ))

clean_lib: clean
	sudo rm -rf $(LIB) $(DLIB_DIR)/$(LIB) $(DLIB_DIR_H)/headers/$(C_LIB_H)

clean_glib: clean
	sudo rm -rf $(LIB) $(DLIB_DIR_GLOBAL)/$(LIB) $(DLIB_DIR_H_GLOBAL)/$(C_LIB_H)
	sudo rm -rf $(DLIB_DIR_GLOBAL)/$(LIB_NAME_ONLY)
	sudo ldconfig $(DLIB_DIR_GLOBAL) # to update the cache /etc/ld.so.cache

clean:
	rm -rf $(C_OBJ_DIR)*.o *~ *.out *.key out.txt

cscrean:
	clear

valg: compile
	valgrind ./$(EXE) $(ARG1) $(ARG2)
	
define n # define a break line - new line to user's message


endef

























	
