// TEST_ID: 241
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

class NodeScalarTest_241 : public ::testing::Test {};

TEST_F(NodeScalarTest_241, DefaultNodeScalarMatchesRefScalar_241) {
  node n;

  // We don't assume what the scalar value is for a default-constructed node.
  // We only verify that node::scalar() is observable and consistent with ref()->scalar().
  ASSERT_NE(n.ref(), nullptr);
  EXPECT_NO_THROW({
    const std::string& s1 = n.scalar();
    const std::string& s2 = n.ref()->scalar();
    EXPECT_EQ(s1, s2);
  });
}

TEST_F(NodeScalarTest_241, SetScalarThenScalarReturnsSameContent_241) {
  node n;

  const std::string value = "hello";
  n.set_scalar(value);

  const std::string& out = n.scalar();
  EXPECT_EQ(out, value);
}

TEST_F(NodeScalarTest_241, ScalarReturnsConstReferenceStableAcrossCallsWithoutMutation_241) {
  node n;

  n.set_scalar("stable");

  const std::string& a = n.scalar();
  const std::string& b = n.scalar();

  // Since the API returns a const reference, repeated calls without mutation
  // should refer to the same underlying string object.
  EXPECT_EQ(&a, &b);
  EXPECT_EQ(a, b);
}

TEST_F(NodeScalarTest_241, ScalarReferenceMatchesUnderlyingRefScalarReference_241) {
  node n;

  n.set_scalar("forwarding-check");

  ASSERT_NE(n.ref(), nullptr);
  const std::string& from_node = n.scalar();
  const std::string& from_ref = n.ref()->scalar();

  // Observable forwarding behavior: both references should refer to the same string.
  EXPECT_EQ(&from_node, &from_ref);
  EXPECT_EQ(from_node, from_ref);
}

TEST_F(NodeScalarTest_241, SetScalarWithEmptyStringRoundTrips_241) {
  node n;

  const std::string value = "";
  n.set_scalar(value);

  const std::string& out = n.scalar();
  EXPECT_EQ(out, value);
}

TEST_F(NodeScalarTest_241, SetScalarWithLongStringRoundTrips_241) {
  node n;

  const std::string value(10000, 'x');
  n.set_scalar(value);

  const std::string& out = n.scalar();
  EXPECT_EQ(out.size(), value.size());
  EXPECT_EQ(out, value);
}

TEST_F(NodeScalarTest_241, SetScalarWithEmbeddedNullRoundTrips_241) {
  node n;

  // std::string can contain embedded '\0'
  const std::string value = std::string("ab\0cd", 5);
  ASSERT_EQ(value.size(), 5u);

  n.set_scalar(value);

  const std::string& out = n.scalar();
  EXPECT_EQ(out.size(), value.size());
  EXPECT_EQ(out, value);
  EXPECT_EQ(out[2], '\0');
}

TEST_F(NodeScalarTest_241, SetScalarWithUtf8ContentRoundTrips_241) {
  node n;

  // UTF-8 content stored as bytes in std::string
  const std::string value = u8"한글-✅-yaml";
  n.set_scalar(value);

  const std::string& out = n.scalar();
  EXPECT_EQ(out, value);
}

TEST_F(NodeScalarTest_241, ScalarCallableOnConstNode_241) {
  node n;
  n.set_scalar("const-ok");

  const node& cn = n;
  const std::string& out = cn.scalar();
  EXPECT_EQ(out, "const-ok");
}

}  // namespace detail
}  // namespace YAML