#include "User.h"

void User_fill(User* user, char* name, char* surname, int age, double salary){
	if (user == NULL) return;
	strcpy(user->name, name);
	strcpy(user->surname, surname);
	user->age = age;
	user->salary = salary;
}

User* User_create(char* name, char* surname, int age, double salary){
	User* user = (User*)malloc(sizeof(User));
	User_fill(user, name, surname, age, salary);
	
	return user;
}

void User_delete(User* user){
	if (user == NULL) return;
	free(user);		
}

void User_print(const User* const user){
	if (user==NULL) return;
	printf("%s %s:\nage: %d\nsalary: %.f\n\n", user->surname, user->name, user->age, user->salary);
}
