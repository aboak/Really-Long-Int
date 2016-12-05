# Really-Long-Int
Andrew Boak
CPS 222 Project 1

Files submitted:
ReallyLongInt.h
ReallyLongInt.cc
ReallyLongInt.o
numberTheory.h
keygen.cc
encrypt.cc
decrypt.cc
Makefile
Homework 1 Cover Sheet.pdf
readme.txt

This project contains one main class with many components. The
command 'make all' will compile the entire project. Alternatively, you
may compile according to the directions below.

---keygen---
To compile: make keygen
To run: ./keygenTest <prime number> <prime number> <public key file> private key file>
Description:
Keygen is a program used to generate two number keys used to encrypt a text message into a set of numbers. These numbers are used in the extended euclid function to create an encrypted version of each character. If they are not prime and under 100,000, the file does not accept the numbers, and exits the function.

---encrypt---
To compile: make encrypt
To run: ./encryptTest <public key file> <file to encrypt> <file to write to>
Description:
Encrypt takes a public file with two numbers generated from keygen.cc, and uses them to encrypt the text in the read file using the extended euclid function. It then writes each encrypted number per character into the write file, which will be used to disguise the actual contents of the message.

---decrypt---
To compile: make decrypt
To run: ./decryptTest <private key file> <encrypted file> <file to write to>
Description:
Decrypt takes a private file with the two numbers used to decrypt the file with the encrypted characters. It utilizes the mod power function and both key numbers to convert each encrypted number back into the ASCII value of the given character, which is then converted back into the string value that it started with. This character is then written into the output file, recreating the read file that was first used as an encryption message.

---ReallyLongInt.o---
To compile: make ReallyLongInt.o
To run: THIS FILE DOES NOT RUN. IT IS AN OBJECT FILE USED TO COMPILE THE OTHER THREE.
Description:
ReallyLongInt.o is an object file based on the class ReallyLongInt, which is declared in ReallyLongInt.h and defined in ReallyLongInt.cc. It allows numbers far greater than the limits of regular C++ number types would normally allow, enabling for almost any number to be used as a key for encryption. Without it, encrypt keys would be limited to at the very most 16 bits.

Known issues:

- Input prime numbers with a large amount of digits (ie. 20 digit numbers) will get caught in the decrypt method, never escaping the mod power function's recursive call.
