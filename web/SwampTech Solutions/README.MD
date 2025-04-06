# SwampTech Solutions

SwampTech Solutions is a multi-step web challenge that ends in an XXE vulnerability. Players will need to uncover hardcoded credentials in the login page, manipulate a hashed cookie value to escalate access, discover a hidden XML-based form, and ultimately exploit an XML External Entity vulnerability to retrieve the flag.

# Full Solution Writeup

Visit the /login.php page

Login with hardcoded credentials 
```
guest:iambutalowlyguest
```
You will be redirected to /dashboard.php

Note that the cookie value is an MD5 hash. Cracking the hash will reveal it is a hash of the word "guest" 
Change the cookie to the hash for "admin":
```
21232f297a57a5a743894a0e4a801fc3
```
You should now be able to access the admin page at /adminpage.php

Refresh the admin page and this time intercept the request in Burp
Right click on the request > Do Intercept > Response to this Request
Scroll through the response to the hidden obfuscated looking form

Just delete the word "hidden" and forward the request
You should now see the new inputs and form. Send whatever data through this form and intercept the request

Notice the data appears to be xml data in URL encoded form
Upon sending the form, a response will appear that reflects the "name" parameter value back at the user.

Replace the decoded data with the following XXE payload and hit apply changes: 

```
<!DOCTYPE foo [
<!ENTITY xxe SYSTEM "php://filter/convert.base64-encode/resource=flag.txt">
]>
<root>
    <name>&xxe;</name>
    <email>emailhere</email>
</root>
```
(You must use a base64 php filter due to the fact that the flag itself contains characters that break the xml syntax)

Forwarding this new request should get you the flag.txt string in base64
Simply decode the base64 string to retrieve the flag
