# OS

##  Heap (Dynamic memory allocation)
The heap and process memory allocation is done using linked list. The memory allocated for this is
not allocated in the own heap but rather in a small chunk of memory at end the of the disk space.

The free heap supports the following functions

1. Insert
2. Delete
3. Find
4. Allocate
5. Deallocate (Delete the process memory allocated in the free block)

> Note: The free memory is not deleted if all the process memory chunks used deallocates from the free block. 
>
> The size of free chunks is alowed to be modifieds by the user, but make sure that the size of the block varies between some uniform range. This is done to avoid fragmentation.
>
> The memory allocation algorithm used is best fit.

The process memory allocation supports the following functions

1. Insert
2. Delete (Deallocate is also done here)
3. Find
4. Allocate

## Display driver

The display driver is used to display the output of the OS. The display driver supports the following functions

1. Write character
2. Write character at position
3. Write string
4. Write string at position
5. Clear screen
6. Set cursor position
7. New line
8. Scroll up
9. Scroll down
10. Form feed
11. Carriage return
12. Backspace
13. Tab
14. Write face (only 128x128)
15. Write face at position (*not implemented yet*)

> For more info: look at `./dev` folder and `./os/faces/*.h` files.

## Keyboard driver

The keyboard driver is used to get the input from the user. The keyboard driver supports the following functions

1. Get character
2. Get string (*not implemented yet*)
3. Support for special keys (*partially implemented*)


## How to run keyboard

> Note: each command must run in it's own terminal

1. Run the `os.c` file (`gcc os.c -I . && ./a.out`)
2. Run the keyboard_adapter (`g++ keyboard.cpp -o main -static && ./main`)
3. Run the auto (`go build . && ./auto || go run .`)

While closing all applications. The below order is recommended.

1. auto
2. adapter
3. os
