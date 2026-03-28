// File: test_iptcdatum_tagname_670.cpp
// Unit tests for Exiv2::Iptcdatum::tagName()
// TEST_ID: 670

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>

namespace {

class IptcdatumTest_670 : public ::testing::Test {};

TEST_F(IptcdatumTest_670, TagNameDelegatesToKeyTagName_670) {
  const Exiv2::IptcKey key(5 /*tag*/, 2 /*record*/);

  ASSERT_NO_THROW({
    Exiv2::Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), key.tagName());
  });
}

TEST_F(IptcdatumTest_670, TagNameMatchesKeyForStringConstructedKey_670) {
  // Use a canonical IPTC key string. Even if the library maps/normalizes it,
  // Iptcdatum::tagName() must match the underlying key's tagName().
  const Exiv2::IptcKey key(std::string("Iptc.Application2.ObjectName"));

  ASSERT_NO_THROW({
    Exiv2::Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), key.tagName());
  });
}

TEST_F(IptcdatumTest_670, CopyConstructorPreservesDelegatedTagName_670) {
  const Exiv2::IptcKey key(120 /*tag*/, 2 /*record*/);

  ASSERT_NO_THROW({
    Exiv2::Iptcdatum original(key, nullptr);
    const std::string expected = key.tagName();

    Exiv2::Iptcdatum copy(original);
    EXPECT_EQ(copy.tagName(), expected);
    EXPECT_EQ(copy.tagName(), original.tagName());
  });
}

TEST_F(IptcdatumTest_670, CopyAssignmentPreservesDelegatedTagName_670) {
  const Exiv2::IptcKey keyA(25 /*tag*/, 2 /*record*/);
  const Exiv2::IptcKey keyB(26 /*tag*/, 2 /*record*/);

  ASSERT_NO_THROW({
    Exiv2::Iptcdatum a(keyA, nullptr);
    Exiv2::Iptcdatum b(keyB, nullptr);

    const std::string expectedA = keyA.tagName();
    const std::string expectedB = keyB.tagName();

    // Sanity: they may or may not be equal depending on the dataset; do not assume.
    EXPECT_EQ(a.tagName(), expectedA);
    EXPECT_EQ(b.tagName(), expectedB);

    b = a;
    EXPECT_EQ(b.tagName(), a.tagName());
    EXPECT_EQ(b.tagName(), expectedA);

    // Self-assignment should not change observable behavior.
    b = b;
    EXPECT_EQ(b.tagName(), expectedA);
  });
}

}  // namespace