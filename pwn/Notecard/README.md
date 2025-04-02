# Notecard

Nodecard is a stripped pwn that requires the user to overwrite a pointer to LIBC in the GOT to solve.

# Solve

One can solve this challenge by following these steps, which are also outlined in solve.py

1) exit_internal is written right after the username buffer which you can leak by writing a name of length 24. You can leak it and from there get the addresses of puts@got and printf@got.
2) From there you can write both of those pointers into the end of the 4th notecard, which is right before the heap array containing the pointers for the different note cards.
3) When selecting which note card you wish to read from you can access negitive notecard indexes which will read the values of the pointers that you wrote to the heap.
4) Once you have leaked the libc pointers for both puts and printf you can calculate what the libc version is with libc.rip for example.
5) From there you can have the address of the system libc function, which you can use to overwrite the puts@got pointer through negative notecard indexing.
6) After that, you can overwrite the address of puts@got and either write "/bin/sh" or "cat flag.txt" to an empty notecard and read it or you can write either string to your name and call the exit command in the menu as this will print your name.

For a full script that leaks all relevant pointers and drops shell

python3 solve.py