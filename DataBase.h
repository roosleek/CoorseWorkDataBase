#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "List.h"
#include "User.h"


List* DataBase_save(List* list);

List* DataBase_load(List* list);

#endif