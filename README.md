[![42](https://img.shields.io/badge/webserver-4_Circle-00babc?style=flat-square&logo=42)](https://1337.ma/en/)
[![result](https://img.shields.io/badge/Success-125/100-5cb85c?style=flat-square&logoWidth=12&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAAAXNSR0IArs4c6QAAAylJREFUaEPtmDmLVEEUhb+LK+IG7qIibuCKYCYYOSoGomjimoggOgiKmYGhgYEMGqgYiJmIG4ig4IKGitsv8Ae4m7ocuWO108u8flWvu+030JXN9Kmqc+49devWM0b4sBHOn56Abmewl4FeBnIiIGk6cBtYCxwzs2vVU0ptIUkzgEfAmkBawFEzu1QRUVoBgfxjYHVdklzEETO77P8vpYAm5CtafgMH3U6lEyBpJuCRX5VzPH4BB0olIJB/AqyMrG4fSiNA0izAya+IJO+wp6UQkGCbam3vgL6uCyhgGxfxl7zZx64KCLbxAxvr+RryXS2jBT3/L/JdvcjaRX7YDEhaBJwB3gOnzexHQlXIhUqa69UDWJYLHgK8DZ7/VD+n5gxIWgfcB7yk+bgF7DaznwmbZUIlzQ6XVEqpbLDNsM2cpI2h65tcx+AmsKdVEYG81/nlCcHwyG/yapM1ZzADkvYBV4ExGcAbwF4z8+s7eUiaF2yzJGFypm1qMiCpH7gQ0di5wENm5o1U9ChI/k3w/Oe8jUzSd2BSHjD8fgU4bGbe0uYOSfND5BfngocA0eR9igu4C2xP2OAi0J8nQtKC0NukkH8dPJ8b+QpfFzABeABsSBBxHjieJaJg5KM8X8+xcoinhPLmZTR2DJjZiXpwwcgXIj9ooQqB8Hh+ltjOnjOzk1VruG38kvLLMHYUJl8jwP8It+RzIMW3Z4FTYc5DYGEsc+BV8PyXhDk10IZuVJITcBFeQWLH11DJRsVOaAf5hgxUWWEp4Haak0AoBeql0m/Yht4mZZFMAcFO/jnD/TwtddEcfFKdz9u76YNGkn8NcxFT8xaK/L2t5JtmoMpO6wE/nBMjSWbB2k4+SkCwUx9wDxhfUETyDRu7T/SbWNI2wFvrsbGLB9xLYLOZeaVq+4gWEDKxFbgDjItk0rHIV/ZPEhBE7AD8fZD1dqis/QLY0qnIFxYQROwErjcR0fHItyQgR8R/Ix9dhbL8LmlXyMTogPHexg9sdD8feZYyYclnoH4lSW6ngfC5b7+ZfWuVVMr8lgWkbNYJbE9AJ6KasmYvAynR6gR2xGfgD5kpEElZbxKNAAAAAElFTkSuQmCC)](https://projects.intra.42.fr/webserv/mine)
# WebServer

42 project, recoding our own web server in c++ 98.
webserv is a HTTP/1.1 server conditionnal compliant with RFC 7230 to 7235.
HTTP is one of the most used protocols on the internet.
Knowing its arcane will be useful, even if you won’t be working on a website.
read the [subject](https://cdn.intra.42.fr/pdf/pdf/81662/en.subject.pdf) for more infrmetion.

## Environment

- MacOS 11.4(Big Sur, Intel)

Developed and tested in this environment.

## Compile

To compile , run the lines below.

```shell
$ git clone https://github.com/moelazhari/inception.git
$ cd inception
$ make
```
## Execute
```shell
$ ./webserv [config_file] (config_file is set to ./www/html/configs/config if not specified)
```
type in the taype in your browser https://localhost:[port] to test
## Configuration File
Configuration file is a text file that contains various settings and directives that dictate how the web server should operate. 
These settings are:<br>
listen: ```listen 8001;```
set the port number to listen on. the port set to 80 if not specified.<br>
host: ```host 127.0.0.1;```
set the ip address to listen on. the ip address set to 127.0.0.1 if not specified.<br>
client_max_body_size: ```client_max_body_size 100;```
set the maximum size of the client request body, set to 10000 if not specified.<br>
meme_types: ```mime_types types.conf;```
set the path to the mime.types file. the mime.types file set to ./www/html/configs/mime.types if not specified.<br>
server_name: ```server_name localhost;```
set the virtual server name.<br>
root: ```root ./www/html;```
set the root directory for the server. the root directory set to ./www/html if not specified.<br>
index: ```index index.html index.htm;```
set the default file to serve when a directory is requested.<br>
error_page: ```error_page 404 ./www/html/404.html;```
set the error page to serve when an error occurs.<br>
location: ```location / { autoindex on; }```
set the location of the server.<br>
autoindex: ```autoindex on;```
Turn on or off directory listing.<br>
methods: ```methods GET POST;```
set the allowed methods. (supported methods: GET, POST, DELETE) set to all methods if not specified.<br>
return: ```return 200 "Hello World";```
set the return status code and the body of the response.<br>
upload: ```upload on```
set on or off the upload feature. the upload feature is off by default.<br>
cgi_path: ```cgi_path .php ./www/html/cgi-bin/php-cgi;```
set the cgi path to cgi executable that will handle the request with the specified extension.<br>
## example of configuration file
```shell
server {
	# default server;

	listen	8001;

	host 127.0.0.1;
	client_max_body_size 10000000;
	root ./www/html;
	error_page 404 www/html/error_pages/404.html;
	error_page 500 www/html/error_pages/500.html;
	allow_methods GET POST DELETE;
	autoindex on;
	index index.html index.php;
	meme_types ./configs/types.conf;


	location /favicon.ico {
		allow_methods GET POST DELETE;
		root ./www/html/favicon.ico;
	}

	location /upload{
		root ./www/html/upload;
		index upload.html;
		allow_methods POST GET;
		upload on;
	}

	location /cgi_bin {
		root ./www/html/cgi_bin;
		allow_methods GET POST;
		index hello.html;
		path_info .py /usr/bin/python3;
		path_info .php ./php-cgi;
	}

}

server {
	listen	8000;

	host 127.0.0.1;

	server_name moelazhari;
	client_max_body_size 26336;
	allow_methods GET POST DELETE;
	autoindex on;
	index server2.html;
	meme_types ./configs/types.conf;
}

server {
	listen	8003;

	host 10.11.6.13;
	client_max_body_size 26000;
	allow_methods GET POST DELETE;
	autoindex on;
	index server3.html;
	meme_types ./configs/types.conf;
}
```
