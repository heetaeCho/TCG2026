// =====================================================================================
// ./TestProjects/exiv2/src/minoltamn_int_test.cpp
// Unit tests for Exiv2::Internal::printMinoltaSonyQualityCs
//
// Constraints honored:
// - Treat implementation as black box (no internal logic assumptions).
// - Test only observable behavior: stream output, stream state, return reference.
// - Include normal, boundary, and error/exception-observable cases.
// =====================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Declaration under test (implemented in ./TestProjects/exiv2/src/minoltamn_int.cpp)
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyQualityCs(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class MinoltaSonyQualityCsPrintTest_1033 : public ::testing::Test {
 protected:
  std::string PrintToString(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    std::ostream& ret = Exiv2::Internal::printMinoltaSonyQualityCs(oss, v, md);
    // Observable: returns a stream reference; in typical printing helpers this is the same stream.
    EXPECT_EQ(&ret, &oss);
    return oss.str();
  }
};

static Exiv2::Value::UniquePtr MakeUShortValue(uint32_t x) {
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  EXPECT_NE(v.get(), nullptr);
  // read(string) is part of Value interface; use it to provide one value.
  EXPECT_NO_THROW({
    (void)v->read(std::to_string(x));
  });
  return v;
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, ReturnsSameStreamReference_1033) {
  auto v = MakeUShortValue(0);
  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyQualityCs(oss, *v, nullptr);
  EXPECT_EQ(&ret, &oss);
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, AcceptsNullMetadataPointer_1033) {
  auto v = MakeUShortValue(32);
  EXPECT_NO_THROW({
    (void)PrintToString(*v, nullptr);
  });
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, AcceptsNonNullMetadataPointer_1033) {
  auto v = MakeUShortValue(32);
  Exiv2::ExifData md;
  EXPECT_NO_THROW({
    (void)PrintToString(*v, &md);
  });
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, WritesSomethingForKnownValueRaw_1033) {
  auto v = MakeUShortValue(0);
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_FALSE(out.empty());
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, WritesSomethingForKnownValueFine_1033) {
  auto v = MakeUShortValue(32);
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_FALSE(out.empty());
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, WritesSomethingForKnownValueStandard_1033) {
  auto v = MakeUShortValue(48);
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_FALSE(out.empty());
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, UnknownValueDoesNotThrowAndProducesOutput_1033) {
  // Boundary/robustness: value not in the provided TagDetails list.
  auto v = MakeUShortValue(1);
  EXPECT_NO_THROW({
    const std::string out = PrintToString(*v, nullptr);
    // Observable behavior: printing should still yield some representation (string or numeric).
    EXPECT_FALSE(out.empty());
  });
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, LargeValueDoesNotThrow_1033) {
  // Boundary: large unsigned short-ish numeric.
  auto v = MakeUShortValue(65535);
  EXPECT_NO_THROW({
    const std::string out = PrintToString(*v, nullptr);
    EXPECT_FALSE(out.empty());
  });
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, StreamFailureStateIsPreserved_1033) {
  auto v = MakeUShortValue(32);

  std::ostringstream oss;
  oss.setstate(std::ios::badbit);  // simulate failure
  const auto before = oss.rdstate();

  std::ostream& ret = Exiv2::Internal::printMinoltaSonyQualityCs(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  // Observable: printing to a bad stream should not "fix" the stream state.
  EXPECT_EQ(oss.rdstate(), before);
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, DoesNotModifyExternalMetadataObservableState_1033) {
  // We don't know if metadata is consulted, but it should not be mutated by a print helper.
  // Observable check: count() remains same.
  auto v = MakeUShortValue(32);
  Exiv2::ExifData md;
  const size_t before = md.count();

  (void)PrintToString(*v, &md);

  EXPECT_EQ(md.count(), before);
}

TEST_F(MinoltaSonyQualityCsPrintTest_1033, WorksWithValueHavingNoElements_1033) {
  // Error-ish/boundary: a Value that may have zero count depending on type/read behavior.
  // We avoid assumptions; simply ensure no throw.
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::printMinoltaSonyQualityCs(oss, *v, nullptr);
  });
}

}  // namespace