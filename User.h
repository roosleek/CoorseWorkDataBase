#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LENGTH 60


typedef struct User{
	char name[NAME_LENGTH];
	char surname[NAME_LENGTH];
	unsigned int age;
	double salary;
} User;

void User_fill(User* user, char* name, char* surname, int age, double salary);

User* User_create(char* name, char* surname, int age, double salary);

void User_delete(User* user);

void User_print(const User* const user);

#endif