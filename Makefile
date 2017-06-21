CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi selsc.cgi coradd.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./.gitinore/*.cgi
install:
		sudo cp ./index.html /var/www/html/
		mv *.cgi  ./.gitinore
		cp ./.gitinore/*.cgi /usr/lib/cgi-bin/sx
