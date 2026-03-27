// File: ./TestProjects/yaml-cpp/test/emit_dump_test_97.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>  // YAML::Node, YAML::Dump

namespace {

class DumpTest_97 : public ::testing::Test {};

TEST_F(DumpTest_97, DumpEmptyDefaultNodeReturnsString_97) {
  YAML::Node n;  // default-constructed
  const std::string out = YAML::Dump(n);
  // Black-box: just ensure it returns a usable string (no crash, stable string object).
  EXPECT_TRUE(out.size() >= 0u);
}

TEST_F(DumpTest_97, DumpScalarStringReturnsNonEmptyString_97) {
  YAML::Node n("hello");
  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpScalarIntegerReturnsNonEmptyString_97) {
  YAML::Node n(123);
  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpScalarBoolReturnsNonEmptyString_97) {
  YAML::Node n(true);
  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpNullNodeReturnsNonEmptyOrEmptyButNotCrash_97) {
  YAML::Node n(YAML::NodeType::Null);
  const std::string out = YAML::Dump(n);
  EXPECT_TRUE(out.size() >= 0u);
}

TEST_F(DumpTest_97, DumpEmptySequenceReturnsNonEmptyString_97) {
  YAML::Node n(YAML::NodeType::Sequence);
  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpSequenceWithScalarsReturnsNonEmptyString_97) {
  YAML::Node n(YAML::NodeType::Sequence);
  n.push_back(1);
  n.push_back("two");
  n.push_back(false);

  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpEmptyMapReturnsNonEmptyString_97) {
  YAML::Node n(YAML::NodeType::Map);
  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpMapWithScalarKeysAndValuesReturnsNonEmptyString_97) {
  YAML::Node n(YAML::NodeType::Map);
  n["a"] = 1;
  n["b"] = "two";
  n["c"] = false;

  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpNestedStructureReturnsNonEmptyString_97) {
  YAML::Node root(YAML::NodeType::Map);
  root["name"] = "yaml";
  root["nums"] = YAML::Node(YAML::NodeType::Sequence);
  root["nums"].push_back(1);
  root["nums"].push_back(2);

  YAML::Node inner(YAML::NodeType::Map);
  inner["k"] = "v";
  root["obj"] = inner;

  const std::string out = YAML::Dump(root);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpDeterministicForSameNodeAcrossCalls_97) {
  YAML::Node n(YAML::NodeType::Map);
  n["x"] = 42;
  n["y"] = "z";

  const std::string out1 = YAML::Dump(n);
  const std::string out2 = YAML::Dump(n);

  // Observable behavior: dumping the same node twice should be stable.
  EXPECT_EQ(out1, out2);
}

TEST_F(DumpTest_97, DumpDoesNotMutateNodeShape_97) {
  YAML::Node n(YAML::NodeType::Sequence);
  n.push_back(1);
  n.push_back(2);
  const std::size_t before = n.size();

  (void)YAML::Dump(n);

  // Observable via public API: size should remain unchanged.
  EXPECT_EQ(n.size(), before);
}

TEST_F(DumpTest_97, DumpLargeSequenceDoesNotCrashAndReturnsNonEmpty_97) {
  YAML::Node n(YAML::NodeType::Sequence);
  for (int i = 0; i < 2000; ++i) {
    n.push_back(i);
  }

  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpWithSpecialCharactersInScalarReturnsNonEmpty_97) {
  YAML::Node n("line1\nline2: value # comment?");
  const std::string out = YAML::Dump(n);
  EXPECT_FALSE(out.empty());
}

TEST_F(DumpTest_97, DumpInvalidOrUndefinedNodeDoesNotThrowStdExceptions_97) {
  // We don't assume yaml-cpp throws or not; we only check no *unexpected* std exceptions escape.
  YAML::Node n;  // default
  EXPECT_NO_THROW({
    const std::string out = YAML::Dump(n);
    (void)out;
  });
}

}  // namespace
