# Beginner Web Writeup

The flag is split into 3 parts and hidden throughout the website. 

The first part of the flag is in a comment within the page of the index.html file. 

The second part of the flag is hidden in a browser cookie. 

The third part of the flag is hidden within the header of a network call. Specifically, there is a duplicate request for the favicon.ico file, and the flag part is hidden in the headers of that request. 

Putting all the parts in the proper format gives:

swampCTF{w3b_br0w53r5_4r3_v3ry_c0mpl1c473d}
