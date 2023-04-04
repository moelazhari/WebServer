import cgi, cgitb

form = cgi.FieldStorage()

file = form.getvalue('file');

print ("Content-type:text/html\r\n")
print ("\r\n")
print ("<html>")
print ("<head>")
print ("<title>Hello py cgi</title>")
print ("</head>")
print ("<body>")
if file:
    print("resev file %s" % (file))
else:
    print("no file")
print ("</body>")
print ("</html>".encode('utf-8'))
# Delete the file

