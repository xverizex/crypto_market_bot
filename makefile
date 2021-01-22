LIBS=`pkg-config libssl, openssl, json-c --cflags --libs`
PRG=sima
all: implement_huobi.o implement_binance.o interface.o main.o libs/libws/libws.so
	$(CC) $^ $(LIBS) -I libs/libws -Wl,-rpath=libs/libws -L libs/libws -lws -pthread  -o $(PRG)
implement_huobi.o: implement_huobi.c 
	$(CC) -c $^ -I libs/libws -L libs/libws -lws
implement_binance.o: implement_binance.c 
	$(CC) -c $^ -I libs/libws -L libs/libws -lws
interface.o: interface.c 
	$(CC) -c $^ -I libs/libws -L libs/libws -lws
main.o: main.c
	$(CC) -c $^
libs/libws/libws.so: 
	make -C libs/libws
clean:
	rm *.o sima libs/libws/libws.so

	