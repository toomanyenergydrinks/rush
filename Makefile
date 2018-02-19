all:
	gcc main.c builtins.c -o rush
test:
	gcc test.c builtins.c -lcmocka -o test
