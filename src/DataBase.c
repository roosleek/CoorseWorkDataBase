#include "DataBase.h"

List* DataBase_save(List* list) {
	char* filename = "database.txt";

	FILE* file;
	file = fopen(filename, "w+");

	for (int i=0; i<List_count(list); i++) {
		User* user = (User*)List_at(list, i);
		fprintf(file, "%s\t%s\t%i\t%.lf\n", user->name, user->surname, user->age, user->salary);
	}

	fclose(file);
	printf("Database saved like %s\n", filename);

	return list;
}

List* DataBase_load(List* list) {
	char* filename = "database.txt";

	FILE* file;
	file = fopen(filename, "r");

    User tmp_user;
	int counter = 0;

	while (fscanf(file, "%s%s%i%lf", tmp_user.name, tmp_user.surname, &tmp_user.age, &tmp_user.salary)!=-1) {
		counter++;
	}
	fseek(file, 0, 0);

	counter = 0;
	while (fscanf(file, "%s%s%i%lf", tmp_user.name, tmp_user.surname, &tmp_user.age, &tmp_user.salary)!=-1) {
		User* user = User_create(tmp_user.name, tmp_user.surname, tmp_user.age, tmp_user.salary);

		counter++;
		list = List_push(list, user);
	}

	fclose(file);
	printf("Data uploaded from file: %s.\n", filename);

	return list;
}