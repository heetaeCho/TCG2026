// File: test_langaltvalue_tostring_857.cpp
#include <gtest/gtest.h>

#include <exiv2/value.hpp>

using Exiv2::LangAltValue;

namespace {

class LangAltValueTest_857 : public ::testing::Test {};

TEST_F(LangAltValueTest_857, MissingQualifierReturnsEmptyAndSetsOkFalse_857) {
  LangAltValue v;

  const std::string out = v.toString("en-US");
  EXPECT_TRUE(out.empty());
  EXPECT_FALSE(v.ok());
}

TEST_F(LangAltValueTest_857, ReadLangEqualsFormatThenToStringReturnsTextAndOkTrue_857) {
  LangAltValue v;

  // Documented CLI format for LangAlt values: `lang=<code> <text>`
  // Example: exiv2 --Modify "set Xmp.dc.title LangAlt lang=en-US My holiday" ...
  ASSERT_EQ(0, v.read("lang=en-US My holiday"));

  EXPECT_EQ("My holiday", v.toString("en-US"));
  EXPECT_TRUE(v.ok());
}

TEST_F(LangAltValueTest_857, ReadWithoutQualifierDefaultsToXDefault_857) {
  LangAltValue v;

  // Documented: if value doesn't start with lang=, x-default is used by default.
  ASSERT_EQ(0, v.read("Hello, World"));

  EXPECT_EQ("Hello, World", v.toString("x-default"));
  EXPECT_TRUE(v.ok());
}

TEST_F(LangAltValueTest_857, ReadWriteStyleCommaSeparatedEntriesSupportsLookupByQualifier_857) {
  LangAltValue v;

  // The write()/CLI output for multiple LangAlt entries is commonly:
  //   lang="en-US" My holiday, lang="fr" Mes vacances
  ASSERT_EQ(0, v.read("lang=\"en-US\" My holiday, lang=\"fr\" Mes vacances"));

  EXPECT_EQ("My holiday", v.toString("en-US"));
  EXPECT_TRUE(v.ok());

  EXPECT_EQ("Mes vacances", v.toString("fr"));
  EXPECT_TRUE(v.ok());
}

TEST_F(LangAltValueTest_857, MissingQualifierAfterSuccessfulReadTogglesOkFlagAndDoesNotBreakFutureLookups_857) {
  LangAltValue v;
  ASSERT_EQ(0, v.read("lang=en-US My holiday"));

  // Missing qualifier -> empty + ok false
  EXPECT_TRUE(v.toString("de-DE").empty());
  EXPECT_FALSE(v.ok());

  // Existing qualifier still retrievable -> ok true again
  EXPECT_EQ("My holiday", v.toString("en-US"));
  EXPECT_TRUE(v.ok());
}

TEST_F(LangAltValueTest_857, ToStringCallableOnConstObject_857) {
  LangAltValue tmp;
  ASSERT_EQ(0, tmp.read("lang=fr Mes vacances"));

  const LangAltValue& v = tmp;
  EXPECT_EQ("Mes vacances", v.toString("fr"));
  EXPECT_TRUE(v.ok());
}

}  // namespace