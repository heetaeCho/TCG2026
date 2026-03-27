// TEST_ID: 558
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/node/node.h"

namespace {

class TagTest_558 : public ::testing::Test {};

TEST_F(TagTest_558, DefaultConstructedNodeTagDoesNotThrow_558) {
  YAML::Node n;
  EXPECT_NO_THROW({
    const std::string& t = n.Tag();
    (void)t;
  });
}

TEST_F(TagTest_558, DefaultConstructedNodeTagReferenceIsStableAcrossCalls_558) {
  YAML::Node n;

  const std::string& t1 = n.Tag();
  const std::string& t2 = n.Tag();

  // The API returns a const std::string&; ensure repeated calls return a stable reference.
  EXPECT_EQ(&t1, &t2);
}

TEST_F(TagTest_558, SetTagThenTagReturnsSameValue_558) {
  YAML::Node n;

  const std::string kTag = "!mytag";
  n.SetTag(kTag);

  const std::string& got = n.Tag();
  EXPECT_EQ(got, kTag);
}

TEST_F(TagTest_558, SetTagEmptyStringThenTagReturnsEmptyString_558) {
  YAML::Node n;

  n.SetTag(std::string{});
  const std::string& got = n.Tag();
  EXPECT_TRUE(got.empty());
}

TEST_F(TagTest_558, SetTagThenTagReferenceIsStableAcrossCalls_558) {
  YAML::Node n;
  n.SetTag("!stable");

  const std::string& t1 = n.Tag();
  const std::string& t2 = n.Tag();

  EXPECT_EQ(t1, "!stable");
  EXPECT_EQ(&t1, &t2);
}

TEST_F(TagTest_558, TagOnInvalidNodeThrowsInvalidNode_558) {
  YAML::Node root;

  // Accessing a missing key commonly yields an invalid ("zombie") node in yaml-cpp.
  // This test asserts only the observable behavior: Tag() throws InvalidNode.
  const YAML::Node missing = root["definitely_missing_key_558"];

  EXPECT_THROW(
      {
        (void)missing.Tag();
      },
      YAML::InvalidNode);
}

TEST_F(TagTest_558, TagOnInvalidNodeThrowsEvenIfCalledMultipleTimes_558) {
  YAML::Node root;
  const YAML::Node missing = root["another_missing_key_558"];

  EXPECT_THROW((void)missing.Tag(), YAML::InvalidNode);
  EXPECT_THROW((void)missing.Tag(), YAML::InvalidNode);
}

}  // namespace