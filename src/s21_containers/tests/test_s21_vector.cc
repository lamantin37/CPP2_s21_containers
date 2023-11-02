#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

TEST(Member_functions_tests, DefaultConstructor) {
  std::vector<int> std_vec;
  s21::s21_vector<int> s21_vec;

  ASSERT_EQ(std_vec.size(), s21_vec.size());
  ASSERT_EQ(std_vec.empty(), s21_vec.empty());
}

TEST(Member_functions_tests, SizeConstructor) {
  std::vector<int> std_vec(10);
  s21::s21_vector<int> s21_vec(10);

  ASSERT_EQ(std_vec.size(), s21_vec.size());
  ASSERT_EQ(std_vec.empty(), s21_vec.empty());
}

TEST(Member_functions_tests, InitializerListConstructor) {
  std::vector<int> std_vec{1, 2, 3, 4, 5};
  s21::s21_vector<int> s21_vec{1, 2, 3, 4, 5};

  ASSERT_EQ(std_vec.size(), s21_vec.size());
  ASSERT_EQ(std_vec.empty(), s21_vec.empty());

  for (long unsigned int i = 0; i < std_vec.size(); ++i) {
    ASSERT_EQ(std_vec[i], s21_vec[i]);
  }
}

TEST(Member_functions_tests, CopyConstructor) {
  std::vector<int> std_vec{1, 2, 3, 4, 5};
  s21::s21_vector<int> s21_vec1{1, 2, 3, 4, 5};

  std::vector<int> std_vec_copy(std_vec);
  s21::s21_vector<int> s21_vec_copy(s21_vec1);

  ASSERT_EQ(std_vec_copy.size(), s21_vec_copy.size());
  ASSERT_EQ(std_vec_copy.empty(), s21_vec_copy.empty());

  for (long unsigned int i = 0; i < std_vec_copy.size(); ++i) {
    ASSERT_EQ(std_vec_copy[i], s21_vec_copy[i]);
  }
}

TEST(Member_functions_tests, MoveConstructor) {
  std::vector<int> std_vec{1, 2, 3, 4, 5};
  s21::s21_vector<int> s21_vec{1, 2, 3, 4, 5};

  std::vector<int> std_vec_move(std::move(std_vec));
  s21::s21_vector<int> s21_vec_move(std::move(s21_vec));

  ASSERT_EQ(std_vec.size(), s21_vec.size());
  ASSERT_EQ(std_vec.empty(), s21_vec.empty());

  ASSERT_EQ(std_vec_move.size(), s21_vec_move.size());
  ASSERT_EQ(std_vec_move.empty(), s21_vec_move.empty());
}

TEST(Member_functions_tests, MoveAssignmentOperator) {
  std::vector<int> std_vec1{1, 2, 3, 4, 5};
  s21::s21_vector<int> s21_vec1{1, 2, 3, 4, 5};

  std::vector<int> std_vec2;
  s21::s21_vector<int> s21_vec2;

  std_vec2 = std::move(std_vec1);
  s21_vec2 = std::move(s21_vec1);

  ASSERT_EQ(std_vec1.size(), s21_vec1.size());
  ASSERT_EQ(std_vec1.empty(), s21_vec1.empty());

  ASSERT_EQ(std_vec2.size(), s21_vec2.size());
  ASSERT_EQ(std_vec2.empty(), s21_vec2.empty());
}

TEST(Element_access_tests, At) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec.at(i), std_vec.at(i));
  }

  EXPECT_THROW(s21_vec.at(100), std::out_of_range);
}

TEST(Element_access_tests, SquareBracketsOperator) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(Element_access_tests, Front) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  EXPECT_EQ(s21_vec.front(), std_vec.front());
}

TEST(Element_access_tests, Back) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST(Element_access_tests, Data) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(*(s21_vec.data() + i), *(std_vec.data() + i));
  }
}

TEST(Iterators_tests, Begin) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  EXPECT_EQ(*s21_vec.begin(), *std_vec.begin());
}

TEST(Iterators_tests, End) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  auto s21_it = s21_vec.begin();
  auto std_it = std_vec.begin();
  while (s21_it != s21_vec.end() && std_it != std_vec.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }

  EXPECT_EQ(s21_it, s21_vec.end());
  EXPECT_EQ(std_it, std_vec.end());
}

TEST(Capacity_tests, Empty) {
  s21::s21_vector<int> s21_vec;
  std::vector<int> std_vec;

  EXPECT_EQ(s21_vec.empty(), std_vec.empty());

  s21_vec.push_back(1);
  std_vec.push_back(1);

  EXPECT_EQ(s21_vec.empty(), std_vec.empty());
}

TEST(Capacity_tests, Size) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  EXPECT_EQ(s21_vec.size(), std_vec.size());
}

TEST(Capacity_tests, MaxSize) {
  s21::s21_vector<int> s21_vec;
  std::vector<int> std_vec;

  EXPECT_EQ(s21_vec.max_size(), std_vec.max_size());
}

TEST(Capacity_tests, ReserveCapacity) {
  s21::s21_vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.reserve(100);
  std_vec.reserve(100);

  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST(Capacity_tests, ShrinkToFit) {
  s21::s21_vector<int> s21_vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  s21_vec.reserve(100);
  std_vec.reserve(100);

  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST(Modifiers_tests, Clear) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.clear();
  std_vec.clear();

  EXPECT_EQ(s21_vec.size(), std_vec.size());
}

TEST(Modifiers_tests, Insert) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.insert(s21_vec.begin(), 4);
  std_vec.insert(std_vec.begin(), 4);

  EXPECT_TRUE(std::equal(s21_vec.begin(), s21_vec.end(), std_vec.begin()));
}

TEST(Modifiers_tests, Erase) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.erase(s21_vec.begin());
  std_vec.erase(std_vec.begin());

  EXPECT_TRUE(std::equal(s21_vec.begin(), s21_vec.end(), std_vec.begin()));
}

TEST(Modifiers_tests, PushBack) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.push_back(4);
  std_vec.push_back(4);

  EXPECT_TRUE(std::equal(s21_vec.begin(), s21_vec.end(), std_vec.begin()));
}

TEST(Modifiers_tests, PopBack) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.pop_back();
  std_vec.pop_back();

  EXPECT_TRUE(std::equal(s21_vec.begin(), s21_vec.end(), std_vec.begin()));
}

TEST(Modifiers_tests, Swap) {
  s21::s21_vector<int> s21_vec1{1, 2, 3};
  s21::s21_vector<int> s21_vec2{4, 5, 6};
  std::vector<int> std_vec1{1, 2, 3};
  std::vector<int> std_vec2{4, 5, 6};

  s21_vec1.swap(s21_vec2);
  std_vec1.swap(std_vec2);

  EXPECT_TRUE(std::equal(s21_vec1.begin(), s21_vec1.end(), std_vec1.begin()));
  EXPECT_TRUE(std::equal(s21_vec2.begin(), s21_vec2.end(), std_vec2.begin()));
}

TEST(Modifiers_tests, Emplace1) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21::s21_vector<int>::const_iterator s21_it = s21_vec.cbegin();
  auto std_it = std_vec.begin();
  s21_vec.insert_many(s21_it, 0);
  std_vec.emplace(std_it, 0);

  auto i = s21_vec.begin();
  auto j = std_vec.begin();
  for (; i != s21_vec.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(Modifiers_tests, Emplace2) {
  s21::s21_vector<int> s21_vec{1, 3, 4};
  std::vector<int> std_vec{1, 3, 4};

  s21::s21_vector<int>::const_iterator s21_it = s21_vec.cbegin();
  auto std_it = std_vec.begin();
  std_it++;
  s21_it++;
  s21_vec.insert_many(s21_it, 2);
  std_vec.emplace(std_it, 2);

  auto i = s21_vec.begin();
  auto j = std_vec.begin();
  for (; i != s21_vec.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

TEST(Modifiers_tests, EmplaceBack) {
  s21::s21_vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.emplace_back(4);
  std_vec.emplace_back(4);

  auto i = s21_vec.begin();
  auto j = std_vec.begin();
  for (; i != s21_vec.end(); ++i, ++j) {
    EXPECT_EQ(*i, *j);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
