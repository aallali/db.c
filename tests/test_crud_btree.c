/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   test_crud_btree.c                           _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/14 18:31:58 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#include <check.h>
#include "btree.h"

// Test creation of nodes
START_TEST(test_one_equals_one)
{
    treeNode *rootNode = createTree(10);
    ck_assert_int_eq(rootNode->value, 10);

    insert_node(&rootNode, 10);
        ck_assert_ptr_null(rootNode->left);
        ck_assert_ptr_null(rootNode->right);

    insert_node(&rootNode, 1);
        ck_assert_int_eq(rootNode->left->value, 1);
        ck_assert_ptr_nonnull(rootNode->left);

    insert_node(&rootNode, 11);
        ck_assert_ptr_nonnull(rootNode->right);
        ck_assert_int_eq(rootNode->right->value, 11);
}
END_TEST

Suite *sample_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Sample");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_one_equals_one);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = sample_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
