#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 10> arr;
  ASSERT_EQ(arr.size(), 0);
  ASSERT_TRUE(arr.empty());
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 10> arr = {1, 2, 3};
  ASSERT_EQ(arr.size(), 3);
  ASSERT_EQ(arr[0], 1);
  ASSERT_EQ(arr[1], 2);
  ASSERT_EQ(arr[2], 3);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 10> arr1 = {1, 2, 3};
  s21::array<int, 10> arr2 = arr1;
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr2[0], 1);
  ASSERT_EQ(arr2[1], 2);
  ASSERT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 10> arr1 = {1, 2, 3};
  s21::array<int, 10> arr2 = std::move(arr1);
  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr2[0], 1);
  ASSERT_EQ(arr2[1], 2);
  ASSERT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 10> arr1 = {1, 2, 3};
  s21::array<int, 10> arr2;
  arr2 = std::move(arr1);
  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr2[0], 1);
  ASSERT_EQ(arr2[1], 2);
  ASSERT_EQ(arr2[2], 3);
}

TEST(ArrayTest, At) {
  s21::array<int, 10> arr = {1, 2, 3};
  ASSERT_EQ(arr.at(0), 1);
  ASSERT_EQ(arr.at(1), 2);
  ASSERT_EQ(arr.at(2), 3);
  ASSERT_THROW(arr.at(3), std::out_of_range);
}

TEST(ArrayTest, Front) {
  s21::array<int, 10> arr = {1, 2, 3};
  ASSERT_EQ(arr.front(), 1);
}

TEST(ArrayTest, Back) {
  s21::array<int, 10> arr = {1, 2, 3};
  ASSERT_EQ(arr.back(), 3);
}

TEST(ArrayTest, Iterator) {
  s21::array<int, 10> arr = {1, 2, 3};
  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    sum += *it;
  }
  ASSERT_EQ(sum, 6);
}

TEST(ArrayTest, ConstIterator) {
  const s21::array<int, 10> arr = {1, 2, 3};
  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    sum += *it;
  }
  ASSERT_EQ(sum, 6);
}

TEST(ArrayTest, Empty) {
  s21::array<int, 10> arr;
  ASSERT_TRUE(arr.empty());
  arr = {1, 2, 3};
  ASSERT_FALSE(arr.empty());
}

TEST(ArrayTest, Size) {
  s21::array<int, 10> arr;
  ASSERT_EQ(arr.size(), 0);
  arr = {1, 2, 3};
  ASSERT_EQ(arr.size(), 3);
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 10> arr;
  ASSERT_EQ(arr.max_size(), 10);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 10> arr1 = {1, 2, 3};
  s21::array<int, 10> arr2 = {4, 5};
  arr1.swap(arr2);
  ASSERT_EQ(arr1.size(), 2);
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr1[0], 4);
  ASSERT_EQ(arr1[1], 5);
  ASSERT_EQ(arr2[0], 1);
  ASSERT_EQ(arr2[1], 2);
  ASSERT_EQ(arr2[2], 3);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 10> arr = {1, 2, 3};
  arr.fill(0);
  ASSERT_EQ(arr[0], 0);
  ASSERT_EQ(arr[1], 0);
  ASSERT_EQ(arr[2], 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
