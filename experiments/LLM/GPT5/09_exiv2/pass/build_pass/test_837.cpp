// =====================================================================================
// Unit tests for Exiv2::XmpTextValue::count()
// File: test_xmp_text_value_count_837.cpp
// =====================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/value.hpp"

namespace {

class XmpTextValueTest_837 : public ::testing::Test {};

TEST_F(XmpTextValueTest_837, DefaultConstruct_CountEqualsSize_837) {
  Exiv2::XmpTextValue v;

  const size_t sz = v.size();
  const size_t cnt = v.count();

  EXPECT_EQ(cnt, sz);
}

TEST_F(XmpTextValueTest_837, ConstructWithBuffer_CountEqualsSize_837) {
  const std::string buf = "hello world";
  Exiv2::XmpTextValue v(buf);

  EXPECT_EQ(v.count(), v.size());
}

TEST_F(XmpTextValueTest_837, ReadDoesNotBreakCountSizeRelationship_837) {
  Exiv2::XmpTextValue v;

  EXPECT_NO_THROW({
    const int rc = v.read("some text payload");
    (void)rc;
  });

  EXPECT_EQ(v.count(), v.size());
}

TEST_F(XmpTextValueTest_837, LargeInputBoundary_CountEqualsSize_837) {
  // Boundary-oriented input: very large text buffer.
  const std::string large(1'000'000, 'x');
  Exiv2::XmpTextValue v;

  EXPECT_NO_THROW({
    const int rc = v.read(large);
    (void)rc;
  });

  EXPECT_EQ(v.count(), v.size());
}

TEST_F(XmpTextValueTest_837, Clone_PreservesCountAndSizeRelationship_837) {
  Exiv2::XmpTextValue v("clone me");

  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Verify observable equality through the public virtual interface.
  EXPECT_EQ(cloned->count(), cloned->size());
  EXPECT_EQ(cloned->count(), v.count());
  EXPECT_EQ(cloned->size(), v.size());
}

TEST_F(XmpTextValueTest_837, Write_DoesNotChangeCountOrSize_837) {
  Exiv2::XmpTextValue v("write test");

  const size_t beforeSize = v.size();
  const size_t beforeCount = v.count();

  std::ostringstream os;
  EXPECT_NO_THROW({
    std::ostream& out = v.write(os);
    EXPECT_EQ(&out, &os);
  });

  // Observable post-condition: relationship still holds and values remain stable.
  EXPECT_EQ(v.count(), v.size());
  EXPECT_EQ(v.size(), beforeSize);
  EXPECT_EQ(v.count(), beforeCount);
}

TEST_F(XmpTextValueTest_837, Count_IsStableAcrossRepeatedCalls_837) {
  Exiv2::XmpTextValue v("repeat");

  const size_t c1 = v.count();
  const size_t c2 = v.count();
  const size_t s1 = v.size();
  const size_t s2 = v.size();

  EXPECT_EQ(c1, c2);
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(c1, s1);
}

}  // namespace