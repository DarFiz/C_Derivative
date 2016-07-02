exec: funkcjePomocnicze.c  funkcjeWyzszegorzedu.c  main.c
	gcc -g funkcjePomocnicze.c  funkcjeWyzszegorzedu.c  main.c -o exec
run:
	./exec
clean:
	rm exec
.PHONY: exec
