#ifndef LINKEDLIST_H_
#define LINKEDLIST_H

struct LinkedListNode {
	unsigned int sizeOfKey;
	unsigned int sizeOfValue;
	void* key;
	void* value;
	struct LinkedListNode* next;
};

int linkedListAddToTail(struct LinkedListNode** head, struct LinkedListNode* node);

int linkedListRemove(struct LinkedListNode** head, struct LinkedListNode* target, int (*comparator) (struct LinkedListNode*, struct LinkedListNode*));

void linkedListDestroy(struct LinkedListNode** head);

void linkedListForEach(struct LinkedListNode** head, void (*func) (struct LinkedListNode*));

#endif 
