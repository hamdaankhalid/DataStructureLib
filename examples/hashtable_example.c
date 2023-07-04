#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <commontypes.h>
# include <hashtable.h>

// djb2 Algorithm
int strHasher(void* input) {
	const char* str = input;
	int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

	return hash;
}

bool customCmp(void* a, void* b) {
	return strcmp(a, b) == 0;
}

void printStrIntNode(struct LinkedListNode node) {
	printf("KEY: %s, VALUE: %d \n", (char*) node.key, *(int*)node.value);
}

int main() {
	struct Hashtable strInttable;
	
	int init = hashTableNew(&strInttable, strHasher, customCmp);

	if (init != 0) {
		printf("Failed init of hashtable \n");
		return -1;
	}
	
	int v1 = 5;
	struct LinkedListNode n1 = { 3, sizeof(int), "abc", &v1, NULL};

	int v2 = 6;
	struct LinkedListNode n2 = { 3, sizeof(int), "cad", &v2, NULL};

	int v3 = 7;
	struct LinkedListNode n3 = { 3, sizeof(int), "cat", &v3, NULL};

	int v4 = 8;
	struct LinkedListNode n4 = { 3, sizeof(int), "bat", &v4, NULL};

	int result = hashTableSet(&strInttable, &n1);
	if (result != 0) {
		return -1;
	}

	result = hashTableSet(&strInttable, &n2);
	if (result != 0) {
		return -1;
	}

	result = hashTableSet(&strInttable, &n3);
	if (result != 0) {
		return -1;
	}

	result = hashTableSet(&strInttable, &n4);
	if (result != 0) {
		return -1;
	}

	struct LinkedListNode getter;
	int found = hashTableGet(&strInttable, (void *) "abc", &getter);
	if (found != 0) {
		return -1;
	}
	printStrIntNode(getter);
	
	int removed = hashTableDelete(&strInttable, (void*) "abc");
	if (removed == 0) {
		printf("Delete failed!");
		return -1;
	}

	printf("node with key abc removed \n");
	
	found = hashTableGet(&strInttable, (void *) "abc", &getter);
	if (found == 0) {
		printf("Shouldn't find anything but it did...wtf");
		return -1;
	}
	
	found = hashTableGet(&strInttable, (void *) "cat", &getter);
	if (found != 0) {
		return -1;
	}
	printStrIntNode(getter);

	// free it all up
	hashTableDestroy(&strInttable);

	printf("Successfully finished \n");
}
