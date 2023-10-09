build:
	gcc -o quadtree main.c tema2.c
run:
	./quadtree
clean:
	rm quadtree
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./quadtree
