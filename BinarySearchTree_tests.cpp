// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(test_empty_is) {
    BinarySearchTree<int> b1;
    ASSERT_TRUE(b1.empty());
}

TEST(test_empty_not) {
    BinarySearchTree<int> b1;
    b1.insert(5);
    b1.insert(1);
    b1.insert(235);
    ASSERT_FALSE(b1.empty());
    ASSERT_EQUAL(b1.size(), 3);
}

TEST(test_size_empty) {
    BinarySearchTree<int> b1;
    ASSERT_TRUE(b1.size() == 0);
}

TEST(test_size_large) {
    BinarySearchTree<int> b1;
    b1.insert(5);
    b1.insert(1);
    b1.insert(235);
    b1.insert(3);
    b1.insert(12);
    b1.insert(56);
    b1.insert(87);
    b1.insert(1242);
    b1.insert(9);
    b1.insert(0);
    ASSERT_EQUAL(b1.size(), 10);
}

TEST(test_height_empty) {
    BinarySearchTree<int> b1;
    ASSERT_EQUAL(b1.height(), 0);
}

TEST(test_height_equal) {
    BinarySearchTree<int> b1;
    b1.insert(10);
    b1.insert(5);
    b1.insert(1);
    b1.insert(8);
    b1.insert(20);
    b1.insert(15);
    b1.insert(456);
    ASSERT_EQUAL(b1.height(), 3);
}

TEST(test_height_long) {
    BinarySearchTree<int> b1;
    b1.insert(10);
    b1.insert(9);
    b1.insert(8);
    b1.insert(7);
    b1.insert(6);
    b1.insert(5);
    b1.insert(4);
    ASSERT_EQUAL(b1.height(), 7);
}

TEST(test_find_empty) {
    BinarySearchTree<int> b1;
    BinarySearchTree<int>::Iterator it = b1.begin();
    ASSERT_EQUAL(b1.find(3), it);
}

TEST(test_find_first_equal) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    ASSERT_EQUAL(*(b1.find(3)), 3);
}

TEST(test_find_left) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    b1.insert(5);
    b1.insert(2);
    b1.insert(1);
    ASSERT_EQUAL(*(b1.find(1)), 1);
}

TEST(test_find_right) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    b1.insert(5);
    b1.insert(10);
    b1.insert(123);
    ASSERT_EQUAL(*(b1.find(123)), 123);
}

TEST(test_min_empty) {
    BinarySearchTree<int> b1;
    BinarySearchTree<int>::Iterator it = b1.begin();
    ASSERT_EQUAL(b1.min_element(), it);
}

TEST(test_min_one) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    ASSERT_EQUAL(*(b1.min_element()), 3);
}

TEST(test_min_root) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    b1.insert(4);
    b1.insert(5);
    b1.insert(6);
    ASSERT_EQUAL(*(b1.min_element()), 3);
}

TEST(test_min_left) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    b1.insert(2);
    b1.insert(1);
    b1.insert(0);
    ASSERT_EQUAL(*(b1.min_element()), 0);
}

TEST(test_max_empty) {
    BinarySearchTree<int> b1;
    BinarySearchTree<int>::Iterator it = b1.begin();
    ASSERT_EQUAL(b1.max_element(), it);
}

TEST(test_max_one) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    ASSERT_EQUAL(*(b1.max_element()), 3);
}

TEST(test_max_root) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    b1.insert(2);
    b1.insert(1);
    b1.insert(0);
    ASSERT_EQUAL(*(b1.max_element()), 3);
}

TEST(test_max_right) {
    BinarySearchTree<int> b1;
    b1.insert(3);
    b1.insert(4);
    b1.insert(34);
    b1.insert(5);
    ASSERT_EQUAL(*(b1.max_element()), 34);
}

TEST(test_in_order_empty) {
    BinarySearchTree<int> b1;
    std::ostringstream os;
    b1.traverse_inorder(os);
    ASSERT_TRUE(os.str() == "");
}

TEST(test_in_order_one) {
    BinarySearchTree<int> b1;
    b1.insert(10);
    std::ostringstream os;
    b1.traverse_inorder(os);
    ASSERT_TRUE(os.str() == "10 ");
}

TEST(test_in_order) {
    BinarySearchTree<int> b1;
    b1.insert(10);
    b1.insert(5);
    b1.insert(15);
    b1.insert(7);
    b1.insert(3);
    std::ostringstream os;
    b1.traverse_inorder(os);
    ASSERT_TRUE(os.str() == "3 5 7 10 15 ");
}

TEST(test_pre_order_empty) {
    BinarySearchTree<int> b1;
    std::stringstream ss;
    b1.traverse_preorder(ss);
    ASSERT_EQUAL(ss.str(), "");
}

TEST(test_pre_order_one) {
    BinarySearchTree<int> b1;
    b1.insert(10);
    std::ostringstream os;
    b1.traverse_preorder(os);
    ASSERT_TRUE(os.str() == "10 ");
}

TEST(test_pre_order) {
    BinarySearchTree<int> b1;
    b1.insert(10);
    b1.insert(5);
    b1.insert(15);
    b1.insert(7);
    b1.insert(3);
    std::ostringstream os;
    b1.traverse_preorder(os);
    ASSERT_TRUE(os.str() == "10 5 3 7 15 ");
}

TEST_MAIN()
