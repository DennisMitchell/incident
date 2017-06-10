all:
	cc -Wall -std=c11 -o incident incident.c

clean:
	rm incident
