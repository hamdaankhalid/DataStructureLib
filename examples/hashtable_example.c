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

void printStrIntNode(struct LinkedListNode* node) {
	char* key = (char*)node->key;
	int value = *((int*)node->value);

	printf("KEY: %s, VALUE: %i \n", key, value);
}

bool customCmp(void* a, void* b) {
	return strcmp(a, b) == 0;
}

int main() {
	struct Hashtable strInttable;
	
	int init = hashTableNew(&strInttable, strHasher, customCmp, printStrIntNode);

	if (init != 0) {
		printf("Failed init of hashtable \n");
		return -1;
	}
	
	int v1 = 5;
	struct LinkedListNode n1 = { 4, sizeof(int), "abc", &v1, NULL};

	int v2 = 6;
	struct LinkedListNode n2 = { 4, sizeof(int), "cad", &v2, NULL};

	int v3 = 7;
	struct LinkedListNode n3 = { 4, sizeof(int), "cat", &v3, NULL};

	int v4 = 8;
	struct LinkedListNode n4 = { 4, sizeof(int), "bat", &v4, NULL};

	printf("Add node 1 \n");

	int result = hashTableSet(&strInttable, &n1);
	if (result != 0) {
		return -1;
	}

	printf("Add node 2 \n");
	result = hashTableSet(&strInttable, &n2);
	if (result != 0) {
		return -1;
	}

	printf("Add node 3 \n");
	result = hashTableSet(&strInttable, &n3);
	if (result != 0) {
		return -1;
	}

	printf("Add node 4 \n");
	result = hashTableSet(&strInttable, &n4);
	if (result != 0) {
		return -1;
	}

	printf("Get node 1 \n");
	struct LinkedListNode getter;
	int found = hashTableGet(&strInttable, (void *) "abc", &getter);
	if (found != 0) {
		printf("Node 1 was not found! \n");
		return -1;
	}
	printStrIntNode(&getter);

	printf("Delete node 1 \n");
	int removed = hashTableDelete(&strInttable, (void*) "abc");
	if (removed == 0) {
		printf("Delete failed!");
		return -1;
	}

	printf("node with key abc removed \n");
	
	printf("Find node 1 \n");
	found = hashTableGet(&strInttable, (void *) "abc", &getter);
	if (found == 0) {
		printf("Shouldn't find anything but it did...wtf");
		return -1;
	}
	
	printf("As expected node 1 was not found \n");

	printf("Find node 3 \n");

	found = hashTableGet(&strInttable, (void *) "cat", &getter);
	if (found != 0) {
		return -1;
	}
	printStrIntNode(&getter);

	printf("Found node 3 \n");
	
	printf("Destroy the hashtable \n");

	// free it all up
	hashTableDestroy(&strInttable);

	printf("Finished Successfully \n");
    return 0;
}
