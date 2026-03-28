// TEST_ID: 251
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node.h"

namespace {

class SetScalarTest_251 : public ::testing::Test {
 protected:
  YAML::detail::node n;
};

TEST_F(SetScalarTest_251, SetScalarMakesNodeDefined_251) {
  // We don't assume the initial defined-state, only that after set_scalar it is defined.
  n.set_scalar("hello");
  EXPECT_TRUE(n.is_defined());
}

TEST_F(SetScalarTest_251, SetScalarStoresValue_251) {
  const std::string value = "hello world";
  n.set_scalar(value);
  EXPECT_EQ(n.scalar(), value);
}

TEST_F(SetScalarTest_251, SetScalarOverwritesPreviousValue_251) {
  n.set_scalar("first");
  EXPECT_EQ(n.scalar(), "first");

  n.set_scalar("second");
  EXPECT_EQ(n.scalar(), "second");
  EXPECT_TRUE(n.is_defined());
}

TEST_F(SetScalarTest_251, SetScalarAcceptsEmptyString_251) {
  n.set_scalar(std::string());
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(n.scalar(), "");
}

TEST_F(SetScalarTest_251, SetScalarAcceptsLargeString_251) {
  std::string big(1 << 20, 'x');  // 1 MiB
  n.set_scalar(big);
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(n.scalar().size(), big.size());
  EXPECT_EQ(n.scalar(), big);
}

TEST_F(SetScalarTest_251, SetScalarAcceptsUnicodeUtf8_251) {
  const std::string utf8 = u8"한글-テスト-😀";
  n.set_scalar(utf8);
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(n.scalar(), utf8);
}

// Error/exceptional (observable) behavior: the call should not throw for normal inputs.
TEST_F(SetScalarTest_251, SetScalarDoesNotThrow_251) {
  EXPECT_NO_THROW(n.set_scalar("no-throw"));
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(n.scalar(), "no-throw");
}

}  // namespace