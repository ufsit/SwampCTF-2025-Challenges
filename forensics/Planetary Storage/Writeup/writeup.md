# Planetary Storage Writeup

To solve this challenge, you first need to investigate the files provided within the .zip folder.
Most of the files won't provide any useful information about the challenge, except for the LOG file (which shows when the challenge was created), and the `.ldb` files which are the most interesting of the bunch. 

The `.ldb` files can be opened using text editors to view their content, but due to the encoding used some editors will fail to render the proper content. I utilized Visual Studio Code to inspect the file contents (Visual Studio Code's built in editor won't show all of the content properly, but all the key data for solving the challenge is visible this way). Alternatively, you can utilize an online viewer to inspect the file contents. 

Investigation of the `000010.ldb` will reveal this content:
```
õ♂H ¶Õ♂/_localHeads☺	 ♣☺ô¶☺[{"payload":"eyJrZXkiOiJcIjMzNTc5M2Q1LTRhYzEtNDgyMy05MmM3LWZkM2I1YTZhMmEwN1wiIiwib3AiOiJQVVQiLCJ2YWx1ZSI6ImV5SmtZWFJoSWpwYkluTjNZVzF3UTFSR2V6RndaalV0WWpRMU0yUXRaRFEzTkdJME5UTjlJbDBzSW1sa0lqb2lYQ0l6TXpVM09UTmtOUzAwWVdNeExUUTRNak10T1RKak55MW1aRE5pTldFMllUSmhNRGRjSWlKOSJ9","id":"/orbitdb/bafyreiejrtaennxufa3wvkdvyoj6ywq6nid3lukdqcnx2fc33tckzjzbke/ctf","next":[{"/":"bafyreibbadm2ajrr6io6ufqidibrpdjfpdyfobp2aqvmcprqu5yrk7mq6q"}],"refs":[{"/↓Mð}esvykh6wt7hn4fry4mphv6ckxr5wq3c2fecvcjbqs4scbkizc6jm"},{"/":"bafyreihq7osywkglsjxn5lmbegtc7izqmb66atx5trkrpcmlvtcyrr6nuy"},{"/↓ˆôi☺ab6do7qxgjipiypoj754vicpuscejf43eguvo2ykb2igoyrtkl64"}],"v":2,"key":"BJx/DXfZOVG6YkoHDGQvNQVMBaoeaEdEvcKFJP0PM1m3h9/o8lJgnTQkqGCAKovuOCovsDHQ5JOVs7qpJm3V8Ks=","sig":"MEQCIF5FwOBiQKgEI7njg6He6iAlwNc+Gj8+PAll5o1PCGhKAiBlnXg9+hinX6AGB2r0uXoJ3q9Tbe6azh9euPx40G8uqw==","identity":{"id":"02020192715ea41d7eaaceb4bd19516d0d4f1e8a2e81903480083dbdbe99dfefc9","publicKey":þ&☺z&☺$natures":{i
ðmMEQCIGx+GRqmTfPqcUL28aG2p1Q2TNEfZ9QlCgB8WU4my68UAiBZClP9WMe385COJ0WuNnXRj7BIolRC2v6vhLqUt3Yk/w==","publicKey":	oð†FC+7AikjMLabNvdHiHh7rwrFTbystu6xc2r1h/1Zr4jAiBFxjxIMNjfI5J996HDYEQd+fnaKDi5GlNw5hgl+RwEOg=="},"type":"orbitdb","Provider":null},"hash"::%♥è6d33ifjj6jbmjptygyksgwzcrjm5kxarbbp6djbzqx2exij27u"},"clock5N♦BJþâ☻bâ☻Dtime":7}}]    ☺   ☺z§w♀◘∟    ☺   ☺♠4Ÿ ↨¶ 	♥0☺ÿ	☺( ®
    ☺   ☺õÙ Õ³


▬                                  Wû€‹$uGÛ
```

In the above text content, the sections of particular note are the "payload" string and the "id" string. The id string indicates that this is related to somethign called 'orbitdb', which is a distributed p2p database built on the InterPlanetary File System (IPFS). You can either read into how this database stores data internally to understand the files, you you can notice that Base64 encodings are utilized to encode various pieces of information. 

The payload string is Base64 encoded. Decoding it will reveal the following content: 
```
{"key":"\"335793d5-4ac1-4823-92c7-fd3b5a6a2a07\"","op":"PUT","value":"eyJkYXRhIjpbInN3YW1wQ1RGezFwZjUtYjQ1M2QtZDQ3NGI0NTN9Il0sImlkIjoiXCIzMzU3OTNkNS00YWMxLTQ4MjMtOTJjNy1mZDNiNWE2YTJhMDdcIiJ9"}
```

Here, the value string is Base64 encoded. Decoding it will reveal the following content:
```
{"data":["swampCTF{1pf5-b453d-d474b453}"],"id":"\"335793d5-4ac1-4823-92c7-fd3b5a6a2a07\""}
```

We have found the flag!

Note: the other `.ldb` files contain other sections of the database, performing the same process on those will reveal other portions of the database which do not have the flag entry, but have other entries instead. The encoding of the payload string in these other files are more obviously Base64 encoded than the one in `000010.ldb`.