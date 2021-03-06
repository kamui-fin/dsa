#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>
#include <malloc.h>
#include "bst.h"

struct teststate_t {
    struct BstNode *tree;
};

static int test_setup(void **state) {
    struct teststate_t *teststate = malloc(sizeof(struct teststate_t));
    teststate->tree = NULL;
    *state = teststate;
    return 0;
}

static int test_teardown(void **state) {
    free(*state);
    return 0;
}

void test_data(struct BstNode **root) {
    bst_insert(root, 10);
    bst_insert(root, 7);
    bst_insert(root, 13);
    bst_insert(root, 8);
    bst_insert(root, 2);
    bst_insert(root, 4);
}

void it_inserts(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    assert_int_equal(root->key, 10);
    assert_int_equal(root->left->key, 7);
    assert_int_equal(root->left->right->key, 8);
    assert_int_equal(root->right->key, 13);
}

void it_gets_minimum(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    struct BstNode *min = bst_get_min(root);
    assert_int_equal(min->key, 2);
}

void it_gets_maximum(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    struct BstNode *max = bst_get_max(root);
    assert_int_equal(max->key, 13);
}

void it_gets_height(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    int height = bst_get_height(root);
    assert_int_equal(height, 4);
}

void it_gets_node_count(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    int count = bst_len(root);
    assert_int_equal(count, 6);
}

void it_is_a_bst(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    bool is_bst = valid_bst(root, INT16_MIN, INT16_MAX);
    assert_int_equal(is_bst, true);

    struct BstNode *wrong_node = malloc(sizeof(struct BstNode));
    wrong_node->left = NULL;
    wrong_node->right = NULL;
    wrong_node->key = 2;

    root->right->left = wrong_node;
    is_bst = valid_bst(root, INT16_MIN, INT16_MAX);
    assert_int_equal(is_bst, false);
}

void it_is_in_tree(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    int in_tree = bst_exists(root, 2);
    assert_int_equal(in_tree, true);

    in_tree = bst_exists(root, 73);
    assert_int_equal(in_tree, false);
}
void it_is_a_sucessor(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);
    struct BstNode *eight = root->left->right;
    struct BstNode *succ = bst_get_successor(root, eight);
    assert_int_equal(succ->key, 10);

    succ = bst_get_successor(root, root);
    assert_int_equal(succ->key, 13);
}

void it_can_delete(void **state) {
    struct BstNode *root = ((struct teststate_t *)(*state))->tree;
    test_data(&root);

    int in_tree = bst_exists(root, 2);
    assert_int_equal(in_tree, true);

    bst_delete(root, root, 2);

    in_tree = bst_exists(root, 2);
    assert_int_equal(in_tree, false);
}

int main(void) {
    printf("Starting binary search tree tests...\n");
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(it_inserts, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_minimum, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_maximum, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_height, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_gets_node_count, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_a_bst, test_setup, test_teardown),
        cmocka_unit_test_setup_teardown(it_is_in_tree, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_is_a_sucessor, test_setup,
                                        test_teardown),
        cmocka_unit_test_setup_teardown(it_can_delete, test_setup,
                                        test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
