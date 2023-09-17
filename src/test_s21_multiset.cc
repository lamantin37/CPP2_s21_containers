#include <gtest/gtest.h>

#include <set>

#include "s21_multiset.h"

TEST(Member_functions_tests, DefaultConstructor) {
  s21::s21_multiset<int> mset;
  EXPECT_EQ(mset.size(), 0);
  EXPECT_TRUE(mset.empty());
}

TEST(Member_functions_tests, InitializerListConstructor) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 3, 4};
  EXPECT_EQ(mset.size(), std_mset.size());
  auto std_it = std_mset.begin();
  for (auto it = mset.begin(); it != mset.end(); ++it, std_it++) {
    EXPECT_EQ(*it, *std_it);
  }
}

TEST(Member_functions_tests, CopyConstructor) {
  s21::s21_multiset<int> mset1 = {1, 2, 3, 4};
  s21::s21_multiset<int> mset2(mset1);

  EXPECT_EQ(mset1.size(), mset2.size());

  auto mset1_it = mset1.begin();
  for (auto it = mset2.begin(); it != mset2.end(); ++it, ++mset1_it) {
    EXPECT_EQ(*it, *mset1_it);
  }
}

TEST(Member_functions_tests, CopyAssignmentConstructor) {
  s21::s21_multiset<int> mset1 = {1, 2, 3, 4};
  s21::s21_multiset<int> mset2;

  mset1 = mset2;
  EXPECT_EQ(mset1.size(), mset2.size());

  auto i = mset1.begin();
  auto j = mset2.begin();
  for (; i != mset1.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
}

TEST(Member_functions_tests, MoveConstructor) {
  s21::s21_multiset<int> mset1 = {1, 2, 3, 4};
  s21::s21_multiset<int> mset2(std::move(mset1));

  EXPECT_EQ(mset1.size(), 0);
  EXPECT_EQ(mset2.size(), 4);
}

TEST(Member_functions_tests, MoveAssignmentOperator) {
  s21::s21_multiset<int> mset1 = {1, 2, 3, 4};
  s21::s21_multiset<int> mset2;
  mset2 = std::move(mset1);

  EXPECT_EQ(mset1.size(), 0);
  EXPECT_EQ(mset2.size(), 4);
}

TEST(Iterators_tests, Begin) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 3, 4};

  EXPECT_EQ((*mset.begin()), *std_mset.begin());
}

TEST(Iterators_tests, End) {
  s21::s21_multiset<int> mset;
  std::multiset<int> std_mset;
  EXPECT_EQ(*mset.end(), *std_mset.end());
}

TEST(Capacity_tests, Empty) {
  s21::s21_multiset<int> mset;
  std::multiset<int> std_mset;

  EXPECT_EQ(mset.empty(), std_mset.empty());
}

TEST(Capacity_tests, Size) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4, 5};
  std::multiset<int> std_mset = {1, 2, 3, 4, 5};

  EXPECT_EQ(mset.size(), std_mset.size());

  mset.insert(5);
  std_mset.insert(5);

  EXPECT_EQ(mset.size(), std_mset.size());
}

TEST(Capacity_tests, MaxSize) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4, 5};
  std::multiset<int> std_mset = {1, 2, 3, 4, 5};

  EXPECT_EQ(mset.max_size(), std_mset.max_size());
}

TEST(Modifiers_tests, Clear) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 3, 4};

  mset.clear();
  std_mset.clear();

  EXPECT_EQ(mset.size(), std_mset.size());
  EXPECT_TRUE(mset.empty());
  EXPECT_TRUE(std_mset.empty());
}

TEST(Modifiers_tests, TestInsert) {
  s21::s21_multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  my_multiset.insert(5);
  std_multiset.insert(5);

  ASSERT_EQ(my_multiset.size(), std_multiset.size());
  ASSERT_EQ(my_multiset.contains(5), std_multiset.count(5) > 0);

  my_multiset.insert(5);
  std_multiset.insert(5);

  ASSERT_EQ(my_multiset.size(), std_multiset.size());
  ASSERT_EQ(my_multiset.contains(5), std_multiset.count(5) > 0);
}

TEST(Modifiers_tests, TestInsert2) {
  s21::s21_multiset<int> my_multiset;
  std::multiset<int> std_multiset;
  for (int i = 0; i < 1e6; i++) {
    my_multiset.insert(i);
    std_multiset.insert(i);
  }
  auto it1 = my_multiset.begin();
  auto it2 = std_multiset.begin();
  for (; it1 != my_multiset.end(), it1 != my_multiset.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, (*it2));
  }
  ASSERT_EQ(my_multiset.size(), std_multiset.size());
}

TEST(Modifiers_tests, TestInsert3) {
  s21::s21_multiset<std::string> mset;
  std::multiset<std::string> std_mset;

  mset.insert("apple");
  mset.insert("banana");
  std_mset.insert("apple");
  std_mset.insert("banana");

  EXPECT_EQ(mset.size(), std_mset.size());
  EXPECT_EQ(*mset.begin(), *std_mset.begin());
}

TEST(MultisetTest, Erase) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 3, 4};

  mset.erase((mset.begin()));
  std_mset.erase((std_mset.begin()));
  EXPECT_EQ(mset.size(), std_mset.size());
  EXPECT_EQ(*mset.begin(), *std_mset.begin());
}

TEST(Modifiers_tests, Swap) {
  s21::s21_multiset<int> mset1 = {1, 2, 3, 4};
  s21::s21_multiset<int> mset2 = {5, 6, 7, 8};
  std::multiset<int> std_mset1 = {1, 2, 3, 4};
  std::multiset<int> std_mset2 = {5, 6, 7, 8};

  mset1.swap(mset2);
  std::swap(std_mset1, std_mset2);

  auto it1 = mset1.begin();
  auto it2 = std_mset1.begin();
  for (; it1 != mset1.end(), it2 != std_mset1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, (*it2));
  }
  it1 = mset2.begin();
  it2 = std_mset2.begin();
  for (; it1 != mset2.end(), it2 != std_mset2.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, (*it2));
  }
}

TEST(Modifiers_tests, Merge) {
  s21::s21_multiset<int> mset1 = {1, 2, 3, 4};
  s21::s21_multiset<int> mset2 = {5, 6, 7, 8};
  std::multiset<int> std_mset1 = {1, 2, 3, 4};
  std::multiset<int> std_mset2 = {5, 6, 7, 8};

  mset1.merge(mset2);
  std_mset1.merge(std_mset2);

  auto it1 = mset1.begin();
  auto it2 = std_mset1.begin();
  for (; it1 != mset1.end(), it2 != std_mset1.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, (*it2));
  }
  ASSERT_EQ(mset1.size(), std_mset1.size());
}

TEST(MultisetTest, TestContains) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 3, 4};

  EXPECT_EQ(mset.contains(3), std_mset.count(3));
  EXPECT_EQ(mset.contains(13), std_mset.count(13));
}

TEST(Lookup_tests, TestFind) {
  s21::s21_multiset<int> mset = {1, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 3, 4};

  EXPECT_EQ((*mset.find(3)), *std_mset.find(3));
}

TEST(Lookup_tests, TestFind2) {
  s21::s21_multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  ASSERT_EQ(my_multiset.find(5), my_multiset.end());
  ASSERT_EQ(std_multiset.find(5), std_multiset.end());

  ASSERT_EQ(my_multiset.count(5), 0);
  ASSERT_EQ(std_multiset.count(5), 0);
}

TEST(Lookup_tests, TestCount) {
  s21::s21_multiset<int> mset = {1, 2, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 2, 3, 4};

  EXPECT_EQ(mset.count(2), std_mset.count(2));
}
TEST(Lookup_tests, TestCount2) {
  s21::s21_multiset<int> my_multiset = {1, 2, 5, 1, 1, 1};
  std::multiset<int> std_multiset = {1, 2, 5, 1, 1, 1};

  ASSERT_EQ(my_multiset.count(1), std_multiset.count(1));
}

TEST(MultisetTest, TestEqualRange) {
  s21::s21_multiset<int> mset = {1, 2, 2, 3, 4};
  std::multiset<int> std_mset = {1, 2, 2, 3, 4};

  auto mset_range = mset.equal_range(2);
  auto std_mset_range = std_mset.equal_range(2);

  EXPECT_EQ(*(mset_range.first), *(std_mset_range.first));
  EXPECT_EQ(*(mset_range.second), *(std_mset_range.second));
}

TEST(MultisetTest, TestLowerBound) {
  s21::s21_multiset<int> my_multiset = {7, 11, 8, 8, 1, 3};
  std::multiset<int> std_multiset = {7, 11, 8, 8, 1, 3};

  ASSERT_EQ(*(my_multiset.lower_bound(3)), (*(std_multiset.lower_bound(3))));
  ASSERT_EQ(*(my_multiset.lower_bound(10)), (*(std_multiset.lower_bound(10))));
}

TEST(MultisetTest, TestUpperBound) {
  s21::s21_multiset<int> my_multiset = {3, 5, 5, 7, 11, 10, 9};
  std::multiset<int> std_multiset = {3, 5, 5, 7, 11, 10, 9};

  ASSERT_EQ(*(my_multiset.upper_bound(3)), (*(std_multiset.upper_bound(3))));
  ASSERT_EQ(*(my_multiset.upper_bound(2)), (*(std_multiset.upper_bound(2))));
}

TEST(Bonus_tests, TestInsertMany) {
  s21::s21_multiset<int> my_multiset = {3, 5, 5, 7, 11, 10, 9};
  std::multiset<int> std_multiset = {3, 5, 5, 7, 11, 10, 9};

  my_multiset.insert_many(5);
  std_multiset.emplace(5);

  auto i = my_multiset.begin();
  auto j = std_multiset.begin();
  for (; i != my_multiset.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
