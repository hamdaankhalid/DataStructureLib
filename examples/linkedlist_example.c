#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <commontypes.h>
#include <linkedlist.h>


bool filterRemove(void* fixedKey, void* variableKey) {
	return strcmp((char*) fixedKey, (char*) variableKey) == 0;
}

void printIntIntNode(struct LinkedListNode* node) {
	int key = *((int*)node->key);
	int value = *((int*)node->value);

	printf("KEY: %i, VALUE: %i \n", key, value);
}

int main() {

	struct LinkedList list = {
		NULL, NULL
	};

	int k1 = 4;
	int v1 = 5;

	struct LinkedListNode n1  = {
		sizeof(int), sizeof(int),
		(void*) &k1,
		(void*) &v1,
		NULL,
	};

	int k2 = 8;
	int v2 = 9;

	struct LinkedListNode n2 = {
		sizeof(int), sizeof(int),
		(void*) &k2,
		(void*) &v2,
		NULL,
	};
	
	int k3 = 11;
	int v3 = 14;

	struct LinkedListNode n3 = {
		sizeof(int), sizeof(int),
		(void*) &k3,
		(void*) &v3,
		NULL,
	};

	int success = linkedListAddToTail(&list, &n1);
	
	if (success != 0) {
		printf("failed to add to linked list tail \n");
		return -1;
	}
	
	success = linkedListAddToTail(&list, &n2);
	
	if (success != 0) {
		printf("failed to add to linked list tail \n");
		return -1;
	}

	
	printf("%p \n", n1.next);
	success = linkedListAddToTail(&list, &n3);
	
	if (success != 0) {
		printf("failed to add to linked list tail \n");
		return -1;
	}
	
	linkedListForEach(&list, printIntIntNode);

	printf("Removing nodes via filter \n");

	struct DeleteFilterClosure filterClosure;
	filterClosure.filter = filterRemove;
	filterClosure.captured = n1.key;

	linkedListRemove(&list, &filterClosure); 

	filterClosure.captured = n2.key;
	linkedListRemove(&list, &filterClosure); 

	linkedListForEach(&list, printIntIntNode);
	
	printf("Adding n1 and n2 back \n");

	linkedListAddToTail(&list, &n1);
	linkedListAddToTail(&list, &n2);

	linkedListForEach(&list, printIntIntNode);
	
	printf("Performing pop based traversal \n");

	struct LinkedListNode* popped;
	while(!linkedListIsEmpty(&list)) {
		popped = linkedListPopLast(&list);
		printIntIntNode(popped);
		linkedListDestroyNode(popped);
	}	

	linkedListDestroy(&list);

	printf("Finished Successfully \n");
	return 0;
}
