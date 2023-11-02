#include <chrono>
#include <list>

#include "../s21_containers.h"
#include "gtest/gtest.h"

TEST(tests_of_list, front_pop_front) {
  s21::list<int> l1 = {1, 2, 3, 4};
  std::list<int> l2 = {1, 2, 3, 4};
  for (size_t a = 0; a < l2.size(); a++) {
    EXPECT_EQ(l1.front(), l2.front());
    l1.pop_front();
    l2.pop_front();
  }
}

TEST(tests_of_list, back_pop_back) {
  s21::list<int> l1 = {1, 2, 3, 4};
  std::list<int> l2 = {1, 2, 3, 4};
  for (size_t a = 0; a < l2.size(); a++) {
    EXPECT_EQ(l1.back(), l2.back());
    l1.pop_back();
    l2.pop_back();
  }
}

TEST(ListTest, PopBackTest) {
  s21::list<int> myList = {1, 2, 3, 4};
  myList.pop_back();
  EXPECT_EQ(myList.back(), 3);
  myList.pop_back();
  EXPECT_EQ(myList.back(), 2);
  myList.pop_back();
  EXPECT_EQ(myList.back(), 1);
}

TEST(ListTest, ClearTest) {
  s21::list<int> myList = {1, 2, 3, 4};
  myList.clear();
  EXPECT_TRUE(myList.empty());
}

TEST(tests_of_list, default_constructor) {
  s21::list<int> l1;
  std::list<int> l2;
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(tests_of_list, parameterized_constructor) {
  s21::list<int> l1(20);
  std::list<int> l2(20);
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(tests_of_list, initizialized_constructor) {
  s21::list<int> l1 = {1, 2, 3, 4};
  std::list<int> l2 = {1, 2, 3, 4};
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(tests_of_list, copy) {
  s21::list<int> l1 = {2, 2, 2, 2};
  s21::list<int> l2(l1);
  for (size_t a = 0; a < l2.size(); a++) {
    EXPECT_EQ(l1.front(), l2.front());
    l1.pop_front();
    l2.pop_front();
  }
}

TEST(tests_of_list, empty) {
  s21::list<int> l1 = {2, 2, 2, 2};
  s21::list<int> l2(l1);
  l2.clear();
  EXPECT_EQ(l2.empty(), true);
}

TEST(tests_of_list, size) {
  s21::list<int> l1 = {2, 2, 2, 2};
  s21::list<int> l2(l1);
  EXPECT_EQ(l2.size(), l1.size());
}

TEST(tests_of_list, insert) {
  s21::list<int> l1 = {2, 2, 2, 2};
  s21::list<int> l2 = {2, 2, 10, 2, 2};
  s21::list<int>::iterator it = l1.begin();
  ++it;
  ++it;
  ++it;
  --it;
  l1.insert(it, 10);
  for (size_t a = 0; a < l2.size(); a++) {
    EXPECT_EQ(l1.front(), l2.front());
    l1.pop_front();
    l2.pop_front();
  }
}

TEST(ListIteratorTest, Traversal) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  int expected_value = 1;

  for (s21::list<int>::iterator it = myList.begin(); it != myList.end(); ++it) {
    EXPECT_EQ(*it, expected_value);
    ++expected_value;
  }
}

TEST(ListIteratorTest, ModifyElements) {
  s21::list<int> myList = {1, 2, 3, 4, 5};

  for (s21::list<int>::iterator it = myList.begin(); it != myList.end(); ++it) {
    *it += 10;
  }

  int expected_value = 11;
  for (const int &value : myList) {
    EXPECT_EQ(value, expected_value);
    ++expected_value;
  }
}

TEST(ListIteratorTest, ListMerge) {
  s21::list<int> list1 = {1, 3, 5, 7};
  s21::list<int> list2 = {2, 4, 6, 8};

  list1.merge(list2);

  std::vector<int> expected_values = {1, 2, 3, 4, 5, 6, 7, 8};
  int index = 0;
  for (const int &value : list1) {
    EXPECT_EQ(value, expected_values[index]);
    ++index;
  }

  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, SpliceTest) {
  s21::list<int> myList1 = {1, 2, 3};
  s21::list<int> myList2 = {4, 5};
  myList1.splice(myList1.end(), myList2);
  EXPECT_EQ(myList1.size(), 5);
  EXPECT_EQ(myList2.empty(), true);
}

TEST(ListTest, SwapTest) {
  s21::list<int> myList1 = {1, 2, 3};
  s21::list<int> myList2 = {4, 5};
  myList1.swap(myList2);
  EXPECT_EQ(myList1.size(), 2);
  EXPECT_EQ(myList2.size(), 3);
}

TEST(ConstIteratorTest, DefaultConstructor) {
  s21::list<int> myList;
  const s21::list<int> &constList = myList;

  EXPECT_EQ(constList.begin(), constList.end());
}

TEST(ConstIteratorTest, BasicIteration) {
  s21::list<int> myList = {1, 2, 3, 4};
  const s21::list<int> &constList = myList;

  int expectedValue = 1;
  for (s21::list<int>::const_iterator it = constList.begin();
       it != constList.end(); ++it) {
    EXPECT_EQ(*it, expectedValue);
    ++expectedValue;
  }
}

TEST(ConstIteratorTest, ConstCorrectness) {
  s21::list<int> myList = {1, 2, 3, 4};
  const s21::list<int> &constList = myList;

  s21::list<int>::const_iterator it = constList.begin();
  EXPECT_EQ(*it, 1);

  const s21::list<int>::const_iterator &constRefIt = it;
  EXPECT_EQ(*constRefIt, 1);
}

TEST(ConstIteratorTest, IterationWithReverseList) {
  s21::list<int> myList = {4, 3, 2, 1};
  const s21::list<int> &constList = myList;

  int expectedValue = 4;
  for (s21::list<int>::const_iterator it = constList.begin();
       it != constList.end(); ++it) {
    EXPECT_EQ(*it, expectedValue);
    --expectedValue;
  }
}

TEST(ListTest, ReverseTest) {
  s21::list<int> emptyList;
  emptyList.reverse();
  EXPECT_TRUE(emptyList.empty());

  s21::list<int> singleElementList;
  singleElementList.push_back(42);
  singleElementList.reverse();
  EXPECT_EQ(singleElementList.front(), 42);
  EXPECT_EQ(singleElementList.back(), 42);

  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);
  myList.reverse();
  EXPECT_EQ(myList.front(), 3);
  EXPECT_EQ(myList.back(), 1);
}

TEST(ListTest, ReverseTIMETest) {
  const int numElements = 1000;
  s21::list<int> myList;
  for (int i = 1; i <= numElements; ++i) {
    myList.push_back(i);
  }
  auto startTime = std::chrono::high_resolution_clock::now();
  myList.reverse();
  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime)
          .count();
  EXPECT_LE(duration, 10);
}

TEST(ListTest, UniqueTest1) {
  s21::list<int> emptyList;
  emptyList.unique();
  EXPECT_TRUE(emptyList.empty());

  s21::list<int> noDuplicatesList;
  noDuplicatesList.push_back(1);
  noDuplicatesList.push_back(2);
  noDuplicatesList.push_back(3);
  noDuplicatesList.unique();
  EXPECT_EQ(noDuplicatesList.size(), 3);

  s21::list<int> duplicatesList;
  duplicatesList.push_back(1);
  duplicatesList.push_back(2);
  duplicatesList.push_back(2);
  duplicatesList.push_back(3);
  duplicatesList.push_back(3);
  duplicatesList.unique();
  EXPECT_EQ(duplicatesList.size(), 3);
}

TEST(ListTest, UniqueTest2) {
  s21::list<int> emptyList;
  emptyList.unique();
  EXPECT_TRUE(emptyList.empty());

  s21::list<int> noDuplicatesList;
  noDuplicatesList.push_back(1);
  noDuplicatesList.push_back(2);
  noDuplicatesList.push_back(3);
  noDuplicatesList.unique();
  EXPECT_EQ(noDuplicatesList.size(), 3);
  EXPECT_EQ(noDuplicatesList.front(), 1);
  EXPECT_EQ(noDuplicatesList.back(), 3);

  s21::list<int> duplicatesList;
  duplicatesList.push_back(1);
  duplicatesList.push_back(2);
  duplicatesList.push_back(2);
  duplicatesList.push_back(3);
  duplicatesList.push_back(3);
  duplicatesList.push_back(3);
  duplicatesList.unique();
  EXPECT_EQ(duplicatesList.size(), 3);
  EXPECT_EQ(duplicatesList.front(), 1);
  EXPECT_EQ(duplicatesList.back(), 3);
}

TEST(ListTest, UniqueExtraordinaryTest) {
  const int numElements = 1000;
  s21::list<int> myList;
  for (int i = 1; i <= numElements; ++i) {
    myList.push_back(i);
    myList.push_back(i);
  }

  auto startTime = std::chrono::high_resolution_clock::now();
  myList.unique();
  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime)
          .count();
  EXPECT_LE(duration, 10);
  EXPECT_EQ(myList.size(), numElements);
}

TEST(ListTest, SortAscendingTest) {
  s21::list<int> myList{9, 3, 7, 1, 5, 2, 8, 4, 6};

  myList.sort();

  int prevValue = myList.front();
  for (const auto &value : myList) {
    EXPECT_LE(prevValue, value);
    prevValue = value;
  }
}

TEST(ListTest, SortEmptyListTest) {
  s21::list<double> emptyList;

  emptyList.sort();

  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, SortDuplicateElementsTest) {
  s21::list<int> myList{9, 3, 7, 1, 5, 2, 8, 4, 6, 3, 1, 5, 4};

  myList.sort();

  int prevValue = myList.front();
  bool hasDuplicates = false;
  for (const auto &value : myList) {
    if (prevValue == value) {
      hasDuplicates = true;
    }
    EXPECT_LE(prevValue, value);
    prevValue = value;
  }

  EXPECT_TRUE(hasDuplicates);
}

TEST(ListTest, MaxSizeTest1) {
  s21::list<int> myList;
  s21::list<int>::size_type maxSize = myList.max_size();
  EXPECT_GT(maxSize, 0);
}

TEST(ListTest, MaxSizeTest2) {
  s21::list<int> myList;

  EXPECT_EQ(myList.max_size(), std::numeric_limits<std::size_t>::max());

  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  EXPECT_EQ(myList.max_size(), std::numeric_limits<std::size_t>::max());
}

TEST(ListTest, MergeTest1) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.push_back(1);
  list1.push_back(3);
  list1.push_back(5);

  list2.push_back(2);
  list2.push_back(4);
  list2.push_back(6);

  list1.merge(list2);

  std::vector<int> expected_values = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (const auto &value : list1) {
    EXPECT_EQ(value, expected_values[i]);
    i++;
  }

  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, SortAndUniqueTest) {
  s21::list<int> myList = {5, 4, 3, 4, 2, 1, 2};
  myList.sort();
  myList.unique();
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(ListTest, InsertMiddleTest) {
  s21::list<int> myList = {1, 2, 4};
  s21::list<int>::iterator it = myList.begin() + 2;
  myList.insert(it, 3);
  int expected[] = {1, 2, 3, 4};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(ListTest, SwapTwoListsTest) {
  s21::list<int> myList1 = {1, 2, 3};
  s21::list<int> myList2 = {4, 5};
  myList1.swap(myList2);
  int expected1[] = {4, 5};
  int expected2[] = {1, 2, 3};
  int i = 0;
  for (const auto &value : myList1) {
    EXPECT_EQ(value, expected1[i]);
    ++i;
  }
  i = 0;
  for (const auto &value : myList2) {
    EXPECT_EQ(value, expected2[i]);
    ++i;
  }
}

TEST(ListTest, MixedInsertDeleteTest) {
  s21::list<int> myList = {1, 2, 3, 4};
  myList.pop_back();
  myList.pop_front();
  s21::list<int>::iterator it = myList.begin();
  ++it;
  myList.insert(it, 5);
  int expected[] = {2, 5};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(ListTest, MergeTwoListsTest) {
  s21::list<int> myList1 = {1, 3, 5};
  s21::list<int> myList2 = {2, 4, 6};
  myList1.merge(myList2);
  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (const auto &value : myList1) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
  EXPECT_TRUE(myList2.empty());
}

TEST(ListTest, MergeAndEraseCombinedTest) {
  s21::list<int> myList1 = {1, 2, 3};
  s21::list<int> myList2 = {2, 3, 4};
  myList1.merge(myList2);

  s21::list<int>::iterator it = myList1.begin();
  ++it;
  myList1.erase(it);
  int expected[] = {1, 2, 3, 3, 4};
  int i = 0;
  for (const auto &value : myList1) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
  EXPECT_TRUE(myList2.empty());
}

TEST(ListTest, InsertAndSortCombinedTest) {
  s21::list<int> myList = {4, 2, 5, 1, 3};
  myList.insert(myList.begin(), 0);
  myList.insert(myList.end(), 6);
  myList.sort();
  int expected[] = {0, 1, 2, 3, 4, 5, 6};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(ListTest, EraseAndInsertCombinedTest) {
  s21::list<int> myList = {1, 2, 3, 4};
  s21::list<int>::iterator it = myList.begin();
  ++it;
  myList.erase(it);
  myList.erase(myList.end());
  myList.insert(myList.begin(), 5);
  myList.insert(myList.end(), 6);
  int expected[] = {5, 1, 3, 6};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(ListTest, SortAndUniqueCombinedTest) {
  s21::list<int> myList = {5, 2, 3, 5, 1, 2, 4, 4};
  myList.sort();
  myList.unique();
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(IteratorTest, ComparisonWithDifferentLists) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  s21::list<int>::iterator it1 = list1.begin();
  s21::list<int>::iterator it2 = list2.begin();

  EXPECT_NE(it1, it2);
  EXPECT_NE(it1, list2.end());
  EXPECT_NE(it2, list1.end());
}

TEST(IteratorTest, IteratorsComperison) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int>::iterator it1 = list1.begin();
  s21::list<int>::iterator it2 = list1.begin();

  EXPECT_TRUE(it1 == it2);
  ++it1;
  EXPECT_TRUE(it1 != it2);
  EXPECT_TRUE(it1 > it2);
  --it1;
  EXPECT_TRUE(it1 >= it2);
  ++it2;
  EXPECT_TRUE(it1 < it2);
  --it2;
  EXPECT_TRUE(it1 <= it2);
  ++it1;
  ++it1;
  EXPECT_EQ(it1 - it2, 1);
}

TEST(ListInsertManyTests, InsertMany) {
  s21::list<int> myList;

  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);
  auto it = myList.begin();
  ++it;
  myList.insert_many(it, 4, 5, 6);

  std::vector<int> expected = {1, 4, 5, 6, 2, 3};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

// TEST(ListInsertManyTests, InsertManyBack) {
//   s21::list<std::string> myList;

//   myList.push_back("apple");
//   myList.push_back("banana");
//   myList.insert_many_back("cherry", "date");

//   std::vector<std::string> expected = {"apple", "banana", "cherry", "date"};
//   int i = 0;
//   for (const auto &value : myList) {
//     EXPECT_EQ(value, expected[i]);
//     ++i;
//   }
// }

// TEST(ListInsertManyTests, InsertManyFront) {
//   s21::list<double> myList;

//   myList.push_back(1.0);
//   myList.push_back(2.0);
//   myList.insert_many_front(0.5, 0.25);

//   std::vector<double> expected = {0.5, 0.25, 1.0, 2.0};
//   auto it = myList.begin();
//   for (const auto &value : expected) {
//     EXPECT_EQ(*it, value);
//     ++it;
//   }
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
