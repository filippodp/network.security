# Alberto Bonizzi, Filippo Dai Prè, Roberto Fellin
# NetworkSecurity2017 docker environment for Kaminsky DNS attack

# Some colors for happy eyes
C1 = "\033[0;33m" #Yellow
C2 = "\033[0;32m" #Green
C3 = "\033[1;31;107m" #Red
END = "\033[0m"




# Default roule/tag
default: short-help




# Now we build all docker settings for setting-up the lab or single setting
build.all: create.subnet dns.auth.fun.build dns.auth.emoji.fun.build dns.recursive.build dns.root.build server.hack.build server.real.0.build server.real.1.build server.real.2.build server.real.3.build server.real.4.build 

create.subnet:
	@echo $(C2)"creating the mlab_subnet 10.10.0.0/16 ..."	$(END)
	sudo docker network create --subnet 10.10.0.0/16 mlab_net

dns.auth.fun.build:
	@echo $(C2)"building dns.auth.fun:internet ..."			$(END)
	sudo docker build -t dns.auth.fun:internet 	dns.auth.fun

dns.auth.emoji.fun.build:
	@echo $(C2)"building dns.auth.emoji.fun:internet ..."	$(END)
	sudo docker build -t dns.auth.emoji.fun:internet 	dns.auth.emoji.fun

dns.recursive.build:
	@echo $(C2)"building dns.recursive:company ..."			$(END)
	sudo docker build -t dns.recursive:company 	dns.recursive

dns.root.build:
	@echo $(C2)"building dns.root:internet ..."				$(END)
	sudo docker build -t dns.root:internet	 	dns.root

server.hack.build:
	@echo $(C2)"building server.hack:attacker ..."			$(END)
	sudo docker build -t server.hack:attacker 	server.hack

server.real.0.build:
	@echo $(C2)"building server.real:internet ..."			$(END)
	sudo docker build -t server.real.0:internet 	server.real.0

server.real.1.build:
	@echo $(C2)"building server.real:internet ..."			$(END)
	sudo docker build -t server.real.1:internet 	server.real.1

server.real.2.build:
	@echo $(C2)"building server.real:internet ..."			$(END)
	sudo docker build -t server.real.2:internet 	server.real.2

server.real.3.build:
	@echo $(C2)"building server.real:internet ..."			$(END)
	sudo docker build -t server.real.3:internet 	server.real.3

server.real.4.build:
	@echo $(C2)"building server.real:internet ..."			$(END)
	sudo docker build -t server.real.4:internet 	server.real.4




# Boot-up the entire environment or select single application
boot.all: 
	@echo ""
	@echo $(C2)"starting server.real.0 10.10.0.5:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.5 -itd -p 0.0.0.6:80:80/tcp server.real.0:internet
	@echo $(C2)"starting server.real.1 10.10.0.6:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.6 -itd -p 0.0.0.7:80:80/tcp server.real.1:internet
	@echo $(C2)"starting server.real.2 10.10.0.7:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.7 -itd -p 0.0.0.8:80:80/tcp server.real.2:internet
	@echo $(C2)"starting server.real.3 10.10.0.8:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.8 -itd -p 0.0.0.9:80:80/tcp server.real.3:internet
	@echo $(C2)"starting server.real.4 10.10.0.9:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.9 -itd -p 0.0.0.10:80:80/tcp server.real.4:internet
	@echo $(C2)"starting server.hack 10.10.50.2:80/TCP ..."			$(END)
	docker run --rm=true --net mlab_net --ip 10.10.50.2 -itd -p 0.0.0.5:80:80/tcp server.hack:attacker
	@echo $(C2)"starting dns.auth.emoji.fun 10.10.0.4:53/UDP ..."	$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.4 -itd -p 0.0.0.2:53:53/udp dns.auth.emoji.fun:internet
	@echo $(C2)"starting dns.auth.fun 10.10.0.3:53/UDP ..."			$(END)
	docker run --rm=true --cap-add=NET_ADMIN --net mlab_net --ip 10.10.0.3 -itd -p 0.0.0.1:53:53/udp dns.auth.fun:internet
	@echo $(C2)"starting dns.root 10.10.0.2:53/UDP ..."				$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.2 -itd -p 0.0.0.4:53:53/udp dns.root:internet	
	@gnome-terminal -x sh -c "make other-terminal; bash"
	@gnome-terminal -x sh -c "make dns.recursive.start; bash"
	@echo ""	

other-terminal:
	@echo $(C3)"--> KEEP this terminal OPEN <--"					$(END)
	sudo -s

dns.auth.fun.start:
	@clear
	@echo $(C2)"starting dns.auth.fun 10.10.0.3:53/UDP ..."			$(END)
	docker run --rm=true --cap-add=NET_ADMIN --net mlab_net --ip 10.10.0.3 -it -p 0.0.0.1:53:53/udp dns.auth.fun:internet

dns.auth.emoji.fun.start:
	@clear
	@echo $(C2)"starting dns.auth.emoji.fun 10.10.0.4:53/UDP ..."	$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.4 -it -p 0.0.0.2:53:53/udp dns.auth.emoji.fun:internet

dns.recursive.start:
	@clear
	@echo $(C2)"starting dns.recursive 10.10.10.1:53/UDP ..."		$(END)
	docker run --rm=true --privileged --cap-add=NET_ADMIN --net mlab_net --ip 10.10.10.1 -it -p 0.0.0.3:53:53/udp dns.recursive:company

dns.root.start:
	@clear
	@echo $(C2)"starting dns.root 10.10.0.2:53/UDP ..."				$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.2 -it -p 0.0.0.4:53:53/udp dns.root:internet

server.hack.start:
	@clear
	@echo $(C2)"starting server.hack 10.10.50.2:80/TCP ..."			$(END)
	docker run --rm=true --net mlab_net --ip 10.10.50.2 -it -p 0.0.0.5:80:80/tcp server.hack:attacker

server.real.0.start:
	@clear
	@echo $(C2)"starting server.real.0 10.10.0.5:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.5 -it -p 0.0.0.6:80:80/tcp server.real.0:internet

server.real.1.start:
	@clear
	@echo $(C2)"starting server.real.1 10.10.0.6:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.6 -it -p 0.0.0.7:80:80/tcp server.real.1:internet

server.real.2.start:
	@clear
	@echo $(C2)"starting server.real.2 10.10.0.7:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.7 -it -p 0.0.0.8:80:80/tcp server.real.2:internet

server.real.3.start:
	@clear
	@echo $(C2)"starting server.real.3 10.10.0.8:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.8 -it -p 0.0.0.9:80:80/tcp server.real.3:internet

server.real.4.start:
	@clear
	@echo $(C2)"starting server.real.4 10.10.0.9:80/TCP ..."		$(END)
	docker run --rm=true --net mlab_net --ip 10.10.0.9 -it -p 0.0.0.10:80:80/tcp server.real.4:internet




# Drop all configurations
delete.all:
	@clear
	@echo $(C3)"ATTENTION! deleting docker environment ..."			$(END)
	sudo docker network rm mlab_net
	sudo docker rmi -f dns.auth.fun:internet dns.auth.emoji.fun:internet dns.recursive:company dns.root:internet server.hack:attacker server.real.0:internet server.real.1:internet server.real.2:internet server.real.3:internet server.real.4:internet
	



# Useful shortcut
images:
	@docker images

containers:
	@docker ps -a




# Little list of best practices
long-help:
	@clear
	@echo "How to use make:" 
	@echo $(C2)"\n\t --- USEFUL SHORTCUT ---"$(END)
	@echo $(C1)"  make" 					$(END) "or "$(C1)"make short-help "$(END)"or "$(C1)"make long-help "$(END)"or "$(C1)"make dafault "$(END)"(display the guide)"
	@echo $(C1)"  make images"				$(END) "(view a list of all docker images)"
	@echo $(C1)"  make containers"			$(END) "(view a list of all docker containers)"
	@echo $(C2)"\n\t --- ROULES FOR MANAGE ALL LAB ---"$(END)
	@echo $(C1)"  make build.all" 			$(END) "(require root privileges, build and setup all the docker environment)"
	@echo $(C1)"  make boot.all" 			$(END) "(start the enviroment, so, every images)"
	@echo $(C1)"  make delete.all" 			$(END) "(require root privileges, delete the docker environment, images and subnet)"
	@echo $(C2)"\n\t --- ROULES FOR BUILDING EACH SINGLE CONTAINER ---"$(END)
	@echo $(C1)"  make create.subnet"		$(END) "(our environment work into a specific subnet, create it before)"
	@echo $(C1)"  make dns.auth.fun.build"	$(END) "(require root privileges, build from the dockerfile the dns.auth.fun machine)"
	@echo $(C1)"  make dns.auth.emoji.fun.build"	$(END) "(require root privileges, build from the dockerfile the dns.auth.emoji.fun machine)"
	@echo $(C1)"  make dns.recursive.build"	$(END) "(require root privileges, build from the dockerfile the dns.recursive machine)"
	@echo $(C1)"  make dns.root.build"		$(END) "(require root privileges, build from the dockerfile the dns.root machine)"
	@echo $(C1)"  make server.hack.build" 	$(END) "(require root privileges, build from the dockerfile the attacker machine)"
	@echo $(C1)"  make server.real.0.build"	$(END) "(require root privileges, build from the dockerfile the web server machine 0)"
	@echo $(C1)"  make server.real.1.build"	$(END) "(require root privileges, build from the dockerfile the web server machine 1)"
	@echo $(C1)"  make server.real.2.build"	$(END) "(require root privileges, build from the dockerfile the web server machine 2)"
	@echo $(C1)"  make server.real.3.build"	$(END) "(require root privileges, build from the dockerfile the web server machine 3)"
	@echo $(C1)"  make server.real.4.build"	$(END) "(require root privileges, build from the dockerfile the web server machine 4)"
	@echo $(C2)"\n\t --- ROULES FOR STARTING EACH SINGLE CONTAINER ---"$(END)
	@echo $(C1)"  make dns.auth.fun.start"	$(END) "(start the dns.auth.fun server)"
	@echo $(C1)"  make dns.auth.emoji.fun.start"	$(END) "(start the dns.auth.emoji.fun server)"
	@echo $(C1)"  make dns.recursive.start"	$(END) "(start the dns.recursive server)"
	@echo $(C1)"  make dns.root.start"		$(END) "(start the dns.root server)"
	@echo $(C1)"  make server.hack.start" 	$(END) "(start the attacker machine)"
	@echo $(C1)"  make server.real.0.start" $(END) "(start the trusted apache2 0 web server)"
	@echo $(C1)"  make server.real.1.start" $(END) "(start the trusted apache2 1 web server)"
	@echo $(C1)"  make server.real.2.start" $(END) "(start the trusted apache2 2 web server)"
	@echo $(C1)"  make server.real.3.start" $(END) "(start the trusted apache2 3 web server)"
	@echo $(C1)"  make server.real.4.start" $(END) "(start the trusted apache2 4 web server)"
	@echo ""

short-help:
	@clear
	@echo "How to use make:  (short version)" 
	@echo $(C1)"  make boot.all" 			$(END) "(start the enviroment, so, every images)"
	@echo $(C1)"  make long-help" 			$(END) "(dysplay the entire commands available)"
	@echo $(C1)"  make dns.recursive.start"	$(END) "(start the dns.recursive server)"	
	@echo ""




# Some docker commands
##### docker attach [CONTAINER ID]  ->  attach terminal to running container
##### docker rm [CONTAINER ID]  ->  remove container
##### docker rmi [IMAGE ID]  ->  remove image
