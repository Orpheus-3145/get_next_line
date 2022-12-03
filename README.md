# get_next_line
Implementation of the C function readline(): giving a file descriptor from the open() function to get_next_line() gives back the line at the current cursor position; notes:
    - is possible to iterate the function to read a whole text file, gives NULL when eof is reached;
    - it reads from normal files or the standard input;
    - it is also possibile to read from different files descriptors at the same time, without loosing the current position when switching from one fd to another
    - at last, when compiling the file which is going to use the archive from GNL, it's possible to add the flag '-D BUFFER_SIZE=X' to set manually the size of the buffer (i.e. the amount of characters read from the read() function), instead of using the default value (42)
