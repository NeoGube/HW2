#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
	unsigned long id;
	char* name;
	unsigned long paycheck;
	union year {
		char hyear[6];
		unsigned long nyear;
	}year;

}worker;
typedef struct WorkerList {
	worker* data;
	struct WorkerList* next;
} WorkerList;
worker* CreateWorker(int type) {
	worker* w = (worker*)malloc(sizeof(worker));
	printf("please enter your name: ");
	char* name = (char*)malloc(sizeof(char));
	scanf("%s", name);
	w->name = name;

	printf("Enter id: ");
	scanf("%d", &(w->id));

	printf("Enter paycheck: ");
	scanf("%d", &(w->paycheck));
	char d[6];
	if (type) {
		printf("Enter Hebrew year: ");
		scanf("%s", &d);
		strcpy(w->year.hyear, d);
	}
	else {
		printf("Enter numerical year: ");
		scanf("%d", &(w->year.nyear));
	}
	printf("\n");
	return(w);
}
void PrintWorker(worker* w, int type) {
	printf("name: %s\nid: %d\npaycheck: %d\n", w->name, w->id, w->paycheck);
	if (type) {
		printf("the yeas is: ");
		puts(w->year.hyear);
	}
	else {
		printf("the year is: %d", w->year.nyear);
	}
	printf("\n");
}
void PrintList(WorkerList* head, int type) {
	WorkerList* temp = head;
	while (temp != NULL) {
		PrintWorker(temp->data, type);
		temp = temp->next;
	}
	printf("\n");
}
WorkerList* addWorker(WorkerList* head, worker* w) {
	WorkerList* newList = (WorkerList*)malloc(sizeof(WorkerList));
	WorkerList* temp = head;
	newList->data = w;
	newList->next = NULL;
	if (head == NULL) {
		head = newList;
		return newList;
	}
	if (head->data->paycheck < w->paycheck) {
		newList->next = head;
		head = newList;
		return head;
	}
	while (temp != NULL) {
		if (w->paycheck > temp->data->paycheck) {
			newList->next = temp->next;
			temp->next = newList;
			return head;
		}
		temp = temp->next;
	}
	return head;
}
int Index(WorkerList* head, unsigned long id) {
	int count = 1;
	WorkerList* temp = head;
	if (head == NULL) return -1;
	while (temp != NULL) {
		if (temp->data->id == id) return count;
		count++;
		temp = temp->next;
	}
	return -1;
	printf("\n");
}
int IndexRec(WorkerList* head, unsigned long id, int count) {
	if (head == NULL) return -1;
	if (head->data->id == id) return count;
	return IndexRec(head->next, id, ++count);
}
void update_worker(WorkerList* head, float percent) {
	if (head == NULL) return;
	head->data->paycheck *= (1 + percent * 0.01);
	return(head->next, percent);
}
WorkerList* deleteWorstWorker(WorkerList* head) {
	if (head == NULL) {
		printf("There are no workers to delete");
		return head;
	}
	WorkerList* temp = head;
	int minimum = temp->data->paycheck;
	while (temp != NULL) {
		minimum = min(minimum, temp->data->paycheck);
		temp = temp->next;
	}
	temp = head;
	while (temp->next->data->paycheck != minimum) {
		temp = temp->next;
	}
	WorkerList* delete = temp->next;
	temp->next = delete->next;
	free(delete);
	return head;
}

WorkerList* reverse(WorkerList* head) {
	if (head == NULL || head->next == NULL) return head;
	WorkerList* temp = head;
	head = head->next;
	temp->next = NULL;
	while (head->next != NULL) {
		WorkerList* current = head;
		head = head->next;
		current->next = temp;
		temp = current;
	}
	head->next = temp;
	return head;
}

void freeWorkers(WorkerList* head) {
	if (head == NULL) return;
	while (head != NULL) {
		WorkerList* temp = head;
		head = head->next;
		free(temp);
	}
}
void main() {
	int type;
	printf("Press 1 for hebrew year and 0 for numeric year: ");
	scanf("%d", &type);
	system("cls");
	worker* worker1 = CreateWorker(type);
	system("cls");
	worker* worker2 = CreateWorker(type);
	system("cls");
	worker* worker3 = CreateWorker(type);
	system("cls");
	worker* worker4 = CreateWorker(type);
	system("cls");
	WorkerList* head = (WorkerList*)malloc(sizeof(WorkerList));
	head = NULL;
	head = addWorker(head, worker1);
	head = addWorker(head, worker2);
	head = addWorker(head, worker3);
	head = addWorker(head, worker4);
	printf("The worker with the id 123 is number: %d\n", Index(head, 123));
	printf("The worker with the id 123 is number: %d\n", IndexRec(head, 123, 1));
	update_worker(head, 100);
	PrintList(head, type);
	PrintList(reverse(head), type);
}