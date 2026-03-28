// File: test_sonymn_int_getMetaVersion_1586.cpp
// TEST_ID: 1586
//
// These tests exercise Exiv2::Internal::getMetaVersion (a TU-local static in sonymn_int.cpp)
// strictly via its observable interface: return value + output parameter.
//
// NOTE: Because getMetaVersion is declared `static` in a .cpp, the only practical way to
//       test it directly (without inventing new public seams) is to compile it into this
//       test translation unit by including the implementation file.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

#include <string>

// Include the implementation to make the `static` function visible in this TU.
// Adjust the include path if your build system differs.
#include "sonymn_int.cpp"

namespace {

class GetMetaVersionTest_1586 : public ::testing::Test {
 protected:
  static constexpr const char* kKey = "Exif.SonySInfo1.MetaVersion";
};

TEST_F(GetMetaVersionTest_1586, MissingKeyReturnsFalseAndClearsOutput_1586) {
  Exiv2::ExifData md;
  std::string out = "previous";

  const bool ok = Exiv2::Internal::getMetaVersion(&md, out);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(out.empty());
}

TEST_F(GetMetaVersionTest_1586, PresentAsciiNonEmptyReturnsTrueAndSetsOutput_1586) {
  Exiv2::ExifData md;
  md[kKey] = std::string("1.00");

  std::string out = "previous";
  const bool ok = Exiv2::Internal::getMetaVersion(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "1.00");
}

TEST_F(GetMetaVersionTest_1586, PresentAsciiEmptyReturnsFalseAndClearsOutput_1586) {
  Exiv2::ExifData md;
  md[kKey] = std::string("");

  std::string out = "previous";
  const bool ok = Exiv2::Internal::getMetaVersion(&md, out);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(out.empty());
}

TEST_F(GetMetaVersionTest_1586, PresentNonAsciiTypeReturnsFalseAndClearsOutput_1586) {
  Exiv2::ExifData md;
  // Set a non-ascii type (e.g., unsignedShort) via the Exifdatum assignment operator.
  md[kKey] = static_cast<uint16_t>(42);

  std::string out = "previous";
  const bool ok = Exiv2::Internal::getMetaVersion(&md, out);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(out.empty());
}

TEST_F(GetMetaVersionTest_1586, LargeAsciiValueIsReturnedExactly_1586) {
  Exiv2::ExifData md;
  const std::string big(4096, 'A');
  md[kKey] = big;

  std::string out;
  const bool ok = Exiv2::Internal::getMetaVersion(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.size(), big.size());
  EXPECT_EQ(out, big);
}

TEST_F(GetMetaVersionTest_1586, OnFailureOutputIsOverwrittenEvenIfPreviouslySet_1586) {
  Exiv2::ExifData md;
  md[kKey] = static_cast<uint32_t>(7);  // non-ascii

  std::string out = "should be cleared";
  const bool ok = Exiv2::Internal::getMetaVersion(&md, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "");
}

}  // namespace