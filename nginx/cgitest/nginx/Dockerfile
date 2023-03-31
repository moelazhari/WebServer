FROM nginx:latest

RUN apt-get update && apt-get install -y \
    spawn-fcgi \
    php7.4-cgi \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY nginx.conf /etc/nginx/nginx.conf
RUN mkdir -p /var/www/html
COPY tools /var/www/html
# COPY index.php /usr/share/nginx/html/index.php

EXPOSE 8080

CMD ["nginx", "-g", "daemon off;"]
