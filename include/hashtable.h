# ifndef HASHTABLE_H
# define HASHTABLE_H

# include <linkedlist.h>

# define INITIAL_HASHTABLE 31
# define OCCUPANCY_THRESHOLD 0.7

struct Hashtable {
	// buckets are an array of linkedlists
	LinkedList** buckets;
	unsigned int capacity;
	unsigned int occupied;
	int (*hasher) (void*);
};

int hashTableNew(struct Hashtable* target, unsigned int capacity, unsigned int occupied, int (*hasher) (void*));

int hashTableDestroy(struct Hashtable* table);

int hashTableSet(struct Hashtable* table, struct LinkedListNode* element);

int hashTableGet(struct Hashtable* table, void* key, struct LinkedListNode* target);

int hashTableDelete(struct Hashtable* table, void* key);

# endif