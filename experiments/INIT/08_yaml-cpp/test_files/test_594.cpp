// TEST_ID: 594
#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

TEST(YAMLDecodeTest_594, ReturnsTrueAndCopiesScalarNode_594) {
  const YAML::Node src("hello");
  YAML::Node dst;

  const bool ok = YAML::decode(src, dst);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(dst.is(src));
  EXPECT_TRUE(dst.IsScalar());
  EXPECT_EQ(dst.Scalar(), src.Scalar());
}

TEST(YAMLDecodeTest_594, OverwritesExistingDestinationContent_594) {
  YAML::Node src;
  src.push_back(1);
  src.push_back(2);

  YAML::Node dst("original");

  const bool ok = YAML::decode(src, dst);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(dst.is(src));
  EXPECT_TRUE(dst.IsSequence());
  EXPECT_EQ(dst.size(), src.size());
}

TEST(YAMLDecodeTest_594, CopiesMapNodeAndAllowsKeyLookup_594) {
  YAML::Node src;
  src.force_insert("k1", "v1");
  src.force_insert("k2", "v2");

  YAML::Node dst;

  const bool ok = YAML::decode(src, dst);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(dst.is(src));
  EXPECT_TRUE(dst.IsMap());

  // Observable behavior through public API: operator[] + Scalar()
  EXPECT_TRUE(dst["k1"].IsDefined());
  EXPECT_TRUE(dst["k1"].IsScalar());
  EXPECT_EQ(dst["k1"].Scalar(), "v1");

  EXPECT_TRUE(dst["k2"].IsDefined());
  EXPECT_TRUE(dst["k2"].IsScalar());
  EXPECT_EQ(dst["k2"].Scalar(), "v2");
}

TEST(YAMLDecodeTest_594, SelfDecodeDoesNotCorruptNode_594) {
  YAML::Node n("x");

  const bool ok = YAML::decode(n, n);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.Scalar(), "x");
}

}  // namespace