#include "gtest/gtest.h"
#include "../s21_containers.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q = {1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2(q1);
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2(std::move(q1));
  EXPECT_TRUE(q1.empty());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2;
  q2 = std::move(q1);
  EXPECT_TRUE(q1.empty());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, Front) {
  s21::queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.front(), 1);
}

TEST(QueueTest, Back) {
  s21::queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, PushAndPop) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);

  q.pop();
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.size(), 2);

  q.pop();
  q.pop();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, Swap) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {4, 5};
  q1.swap(q2);
  EXPECT_EQ(q1.size(), 2);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, Empty) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  q.push(42);
  EXPECT_FALSE(q.empty());
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> q;
  EXPECT_EQ(q.size(), 0);
  q.push(10);
  q.push(20);
  EXPECT_EQ(q.size(), 2);
  q.pop();
  EXPECT_EQ(q.size(), 1);
  q.pop();
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, PushAndFront) {
  s21::queue<int> q;
  q.push(5);
  q.push(10);
  q.push(15);
  EXPECT_EQ(q.front(), 5);
  q.pop();
  EXPECT_EQ(q.front(), 10);
  q.pop();
  EXPECT_EQ(q.front(), 15);
}

TEST(QueueTest, Pop) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  q.pop();
  EXPECT_EQ(q.front(), 3);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, SwapEmpty) {
  s21::queue<int> q1;
  s21::queue<int> q2;
  q1.swap(q2);
  EXPECT_TRUE(q1.empty());
  EXPECT_TRUE(q2.empty());
}

TEST(QueueTest, SwapNonEmpty) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {4, 5, 6};
  q1.swap(q2);
  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, CopyConstructorEmpty) {
  s21::queue<int> q1;
  s21::queue<int> q2(q1);
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q2.size(), 0);
}

TEST(QueueTest, CopyConstructorNonEmpty) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, MoveConstructorEmpty) {
  s21::queue<int> q1;
  s21::queue<int> q2(std::move(q1));
  EXPECT_TRUE(q1.empty());
  EXPECT_TRUE(q2.empty());
}

TEST(QueueTest, MoveConstructorNonEmpty) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2(std::move(q1));
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
