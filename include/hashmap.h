#ifndef HASHMAP_H 
#define HASHMAP_H

#include <dynamicarray.h>

struct Hashmap {
    unsigned int sizeOfKey;
	unsigned int sizOfValue;
	struct DynamicArray* arr;
};

int hashmapNew(struct Hashmap* hm, unsigned int sizeOfKey, unsigned int sizOfValue);

int hashmapInsert(struct Hashmap* hm, void* key, void* val);

int hashmapRemove(struct Hashmap* hm, void* key);

int hashmapGet(struct Hashmap* hm, void* val);

#endif 
