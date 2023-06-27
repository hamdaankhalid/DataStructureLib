#include <stdio.h>
#include <linkedlist.h>

void printIntIntNode(struct LinkedListNode* node) {
	int key = *((int*)node->key);
	int value = *((int*)node->value);

	printf("KEY: %i, VALUE: %i \n", key, value);
}

int main() {
	struct LinkedListNode *head = NULL;
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


	int success = linkedListAddToTail(&head, &n1);
	
	if (success != 0) {
		printf("failed to add to linked list tail \n");
		return -1;
	}
	
	success = linkedListAddToTail(&head, &n2);
	
	if (success != 0) {
		printf("failed to add to linked list tail \n");
		return -1;
	}
	
	linkedListForEach(&head, printIntIntNode);

	linkedListDestroy(&head);
}
