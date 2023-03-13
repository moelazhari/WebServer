FROM debian:buster

RUN apt-get update -y \
	&& apt-get install nginx -y;

COPY ./conf/nginx.conf /etc/nginx/nginx.conf
COPY var.html /var/www/html
COPY index.html /var/www/html
COPY ./tools /var/www/html

CMD ["nginx", "-g", "daemon off;"]
