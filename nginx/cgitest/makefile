all: build

build:
	mkdir -p test
	docker-compose -f ./docker-compose.yml up --build -d


clean:
	docker-compose -f ./docker-compose.yml down -v
	rm -rf test
	
fclean:
	docker rmi -f $$(docker images -aq)

.PHONY: all clean build fclean