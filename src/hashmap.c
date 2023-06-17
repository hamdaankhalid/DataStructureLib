#include <hashmap.h>
#include <dynamicarray.h>

struct Pair {
	unsigned int sizeOfKey;
	unsigned int sizeOfVal;
	void* key;
	void* val;
};

int hashmapNew(struct Hashmap* hm, unsigned int sizeOfKey, unsigned int sizOfValue, int (*hasher)(int, int)) {
	hm->sizeOfKey = sizeOfKey;
	hm->sizeOfValue = sizeOfVal;
	hm->hasher = hasher;

	int success = newArray(hm->arr, sizeof (struct Pair));

	if (success != 0)
	{
		return -1;
	}
	return 0;
}

int hashmapInsert(struct Hashmap* hm, void* key, void* val){
	// hash the key
	// and insert at the index
}
