// TEST_ID: 658
//
// Unit tests for yaml-cpp/stlemitter.h operator<< overload for std::map<K,V>.
//
// Constraints honored:
// - Treat YAML::Emitter as a black box: we only use public APIs (c_str/size/good/GetLastError)
// - We do NOT access private state
// - We avoid asserting an exact YAML formatting (flow vs block, braces, spacing, quoting).
//   Instead, we assert observable properties: emitter stays "good", chaining works, and
//   serialized output contains keys/values in expected relative order for simple scalars.

#include <gtest/gtest.h>

#include <map>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/stlemitter.h"

namespace {

class StlEmitterMapTest_658 : public ::testing::Test {
protected:
  static std::string Dump(YAML::Emitter& out) {
    // Prefer c_str/size for a stable view of the produced buffer.
    const char* s = out.c_str();
    return s ? std::string(s, out.size()) : std::string();
  }

  static void ExpectGood(const YAML::Emitter& out) {
    EXPECT_TRUE(out.good()) << "Emitter not good. LastError=" << out.GetLastError();
  }

  static size_t FindOrFail(const std::string& haystack, const std::string& needle) {
    const size_t pos = haystack.find(needle);
    EXPECT_NE(pos, std::string::npos) << "Expected to find substring: [" << needle
                                      << "] in output: [" << haystack << "]";
    return pos;
  }
};

TEST_F(StlEmitterMapTest_658, ReturnsSameEmitterReference_658) {
  YAML::Emitter out;
  std::map<std::string, int> m{{"a", 1}};

  YAML::Emitter* returned = &(out << m);
  EXPECT_EQ(returned, &out);

  ExpectGood(out);
}

TEST_F(StlEmitterMapTest_658, EmptyMapDoesNotErrorAndProducesSomeOutput_658) {
  YAML::Emitter out;
  std::map<std::string, int> m;

  out << m;

  ExpectGood(out);
  const std::string dumped = Dump(out);

  // We don't assume exact YAML style. Just ensure the emitter produced something.
  EXPECT_GT(dumped.size(), 0u) << "Empty map serialization unexpectedly empty.";
}

TEST_F(StlEmitterMapTest_658, SingleElementMapContainsKeyAndValue_658) {
  YAML::Emitter out;
  std::map<std::string, int> m{{"key", 42}};

  out << m;

  ExpectGood(out);
  const std::string dumped = Dump(out);

  // Avoid exact formatting expectations; just require the tokens appear.
  FindOrFail(dumped, "key");
  FindOrFail(dumped, "42");
}

TEST_F(StlEmitterMapTest_658, MultipleElementsPreserveRelativeOrderOfPairs_658) {
  YAML::Emitter out;

  // std::map iteration is ordered by key. We rely only on that standard behavior,
  // and on the observable output containing the key/value spellings.
  std::map<std::string, int> m{{"a", 1}, {"b", 2}, {"c", 3}};

  out << m;

  ExpectGood(out);
  const std::string dumped = Dump(out);

  // Verify each key/value appears and that the overall order is consistent with map order.
  const size_t aPos = FindOrFail(dumped, "a");
  const size_t onePos = FindOrFail(dumped, "1");
  const size_t bPos = FindOrFail(dumped, "b");
  const size_t twoPos = FindOrFail(dumped, "2");
  const size_t cPos = FindOrFail(dumped, "c");
  const size_t threePos = FindOrFail(dumped, "3");

  // "a" should appear before "b" before "c", and each key should appear before its value.
  EXPECT_LT(aPos, bPos);
  EXPECT_LT(bPos, cPos);

  EXPECT_LT(aPos, onePos);
  EXPECT_LT(bPos, twoPos);
  EXPECT_LT(cPos, threePos);
}

TEST_F(StlEmitterMapTest_658, WorksWithNonStringKeyValueTypes_658) {
  YAML::Emitter out;
  std::map<int, int> m{{10, 20}, {30, 40}};

  out << m;

  ExpectGood(out);
  const std::string dumped = Dump(out);

  // Ensure integer tokens appear (again without asserting exact YAML punctuation).
  FindOrFail(dumped, "10");
  FindOrFail(dumped, "20");
  FindOrFail(dumped, "30");
  FindOrFail(dumped, "40");
}

TEST_F(StlEmitterMapTest_658, NestedMapEmitsAllNestedKeysAndValues_658) {
  YAML::Emitter out;

  std::map<std::string, std::map<std::string, int>> m{
      {"outer", {{"innerA", 1}, {"innerB", 2}}},
  };

  out << m;

  ExpectGood(out);
  const std::string dumped = Dump(out);

  // Presence checks only; nested formatting can vary.
  FindOrFail(dumped, "outer");
  FindOrFail(dumped, "innerA");
  FindOrFail(dumped, "1");
  FindOrFail(dumped, "innerB");
  FindOrFail(dumped, "2");
}

TEST_F(StlEmitterMapTest_658, CanChainAfterMapInsertion_658) {
  YAML::Emitter out;
  std::map<std::string, int> m{{"k", 7}};

  // Observable behavior: the returned reference supports further streaming.
  out << m << YAML::Newline << "tail";

  ExpectGood(out);
  const std::string dumped = Dump(out);

  FindOrFail(dumped, "k");
  FindOrFail(dumped, "7");
  FindOrFail(dumped, "tail");
}

}  // namespace