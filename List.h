#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct List {
	void* data;
	struct List* next;
} List;

List* List_push(List* root, void* data);

List* List_delete(List* root, int id);

List* List_at(List* root, int id);

int List_count(List* root);

#endif