#include <stdio.h>
#include <linkedlist.h>

int customIntIntNodeCompare(struct LinkedListNode* a, struct LinkedListNode* b) {
	int k1 = *((int*)a->key);
	int k2 = *((int*)b->key);

	int v1 = *((int*)a->value);
	int v2 = *((int*)b->value);

	return k1==k2 && v1==v2 ? 0 : 1;
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

	
	success = linkedListAddToTail(&list, &n3);
	
	if (success != 0) {
		printf("failed to add to linked list tail \n");
		return -1;
	}
	
	linkedListForEach(&list, printIntIntNode);

	printf("Removing n2 \n");

	linkedListRemove(&list, &n2, customIntIntNodeCompare);

	linkedListForEach(&list, printIntIntNode);

	printf("Removing n1 \n");

	linkedListRemove(&list, &n1, customIntIntNodeCompare);

	linkedListForEach(&list, printIntIntNode);


	printf("Removing n1 when already not there! \n");

	linkedListRemove(&list, &n1, customIntIntNodeCompare);

	linkedListForEach(&list, printIntIntNode);

	printf("Removing n3 \n");

	linkedListRemove(&list, &n3, customIntIntNodeCompare);

	linkedListForEach(&list, printIntIntNode);

	linkedListDestroy(&list);
}
