#include <stdio.h>
#include <linkedlist.h>
#include <stdlib.h>
#include <string.h>

// this method expects the user to have allocated the memory for the node on stack.
int linkedListAddToTail(struct LinkedListNode **head, struct LinkedListNode *node) {
    struct LinkedListNode* newNode = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Error allocating memory for new node to linkedlist\n");
        return -1;
    }

    // Copy data from node to newNode
    newNode->key = node->key;
    newNode->value = node->value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return 0;
    }

    struct LinkedListNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return 0;
}

int linkedListRemove(struct LinkedListNode** head, struct LinkedListNode* target, int (*comparator) (struct LinkedListNode*, struct LinkedListNode*)) {
	// iterater till you find the target while keeping track of previous and current.
	struct LinkedListNode* previous = NULL;
	struct LinkedListNode* current = *head;
	
	while(current != NULL || comparator(current, target) != 0) {
		previous = current;
		current = current->next;	
	}

	if (current == NULL) 
	{
		printf("target node not found \n");
		return -1;
	}

	if (previous == NULL) {
		struct LinkedListNode* newHead = current->next;
		free(current);
		*head = newHead;
		return 0;
	}

	struct LinkedListNode* afterTarget = current->next;	
	free(current);
	previous->next = afterTarget;
	return 0;	
}

void destroyNode(struct LinkedListNode* node) {
	free(node);
}

void linkedListDestroy(struct LinkedListNode** head) {
	// each node is allocated and stored on the heap, we must go through the linked list destorying
	// each of the nodes
	linkedListForEach(head, destroyNode);
}

void linkedListForEach(struct LinkedListNode **head, void (*func)(struct LinkedListNode *)) {
	struct LinkedListNode* current = *head;
	while(current != NULL) {
		struct LinkedListNode* nxt = current->next;
		func(current);
		current = nxt;
	}
}
