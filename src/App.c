#include "App.h"

// clrscr() - функция очистки консоли
void clrscr()
{
    system("@cls||clear");
}

void App_sort_by_salary(List* list, int direction){
	int total_users = List_count(list);

	int order[total_users];
	int order_rev[total_users];
	double salaries[total_users];

	int tmp_order;
	double tmp_salary;

	for (int i=0; i<total_users; i++) {
		User* user = (User*)List_at(list, i);
		order[i] = i;
		salaries[i] = user->salary;
	}

    for (int i = 0; i < total_users; i++) {   
        for (int j = 0; j < total_users - i - 1; j++) { 
            if (salaries[j] > salaries[j + 1]) {  
                tmp_salary = salaries[j];
                salaries[j] = salaries[j + 1];
                salaries[j + 1] = tmp_salary;

                tmp_order = order[j];
                order[j] = order[j + 1];
                order[j + 1] = tmp_order;
            }
        }
    }
	User* pUsers = (User*) malloc(sizeof(User)*total_users);
	if (direction==2) {
		for (int i=0; i<total_users; i++) {
			order_rev[total_users-i-1]=order[i];
		}
		for (int i=0; i<total_users; i++) {
			order[i]=order_rev[i];
		}
	}

	for (int i=0; i<total_users; i++){
		User* user = (User*)List_at(list, order[i]);
		strcpy(pUsers[i].name, user->name);
		strcpy(pUsers[i].surname, user->surname);
		pUsers[i].age = user->age;
		pUsers[i].salary = user->salary;
	}
	
	for (int i=0; i<total_users; i++){
		User* user = (User*)List_at(list, i);
		strcpy(user->name, pUsers[i].name);
		strcpy(user->surname, pUsers[i].surname);
		user->age = pUsers[i].age;
		user->salary = pUsers[i].salary;
	}

	free(pUsers);
}

void App_filter_by_salary(List* list, double min_val, double max_val) {
	int total_users = List_count(list);
	printf("+---------------+---------------+---------------+---------------+\n");
	printf("|      id       |     name      |      age      |     salary    |\n");
	printf("+---------------+---------------+---------------+---------------+\n");
	
	for (int i=0; i<List_count(list); i++){
		User* user = (User*)List_at(list, i);

		if ((user->salary >= min_val) && (user->salary <=max_val)) {
			printf("|%15i|%15s|%15i|%15.lf|\n", i, user->name, user->age, user->salary);
			printf("+---------------+---------------+---------------+---------------+\n");
		}
	}
	printf("\n");
}


void App_filter_by_name(List* list, const char const *name) {
	int total_users = List_count(list);
	printf("+---------------+---------------+---------------+---------------+\n");
	printf("|      id       |     name      |      age      |     salary    |\n");
	printf("+---------------+---------------+---------------+---------------+\n");
	
	int len = 0;
	while (name[len] != '\0'){
		len++;
	}

	int flag;
	for (int i=0; i<List_count(list); i++){
		User* user = (User*)List_at(list, i);
		flag = 1;

		for (int j=0; j<len; j++){
			if (user->name[j] != name[j]) {
				flag = 0;
				break;
			}
		}

		if (flag) {
			printf("|%15i|%15s|%15i|%15.lf|\n", i, user->name, user->age, user->salary);
			printf("+---------------+---------------+---------------+---------------+\n");
		}
	}
	printf("\n");
}

void App_sort_by_name(List* list, int direction){
	int total_users = List_count(list);

	int order[total_users];
	int order_rev[total_users];
	char names[total_users][NAME_LENGTH];

	int tmp_order;
	char tmp_name[NAME_LENGTH];

	for (int i=0; i<total_users; i++) {
		User* user = (User*)List_at(list, i);
		order[i] = i;
		strcpy(&names[i][0], user->name);
	}

    for (int i = 0; i < total_users; i++) {   
        for (int j = 0; j < total_users - i - 1; j++) { 
			for (int k = 0; k < NAME_LENGTH-1; k++) {
				if ((names[j][k] < names[j+1][k]) || (names[j][k]=='\0')) {
					break;
				}
				if ((names[j][k] > names[j+1][k]) || (names[j+1][k]=='\0')){  					
					strcpy(tmp_name, &names[j][0]);
					strcpy(&names[j][0], &names[j+1][0]);
					strcpy(&names[j+1][0], tmp_name);

					tmp_order = order[j];
					order[j] = order[j + 1];
					order[j + 1] = tmp_order;
					break;
				}
			}
        }
    }
	User* pUsers = (User*) malloc(sizeof(User)*total_users);
	if (direction==2) {
		for (int i=0; i<total_users; i++) {
			order_rev[total_users-i-1]=order[i];
		}
		for (int i=0; i<total_users; i++) {
			order[i]=order_rev[i];
		}
	}

	for (int i=0; i<total_users; i++){
		User* user = (User*)List_at(list, order[i]);
		strcpy(pUsers[i].name, user->name);
		strcpy(pUsers[i].surname, user->surname);
		pUsers[i].age = user->age;
		pUsers[i].salary = user->salary;
	}
	
	for (int i=0; i<total_users; i++){
		User* user = (User*)List_at(list, i);
		strcpy(user->name, pUsers[i].name);
		strcpy(user->surname, pUsers[i].surname);
		user->age = pUsers[i].age;
		user->salary = pUsers[i].salary;
	}

	free(pUsers);
}

void App_deleteAllUsersFromList(List* root) {
	for (int i=List_count(root)-1; i>=0; i--){
		User* user = (User*)List_at(root, i);

		printf("%.1d) %s deleted\n", i, user->name);
		User_delete(user);
		root = List_delete(root, i);
	}
}

void App_printAllUserFromList(List* root) {
	printf("+---------------+---------------+---------------+---------------+\n");
	printf("|      id       |     name      |      age      |     salary    |\n");
	printf("+---------------+---------------+---------------+---------------+\n");
	
	for (int i=0; i<List_count(root); i++){
		User* user = (User*)List_at(root, i);

		printf("|%15i|%15s|%15i|%15.lf|\n", i, user->name, user->age, user->salary);
		printf("+---------------+---------------+---------------+---------------+\n");
	}
	printf("\n");
}

int App_showMenu() {
	printf("\n---------    Menu     ---------\n");
	printf("[1] Print all users\n");
	printf("[2] Add new user\n");
	printf("[3] Delete user\n");
	printf("[4] Load from DB\n");
	printf("[5] Save to DB\n");
	printf("[6] Exit\n");
	printf("[7] Sort by salary\n");
	printf("[8] Filter by salary\n");
	printf("[9] Filter by name\n");
	printf("[10] Sort by name\n");
	printf("\n");
	printf("Input action [1-10]:\n");
	printf("\n-------------------------------\n");
	int id;
	scanf("%d", &id);
	return id;
}

int App_run() {
    clrscr();
	List* root = NULL;
	int action = 0;
	
	while (action!=6) {
		action = App_showMenu();
		clrscr();
		
		switch(action) {
			case 1: {
				App_printAllUserFromList(root);
			} break;

			case 2: {
				User tmp;
				
				printf("Input user name: ");
				scanf("%s", tmp.name);
			
				printf("Input user surname: ");
				scanf("%s", tmp.surname);
				
				printf("Input user age: ");
				scanf("%d", &tmp.age);
				
				printf("Input user salary: ");
				scanf("%lf", &tmp.salary);
				
				root = List_push(root, User_create(tmp.name, tmp.surname, tmp.age, tmp.salary));
			} break;

			case 3: {
				int id;
				
				printf("Input user id: ");
				scanf("%d", &id);
				
				User_delete((User*)List_at(root, id));
				root = List_delete(root, id);
			} break;

			case 4: {
				root = DataBase_load(root);
			} break;

			case 5: {
				root = DataBase_save(root);
			} break;

			case 7: {
				int direction;
				printf("[1] From min to max\n");
				printf("[2] From max to min\n");
				scanf("%d", &direction);

				printf("Sorted by salary.\n");
				App_sort_by_salary(root, direction);
			} break;

			case 8: {
				double min_val;
				double max_val;

				printf("Enter min value of salary:\n");
				scanf("%lf", &min_val);
				
				printf("Enter max value of salary:\n");
				scanf("%lf", &max_val);

				App_filter_by_salary(root, min_val, max_val);
			} break;
            
			case 9: {
				char name[NAME_LENGTH];

				printf("Enter name:\n");
				scanf("%s", name);

				App_filter_by_name(root, name);
			} break;

			case 10: {
				int direction;
				printf("[1] From min to max\n");
				printf("[2] From max to min\n");
				scanf("%d", &direction);

				printf("Sorted by name.\n");
				App_sort_by_name(root, direction);
			} break;
		}
	}
    App_deleteAllUsersFromList(root);
    clrscr();
    
    return 0;
}