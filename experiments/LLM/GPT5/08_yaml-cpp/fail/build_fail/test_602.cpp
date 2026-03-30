// File: yaml-cpp/node/convert_null_test.cpp
// TEST_ID: 602

#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/convert.h"

namespace {

TEST(ConvertNullTest_602, EncodeNullReturnsNode_602) {
  // This exercises the only observable contract we have:
  // YAML::encode(const _Null&) returns a YAML::Node.
  // We only verify it is constructible and does not throw.
  YAML::_Null n;
  EXPECT_NO_THROW({
    YAML::Node node = YAML::encode(n);
    (void)node;
  });
}

TEST(ConvertNullTest_602, EncodeNullCanBeCalledRepeatedly_602) {
  YAML::_Null n;

  EXPECT_NO_THROW({
    YAML::Node a = YAML::encode(n);
    YAML::Node b = YAML::encode(n);
    (void)a;
    (void)b;
  });
}

TEST(ConvertNullTest_602, EncodeNullAcceptsTemporary_602) {
  // Boundary-ish case: pass a temporary object.
  EXPECT_NO_THROW({
    YAML::Node node = YAML::encode(YAML::_Null{});
    (void)node;
  });
}

TEST(ConvertNullTest_602, EncodeNullResultIsDefaultConstructibleNodeLike_602) {
  // We avoid assuming semantics like IsNull(), Type(), or bool conversion.
  // Only check that the returned Node supports copy/move operations.
  YAML::_Null n;

  YAML::Node node = YAML::encode(n);
  EXPECT_NO_THROW({
    YAML::Node copy(node);
    YAML::Node moved(std::move(node));
    (void)copy;
    (void)moved;
  });
}

}  // namespace