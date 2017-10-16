md5: md5.c
	gcc md5.c -std=c11 -O3 -o md5

debug: md5.c
	gcc md5.c -std=c11 -g -o md5

clean:
	rm md5