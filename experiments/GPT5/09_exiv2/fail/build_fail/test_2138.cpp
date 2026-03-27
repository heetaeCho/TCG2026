// ============================================================================
// TEST_ID: 2138
// Unit tests for DumpClearString (./TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp)
// ============================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// Bring the static function into this translation unit so it is callable.
// This test intentionally includes the .cpp to access internal-linkage code.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

struct OutProcMock {
  MOCK_METHOD(XMP_Status, Call, (void* refCon, XMP_StringPtr buffer, XMP_StringLen count));
};

static XMP_Status OutProcTrampoline(void* refCon, XMP_StringPtr buffer, XMP_StringLen count) {
  auto* mock = static_cast<OutProcMock*>(refCon);
  return mock->Call(refCon, buffer, count);
}

static std::string BytesToString(const char* p, size_t n) {
  return std::string(p, p + n);
}

class DumpClearStringTest_2138 : public ::testing::Test {};

TEST_F(DumpClearStringTest_2138, EmptyStringProducesNoOutputAndReturnsZero_2138) {
  StrictMock<OutProcMock> mock;

  const XMP_VarString value;  // empty
  // Expect no calls for empty input.
  EXPECT_CALL(mock, Call(_, _, _)).Times(0);

  const XMP_Status st = DumpClearString(value, &OutProcTrampoline, &mock);
  EXPECT_EQ(st, 0);
}

TEST_F(DumpClearStringTest_2138, AllPrintableAsciiIsForwardedVerbatim_2138) {
  StrictMock<OutProcMock> mock;

  const XMP_VarString value("Hello, World!");

  std::string collected;
  EXPECT_CALL(mock, Call(_, _, _))
      .WillRepeatedly(Invoke([&](void*, XMP_StringPtr buf, XMP_StringLen n) -> XMP_Status {
        collected.append(buf, buf + n);
        return 0;
      }));

  const XMP_Status st = DumpClearString(value, &OutProcTrampoline, &mock);
  EXPECT_EQ(st, 0);
  EXPECT_EQ(collected, "Hello, World!");
}

TEST_F(DumpClearStringTest_2138, TabAndLineFeedAreTreatedAsClearCharacters_2138) {
  StrictMock<OutProcMock> mock;

  const XMP_VarString value(std::string("A\tB\nC").c_str());

  std::string collected;
  EXPECT_CALL(mock, Call(_, _, _))
      .WillRepeatedly(Invoke([&](void*, XMP_StringPtr buf, XMP_StringLen n) -> XMP_Status {
        collected.append(buf, buf + n);
        return 0;
      }));

  const XMP_Status st = DumpClearString(value, &OutProcTrampoline, &mock);
  EXPECT_EQ(st, 0);
  EXPECT_EQ(collected, "A\tB\nC");
}

TEST_F(DumpClearStringTest_2138, OutputProcNonZeroAbortsAndIsReturned_2138) {
  StrictMock<OutProcMock> mock;

  const XMP_VarString value("abc");

  // Fail on the first attempted write; function should return that code.
  EXPECT_CALL(mock, Call(_, _, _)).WillOnce(Return(7));

  const XMP_Status st = DumpClearString(value, &OutProcTrampoline, &mock);
  EXPECT_EQ(st, 7);
}

TEST_F(DumpClearStringTest_2138, NonAsciiByteIsEscapedWithAngleBrackets_2138) {
  StrictMock<OutProcMock> mock;

  // Construct: "A" + 0x80 + "B"
  std::string s;
  s.push_back('A');
  s.push_back(static_cast<char>(0x80));
  s.push_back('B');
  const XMP_VarString value(s.c_str(), s.size());

  std::string collected;
  EXPECT_CALL(mock, Call(_, _, _))
      .WillRepeatedly(Invoke([&](void*, XMP_StringPtr buf, XMP_StringLen n) -> XMP_Status {
        collected.append(buf, buf + n);
        return 0;
      }));

  const XMP_Status st = DumpClearString(value, &OutProcTrampoline, &mock);
  EXPECT_EQ(st, 0);

  // Observable behavior: printable prefix/suffix should remain, and an escaped span should appear.
  ASSERT_FALSE(collected.empty());
  EXPECT_EQ(collected.front(), 'A');
  EXPECT_EQ(collected.back(), 'B');

  const auto lt = collected.find('<');
  const auto gt = collected.find('>');
  EXPECT_NE(lt, std::string::npos);
  EXPECT_NE(gt, std::string::npos);
  EXPECT_LT(lt, gt);

  // The raw 0x80 byte should not appear in the output (escape expected).
  EXPECT_EQ(collected.find(static_cast<char>(0x80)), std::string::npos);
}

TEST_F(DumpClearStringTest_2138, ControlCharacterBelowSpaceIsEscaped_2138) {
  StrictMock<OutProcMock> mock;

  // Include a control char (0x01) which is not tab or LF.
  std::string s = "X";
  s.push_back(static_cast<char>(0x01));
  s += "Y";
  const XMP_VarString value(s.c_str(), s.size());

  std::string collected;
  EXPECT_CALL(mock, Call(_, _, _))
      .WillRepeatedly(Invoke([&](void*, XMP_StringPtr buf, XMP_StringLen n) -> XMP_Status {
        collected.append(buf, buf + n);
        return 0;
      }));

  const XMP_Status st = DumpClearString(value, &OutProcTrampoline, &mock);
  EXPECT_EQ(st, 0);

  EXPECT_EQ(collected.front(), 'X');
  EXPECT_EQ(collected.back(), 'Y');

  const auto lt = collected.find('<');
  const auto gt = collected.find('>');
  EXPECT_NE(lt, std::string::npos);
  EXPECT_NE(gt, std::string::npos);
  EXPECT_LT(lt, gt);

  // The raw 0x01 byte should not appear in the output (escape expected).
  EXPECT_EQ(collected.find(static_cast<char>(0x01)), std::string::npos);
}

}  // namespace