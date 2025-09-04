# Lost In Translation Writeup

Upon opening the provided challenge file, it should be pretty obvious that something fishy is going on due to the strange whitespace which is present in the file. Turns out, there is a reason for this. There are some esoteric programming languages which are written completely using whitespace characters. In this case, the language in use is called 'whitespace' and has been hidden within a JavaScript file, with the intention that many people would assume that the programmer simply hates traditional whitespace rules.

Utilizing an online whitespace programming language compiler the entire program can be ran and the flag retreived. I used this one. 
https://ideone.com/l/whitespace

![Found Flag](./Flag_Found.png?raw=true)

The whitespace program code utilized in this challenge was generated using the following resource:
https://glitch.com/~whitespace-generator