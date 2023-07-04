# ifndef HASHTABLE_H
# define HASHTABLE_H

# include "linkedlist.h"

# define INITIAL_HASHTABLE 31
# define OCCUPANCY_THRESHOLD 0.7

struct Hashtable {
	// buckets are an array of linkedlists
	struct LinkedList** buckets;
	unsigned int capacity;
	unsigned int occupied;
	struct DeleteFilterClosure* deleteClosure;
	int (*hasher) (void*);
	bool (*comparer) (struct LinkedListNode*, struct LinkedListNode*); // create a function that can compare 2 keys and returns 0 if equal, and -1 if not
};

int hashTableNew(struct Hashtable* target, int (*hasher) (void*), bool(*comparer) (void*, void*));

int hashTableDestroy(struct Hashtable* table);

int hashTableSet(struct Hashtable* table, struct LinkedListNode* element);

int hashTableGet(struct Hashtable* table, void* key, struct LinkedListNode* target);

int hashTableDelete(struct Hashtable* table, void* key);

# endif
