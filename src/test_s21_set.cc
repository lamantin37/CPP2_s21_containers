#include <gtest/gtest.h>

#include "s21_set.h"

TEST(Member_functions_tests, DefaultConstructor) {
  s21::s21_set<int> custom_set;
  std::set<int> std_set;

  ASSERT_EQ(custom_set.empty(), std_set.empty());
}

TEST(Member_functions_tests, InitializerListConstructor) {
  s21::s21_set<int> custom_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  ASSERT_EQ(custom_set.size(), std_set.size());
  ASSERT_TRUE(custom_set.contains(1));
  ASSERT_TRUE(custom_set.contains(2));
  ASSERT_TRUE(custom_set.contains(3));
  ASSERT_TRUE(custom_set.contains(4));
  ASSERT_TRUE(custom_set.contains(5));
}

TEST(Member_functions_tests, TestClear) {
  s21::s21_set<int> s;
  s.insert(1);
  s.clear();
  ASSERT_TRUE(s.empty());
}

TEST(Member_functions_tests, CopyConstructor) {
  s21::s21_set<int> custom_set1 = {1, 2, 3, 4, 5};
  s21::s21_set<int> custom_set2 = custom_set1;

  ASSERT_EQ(custom_set2.size(), custom_set1.size());
  ASSERT_TRUE(custom_set2.contains(1));
  ASSERT_TRUE(custom_set2.contains(2));
  ASSERT_TRUE(custom_set2.contains(3));
  ASSERT_TRUE(custom_set2.contains(4));
  ASSERT_TRUE(custom_set2.contains(5));
}

TEST(Member_functions_tests, MoveConstructor) {
  s21::s21_set<int> custom_set1 = {1, 2, 3, 4, 5};
  s21::s21_set<int> custom_set2 = std::move(custom_set1);

  ASSERT_EQ(custom_set2.size(), 5);
  ASSERT_TRUE(custom_set2.contains(1));
  ASSERT_TRUE(custom_set2.contains(2));
  ASSERT_TRUE(custom_set2.contains(3));
  ASSERT_TRUE(custom_set2.contains(4));
  ASSERT_TRUE(custom_set2.contains(5));
  ASSERT_TRUE(custom_set1.empty());
}

TEST(Member_functions_tests, TestDestructor) {
  s21::s21_set<int> *s = new s21::s21_set<int>();
  s->insert(1);
  delete s;
}

TEST(Member_functions_tests, TestAssignmentOperator) {
  s21::s21_set<int> s1;
  s1.insert(1);
  s21::s21_set<int> s2;
  s2 = std::move(s1);
  ASSERT_EQ(s2.size(), 1);
  ASSERT_TRUE(s1.empty());
}

TEST(Iterators_tests, TestBeginEnd) {
  s21::s21_set<int> s;
  s.insert(1);
  ASSERT_EQ((*s.begin()), 1);
  ASSERT_EQ(s.end(), s21::s21_set<int>::iterator());
}

TEST(Capacity_tests, TestSize) {
  s21::s21_set<int> s;
  s.insert(1);
  ASSERT_EQ(s.size(), 1);
}

TEST(Capacity_tests, TestMaxSize) {
  s21::s21_set<int> s;
  std::set<int> st;
  ASSERT_EQ(s.max_size(), st.max_size());
}

TEST(Capacity_tests, TestClear) {
  s21::s21_set<int> s;
  s.insert(1);
  s.clear();
  ASSERT_TRUE(s.empty());
}

TEST(Capacity_tests, TestEmpty) {
  s21::s21_set<int> s;
  ASSERT_TRUE(s.empty());
  s.insert(1);
  ASSERT_FALSE(s.empty());
}

TEST(Modifiers_tests, InsertTest) {
  s21::s21_set<int> custom_set;
  std::set<int> std_set;

  custom_set.insert(1);
  std_set.insert(1);

  ASSERT_EQ(custom_set.size(), std_set.size());
  ASSERT_TRUE(custom_set.contains(1));
}

TEST(Modifiers_tests, EraseTest) {
  s21::s21_set<int> custom_set = {1, 2, 3, 4, 5};

  auto it = custom_set.find(3);
  custom_set.erase(it);

  ASSERT_EQ(custom_set.size(), 4);
  ASSERT_FALSE(custom_set.contains(3));
}

TEST(Modifiers_tests, SwapTest) {
  s21::s21_set<int> custom_set1 = {1, 2, 3, 4, 5};
  s21::s21_set<int> custom_set2 = {6, 7, 8, 9, 10};

  custom_set1.swap(custom_set2);

  ASSERT_TRUE(custom_set1.contains(6));
  ASSERT_TRUE(custom_set1.contains(7));
  ASSERT_TRUE(custom_set1.contains(8));
  ASSERT_TRUE(custom_set1.contains(9));
  ASSERT_TRUE(custom_set1.contains(10));
  ASSERT_TRUE(custom_set2.contains(1));
  ASSERT_TRUE(custom_set2.contains(2));
  ASSERT_TRUE(custom_set2.contains(3));
  ASSERT_TRUE(custom_set2.contains(4));
  ASSERT_TRUE(custom_set2.contains(5));
}

TEST(Modifiers_tests, MergeTest) {
  s21::s21_set<int> custom_set1 = {1, 2, 3, 4, 5};
  s21::s21_set<int> custom_set2 = {6, 7, 8, 9, 10};

  custom_set1.merge(custom_set2);

  ASSERT_EQ(custom_set1.size(), 10);
  ASSERT_TRUE(custom_set1.contains(6));
  ASSERT_TRUE(custom_set1.contains(7));
  ASSERT_TRUE(custom_set1.contains(8));
  ASSERT_TRUE(custom_set1.contains(9));
  ASSERT_TRUE(custom_set1.contains(10));
  ASSERT_TRUE(custom_set2.empty());
}

TEST(Modifiers_tests, NoDuplicatesTest) {
  s21::s21_set<int> custom_set = {1, 1, 1, 1};

  custom_set.insert(1);
  size_t old_size = custom_set.size();

  custom_set.insert(1);

  ASSERT_EQ(custom_set.size(), old_size);
}

TEST(Lookup_tests, ContainsTest) {
  s21::s21_set<int> custom_set = {1, 2, 3, 4, 5};

  ASSERT_TRUE(custom_set.contains(1));
  ASSERT_TRUE(custom_set.contains(2));
  ASSERT_TRUE(custom_set.contains(3));
  ASSERT_TRUE(custom_set.contains(4));
  ASSERT_TRUE(custom_set.contains(5));
  ASSERT_FALSE(custom_set.contains(6));
}

TEST(Lookup_tests, TestFind) {
  s21::s21_set<int> s;
  s.insert(1);
  auto it = s.find(1);
  ASSERT_EQ((*it), 1);
  it = s.find(2);
  ASSERT_EQ(it, s.end());
}

TEST(Modifiers_tests, EmplaceTest) {
  s21::s21_set<int> custom_set = {1, 2, 3, 5, 6, 7};
  std::set<int> std_set = {1, 2, 3, 5, 6, 7};

  custom_set.emplace(4);
  std_set.emplace(4);

  auto i = custom_set.begin();
  auto j = std_set.begin();
  for (; i != custom_set.end(); i++, j++) {
    ASSERT_EQ(*i, *j);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
