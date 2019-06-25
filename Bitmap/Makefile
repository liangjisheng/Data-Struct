bitmap: bitmap.o bitmap_test.o
	g++ bitmap.o bitmap_test.o -o bitmap

bitmap.o: bitmap.h bitmap.cpp
	g++ -c bitmap.cpp

bitmap_test.o: bitmap.h bitmap_test.cpp
	g++ -c bitmap_test.cpp

run:
	@./bitmap
	
.PHONY:clean
clean:
	@- rm *.o bitmap