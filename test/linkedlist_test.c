#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include "linked_list.h"

struct teststate_t {
    struct ListNode *head;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    teststate->head = NULL;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void it_gets_front(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    list_push_back(&head, 5);
    int f = list_front(head)->data;
    assert_int_equal(f, 5);
}

void it_gets_back(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    list_push_back(&head, 5);
    int b = list_back(head)->data;
    assert_int_equal(b, 5);
}

void it_is_empty(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    bool e = list_empty(head);
    assert_int_equal(e, true);
}

void it_calcs_size(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, 0);
    int s = list_len(head);
    assert_int_equal(s, 5);
}

void it_gets_third_elm(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    int third = list_at(head, 3)->data;
    assert_int_equal(third, 3);
}

void it_pushes_front(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    list_push_back(&head, 3);
    int first = list_at(head, 0)->data;
    assert_int_equal(first, 3);
}

void it_pops_front(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    list_push_back(&head, 3);
    int first = list_pop_front(&head)->data;
    assert_int_equal(first, 3);
}

void it_pushes_back(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    int last = list_at(head, list_len(head) - 1)->data;
    assert_int_equal(last, 4);
}

void it_pops_back(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    int last = list_pop_back(&head)->data;
    assert_int_equal(last, 4);
}

void it_inserts_node(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    list_insert(&head, 2, 55);
    int val = list_at(head, 2)->data;
    assert_int_equal(val, 55);
}

void it_erases_node(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    list_erase(&head, 2);
    int val = list_at(head, 2)->data;
    assert_int_equal(val, 3);
}

void it_gets_n_value_from_the_end(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    int val = list_n_from_end(head, 2)->data;
    assert_int_equal(val, 2);
}

void it_removes_by_value(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    list_remove(&head, 4);
    int val = list_back(head)->data;
    assert_int_not_equal(val, 4);
}

void it_reverses_list(void **state) {
    struct ListNode *head = ((struct teststate_t *)(*state))->head;
    for (int i = 0; i < 5; i++)
        list_push_back(&head, i);
    list_reverse(&head);
    int last = list_back(head)->data;
    assert_int_equal(last, 0);
}

int main(void) {
    printf("Starting linked list tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_gets_front, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_back, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_empty, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_calcs_size, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_third_elm, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pushes_front, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pops_front, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pushes_back, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_pops_back, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_inserts_node, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_erases_node, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_n_value_from_the_end,
                                        test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_removes_by_value, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_reverses_list, test_setup,
                                        test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
