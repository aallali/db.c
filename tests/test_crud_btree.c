/* ************************************************************************** */
/*                                                                            */
/*                                                __ ______ ______ _______    */
/*   test_crud_btree.c                           _██ ██████ ██████ ███████    */
/*                                               ███  ____█  ____█     _██    */
/*   By: aallali <hi@allali.me>                   ██  █████  █████    _██     */
/*                                                ██ _____█ _____█   _██      */
/*   Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma    */
/*   Updated: 2024/12/15 01:10:19 by aallali      -------- 1337.ma -------    */
/*                                                                            */
/* ************************************************************************** */

#include <check.h>
#include "btree.h"

// Test creation of nodes
START_TEST(test_one_equals_one)
{
    btree *root_node = bt_create_tree(10);
    ck_assert_int_eq(root_node->value, 10);

    bt_insert_node(&root_node, 10);
    ck_assert_ptr_null(root_node->left);
    ck_assert_ptr_null(root_node->right);

    bt_insert_node(&root_node, 1);
    ck_assert_int_eq(root_node->left->value, 1);
    ck_assert_ptr_nonnull(root_node->left);

    bt_insert_node(&root_node, 11);
    ck_assert_ptr_nonnull(root_node->right);
    ck_assert_int_eq(root_node->right->value, 11);
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
