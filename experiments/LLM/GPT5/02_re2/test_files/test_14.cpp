// File: re2_options_encoding_test_14.cc

#include "gtest/gtest.h"
#include "re2/re2.h"

using namespace re2;

//
// Test suite name and each test name include TEST_ID suffix `_14`
//

TEST(RE2OptionsEncodingTest_14, DefaultEncodingIsUTF8_14) {
  RE2::Options opt;
  // Observable behavior: default-constructed Options reports its encoding.
  EXPECT_EQ(opt.encoding(), EncodingUTF8);
}

TEST(RE2OptionsEncodingTest_14, SetEncodingSwitchesValue_14) {
  RE2::Options opt;

  // Change to Latin1 and verify via the public getter.
  opt.set_encoding(EncodingLatin1);
  EXPECT_EQ(opt.encoding(), EncodingLatin1);

  // Change back to UTF8 and verify again.
  opt.set_encoding(EncodingUTF8);
  EXPECT_EQ(opt.encoding(), EncodingUTF8);
}

TEST(RE2OptionsEncodingTest_14, CannedOptionsLatin1SetsEncodingLatin1_14) {
  // Construct with canned option Latin1 and verify via getter.
  RE2::Options opt(RE2::Latin1);
  EXPECT_EQ(opt.encoding(), EncodingLatin1);
}

TEST(RE2OptionsEncodingTest_14, CannedOptionsPOSIXKeepsUTF8_14) {
  // For non-Latin1 canned options, encoding should be UTF8 (observable via getter).
  RE2::Options opt(RE2::POSIX);
  EXPECT_EQ(opt.encoding(), EncodingUTF8);
}

TEST(RE2OptionsEncodingTest_14, CannedOptionsQuietKeepsUTF8_14) {
  RE2::Options opt(RE2::Quiet);
  EXPECT_EQ(opt.encoding(), EncodingUTF8);
}
