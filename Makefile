run:
	cc main.c -o echo && ./echo -ne "Hello\nWorld"

test:
	./test.sh