#include <gtest/gtest.h>

#include <map>

#include "s21_map.h"

TEST(Member_functions_tests, DefaultConstructor) {
  s21::s21_map<int, int> s;
  std::map<int, int> m;

  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), m.size());
}

TEST(Member_functions_tests, InitializerListConstructor) {
  s21::s21_map<int, int> s{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> m{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s.size(), m.size());

  for (auto it = s.begin(); it != s.end(); it++) {
    auto pair = it;
    ASSERT_EQ(pair->second, m[pair->first]);
  }
}

TEST(Member_functions_tests, CopyConstructor) {
  s21::s21_map<int, int> first_map{{1, 2}, {3, 4}, {5, 6}};
  s21::s21_map<int, int> second_map(first_map);

  ASSERT_EQ(first_map.size(), second_map.size());

  for (auto it = second_map.begin(); it != second_map.end(); it++) {
    auto pair = it;
    ASSERT_EQ(pair->second, first_map[pair->first]);
  }
}

TEST(Member_functions_tests, MoveConstructor) {
  s21::s21_map<int, int> first_map{{1, 2}, {3, 4}, {5, 6}};
  s21::s21_map<int, int> second_map(std::move(first_map));

  ASSERT_TRUE(first_map.empty());
  ASSERT_EQ(second_map.size(), 3);
}

TEST(Member_functions_tests, Destructor) {
  auto s = new s21::s21_map<int, int>{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s->size(), 3);

  delete s;
}

TEST(Member_functions_tests, MoveAssignmentOperator) {
  s21::s21_map<int, int> original{{1, 2}, {3, 4}, {5, 6}};
  s21::s21_map<int, int> assigned;

  assigned = std::move(original);

  ASSERT_TRUE(original.empty());
  ASSERT_EQ(assigned.size(), 3);
  ASSERT_EQ(assigned[1], 2);
  ASSERT_EQ(assigned[3], 4);
  ASSERT_EQ(assigned[5], 6);
}

TEST(Iterators_tests, Begin) {
  s21::s21_map<int, int> s21Map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s21Map.begin()->first, stdMap.begin()->first);
  ASSERT_EQ(s21Map.begin()->second, stdMap.begin()->second);
}

TEST(Iterators_tests, End) {
  s21::s21_map<int, int> s21Map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap{{1, 2}, {3, 4}, {5, 6}};

  auto s21MapEnd = s21Map.end();
  s21MapEnd--;
  auto stdMapEnd = stdMap.end();
  stdMapEnd--;

  ASSERT_EQ(s21MapEnd->first, stdMapEnd->first);
  ASSERT_EQ(s21MapEnd->second, stdMapEnd->second);
}

TEST(Element_access_tests, At) {
  s21::s21_map<int, int> s21Map;
  std::map<int, int> stdMap;

  s21Map.insert({1, 2});
  stdMap.insert({1, 2});

  ASSERT_EQ(s21Map.at(1), stdMap.at(1));
}

TEST(Element_access_tests, OperatorBracket) {
  s21::s21_map<int, int> s21Map;
  std::map<int, int> stdMap;

  s21Map[1] = 2;
  stdMap[1] = 2;

  ASSERT_EQ(s21Map[1], stdMap[1]);
}

TEST(Capacity_tests, Empty) {
  s21::s21_map<int, int> s21Map;
  std::map<int, int> stdMap;

  ASSERT_EQ(s21Map.empty(), stdMap.empty());
}

TEST(Capacity_tests, Size) {
  s21::s21_map<int, int> s21Map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s21Map.size(), stdMap.size());
}

TEST(Capacity_tests, MaxSize) {
  s21::s21_map<int, int> s21Map;
  std::map<int, int> stdMap;

  ASSERT_EQ(s21Map.max_size(), stdMap.max_size());
}

TEST(Modifiers_tests, Clear) {
  s21::s21_map<int, int> s21Map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap{{1, 2}, {3, 4}, {5, 6}};

  s21Map.clear();
  stdMap.clear();

  ASSERT_EQ(s21Map.empty(), stdMap.empty());
}

TEST(Modifiers_tests, Insert) {
  s21::s21_map<int, int> s21Map;
  std::map<int, int> stdMap;

  ASSERT_EQ(s21Map.insert({1, 2}).second, stdMap.insert({1, 2}).second);
}

TEST(Modifiers_tests, Insert2) {
  s21::s21_map<int, int> s21Map;
  std::map<int, int> stdMap;

  ASSERT_EQ(s21Map.insert(1, 2).second, stdMap.insert({1, 2}).second);
}

TEST(Modifiers_tests, InsertOrAssign) {
  s21::s21_map<int, int> s21Map;
  std::map<int, int> stdMap;

  ASSERT_EQ(s21Map.insert_or_assign(1, 2).second,
            stdMap.insert_or_assign(1, 2).second);
}

TEST(Modifiers_tests, Erase) {
  s21::s21_map<int, int> s21Map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap{{1, 2}, {3, 4}, {5, 6}};

  s21Map.erase(s21Map.begin());
  stdMap.erase(stdMap.begin());

  ASSERT_EQ(s21Map.size(), stdMap.size());
}

TEST(Modifiers_tests, Swap) {
  s21::s21_map<int, int> s21Map1{{1, 2}, {3, 4}, {5, 6}};
  s21::s21_map<int, int> s21Map2{{7, 8}, {9, 10}, {11, 12}};
  std::map<int, int> stdMap1{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdMap2{{7, 8}, {9, 10}, {11, 12}};

  s21Map1.swap(s21Map2);
  stdMap1.swap(stdMap2);

  ASSERT_EQ(s21Map1.size(), stdMap1.size());
  ASSERT_EQ(s21Map2.size(), stdMap2.size());
}

TEST(Modifiers_tests, Merge) {
  s21::s21_map<int, int> s21Map1{{1, 2}, {3, 4}};
  s21::s21_map<int, int> s21Map2{{5, 6}, {7, 8}};
  std::map<int, int> stdMap1{{1, 2}, {3, 4}};
  std::map<int, int> stdMap2{{5, 6}, {7, 8}};

  s21Map1.merge(s21Map2);
  stdMap1.merge(stdMap2);

  ASSERT_EQ(s21Map1.size(), stdMap1.size());
  ASSERT_EQ(s21Map2.empty(), stdMap2.empty());
}

TEST(Lookup_tests, Contains) {
  s21::s21_map<int, std::string> looking{{1, "one"}, {3, "three"}, {5, "five"}};

  ASSERT_TRUE(looking.contains(1));
  ASSERT_FALSE(looking.contains(7));
}

TEST(Modifiers_tests, EmplaceTest) {
  s21::s21_map<int, std::string> s21_map = {
      {1, "one"}, {3, "three"}, {5, "five"}};
  std::map<int, std::string> std_map = {{1, "one"}, {3, "three"}, {5, "five"}};
  s21_map.insert_many(2, "two");
  std_map.emplace(2, "two");
  s21_map.insert_many(4, "four");
  std_map.emplace(4, "four");

  auto i = s21_map.begin();
  auto j = std_map.begin();
  for (; i != s21_map.end(); i++, j++) {
    ASSERT_EQ(i->first, j->first);
    ASSERT_EQ(i->second, j->second);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
