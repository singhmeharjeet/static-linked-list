#include <string.h>

#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void myFree(void* pItem) {

}
bool intCompare(void* pItem, void* pComparisonArg) {
	return *(int*)pItem == *(int*)pComparisonArg ? 1 : 0;
}

bool test_create() {
	List* pList = List_create();
	assert(pList != NULL);
	assert(pList->head == NULL);
	assert(pList->tail == NULL);
	assert(pList->currentItem == NULL);
	assert(pList->numItems == 0);
	assert(pList->OOB == LIST_OOB_START);
	List_free(pList, myFree);
	return true;
}
bool test_free() {
	List* pList = List_create();
	List* pList2 = List_create();
	List* pList3 = List_create();
	List* pList4 = List_create();
	List* pList5 = List_create();
	List* pList6= List_create();
	List* pList7= List_create();
	List* pList8= List_create();
	List* pList9= List_create();
	List* pList10= List_create();
	List* pList11= List_create();
	List_free(pList10, NULL);
	List* pList12 = List_create();
	if (pList12 !=NULL) {
		List_free(pList, NULL);
		List_free(pList2, NULL);
		List_free(pList3, NULL);
		List_free(pList4, NULL);
		List_free(pList5, NULL);
		List_free(pList6, NULL);
		List_free(pList7, NULL);
		List_free(pList8, NULL);
		List_free(pList9, NULL);
		List_free(pList10, NULL);
		List_free(pList12, NULL);
		return true;
	}
	return false;
}
bool test_free_with_data() {
	List* pList = List_create();
	List_append(pList, "Hello");
	List_append(pList, "Hello");
	List_append(pList, "Hello");
	if (List_count(pList) == 3) {
		List_free(pList, myFree);
	}
	if(List_count(pList) == 0) {
		return true;
	}
	return false;
}
bool test_double_free() {
	List* pList = List_create();
	List_free(pList, NULL);
	List_free(pList, NULL);

	List *pList2 = List_create();
	if (pList2 == pList) {
		// success
		List_free(pList2, NULL);
		return true;
	}
	return false;
}
bool test_append() {
	List* pList = List_create();
	List_append(pList, "hello");

	if (strcmp(List_curr(pList), "hello") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}

}
bool test_append_check_head() {
	List* pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	if (strcmp(List_first(pList), "hello") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_append_check_tail() {
	List* pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	if (strcmp(List_last(pList), "hello3") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_append_many() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello");
	List_append(pList, "hello3");

	List_last(pList);
	if (strcmp(List_curr(pList), "hello3") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}

}
bool test_count() {
	List* pList = List_create();

	if (List_count(pList) != 0) {
		return false;
	}

	List_append(pList, "hello");
	if (List_count(pList) != 1) {
		return false;
	}
	List_remove(pList);
	if (List_count(pList) != 0) {
		return false;
	}

	List_free(pList, NULL);
	pList = NULL;

	return true;
}
bool test_remove() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_remove(pList);
	if (List_count(pList) == 3 && strcmp(List_last(pList), "hello3") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_remove_many() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_remove(pList);
	List_last(pList);
	List_remove(pList);
	List_last(pList);
	List_remove(pList);
	if (List_count(pList) == 1 && strcmp(List_last(pList), "hello") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_remove_extra() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_remove(pList);
	List_first(pList);
	List_remove(pList);
	List_remove(pList);
	List_remove(pList);
	List_remove(pList);
	List_remove(pList);
	List_remove(pList);
	if (List_count(pList) == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_insert_after_OOB_START() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_first(pList);
	List_prev(pList);
	List_insert_after(pList, "hello5");
	if (strcmp(List_first(pList), "hello5") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_insert_after_OOB_END() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_last(pList);
	List_next(pList);
	List_insert_after(pList, "hello5");
	if (strcmp(List_last(pList), "hello5") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_insert_before_OOB_START() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_first(pList);
	List_prev(pList);
	List_insert_before(pList, "hello5");
	if (strcmp(List_first(pList), "hello5") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_insert_before_OOB_END() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_last(pList);
	List_next(pList);
	List_insert_before(pList, "hello5");
	if (strcmp(List_last(pList), "hello5") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_insert_before_MIDDLE() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_append(pList, "hello4");
	List_first(pList);
	List_next(pList);
	List_insert_before(pList, "hello5");
	if (strcmp(List_curr(pList), "hello5") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_prepend() {
	List *pList = List_create();
	List_prepend(pList, "hello");
	List_prepend(pList, "hello2");
	if (strcmp(List_first(pList), "hello2") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_prev_empty() {
	List *pList = List_create();
	List_prev(pList);
	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_prev_OOB_START() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_prev(pList);

	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_prev_OOB_START_many() {
	List *pList = List_create();

	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_prev(pList);
	List_prev(pList);
	List_prev(pList);
	List_prev(pList);
	List_prev(pList);
	List_prev(pList);
	List_prev(pList);

	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_next_empty() {
	List *pList = List_create();
	List_next(pList);
	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_prev_OOB_END() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_next(pList);

	List_prev(pList);

	if (List_curr(pList) == List_last(pList)) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_next_OOB_START() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_first(pList);
	List_prev(pList);
	List_next(pList);

	if (List_curr(pList) == List_first(pList)) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_next_OOB_END() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_next(pList);

	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_first_empty() {
	List *pList = List_create();
	List_first(pList);
	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_first() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_first(pList);
	if (strcmp(List_curr(pList), "hello") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_last_empty() {
	List *pList = List_create();
	List_last(pList);
	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_last() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_last(pList);
	if (strcmp(List_curr(pList), "hello3") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_trim() {
	List *pList = List_create();
	List_append(pList, "hello");
	List_append(pList, "hello2");
	List_append(pList, "hello3");
	List_trim(pList);
	if (strcmp(List_last(pList), "hello2") == 0) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_trim_empty() {
	List *pList = List_create();
	List_trim(pList);
	if (List_curr(pList) == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_concat() {
	List* pList1 = List_create();
	List* pList2 = List_create();
	List_append(pList1, "hello");
	List_append(pList1, "hello2");
	List_append(pList1, "hello3");

	List_append(pList2, "hello4");
	List_append(pList2, "hello5");
	List_append(pList2, "hello6");

	List_concat(pList1, pList2);

	if (List_count(pList1) == 6) {
		List_free(pList1, myFree);
		return true;
	}
	else {
		List_free(pList1, myFree);
		return false;
	}
}
bool test_search_fail() {
	List* pList = List_create();
	int *x = malloc(sizeof(int));
	int *y = malloc(sizeof(int));
	int *z = malloc(sizeof(int));

	List_append(pList, &x);
	List_append(pList, &y);

	void* found = List_search(pList, intCompare, &z);

	free(x);
	free(y);
	free(z);

	if (found == NULL) {
		List_free(pList, myFree);
		return true;
	}
	else {
		List_free(pList, myFree);
		return false;
	}
}
bool test_search_pass() {
	List* pList = List_create();

	int* x = malloc(sizeof(int));
	*x = 1;
	int* y = malloc(sizeof(int));
	*y = 2;

	List_append(pList, x);
	List_append(pList, y);

	void* found = List_search(pList, intCompare, y);


	if (*(int*)found == 2) {
		free(x);
		free(y);
		List_free(pList, myFree);
		return true;
	}
	else {
		free(x);
		free(y);
		List_free(pList, myFree);
		return false;
	}
}

void check(bool res, char* name) {
	if (res) {
		printf("Passed");
	}
	else {
		printf(">>----> Failed");
	}
	printf(" %s\n", name);
}
int main() {
	check(test_create(), "test_create");
	check(test_free(), "test_free");
	check(test_free_with_data(), "test_free_with_data");
	check(test_double_free(), "test_double_free");
	check(test_append(), "test_append");
	check(test_append_many(), "test_append_many");
	check(test_append_check_head(), "test_append_check_head");
	check(test_append_check_tail(), "test_append_check_tail");
	check(test_count(), "test_count");
	check(test_remove(), "test_remove");
	check(test_remove_many(), "test_remove_many");
	check(test_remove_extra(), "test_remove_extra");
	check(test_insert_after_OOB_START(), "test_insert_after_OOB_START");
	check(test_insert_after_OOB_END(), "test_insert_after_OOB_END");
	check(test_insert_before_OOB_START(), "test_insert_before_OOB_START");
	check(test_insert_before_OOB_END(), "test_insert_before_OOB_END");
	check(test_insert_before_MIDDLE(), "test_insert_before_MIDDLE");
	check(test_prepend(), "test_prepend");
	check(test_prev_empty(), "test_prev_empty");
	check(test_prev_OOB_START(), "test_prev_OOB_START");
	check(test_prev_OOB_START_many(), "test_prev_OOB_START_many");
	check(test_prev_OOB_END(), "test_prev_OOB_END");
	check(test_next_empty(), "test_next_empty");
	check(test_next_OOB_START(), "test_next_OOB_START");
	check(test_next_OOB_END(), "test_next_OOB_END");
	check(test_first_empty(), "test_first_empty");
	check(test_first(), "test_first");
	check(test_last_empty(), "test_last_empty");
	check(test_last(), "test_last");
	check(test_trim(), "test_trim");
	check(test_trim_empty(), "test_trim_empty");
	check(test_concat(), "test_concat");
	check(test_search_fail(), "test_search_fail");
	check(test_search_pass(), "test_search_pass");


	return 0;
}