#include <chrono>
#include <list>

#include "gtest/gtest.h"
#include "s21_list.h"

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

TEST(ListIteratorTest, InsertionAndDeletion1) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  s21::list<int>::iterator it = myList.begin();

  it = myList.insert(it, 10);
  it = myList.insert(it, 20);
  it = myList.insert(it, 30);

  std::vector<int> expected_values = {30, 20, 10, 1, 2, 3, 4, 5};
  int index = 0;
  for (const int &value : myList) {
    EXPECT_EQ(value, expected_values[index]);
    ++index;
  }

  it = myList.begin();
  ++it;
  it = myList.erase(it);
  ++it;
  ++it;
  it = myList.erase(it);
  it = myList.erase(it);

  expected_values = {30, 10, 1, 4, 5};
  index = 0;
  for (const int &value : myList) {
    EXPECT_EQ(value, expected_values[index]);
    ++index;
  }
}

TEST(ListIteratorTest, InsertionAndDeletion2) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  s21::list<int>::iterator it = myList.begin();

  it = myList.insert(it, 10);
  it = myList.insert(it, 20);
  it = myList.insert(it, 30);

  std::vector<int> expected_values = {30, 20, 10, 1, 2, 3, 4, 5};
  int index = 0;
  for (const int &value : myList) {
    EXPECT_EQ(value, expected_values[index]);
    ++index;
  }

  it = myList.begin();
  ++it;
  myList.erase(&it);
  ++it;
  ++it;
  myList.erase(&it);
  myList.erase(&it);

  expected_values = {30, 10, 1, 4, 5};
  index = 0;
  for (const int &value : myList) {
    EXPECT_EQ(value, expected_values[index]);
    ++index;
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

TEST(ListInsertManyTests, InsertMany) {
  s21::list<int> myList;

  // Вставляем элементы в середину списка
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);
  auto it = myList.begin();
  ++it;
  myList.insert_many(it, 4, 5, 6);

  // Проверяем результат
  std::vector<int> expected = {1, 4, 5, 6, 2, 3};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(ListInsertManyTests, InsertManyBack) {
  s21::list<std::string> myList;

  // Вставляем элементы в конец списка
  myList.push_back("apple");
  myList.push_back("banana");
  myList.insert_many_back("cherry", "date");

  // Проверяем результат
  std::vector<std::string> expected = {"apple", "banana", "cherry", "date"};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

TEST(ListInsertManyTests, InsertManyFront) {
  s21::list<double> myList;

  // Вставляем элементы в начало списка
  myList.push_back(1.0);
  myList.push_back(2.0);
  myList.insert_many_front(0.5, 0.25);

  // Проверяем результат
  std::vector<double> expected = {0.25, 0.5, 1.0, 2.0};
  int i = 0;
  for (const auto &value : myList) {
    EXPECT_EQ(value, expected[i]);
    ++i;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}