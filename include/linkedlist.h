#ifndef LINKEDLIST_H_
#define LINKEDLIST_H

struct LinkedListNode {
	unsigned int sizeOfKey;
	unsigned int sizeOfValue;
	void* key;
	void* value;
	struct LinkedListNode* next;
};

struct LinkedList {
	struct LinkedListNode* head;
	struct LinkedListNode* tail;
};

int linkedListAddToTail(struct LinkedList* list, struct LinkedListNode* node);

int linkedListRemove(struct LinkedList* list, struct LinkedListNode* target, int (*comparator) (struct LinkedListNode*, struct LinkedListNode*));

void linkedListDestroy(struct LinkedList* list);

void linkedListForEach(struct LinkedList* list, void (*func) (struct LinkedListNode*));

#endif 
