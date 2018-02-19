rush:
	gcc builtins.c main.c -o rush
test:
	gcc builtins.c test.c -lcmocka -o test
