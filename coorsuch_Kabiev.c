#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// clrscr() - функция очистки консоли
void clrscr()
{
    system("@cls||clear");
}



/* ------ user ------*/
typedef struct User{
	char name[60];
	char surname[60];
	unsigned int age;
	double salary;
} User;

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
/* ------ /user ------*/



/* ------ list.h ------*/
typedef struct List {
	void* data;
	struct List* next;
} List;

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

/* ------ /list.h ------*/

/* ------ saver.h ------*/
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

	char name[60];
	char surname[60];
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
/* ------ /saver.h ------*/

/* ------ viewer.h ------*/
void Viewer_sort_by_salary(List* list, int direction){
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

void Viewer_filter_by_salary(List* list, double min_val, double max_val) {
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



void Viewer_filter_by_name(List* list, const char const *name) {
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


/* ------ /viewer.h ------*/


/* ------ app.h ------*/
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
	printf("\n!!!!!!! Menu !!!!!!!\n");
	printf("1. Print all users\n");
	printf("2. Add new user\n");
	printf("3. Delete user\n");
	printf("4. Load from DB\n");
	printf("5. Save to DB\n");
	printf("6. Exit\n");
	printf("7. Sort by salary\n");
	printf("8. Filter by salary\n");
	printf("9. Filter by name\n");
	printf("\n");
	printf("Input action [1-6]:\n");
	
	int id;
	scanf("%d", &id);
	return id;
}


/* ------ /app.h ------*/

int main(){
	// User* user1 = User_create("Vasia", "Ivanov", 25, 44);
	// User* user2 = User_create("Peter", "Sidorov", 24, 100);
	// User* user3 = User_create("Alex", "Markov", 24, 100);


	// List* root = NULL;
	// root = List_push(root, user1);
	// root = List_push(root, user2);
	// root = List_push(root, user3);

	List* root = NULL;
	// root = DataBase_load(root);

	// User_print((User*)List_at(root, 0));
	// User_print((User*)List_at(root, 1));
	// User_print((User*)List_at(root, 2));
	// User_print((User*)List_at(root, 0));
	
	// //User_print(user1);
	// //User_print(user2);
	
	// //User_delete(user1);
	// //User_delete(user2);
	
	// //User_print(user1);
	// //User_print(user2);
	
	// /*printf("%i\n", List_count(root));
	// App_printAllUserFromList(root);
	// App_deleteAllUsersFromList(root);*/
	
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
				printf("1. from min to max\n");
				printf("2. from max to min\n");

				scanf("%d", &direction);
				printf("Sorted by salary.\n");
				Viewer_sort_by_salary(root, direction);
			} break;
			case 8: {
				double min_val;
				double max_val;

				printf("Enter min value of salary:\n");
				scanf("%lf", &min_val);
				
				printf("Enter max value of salary:\n");
				scanf("%lf", &max_val);

				Viewer_filter_by_salary(root, min_val, max_val);
			} break;
			case 9: {
				char name[60];

				printf("Enter name:\n");
				scanf("%s", name);

				Viewer_filter_by_name(root, name);
			} break;
		}
	}
	
	// List* list = NULL;

	// DataBase_save(root);
	// DataBase_load(list);
	
	
	return 0;
}