#include "List.h"

List* List_push(List* root, void* data){
	if (root==NULL) {
		List* list = (List*)malloc(sizeof(List));
		list->data = data;
		list->next = NULL;
		
		return list; 
	}
	List* current = root;
	while (current->next != NULL) {
		current = current->next;
	}

	List* list = (List*)malloc(sizeof(List));
	list->data = data;
	list->next = NULL;
	current->next = list;
	
	return root;
}

List* List_delete(List* root, int id) {
	if (id == 0) {
		List* next = root->next;
		free(root);
		return next;
	}
	
	List* current = root;
	List* prev = current;
	
	int i=0;
	
	while (current){
		if (i==id) {
			prev->next = current->next;
			free(current);
			return root;
		};
		prev = current;
		current = current->next;
		i++;
	}
	
	return root;
}

List* List_at(List* root, int id) {
	List* current = root;
	int i=0;
	
	while (current){
		if (i==id) return current->data;
		current = current->next;
		i++;
	}
	return NULL;
}

int List_count(List* root) {
	List* current = root;
	int i = 0;
	
	while (current != NULL){
		current = current->next;
		i++;
	}
	return i;
}