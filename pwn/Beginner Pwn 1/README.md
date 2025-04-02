# Beginner Pwn 1

This challenge demonstrates the basics of buffer overflows by demonstrating how the accounts name can be used to overflow the "is_admin" bool, thus flipping it's value from False to True for any nonzero value that overflows into it.

# Solve

Send the binary AAAAAAAAAAAAAA to overflow the is_admin boolean, granting admin permission.