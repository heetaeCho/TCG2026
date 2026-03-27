// File: test_langaltvalue_read_852.cpp
// TEST_ID: 852

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

#include <sstream>
#include <string>

namespace {

using Exiv2::LangAltValue;

// NOTE: These tests treat LangAltValue as a black box and validate behavior
// only through the public interface (read/count/toString/write/clone).

class LangAltValueReadTest_852 : public ::testing::Test {};

TEST_F(LangAltValueReadTest_852, ReadWithoutLangPrefixStoresInXDefault_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("Hello world"));

  // Observable via qualifier lookup
  EXPECT_EQ("Hello world", v.toString("x-default"));

  // Count should be at least 1 after inserting a value.
  EXPECT_GE(v.count(), 1u);
}

TEST_F(LangAltValueReadTest_852, ReadWithLangAndValueAfterSpaceStoresUnderThatLang_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=en-US Hello"));

  EXPECT_EQ("Hello", v.toString("en-US"));
  // Should not clobber x-default unless explicitly written there.
  // (We avoid asserting x-default exact content, but count should be >= 1.)
  EXPECT_GE(v.count(), 1u);
}

TEST_F(LangAltValueReadTest_852, ReadWithLangButNoSpaceStoresEmptyStringValue_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=fr"));

  EXPECT_EQ("", v.toString("fr"));
  EXPECT_GE(v.count(), 1u);
}

TEST_F(LangAltValueReadTest_852, ReadWithQuotedLangParsesAndStoresValue_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=\"de\" GutenTag"));

  EXPECT_EQ("GutenTag", v.toString("de"));
}

TEST_F(LangAltValueReadTest_852, MultipleReadsAddDifferentLanguagesAndPreserveExisting_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=en Hello"));
  const size_t count_after_en = v.count();

  EXPECT_EQ(0, v.read("lang=es Hola"));
  const size_t count_after_es = v.count();

  EXPECT_EQ("Hello", v.toString("en"));
  EXPECT_EQ("Hola", v.toString("es"));

  // Adding a new language should not reduce the count.
  EXPECT_GE(count_after_es, count_after_en);
  EXPECT_GE(count_after_es, 2u);
}

TEST_F(LangAltValueReadTest_852, ReadSameLanguageTwiceUpdatesThatEntry_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=en First"));
  const size_t count_after_first = v.count();
  EXPECT_EQ("First", v.toString("en"));

  EXPECT_EQ(0, v.read("lang=en Second"));
  const size_t count_after_second = v.count();
  EXPECT_EQ("Second", v.toString("en"));

  // Updating an existing key should not increase count (best-effort expectation),
  // but we only assert it doesn't decrease.
  EXPECT_GE(count_after_second, count_after_first);
}

TEST_F(LangAltValueReadTest_852, DefaultLanguageCanBeOverwrittenByNonPrefixedRead_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("Initial"));
  EXPECT_EQ("Initial", v.toString("x-default"));

  EXPECT_EQ(0, v.read("Updated"));
  EXPECT_EQ("Updated", v.toString("x-default"));
}

TEST_F(LangAltValueReadTest_852, InvalidEmptyLangAfterPrefixThrows_852) {
  LangAltValue v;

  EXPECT_THROW(v.read("lang="), Exiv2::Error);
}

TEST_F(LangAltValueReadTest_852, InvalidQuotedLangMissingClosingQuoteThrows_852) {
  LangAltValue v;

  EXPECT_THROW(v.read("lang=\"en Hello"), Exiv2::Error);
}

TEST_F(LangAltValueReadTest_852, InvalidLangWithNonAlphaAndNoHyphenThrows_852) {
  LangAltValue v;

  // Underscore is not allowed by the observed validation rules.
  EXPECT_THROW(v.read("lang=en_US Hello"), Exiv2::Error);
}

TEST_F(LangAltValueReadTest_852, InvalidLangWithDigitWithoutHyphenThrows_852) {
  LangAltValue v;

  // Digits appearing without a hyphen separator are rejected by the observed rules.
  EXPECT_THROW(v.read("lang=en1 Hello"), Exiv2::Error);
}

TEST_F(LangAltValueReadTest_852, InvalidLangWithExtraHyphenSegmentThrows_852) {
  LangAltValue v;

  // Only a single hyphen with alphanumerics after it is accepted by the observed rules.
  EXPECT_THROW(v.read("lang=en-US-x Hello"), Exiv2::Error);
}

TEST_F(LangAltValueReadTest_852, Boundary_AllowsLangWithHyphenAndAlnumSuffix_852) {
  LangAltValue v;

  EXPECT_NO_THROW(v.read("lang=zh-Hant Hello"));
  EXPECT_EQ("Hello", v.toString("zh-Hant"));
}

TEST_F(LangAltValueReadTest_852, Boundary_AllowsSingleHyphenWithNumericSuffix_852) {
  LangAltValue v;

  EXPECT_NO_THROW(v.read("lang=en-1 One"));
  EXPECT_EQ("One", v.toString("en-1"));
}

TEST_F(LangAltValueReadTest_852, Boundary_LangParsingStopsAtFirstSpaceAndRemainderMayContainSpaces_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=it Ciao mondo come va"));

  EXPECT_EQ("Ciao mondo come va", v.toString("it"));
}

TEST_F(LangAltValueReadTest_852, ExternalInteraction_WriteToStreamIsCallableAfterRead_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=en Hello"));

  std::ostringstream os;
  EXPECT_NO_THROW(v.write(os));

  // We don't assume an exact format, only that something can be written.
  // If write() legitimately writes nothing, this still passes as long as no exception is thrown.
}

TEST_F(LangAltValueReadTest_852, ExternalInteraction_CloneProducesIndependentObject_852) {
  LangAltValue v;

  EXPECT_EQ(0, v.read("lang=en Hello"));

  auto cloned = v.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));

  EXPECT_EQ("Hello", cloned->toString("en"));

  // Mutate original; clone should remain stable (observable independence).
  EXPECT_EQ(0, v.read("lang=en Bye"));
  EXPECT_EQ("Bye", v.toString("en"));
  EXPECT_EQ("Hello", cloned->toString("en"));
}

}  // namespace