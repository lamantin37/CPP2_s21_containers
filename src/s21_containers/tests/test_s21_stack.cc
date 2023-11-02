#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> stack;
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0u);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> stack = {1, 2, 3};
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.size(), 3u);
  EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, PushAndPop) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  EXPECT_EQ(stack.size(), 3u);
  EXPECT_EQ(stack.top(), 3);

  stack.pop();
  EXPECT_EQ(stack.size(), 2u);
  EXPECT_EQ(stack.top(), 2);

  stack.pop();
  stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2(stack1);
  EXPECT_EQ(stack1.size(), stack2.size());
  EXPECT_EQ(stack1.top(), stack2.top());
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2(std::move(stack1));
  EXPECT_TRUE(stack1.empty());
  EXPECT_FALSE(stack2.empty());
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2;
  stack2 = std::move(stack1);
  EXPECT_TRUE(stack1.empty());
  EXPECT_FALSE(stack2.empty());
}

TEST(StackTest, Swap) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2 = {4, 5, 6};
  stack1.swap(stack2);
  EXPECT_EQ(stack1.size(), 3u);
  EXPECT_EQ(stack2.size(), 3u);
  EXPECT_EQ(stack1.top(), 6);
  EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, EmptyStack) {
  s21::stack<int> stack;
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0u);
}

TEST(StackTest, Push) {
  s21::stack<int> stack;
  stack.push(1);
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.size(), 1u);
  EXPECT_EQ(stack.top(), 1);
}

class CustomType {
 public:
  int value;
  CustomType(int val) : value(val) {}
};

TEST(StackTest, CustomType) {
  s21::stack<CustomType> stack;
  CustomType obj1(42);
  CustomType obj2(23);

  stack.push(obj1);
  stack.push(obj2);
  EXPECT_EQ(stack.size(), 2u);
  EXPECT_EQ(stack.top().value, obj2.value);

  stack.pop();
  EXPECT_EQ(stack.size(), 1u);
  EXPECT_EQ(stack.top().value, obj1.value);
}

TEST(StackTest, DoubleStack) {
  s21::stack<double> stack;
  stack.push(3.14);
  stack.push(2.71);

  EXPECT_EQ(stack.size(), 2u);
  EXPECT_DOUBLE_EQ(stack.top(), 2.71);
}

TEST(StackTest, PopAll) {
  s21::stack<int> stack = {1, 2, 3, 4, 5};
  stack.pop();
  stack.pop();
  stack.pop();
  stack.pop();
  stack.pop();

  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0u);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
