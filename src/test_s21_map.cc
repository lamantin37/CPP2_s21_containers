#include <gtest/gtest.h>

#include <map>
#include <vector>

#include "s21_map.h"
#include "s21_vector.h"

TEST(Member_functions_tests, DefaultConstructor) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  ASSERT_TRUE(s21map.empty());
  ASSERT_EQ(s21map.size(), stdmap.size());
}

TEST(Member_functions_tests, InitializerListConstructor) {
  s21::s21_map<int, int> s21map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdmap{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s21map.size(), stdmap.size());

  for (auto it = s21map.begin(); it != s21map.end(); it++) {
    auto pair = it;
    ASSERT_EQ(pair->second, stdmap[pair->first]);
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

TEST(Member_functions_tests, CopyAssignmentOperator) {
  s21::s21_map<int, int> original{{1, 2}, {3, 4}, {5, 6}};
  s21::s21_map<int, int> copied;

  copied = original;

  ASSERT_EQ(copied.size(), 3);
  ASSERT_EQ(copied[1], original[1]);
  ASSERT_EQ(copied[3], original[3]);
  ASSERT_EQ(copied[5], original[5]);
}

TEST(Member_functions_tests, MoveConstructor) {
  s21::s21_map<int, int> first_map{{1, 2}, {3, 4}, {5, 6}};
  s21::s21_map<int, int> second_map(std::move(first_map));

  ASSERT_TRUE(first_map.empty());
  ASSERT_EQ(second_map.size(), 3);
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

TEST(Member_functions_tests, Destructor) {
  auto s21map = new s21::s21_map<int, int>{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s21map->size(), 3);

  delete s21map;
}

TEST(Element_access_tests, OperatorBracket) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  s21map[1] = 2;
  stdmap[1] = 2;

  ASSERT_EQ(s21map[1], stdmap[1]);
}

TEST(Element_access_tests, OperatorBracket2) {
  s21::s21_map<int, std::vector<std::string>> s21map;
  std::map<int, std::vector<std::string>> stdmap;

  s21map[1] = {"one", "uno", "eins"};
  stdmap[1] = {"one", "uno", "eins"};

  ASSERT_EQ(s21map[1], stdmap[1]);
}

TEST(Element_access_tests, At) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  s21map.insert({1, 2});
  stdmap.insert({1, 2});

  ASSERT_EQ(s21map.at(1), stdmap.at(1));
}

TEST(Element_access_tests, At2) {
  s21::s21_map<int, std::pair<std::string, double>> s21map;
  std::map<int, std::pair<std::string, double>> stdmap;

  s21map.insert({1, {"apple", 0.5}});
  stdmap.insert({1, {"apple", 0.5}});

  ASSERT_EQ(s21map.at(1), stdmap.at(1));
}

TEST(Iterators_tests, Begin) {
  s21::s21_map<int, int> s21map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdmap{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s21map.begin()->first, stdmap.begin()->first);
  ASSERT_EQ(s21map.begin()->second, stdmap.begin()->second);
}

TEST(Iterators_tests, Begin2) {
  s21::s21_map<int, std::vector<int>> s21map{{1, {2, 3, 4}}, {5, {6, 7, 8}}};
  std::map<int, std::vector<int>> stdmap{{1, {2, 3, 4}}, {5, {6, 7, 8}}};

  ASSERT_EQ(s21map.begin()->first, stdmap.begin()->first);
  ASSERT_EQ(s21map.begin()->second, stdmap.begin()->second);
}

TEST(Iterators_tests, End) {
  s21::s21_map<int, int> s21map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdmap{{1, 2}, {3, 4}, {5, 6}};

  auto s21MapEnd = s21map.end();
  s21MapEnd--;
  auto stdMapEnd = stdmap.end();
  stdMapEnd--;

  ASSERT_EQ(s21MapEnd->first, stdMapEnd->first);
  ASSERT_EQ(s21MapEnd->second, stdMapEnd->second);
}

TEST(Capacity_tests, Empty) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  ASSERT_EQ(s21map.empty(), stdmap.empty());
}

TEST(Capacity_tests, Size) {
  s21::s21_map<int, int> s21map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdmap{{1, 2}, {3, 4}, {5, 6}};

  ASSERT_EQ(s21map.size(), stdmap.size());
}

TEST(Capacity_tests, MaxSize) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  ASSERT_EQ(s21map.max_size(), stdmap.max_size());
}

TEST(Modifiers_tests, Clear) {
  s21::s21_map<int, int> s21map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdmap{{1, 2}, {3, 4}, {5, 6}};

  s21map.clear();
  stdmap.clear();

  ASSERT_EQ(s21map.empty(), stdmap.empty());
}

TEST(Modifiers_tests, Insert) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  ASSERT_EQ(s21map.insert({1, 2}).second, stdmap.insert({1, 2}).second);
}

TEST(Modifiers_tests, Insert2) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  ASSERT_EQ(s21map.insert(1, 2).second, stdmap.insert({1, 2}).second);
}

TEST(Modifiers_tests, Insert3) {
  s21::s21_map<std::string, std::vector<int>> s21map;
  std::map<std::string, std::vector<int>> stdmap;

  ASSERT_EQ(s21map.insert({"fruits", {1, 2, 3}}).second,
            stdmap.insert({"fruits", {1, 2, 3}}).second);
}

TEST(Modifiers_tests, InsertOrAssign) {
  s21::s21_map<int, int> s21map;
  std::map<int, int> stdmap;

  ASSERT_EQ(s21map.insert_or_assign(1, 2).second,
            stdmap.insert_or_assign(1, 2).second);
}

TEST(Modifiers_tests, Erase) {
  s21::s21_map<int, int> s21map{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdmap{{1, 2}, {3, 4}, {5, 6}};

  s21map.erase(s21map.begin());
  stdmap.erase(stdmap.begin());

  ASSERT_EQ(s21map.size(), stdmap.size());
}

TEST(Modifiers_tests, Swap) {
  s21::s21_map<int, int> s21map1{{1, 2}, {3, 4}, {5, 6}};
  s21::s21_map<int, int> s21map2{{7, 8}, {9, 10}, {11, 12}};
  std::map<int, int> stdmap1{{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> stdmap2{{7, 8}, {9, 10}, {11, 12}};

  s21map1.swap(s21map2);
  stdmap1.swap(stdmap2);

  ASSERT_EQ(s21map1.size(), stdmap1.size());
  ASSERT_EQ(s21map2.size(), stdmap2.size());
}

TEST(Modifiers_tests, Merge) {
  s21::s21_map<int, int> s21map1{{1, 2}, {3, 4}};
  s21::s21_map<int, int> s21map2{{5, 6}, {7, 8}};
  std::map<int, int> stdmap1{{1, 2}, {3, 4}};
  std::map<int, int> stdmap2{{5, 6}, {7, 8}};

  s21map1.merge(s21map2);
  stdmap1.merge(stdmap2);

  ASSERT_EQ(s21map1.size(), stdmap1.size());
  ASSERT_EQ(s21map2.empty(), stdmap2.empty());
}

TEST(Lookup_tests, Contains) {
  s21::s21_map<int, std::string> looking{{1, "one"}, {3, "three"}, {5, "five"}};

  ASSERT_TRUE(looking.contains(1));
  ASSERT_FALSE(looking.contains(7));
}

TEST(Lookup_tests, Contains2) {
  s21::s21_map<std::string, std::vector<std::string>> looking{
      {"fruits", {"apple", "banana", "cherry"}},
      {"colors", {"red", "green", "blue"}}};

  ASSERT_TRUE(looking.contains("fruits"));
  ASSERT_FALSE(looking.contains("animals"));
}

TEST(Bonus_tests, InsertMany) {
  s21::s21_map<int, std::string> s21map = {
      {1, "one"}, {3, "three"}, {5, "five"}};
  std::map<int, std::string> stdmap = {{1, "one"}, {3, "three"}, {5, "five"}};
  s21map.insert_many(2, "two");
  stdmap.emplace(2, "two");
  s21map.insert_many(4, "four");
  stdmap.emplace(4, "four");

  auto i = s21map.begin();
  auto j = stdmap.begin();
  for (; i != s21map.end(); i++, j++) {
    ASSERT_EQ(i->first, j->first);
    ASSERT_EQ(i->second, j->second);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
