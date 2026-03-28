// File: yaml-cpp/node/convert_map_decode_test_608.cpp

#include <gtest/gtest.h>

#include <map>
#include <string>

#include <yaml-cpp/yaml.h>          // YAML::Node, YAML::NodeType, YAML::convert
#include <yaml-cpp/exceptions.h>    // YAML::BadConversion (if enabled in this build)

namespace {

class ConvertMapDecodeTest_608 : public ::testing::Test {
 protected:
  // Helper to build a YAML map node without relying on parsing.
  static YAML::Node MakeMapNode() {
    return YAML::Node(YAML::NodeType::Map);
  }
};

TEST_F(ConvertMapDecodeTest_608, ReturnsFalseAndDoesNotModifyMapWhenNodeIsNotMap_608) {
  std::map<std::string, int> out;
  out["keep"] = 123;

  // Null node
  {
    YAML::Node n;  // default constructed
    const bool ok = YAML::convert<std::map<std::string, int>>::decode(n, out);
    EXPECT_FALSE(ok);
    // Per interface behavior: when !IsMap(), decode returns false before clearing.
    EXPECT_EQ(out.size(), 1u);
    EXPECT_EQ(out["keep"], 123);
  }

  // Scalar node
  {
    YAML::Node n("scalar");
    const bool ok = YAML::convert<std::map<std::string, int>>::decode(n, out);
    EXPECT_FALSE(ok);
    EXPECT_EQ(out.size(), 1u);
    EXPECT_EQ(out["keep"], 123);
  }

  // Sequence node
  {
    YAML::Node n(YAML::NodeType::Sequence);
    n.push_back("a");
    n.push_back("b");
    const bool ok = YAML::convert<std::map<std::string, int>>::decode(n, out);
    EXPECT_FALSE(ok);
    EXPECT_EQ(out.size(), 1u);
    EXPECT_EQ(out["keep"], 123);
  }
}

TEST_F(ConvertMapDecodeTest_608, ReturnsTrueAndClearsExistingContentsWhenNodeIsMap_608) {
  std::map<std::string, int> out;
  out["old1"] = 1;
  out["old2"] = 2;

  YAML::Node n = MakeMapNode();
  n.force_insert("newKey", 42);

  const bool ok = YAML::convert<std::map<std::string, int>>::decode(n, out);
  EXPECT_TRUE(ok);

  // Existing contents should be cleared then repopulated.
  EXPECT_EQ(out.size(), 1u);
  EXPECT_EQ(out["newKey"], 42);
  EXPECT_EQ(out.count("old1"), 0u);
  EXPECT_EQ(out.count("old2"), 0u);
}

TEST_F(ConvertMapDecodeTest_608, DecodesAllEntriesFromMapNode_608) {
  YAML::Node n = MakeMapNode();
  n.force_insert("a", 1);
  n.force_insert("b", 2);
  n.force_insert("c", 3);

  std::map<std::string, int> out;
  const bool ok = YAML::convert<std::map<std::string, int>>::decode(n, out);
  EXPECT_TRUE(ok);

  EXPECT_EQ(out.size(), 3u);
  EXPECT_EQ(out["a"], 1);
  EXPECT_EQ(out["b"], 2);
  EXPECT_EQ(out["c"], 3);
}

TEST_F(ConvertMapDecodeTest_608, DecodingEmptyMapResultsInEmptyStdMap_608) {
  YAML::Node n = MakeMapNode();  // empty map node

  std::map<std::string, int> out;
  out["preexisting"] = 9;

  const bool ok = YAML::convert<std::map<std::string, int>>::decode(n, out);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.empty());
}

TEST_F(ConvertMapDecodeTest_608, SupportsNonStringKeyTypesWhenConvertible_608) {
  YAML::Node n = MakeMapNode();
  // Insert keys as scalars that should be convertible to int.
  n.force_insert("10", "100");
  n.force_insert("20", "200");

  std::map<int, int> out;
  const bool ok = YAML::convert<std::map<int, int>>::decode(n, out);
  EXPECT_TRUE(ok);

  EXPECT_EQ(out.size(), 2u);
  EXPECT_EQ(out[10], 100);
  EXPECT_EQ(out[20], 200);
}

TEST_F(ConvertMapDecodeTest_608, ThrowsOnUnconvertibleKeyOrValueIfAsConversionFails_608) {
  YAML::Node n = MakeMapNode();
  // Key "not_an_int" cannot be converted to int (expected to throw via Node::as<int>()).
  n.force_insert("not_an_int", "1");

  std::map<int, int> out;

  // If this build of yaml-cpp throws YAML::BadConversion, verify it.
  // Otherwise, accept any exception to avoid assuming a specific exception type.
  try {
    (void)YAML::convert<std::map<int, int>>::decode(n, out);
    FAIL() << "Expected an exception due to unconvertible key.";
  } catch (const YAML::BadConversion&) {
    SUCCEED();
  } catch (...) {
    SUCCEED();
  }
}

}  // namespace