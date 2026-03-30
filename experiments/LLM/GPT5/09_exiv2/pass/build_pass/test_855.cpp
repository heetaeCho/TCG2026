// ============================================================================
// TEST_ID: 855
// File: test_langaltvalue_write_855.cpp
// Unit tests for Exiv2::LangAltValue::write(std::ostream&)
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <sstream>
#include <string>

namespace {

class LangAltValueWriteTest_855 : public ::testing::Test {};

TEST_F(LangAltValueWriteTest_855, Write_OnNewObject_DoesNotCrash_855) {
  Exiv2::LangAltValue v;

  std::ostringstream os;
  EXPECT_NO_THROW(v.write(os));

  // Observable requirement: should return the stream reference (chainable).
  std::ostringstream os2;
  auto& ret = v.write(os2);
  EXPECT_EQ(&ret, &os2);
}

TEST_F(LangAltValueWriteTest_855, Write_OutputIsDeterministicAcrossCalls_855) {
  Exiv2::LangAltValue v;

  std::ostringstream os1;
  std::ostringstream os2;

  v.write(os1);
  v.write(os2);

  // Black-box: we only assert stability for the same instance state.
  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(LangAltValueWriteTest_855, Write_DoesNotModifyStreamFlagsOrFormatState_855) {
  Exiv2::LangAltValue v;

  std::ostringstream os;
  os.setf(std::ios::hex, std::ios::basefield);
  os.setf(std::ios::showbase);
  os.width(7);
  os.fill('*');

  const auto flags_before = os.flags();
  const auto width_before = os.width();  // Note: width resets after insertion ops, but we haven't inserted yet.
  const auto fill_before = os.fill();

  v.write(os);

  // We only check what is reasonably expected for a well-behaved "write" method:
  // - flags and fill character should remain unchanged.
  // - width might be changed by i/o insertions, but many implementations do not set width.
  //   To avoid over-specifying, we do not assert width preservation.
  EXPECT_EQ(os.flags(), flags_before);
  EXPECT_EQ(os.fill(), fill_before);

  // Restore expectation about width only if it was unchanged by our own reads.
  (void)width_before;
}

TEST_F(LangAltValueWriteTest_855, Write_CanBeChained_855) {
  Exiv2::LangAltValue v;

  std::ostringstream os;
  auto& ret1 = v.write(os);
  ret1 << " tail";
  EXPECT_EQ(os.str().find(" tail") != std::string::npos, true);
}

TEST_F(LangAltValueWriteTest_855, Write_DoesNotThrowOnBadbitStream_855) {
  Exiv2::LangAltValue v;

  std::ostringstream os;
  os.setstate(std::ios::badbit);

  // Even if the stream is already in a bad state, write should not crash.
  EXPECT_NO_THROW(v.write(os));

  // Return should still be the same stream object.
  auto& ret = v.write(os);
  EXPECT_EQ(&ret, &os);
}

TEST_F(LangAltValueWriteTest_855, Write_OutputStableThroughClone_855) {
  Exiv2::LangAltValue v;

  std::ostringstream os_before;
  v.write(os_before);

  // clone() should produce an independent object with equivalent observable output.
  auto cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  std::ostringstream os_after;
  cloned->write(os_after);

  EXPECT_EQ(os_before.str(), os_after.str());
}

TEST_F(LangAltValueWriteTest_855, Write_OutputStableAfterReadSameBufferTwice_855) {
  // We do not assume parsing rules; we only verify "same input -> same observable write output".
  const std::string buf = "lang=\"x-default\" hello";

  Exiv2::LangAltValue v1;
  Exiv2::LangAltValue v2;

  // read() returns int; we don't assume meaning, only that it can be called.
  EXPECT_NO_THROW((void)v1.read(buf));
  EXPECT_NO_THROW((void)v2.read(buf));

  std::ostringstream os1;
  std::ostringstream os2;
  v1.write(os1);
  v2.write(os2);

  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(LangAltValueWriteTest_855, Write_WithEmptyQualifierToStringDoesNotAffectWrite_855) {
  Exiv2::LangAltValue v;

  std::ostringstream os1;
  v.write(os1);

  // Calling other public APIs should not corrupt the object such that write changes unexpectedly.
  // We avoid assuming any specific content; just check determinism relative to baseline.
  EXPECT_NO_THROW((void)v.toString(std::string{}));

  std::ostringstream os2;
  v.write(os2);

  EXPECT_EQ(os1.str(), os2.str());
}

}  // namespace