#ifndef DISK_H
#define DISK_H

typedef unsigned int NN_OS_DISK_TYPE;


// Represents a real physical hard disk
#define NN_OS_DISK_TYPE_REAL 0

struct disk
{
    NN_OS_DISK_TYPE type;
    int sector_size;
};

void disk_search_and_init();
struct disk* disk_get(int index);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);

#endif