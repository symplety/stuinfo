CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi selsc.cgi coradd.cgi scoreadd.cgi schooladd.cgi delornot.cgi rest.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./.gitinore/*.cgi
install:
		sudo cp *.html /var/www/html/
		mv *.cgi  ./.gitinore
		cp ./.gitinore/*.cgi /usr/lib/cgi-bin/sx
		cp *.html  /usr/lib/cgi-bin/sx
