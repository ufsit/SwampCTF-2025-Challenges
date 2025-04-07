# Editor Writeup

This is an angular and flask application, as is obvious by the given files. 

Simply going to the provided url for where the file is shows that we aren't allowed to access the resource. 
Investigating the provided backend directory source code shows the issue is the referrer field, which the browser isn't setting. 

To bypass this, we need a method to have the webpage query for this flag resource. Normally this is done via JavaScript, but the page prevents JavaScript from executing.

However, using the `url()` and CSS imports it is possible to write CSS which will query for the resource, and this network call can be inspected within the browser tools. 

```
@import url('http://localhost:5000/flag.txt);
```

Investigate the output in the browser tools and you will have the flag.

swampCTF{c55_qu3r135_n07_j5}