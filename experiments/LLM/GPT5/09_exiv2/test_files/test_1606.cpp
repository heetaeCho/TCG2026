// File: test_sonymn_int_findLensSpecFlags_1606.cpp
//
// Unit tests for Exiv2::Internal::findLensSpecFlags (from sonymn_int.cpp)
//
// NOTE:
// - The function under test has internal linkage (static) in a .cpp file.
// - To test it strictly via the provided interface (without re-implementing logic),
//   we include the implementation file so the function is in the same translation unit.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/error.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <string>

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Minimal mock of Exiv2::Value for this specific function.
// We only mock toUint32(size_t) because that's the only observable dependency used.
class MockValue final : public Exiv2::Value {
 public:
  MockValue() : Exiv2::Value(Exiv2::unsignedLong) {}
  MOCK_METHOD(uint32_t, toUint32, (size_t n), (override));
};

// Helper: configure the joined 16-bit value used by the implementation:
// joined = (toUint32(0) << 8) + toUint32(7)
inline void ExpectJoinedValue(MockValue& v, uint16_t joined) {
  const uint32_t v0 = static_cast<uint32_t>((joined >> 8) & 0xff);
  const uint32_t v7 = static_cast<uint32_t>(joined & 0xff);

  EXPECT_CALL(v, toUint32(0)).Times(1).WillOnce(Return(v0));
  EXPECT_CALL(v, toUint32(7)).Times(1).WillOnce(Return(v7));
}

class FindLensSpecFlagsTest_1606 : public ::testing::Test {};

}  // namespace

// Include the .cpp so the internal-linkage function is available in this TU.
#include "sonymn_int.cpp"

TEST_F(FindLensSpecFlagsTest_1606, NoBitsSet_LeavesFlagsEmpty_1606) {
  StrictMock<MockValue> v;
  ExpectJoinedValue(v, /*joined=*/0x0000);

  std::string start, end;
  EXPECT_NO_THROW(Exiv2::Internal::findLensSpecFlags(v, start, end));
  EXPECT_TRUE(start.empty());
  EXPECT_TRUE(end.empty());
}

TEST_F(FindLensSpecFlagsTest_1606, SinglePrependFlag_PZ_GoesToFlagsStart_1606) {
  StrictMock<MockValue> v;
  // 0x4000 corresponds to "PZ" and is a prepend flag.
  ExpectJoinedValue(v, /*joined=*/0x4000);

  std::string start, end;
  EXPECT_NO_THROW(Exiv2::Internal::findLensSpecFlags(v, start, end));
  EXPECT_EQ(start, "PZ");
  EXPECT_TRUE(end.empty());
}

TEST_F(FindLensSpecFlagsTest_1606, SinglePrependFlag_FE_GoesToFlagsStart_1606) {
  StrictMock<MockValue> v;
  // 0x0200 corresponds to "FE" and is a prepend flag.
  ExpectJoinedValue(v, /*joined=*/0x0200);

  std::string start, end;
  EXPECT_NO_THROW(Exiv2::Internal::findLensSpecFlags(v, start, end));
  EXPECT_EQ(start, "FE");
  EXPECT_TRUE(end.empty());
}

TEST_F(FindLensSpecFlagsTest_1606, SingleAppendFlag_G_GoesToFlagsEnd_1606) {
  StrictMock<MockValue> v;
  // 0x0008 corresponds to "G" and is an append flag.
  ExpectJoinedValue(v, /*joined=*/0x0008);

  std::string start, end;
  EXPECT_NO_THROW(Exiv2::Internal::findLensSpecFlags(v, start, end));
  EXPECT_TRUE(start.empty());
  EXPECT_EQ(end, "G");
}

TEST_F(FindLensSpecFlagsTest_1606, MultiplePrependFlags_NewerOnesPrependInOrder_1606) {
  StrictMock<MockValue> v;
  // Combine:
  // - 0x4000 -> "PZ" (prepend)
  // - 0x0300 -> "E"  (prepend)
  // Expect: "E PZ" because second prepend places label before existing start.
  ExpectJoinedValue(v, /*joined=*/static_cast<uint16_t>(0x4000 | 0x0300));

  std::string start, end;
  EXPECT_NO_THROW(Exiv2::Internal::findLensSpecFlags(v, start, end));
  EXPECT_EQ(start, "E PZ");
  EXPECT_TRUE(end.empty());
}

TEST_F(FindLensSpecFlagsTest_1606, MixedPrependAndAppendFlags_AreSeparatedIntoStartAndEnd_1606) {
  StrictMock<MockValue> v;
  // Combine:
  // - 0x0300 -> "E" (prepend)
  // - 0x8000 -> "OSS" (append)
  // - 0x0004 -> "ZA" (append)
  ExpectJoinedValue(v, /*joined=*/static_cast<uint16_t>(0x0300 | 0x8000 | 0x0004));

  std::string start, end;
  EXPECT_NO_THROW(Exiv2::Internal::findLensSpecFlags(v, start, end));
  EXPECT_EQ(start, "E");
  // Append flags should be space-separated in the order they are discovered.
  // (Per observable behavior of the function with this input.)
  EXPECT_EQ(end, "ZA OSS");
}

TEST_F(FindLensSpecFlagsTest_1606, AppendFlags_AreAppendedInDiscoveryOrder_1606) {
  StrictMock<MockValue> v;
  // Combine:
  // - 0x0004 -> "ZA" (append)
  // - 0x0002 -> "SAM" (append)
  // Expect: "ZA SAM" (same end string order as flags encountered).
  ExpectJoinedValue(v, /*joined=*/static_cast<uint16_t>(0x0004 | 0x0002));

  std::string start, end;
  EXPECT_NO_THROW(Exiv2::Internal::findLensSpecFlags(v, start, end));
  EXPECT_TRUE(start.empty());
  EXPECT_EQ(end, "ZA SAM");
}

TEST_F(FindLensSpecFlagsTest_1606, InvalidCombinationWithinMaskedGroup_ThrowsError_1606) {
  StrictMock<MockValue> v;
  // 0x00e0 group is checked when any of those bits are set, and only specific
  // values are valid. Use a combination that is within the mask but not a listed value.
  // Example: 0x00a0 (0x0020 | 0x0080) should trigger the "mask doesn't match" error.
  ExpectJoinedValue(v, /*joined=*/0x00a0);

  std::string start, end;
  try {
    Exiv2::Internal::findLensSpecFlags(v, start, end);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // ErrorCode is observable via the exception type in Exiv2.
    // If Exiv2::Error exposes code(), validate it; otherwise, just assert exception thrown.
#if defined(EXV_HAVE_ERROR_CODE_ACCESSOR)  // (kept conservative; may not be defined)
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerErrorMessage);
#else
    (void)e;
#endif
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}