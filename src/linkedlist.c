#include <stdio.h>
#include <linkedlist.h>
#include <stdlib.h>
#include <string.h>

# define EXIT_IF_MALLOC_FAIL(d) \
	if (d == NULL) { \
        fprintf(stderr, "Error allocating memory for new node to linkedlist\n"); \
        return -1; \
	}

void destroyNode(struct LinkedListNode* node) {
	free(node->key);
	free(node->value);
	free(node);
}

// this method expects the user to have allocated the memory for the node on stack.
int linkedListAddToTail(struct LinkedList* list, struct LinkedListNode *node) {
    struct LinkedListNode* newNode = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
	EXIT_IF_MALLOC_FAIL(newNode);

	newNode->key = malloc(node->sizeOfKey);
	EXIT_IF_MALLOC_FAIL(newNode->key);

	newNode->value= malloc(node->sizeOfValue);
	EXIT_IF_MALLOC_FAIL(newNode->value);

    // Copy data from node to newNode
    memcpy(newNode->key,node->key, node->sizeOfKey);
    memcpy(newNode->value,node->value, node->sizeOfValue);

	newNode->sizeOfKey = node->sizeOfKey;
	newNode->sizeOfValue = node->sizeOfValue;
    newNode->next = NULL;

    if (list->head == NULL) {
		printf("first node added as head and tail \n");
        list->head = newNode;
		list->tail = newNode;
        return 0;
    }

	list->tail->next = newNode;
	list->tail = newNode;

    return 0;
}

int linkedListRemove(struct LinkedList* list, struct LinkedListNode* target, int (*comparator) (struct LinkedListNode*, struct LinkedListNode*)) {
	// iterate till you find the target while keeping track of previous and current.
	struct LinkedListNode* previous = NULL;
	struct LinkedListNode* current = list->head;
	
	while(current != NULL && comparator(current, target) != 0) {
		previous = current;
		current = current->next;	
	}

	// completed iteration without target
	if (current == NULL) {
		printf("target node not found \n");
		return -1;
	}
	
	// removing the head when only one node in list
	if (previous == NULL && current == list->tail) {
			destroyNode(current);
			list->tail = NULL;
			list->head = NULL; 
			printf("single node list, node removed successfully \n");

			return 0;
	}

	// removing the first node but more than one node exists
	if (previous == NULL) {
		struct LinkedListNode* newHead = current->next;
		destroyNode(current);
		list->head = newHead; 
		printf("target node was the head of list, successfully removed \n");
		return 0;
	}

	struct LinkedListNode* afterTarget = current->next;	
	// removing the last node
	if (current == list->tail) {
		list->tail = afterTarget;
	}

	destroyNode(current);
	previous->next = afterTarget;
	printf("target node successfully removed \n");
	return 0;	
}

void linkedListDestroy(struct LinkedList* list) {
	// each node is allocated and stored on the heap, we must go through the linked list destorying
	// each of the nodes
	linkedListForEach(list, destroyNode);
	list->head = NULL;
	list->tail = NULL;
}

void linkedListForEach(struct LinkedList* list, void (*func)(struct LinkedListNode *)) {
	struct LinkedListNode* current = list->head;
	while(current != NULL) {
		struct LinkedListNode* nxt = current->next;
		func(current);
		current = nxt;
	}
}
