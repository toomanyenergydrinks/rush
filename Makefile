rush:
	gcc history.c builtins.c main.c -ggdb -o rush
test:
	gcc builtins.c test.c -lcmocka -o test
