OPTS = -Wall

all: encrypt decrypt keygen ReallyLongInt.o

encrypt: encrypt.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o encryptTest encrypt.cc ReallyLongInt.o

decrypt: decrypt.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o decryptTest decrypt.cc ReallyLongInt.o

keygen: keygen.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o keygenTest keygen.cc ReallyLongInt.o

ReallyLongInt.o: ReallyLongInt.cc ReallyLongInt.h
	g++ ${OPTS} -c ReallyLongInt.cc

cleanemacs:
	rm *~
