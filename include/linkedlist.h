#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

struct LinkedListNode {
	unsigned int sizeOfKey;
	unsigned int sizeOfValue;
	void* key;
	void* value;
	struct LinkedListNode* next;
};

// During initialization the user may set the 2 pointers
// to null. The first call to linkedListAddToTail will take care of setting them to addresses on the heap
struct LinkedList {
	struct LinkedListNode* head;
	struct LinkedListNode* tail;
};

// the invoker may provide a node that was allocated on theap or on the stack. The node is then copied into a new block on the heap.
// the invoker may then choose to do whatever with the node that was passed in -> i.e. free it
int linkedListAddToTail(struct LinkedList* list, struct LinkedListNode* node);

// The method is used to remove a linkedlist element if you already know the data in it.
int linkedListRemove(struct LinkedList* list, struct LinkedListNode* target, int (*comparator) (struct LinkedListNode*, struct LinkedListNode*));

// destroys only the internal data, the invoker frees the list if on heap.
// If not on heap, we let the stack take care of it.
void linkedListDestroy(struct LinkedList* list);

// function for performing side-effects on each element such as printing
void linkedListForEach(struct LinkedList* list, void (*func) (struct LinkedListNode*));

bool linkedListIsEmpty(struct LinkedList* list);

struct LinkedListNode* linkedListPopLast(struct LinkedList* list);

void linkedListDestroyNode(struct LinkedListNode* node);

#endif 
