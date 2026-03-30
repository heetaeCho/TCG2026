// FoFiIdentifierTest_50.cc
// Unit tests for static identify(Reader*) in FoFiIdentifier.cc
//
// NOTE: identify() is a file-local static function, so this test includes the
// implementation file directly to access it.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TestProjects/poppler/fofi/FoFiIdentifier.h"

// Include the .cc to access the file-local static identify(Reader*).
#include "TestProjects/poppler/fofi/FoFiIdentifier.cc"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrEq;
using ::testing::StrictMock;

namespace {

class MockReader : public Reader {
public:
  MOCK_METHOD(int, getByte, (int pos), (override));
  MOCK_METHOD(bool, getU16BE, (int pos, int* val), (override));
  MOCK_METHOD(bool, getU32BE, (int pos, unsigned int* val), (override));
  MOCK_METHOD(bool, getU32LE, (int pos, unsigned int* val), (override));
  MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int* val), (override));
  MOCK_METHOD(bool, cmp, (int pos, const char* s), (override));
};

class FoFiIdentifierTest_50 : public ::testing::Test {};

TEST_F(FoFiIdentifierTest_50, ReturnsType1PFA_WhenAdobeFontHeaderMatches_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(true));
  // Short-circuit: second cmp must not be called.
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).Times(0);
  // Should return immediately without consulting bytes/U32.
  EXPECT_CALL(r, getByte(_)).Times(0);
  EXPECT_CALL(r, getU32LE(_, _)).Times(0);

  EXPECT_EQ(fofiIdType1PFA, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, ReturnsType1PFA_WhenFontType1HeaderMatches_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(true));
  EXPECT_CALL(r, getByte(_)).Times(0);
  EXPECT_CALL(r, getU32LE(_, _)).Times(0);

  EXPECT_EQ(fofiIdType1PFA, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, ReturnsType1PFB_WhenPfbHeaderAndAdobeFontAtOffset6_50) {
  StrictMock<MockReader> r;

  // First check: cmp at 0 for PFA must fail to reach PFB logic.
  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  EXPECT_CALL(r, getByte(0)).WillOnce(Return(0x80));
  EXPECT_CALL(r, getByte(1)).WillOnce(Return(0x01));

  // n >= 16 and AdobeFont header at pos 6 -> PFB.
  EXPECT_CALL(r, getU32LE(2, _))
      .WillOnce(DoAll(SetArgPointee<1>(16u), Return(true)));
  EXPECT_CALL(r, cmp(6, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(true));
  // Because the first side of the || is true, the FontType1 cmp at pos 6 must not be called.
  EXPECT_CALL(r, cmp(6, StrEq("%!FontType1"))).Times(0);

  EXPECT_EQ(fofiIdType1PFB, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, ReturnsType1PFB_WhenPfbHeaderAndFontType1AtOffset6_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  EXPECT_CALL(r, getByte(0)).WillOnce(Return(0x80));
  EXPECT_CALL(r, getByte(1)).WillOnce(Return(0x01));

  // n >= 11 and "%!FontType1" at pos 6 -> PFB
  EXPECT_CALL(r, getU32LE(2, _))
      .WillOnce(DoAll(SetArgPointee<1>(11u), Return(true)));

  EXPECT_CALL(r, cmp(6, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(6, StrEq("%!FontType1"))).WillOnce(Return(true));

  EXPECT_EQ(fofiIdType1PFB, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, DoesNotAttemptPfbBlockStringCompare_WhenLengthTooSmall_50) {
  // Boundary: n just below the threshold for "%!PS-AdobeFont-1" (needs >=16).
  // With defaults for later magic checks, this should fall through to Unknown.
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  EXPECT_CALL(r, getByte(0)).WillOnce(Return(0x80));
  EXPECT_CALL(r, getByte(1)).WillOnce(Return(0x01));

  EXPECT_CALL(r, getU32LE(2, _))
      .WillOnce(DoAll(SetArgPointee<1>(15u), Return(true)));

  // Because n < 16, the AdobeFont compare at pos 6 must not be used to decide PFB.
  // However, the code may still evaluate the second part (FontType1) only if needed.
  // For n=15, FontType1 check requires n>=11; it *can* be evaluated. We force it false.
  EXPECT_CALL(r, cmp(6, StrEq("%!PS-AdobeFont-1"))).Times(0);
  EXPECT_CALL(r, cmp(6, StrEq("%!FontType1"))).WillOnce(Return(false));

  // Ensure it continues to later checks by providing bytes that do not match TT/TTC/OTTO/CFF.
  EXPECT_CALL(r, getByte(2)).WillRepeatedly(Return(0xFF));
  EXPECT_CALL(r, getByte(3)).WillRepeatedly(Return(0xFF));
  EXPECT_CALL(r, getByte(1)).WillRepeatedly(Return(0x01)); // already set once; repeated ok
  EXPECT_CALL(r, getByte(0)).WillRepeatedly(Return(0x80)); // already set once; repeated ok

  EXPECT_EQ(fofiIdUnknown, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, DoesNotCallGetU32LE_WhenPfbMarkerBytesDoNotMatch_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  // First marker byte matches, second does not -> should not call getU32LE.
  EXPECT_CALL(r, getByte(0)).WillOnce(Return(0x80));
  EXPECT_CALL(r, getByte(1)).WillOnce(Return(0x00));
  EXPECT_CALL(r, getU32LE(_, _)).Times(0);

  // Avoid later magic matches.
  EXPECT_CALL(r, getByte(2)).WillRepeatedly(Return(0xFF));
  EXPECT_CALL(r, getByte(3)).WillRepeatedly(Return(0xFF));

  EXPECT_EQ(fofiIdUnknown, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, ReturnsTrueType_WhenSfntVersion00010000_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  // Ensure PFB marker isn't taken: first byte not 0x80
  EXPECT_CALL(r, getByte(0)).WillRepeatedly(Return(0x00));
  EXPECT_CALL(r, getByte(1)).WillRepeatedly(Return(0x01));
  EXPECT_CALL(r, getByte(2)).WillRepeatedly(Return(0x00));
  EXPECT_CALL(r, getByte(3)).WillRepeatedly(Return(0x00));

  // If getU32LE is attempted, make it fail so it doesn't accidentally satisfy PFB.
  EXPECT_CALL(r, getU32LE(_, _)).WillRepeatedly(Return(false));

  EXPECT_EQ(fofiIdTrueType, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, ReturnsTrueType_WhenMagicIsTrueString_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  // Not PFB marker.
  EXPECT_CALL(r, getByte(0)).WillRepeatedly(Return(0x74)); // 't'
  EXPECT_CALL(r, getByte(1)).WillRepeatedly(Return(0x72)); // 'r'
  EXPECT_CALL(r, getByte(2)).WillRepeatedly(Return(0x75)); // 'u'
  EXPECT_CALL(r, getByte(3)).WillRepeatedly(Return(0x65)); // 'e'
  EXPECT_CALL(r, getU32LE(_, _)).WillRepeatedly(Return(false));

  EXPECT_EQ(fofiIdTrueType, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, ReturnsTrueTypeCollection_WhenMagicIsTtcf_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  // Not PFB marker.
  EXPECT_CALL(r, getByte(0)).WillRepeatedly(Return(0x74)); // 't'
  EXPECT_CALL(r, getByte(1)).WillRepeatedly(Return(0x74)); // 't'
  EXPECT_CALL(r, getByte(2)).WillRepeatedly(Return(0x63)); // 'c'
  EXPECT_CALL(r, getByte(3)).WillRepeatedly(Return(0x66)); // 'f'
  EXPECT_CALL(r, getU32LE(_, _)).WillRepeatedly(Return(false));

  EXPECT_EQ(fofiIdTrueTypeCollection, identify(&r));
}

TEST_F(FoFiIdentifierTest_50, ReturnsUnknown_WhenNoKnownSignaturesMatch_50) {
  StrictMock<MockReader> r;

  EXPECT_CALL(r, cmp(0, StrEq("%!PS-AdobeFont-1"))).WillOnce(Return(false));
  EXPECT_CALL(r, cmp(0, StrEq("%!FontType1"))).WillOnce(Return(false));

  // No PFB marker, no TT/TTC/OTTO/CFF patterns.
  EXPECT_CALL(r, getByte(_)).WillRepeatedly(Return(0xFF));
  EXPECT_CALL(r, getU32LE(_, _)).WillRepeatedly(Return(false));
  EXPECT_CALL(r, cmp(_, _)).WillRepeatedly(Return(false));

  EXPECT_EQ(fofiIdUnknown, identify(&r));
}

} // namespace