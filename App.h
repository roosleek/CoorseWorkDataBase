#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "List.h"
#include "User.h"
#include "DataBase.h"

void App_sort_by_salary(List* list, int direction);

void App_filter_by_salary(List* list, double min_val, double max_val);

void App_filter_by_name(List* list, const char const *name);

void App_sort_by_name(List* list, int direction);

void App_deleteAllUsersFromList(List* root);

void App_printAllUserFromList(List* root);

int App_showMenu();

int App_run();

#endif