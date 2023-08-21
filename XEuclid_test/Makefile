LDLIBS += -L.. -lcrypto
CFLAGS += -I../include/crypto

all: xeuclid_test

xeculid_test: xeuclid_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $<

clean:
	rm -f xeculid_test *.o
