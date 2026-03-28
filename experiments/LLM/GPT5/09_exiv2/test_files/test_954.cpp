// ============================================================================
// TEST_ID: 954
// File: test_canonmn_int_printSi0x0002_954.cpp
// Unit tests for Exiv2::Internal::CanonMakerNote::printSi0x0002
// ============================================================================

#include <gtest/gtest.h>

#include <cmath>
#include <iomanip>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

#include "canonmn_int.hpp"  // CanonMakerNote
#include "value.hpp"        // Exiv2::Value, Exiv2::Value::UniquePtr, TypeId
#include "types.hpp"        // Exiv2::TypeId (e.g., unsignedShort)
#include "exif.hpp"         // Exiv2::ExifData (only for pointer type)

namespace {

using Exiv2::Internal::CanonMakerNote;

// Helper: create a Value of a given TypeId using Exiv2 factory, then read() data into it.
// This avoids relying on any specific concrete Value subclass.
static Exiv2::Value::UniquePtr MakeValueFromRaw(Exiv2::TypeId typeId,
                                                const std::string& raw) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(typeId);
  EXPECT_TRUE(static_cast<bool>(v));
  if (v) v->read(raw);
  return v;
}

// Helper: extracts the exact string printed by printSi0x0002 into an std::string.
static std::string CallPrintSi0x0002ToString(CanonMakerNote& mn,
                                             const Exiv2::Value& value,
                                             const Exiv2::ExifData* exif = nullptr) {
  std::ostringstream oss;
  // Make stream formatting explicit/consistent for comparisons.
  oss.setf(std::ios::fmtflags(0), std::ios::floatfield);
  oss << std::setprecision(12);
  mn.printSi0x0002(oss, value, exif);
  return oss.str();
}

class CanonMakerNotePrintSi0x0002Test_954 : public ::testing::Test {
 protected:
  CanonMakerNote mn_;
};

}  // namespace

// --- Normal operation --------------------------------------------------------

TEST_F(CanonMakerNotePrintSi0x0002Test_954, ReturnsSameStreamReference_954) {
  auto v = MakeValueFromRaw(Exiv2::unsignedShort, "0");
  ASSERT_TRUE(v);

  std::ostringstream oss;
  std::ostream& ret = mn_.printSi0x0002(oss, *v, nullptr);

  // Observable behavior: method returns std::ostream&; ensure it returns the same object.
  EXPECT_EQ(&ret, &oss);
}

TEST_F(CanonMakerNotePrintSi0x0002Test_954, WritesSomethingForUnsignedShortWithPositiveCount_954) {
  auto v = MakeValueFromRaw(Exiv2::unsignedShort, "0");
  ASSERT_TRUE(v);
  ASSERT_GT(v->count(), 0u);  // boundary assumption based on read("0")

  const std::string out = CallPrintSi0x0002ToString(mn_, *v, nullptr);

  // Black-box: it should write something (not necessarily a specific number formatting).
  EXPECT_FALSE(out.empty());
}

TEST_F(CanonMakerNotePrintSi0x0002Test_954, OutputIsParseableAsDoubleForUnsignedShort_954) {
  auto v = MakeValueFromRaw(Exiv2::unsignedShort, "0");
  ASSERT_TRUE(v);

  const std::string out = CallPrintSi0x0002ToString(mn_, *v, nullptr);

  // Verify observable behavior: output can be interpreted as a number.
  std::istringstream iss(out);
  double parsed = std::numeric_limits<double>::quiet_NaN();
  iss >> parsed;
  EXPECT_FALSE(iss.fail());
  EXPECT_TRUE(std::isfinite(parsed) || std::isinf(parsed));  // accept inf if produced
}

TEST_F(CanonMakerNotePrintSi0x0002Test_954, ExifDataPointerDoesNotAffectOutputWhenProvidedOrNull_954) {
  auto v = MakeValueFromRaw(Exiv2::unsignedShort, "0");
  ASSERT_TRUE(v);

  // We do not rely on any ExifData content; only that passing a non-null pointer is accepted.
  Exiv2::ExifData dummyExif;

  const std::string outNull = CallPrintSi0x0002ToString(mn_, *v, nullptr);
  const std::string outNonNull = CallPrintSi0x0002ToString(mn_, *v, &dummyExif);

  // Based on visible code: ExifData* isn't used; treat as black-box but verify consistent behavior.
  EXPECT_EQ(outNull, outNonNull);
}

// --- Boundary conditions -----------------------------------------------------

TEST_F(CanonMakerNotePrintSi0x0002Test_954, DoesNotWriteAnythingWhenTypeIsNotUnsignedShort_954) {
  // Use a different type (e.g., unsignedLong). If not available, fall back to signedLong.
  Exiv2::TypeId otherType = Exiv2::unsignedLong;
  auto v = MakeValueFromRaw(otherType, "0");
  if (!v) {
    otherType = Exiv2::signedLong;
    v = MakeValueFromRaw(otherType, "0");
  }
  ASSERT_TRUE(v);

  std::ostringstream oss;
  oss << "prefix";
  mn_.printSi0x0002(oss, *v, nullptr);

  // Observable behavior: for non-unsignedShort type, stream should remain unchanged (no extra output).
  EXPECT_EQ(oss.str(), "prefix");
}

TEST_F(CanonMakerNotePrintSi0x0002Test_954, DoesNotWriteAnythingWhenCountIsZero_954) {
  // Construct an unsignedShort value but with empty content (count==0) if supported by Value::read("").
  auto v = MakeValueFromRaw(Exiv2::unsignedShort, "");
  ASSERT_TRUE(v);

  std::ostringstream oss;
  oss << "prefix";
  mn_.printSi0x0002(oss, *v, nullptr);

  if (v->count() == 0u) {
    EXPECT_EQ(oss.str(), "prefix");
  } else {
    // If the library interprets empty read as count>0 (implementation-defined),
    // we still validate it doesn't crash and returns a stream (already covered elsewhere).
    EXPECT_NE(oss.str(), "");  // minimal observable check
  }
}

TEST_F(CanonMakerNotePrintSi0x0002Test_954, AppendsOutputToExistingStreamContent_954) {
  auto v = MakeValueFromRaw(Exiv2::unsignedShort, "0");
  ASSERT_TRUE(v);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream oss;
  oss << "prefix:";
  mn_.printSi0x0002(oss, *v, nullptr);

  const std::string out = oss.str();
  ASSERT_GE(out.size(), std::string("prefix:").size());
  EXPECT_EQ(out.rfind("prefix:", 0), 0u);  // starts with prefix
  EXPECT_GT(out.size(), std::string("prefix:").size());  // appended something
}

// --- Exceptional / error cases (observable) ---------------------------------

TEST_F(CanonMakerNotePrintSi0x0002Test_954, DoesNotThrowForValidUnsignedShort_954) {
  auto v = MakeValueFromRaw(Exiv2::unsignedShort, "0");
  ASSERT_TRUE(v);

  std::ostringstream oss;
  EXPECT_NO_THROW({ mn_.printSi0x0002(oss, *v, nullptr); });
}

TEST_F(CanonMakerNotePrintSi0x0002Test_954, DoesNotThrowForNonUnsignedShort_954) {
  auto v = MakeValueFromRaw(Exiv2::unsignedLong, "0");
  if (!v) v = MakeValueFromRaw(Exiv2::signedLong, "0");
  ASSERT_TRUE(v);

  std::ostringstream oss;
  EXPECT_NO_THROW({ mn_.printSi0x0002(oss, *v, nullptr); });
}