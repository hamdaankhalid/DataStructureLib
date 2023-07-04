#include <stdio.h>
#include <linkedlist.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <commontypes.h>

void linkedListDestroyNode(struct LinkedListNode* node) {
	free(node->key);
	free(node->value);
	free(node);
}

bool linkedListIsEmpty(struct LinkedList* list) {
	return list->head == NULL;
}

struct LinkedListNode* linkedListPopLast(struct LinkedList* list) {
	struct LinkedListNode* previous = NULL;
	struct LinkedListNode* current = list->head;	

	if (current == NULL) {
		return NULL;
	}

	while (current->next != NULL) {
		previous = current;
		current = current->next;
	}
	
	if (previous == NULL) {
		list->head = NULL;	
	} else {
		previous->next = NULL;
	}

	list->tail = previous;
	return current;
}


// this method expects the user to have allocated the memory for the node on stack.
int linkedListAddToTail(struct LinkedList* list, struct LinkedListNode *node) {
    struct LinkedListNode* newNode = malloc(sizeof(struct LinkedListNode));
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
	
	printf("non-head node added \n");

	list->tail->next = newNode;
	list->tail = newNode;

    return 0;
}

int linkedListRemove(struct LinkedList* list, struct DeleteFilterClosure* filterClosure) { 
	// iterate till you find the target while keeping track of previous and current.
	struct LinkedListNode* previous = NULL;
	struct LinkedListNode* current = list->head;
	
	int removed = 0;
	while (current != NULL) {
		if (filterClosure->filter(filterClosure->captured, current->key)) {
			// handle the removal of current node
			struct LinkedListNode* next = current->next;
			if (previous != NULL) {
				previous->next = next;
			} else {
				list->head = next;
			}

			if (current->next == NULL) {
				list->tail = previous;
			}

			linkedListDestroyNode(current);
			removed++;
			current = next;
		} else {
			previous = current;
			current = current->next;	
		}
	}
	
	// return number of nodes removed
	return removed;
}

void linkedListDestroy(struct LinkedList* list) {
	// each node is allocated and stored on the heap, we must go through the linked list destorying
	// each of the nodes
	linkedListForEach(list, linkedListDestroyNode);
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
