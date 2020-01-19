#include "container.h"
using namespace cpputil;

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <vector>
#include "test.h"
using namespace std;

inline void testArray() {
  cout << "# test array" << endl;
  array<int, 0> a0;
  testResult(toContainer(a0).makeString(), "[]");
  testResult(toContainer(a0).makeString(", "), "[]");
  testResult(toContainer(a0).makeString("<", ", ", ">"), "<>");
  array<int, 1> a1 = {1};
  testResult(toContainer(a1).makeString(), "[1]");
  testResult(toContainer(a1).makeString(", "), "[1]");
  testResult(toContainer(a1).makeString("<", ", ", ">"), "<1>");
  array<int, 2> a2 = {1, 2};
  testResult(toContainer(a2).makeString(), "[1, 2]");
  testResult(toContainer(a2).makeString(", "), "[1, 2]");
  testResult(toContainer(a2).makeString("<", ", ", ">"), "<1, 2>");
}

template <typename IntSeq>
void testSequenceContainer(const char* description) {
  cout << "# test " << description << endl;
  IntSeq seq;

  auto c = toContainer(seq);
  testResult(c.makeString(), "[]");
  testResult(c.makeString(", "), "[]");
  testResult(c.makeString("<", ", ", ">"), "<>");

  seq = IntSeq{1};
  testResult(c.makeString(), "[1]");
  testResult(c.makeString(", "), "[1]");
  testResult(c.makeString("<", ", ", ">"), "<1>");

  seq = IntSeq{1, 2};
  testResult(c.makeString(), "[1, 2]");
  testResult(c.makeString(", "), "[1, 2]");
  testResult(c.makeString("<", ", ", ">"), "<1, 2>");
}

void testMap() {
  cout << "# test map" << endl;
  map<int, int> m;
  auto c = toContainer(m);

  testResult(c.makeString(), "{}");
  testResult(c.makeString(", "), "{}");
  testResult(c.makeString("<", ", ", ">"), "<>");

  m.emplace(1, 2);
  testResult(c.makeString(), "{1 => 2}");
  testResult(c.makeString(", "), "{1 => 2}");
  testResult(c.makeString("<", ", ", ">"), "<1 => 2>");

  m.emplace(2, 4);
  testResult(c.makeString(), "{1 => 2, 2 => 4}");
  testResult(c.makeString(", "), "{1 => 2, 2 => 4}");
  testResult(c.makeString("<", ", ", ">"), "<1 => 2, 2 => 4>");
}

int main(int argc, char* argv[]) {
  testArray();
  testSequenceContainer<deque<int>>("deque");
  testSequenceContainer<vector<int>>("vector");
  testSequenceContainer<list<int>>("list");
  testSequenceContainer<set<int>>("set");
  testSequenceContainer<forward_list<int>>("forward_list");
  testMap();

  // The elements' order in unordered_set and unordered_map are unknown so
  // the tests may not be portable

  return 0;
}
