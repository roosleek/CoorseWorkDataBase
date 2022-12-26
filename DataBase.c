#include "DataBase.h"

List* DataBase_save(List* list) {
	char* filename = "database.txt";

	FILE* file;
	file = fopen(filename, "w+");
	// printf("File opened.\n");

	for (int i=0; i<List_count(list); i++) {
		// printf("User.\n");
		User* user = (User*)List_at(list, i);
		// User_print(user);
		fprintf(file, "%s\t%s\t%i\t%.lf\n", user->name, user->surname, user->age, user->salary);
	}

	fclose(file);
	// printf("File closed.\n");
	printf("Database saved like %s\n", filename);

	return list;
}

List* DataBase_load(List* list) {
	char* filename = "database.txt";

	FILE* file;
	file = fopen(filename, "r");
	// printf("File opened.\n");

	char name[NAME_LENGTH];
	char surname[NAME_LENGTH];
	unsigned int age;
	double salary;

	int counter = 0;

	while (fscanf(file, "%s%s%i%lf", name, surname, &age, &salary)!=-1) {
		counter++;
	}

	fseek(file, 0, 0);

	counter = 0;
	while (fscanf(file, "%s%s%i%lf", name, surname, &age, &salary)!=-1) {
		User* user = User_create(name, surname, age, salary);

		counter++;
		list = List_push(list, user);
		// User_print(user);
	}


	fclose(file);
	printf("Data uploaded from file: %s.\n", filename);

	return list;
}