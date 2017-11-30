all: btest atest comp

gen.out:
	g++ generate.cpp -o gen.out

gen: gen.out
	./gen.out

atest: 
	g++ providedCode.cpp
	echo -e "t1.txt\nsort1.txt" | ./a.out
	echo 
	echo -e "t2.txt\nsort2.txt" | ./a.out
	echo 
	echo -e "t3.txt\nsort3.txt" | ./a.out
	echo
	echo -e "t4.txt\nsort4.txt" | ./a.out
	echo

.PHONY: atest

btest: gen
	echo -e "t1.txt\ncorrect1.txt" | ./b.out
	echo 
	echo -e "t2.txt\ncorrect2.txt" | ./b.out
	echo 
	echo -e "t3.txt\ncorrect3.txt" | ./b.out
	echo
	echo -e "t4.txt\ncorrect4.txt" | ./b.out
	echo

.PHONY: btest
	 
comp:
	diff sort1.txt correct1.txt
	diff sort2.txt correct2.txt
	diff sort3.txt correct3.txt
	diff sort4.txt correct4.txt

.PHONY: comp

