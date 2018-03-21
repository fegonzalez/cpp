
###############################################################################
# I. In the library 
###############################################################################

/** Step 1: Compiling with Position Independent Code (PIC):

 -fpic   compilation option


PIC: What is position independent code? PIC is code that works no
matter where in memory it is placed. Because several different
programs can all use one instance of your shared library, the library
cannot store things at fixed addresses, since the location of that
library in memory will vary from program to program.

*/

>> g++ -c -Wall -Werror -fpic foo.cc

# generated:  foo.o  


/** Step 2: Creating a shared library from an object file

 -shared   compilation option

*/

>> g++ -shared  foo.o -o libfoo.so


# generated:  libfoo.so



###############################################################################
# II. In the client (user) of the library
###############################################################################

/** Step 3: Linking (the test / user of the library) with a shared library

    Required: Telling GCC where to find the shared library

    -L   linkage option:

          -L/lib-path    # path to the .so/.a file
                         # path may be absolute or relative

    -l linker option: lib-name without "lib" prefix & ".so" suffix	 
 
*/
    
>> g++ -L`pwd` -Wall -o test test.cc  -lfoo

# generated:  test          # executable, user of the lib.



/** Step 4: Making the library available at runtime

4.1) Using LD_LIBRARY_PATH: recommended only for test purposes

	 Pasamos

4.2) Using rpath linker option:

	 Rpath, or the run path, is a way of embedding the location of
	 shared libraries in the executable itsel

	 During the linking.

	 -Wl linker option: portion sends comma-separated options to the linker

	 -rpath linker option: with our working directory (`pwd`)

	 -l linker option: lib-name without "lib" prefix & ".so" suffix	 
*/

>> g++ -L`pwd` -Wl,-rpath=`pwd` -Wall -o test test.cc -lfoo



## Ahora ya se peude ejecutar contra la librería.

>> ./test






# Nota: estructura directorios

# en la librería  some_lib
src/  # src & headers of the lib.


# en el cliente ./test/
test/include/  # .h de las librerías
test/lib/      # .so/.a librerías





d lib  SIMPLE_ALLINONE_DIR  src  test





