#ifndef IO_H
#define IO_H

unsigned char insb(unsigned short port);            // Outputting 1 byte to port
unsigned short insw(unsigned short port);           // Outputting 2 bytes to port

void outb(unsigned short port, unsigned char val);  // Outputting 1 byte to port
void outw(unsigned short port, unsigned short val); // Outputting 2 bytes to port

#endif