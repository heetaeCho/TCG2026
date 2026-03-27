// FoFiIdentifier_identifyOpenType_51_test.cc
#include <climits>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "FoFiIdentifier.h"

// The function under test is `static` in FoFiIdentifier.cc.
// We include the .cc into this test TU to access it.
// To control the external collaborator `identifyCFF(Reader*, int)` (called by identifyOpenType),
// we macro-rename it to a test shim symbol and provide a controllable stub.
//
// NOTE: This does NOT infer internal logic of identifyCFF; it only lets us observe that
// identifyOpenType calls it (and how it maps its return values).

class Reader; // forward (matches the production type name)

// Test shim controls
namespace {
FoFiIdentifierType g_identifyCFF_return = fofiIdUnknown;
int g_identifyCFF_calls = 0;
int g_identifyCFF_lastOffset = -1;

static FoFiIdentifierType test_identifyCFF(Reader *reader, int offset);
} // namespace

#define identifyCFF test_identifyCFF
#include "FoFiIdentifier.cc"
#undef identifyCFF

namespace {
static FoFiIdentifierType test_identifyCFF(Reader * /*reader*/, int offset) {
  ++g_identifyCFF_calls;
  g_identifyCFF_lastOffset = offset;
  return g_identifyCFF_return;
}
} // namespace

// Mock Reader (external dependency)
class MockReader : public Reader {
public:
  MOCK_METHOD(int, getByte, (int pos), (override));
  MOCK_METHOD(bool, getU16BE, (int pos, int *val), (override));
  MOCK_METHOD(bool, getU32BE, (int pos, unsigned int *val), (override));
  MOCK_METHOD(bool, getU32LE, (int pos, unsigned int *val), (override));
  MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int *val), (override));
  MOCK_METHOD(bool, cmp, (int pos, const char *s), (override));
};

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrictMock;

class FoFiIdentifyOpenTypeTest_51 : public ::testing::Test {
protected:
  void SetUp() override {
    g_identifyCFF_return = fofiIdUnknown;
    g_identifyCFF_calls = 0;
    g_identifyCFF_lastOffset = -1;
  }
};

// -------- Tests --------

TEST_F(FoFiIdentifyOpenTypeTest_51, ReturnsUnknownWhenCannotReadNumTables_51) {
  StrictMock<MockReader> reader;

  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(Return(false));
  // No other calls expected.

  EXPECT_EQ(identifyOpenType(&reader), fofiIdUnknown);
  EXPECT_EQ(g_identifyCFF_calls, 0);
}

TEST_F(FoFiIdentifyOpenTypeTest_51, ReturnsUnknownWhenNumTablesIsZero_51) {
  StrictMock<MockReader> reader;

  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
  // With 0 tables, loop is skipped; no cmp calls.

  EXPECT_EQ(identifyOpenType(&reader), fofiIdUnknown);
  EXPECT_EQ(g_identifyCFF_calls, 0);
}

TEST_F(FoFiIdentifyOpenTypeTest_51, ReturnsUnknownWhenNoCFFTableFound_51) {
  StrictMock<MockReader> reader;

  constexpr int nTables = 3;
  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(DoAll(SetArgPointee<1>(nTables), Return(true)));

  // identifyOpenType checks each table at (12 + i*16) for tag "CFF "
  EXPECT_CALL(reader, cmp(12 + 0 * 16, testing::StrEq("CFF "))).WillOnce(Return(false));
  EXPECT_CALL(reader, cmp(12 + 1 * 16, testing::StrEq("CFF "))).WillOnce(Return(false));
  EXPECT_CALL(reader, cmp(12 + 2 * 16, testing::StrEq("CFF "))).WillOnce(Return(false));

  EXPECT_EQ(identifyOpenType(&reader), fofiIdUnknown);
  EXPECT_EQ(g_identifyCFF_calls, 0);
}

TEST_F(FoFiIdentifyOpenTypeTest_51, ReturnsUnknownWhenCFFFoundButCannotReadOffset_51) {
  StrictMock<MockReader> reader;

  constexpr int nTables = 2;
  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(DoAll(SetArgPointee<1>(nTables), Return(true)));

  // First table not CFF, second is CFF.
  EXPECT_CALL(reader, cmp(12 + 0 * 16, testing::StrEq("CFF "))).WillOnce(Return(false));
  EXPECT_CALL(reader, cmp(12 + 1 * 16, testing::StrEq("CFF "))).WillOnce(Return(true));

  // getU32BE at (12 + i*16 + 8)
  EXPECT_CALL(reader, getU32BE(12 + 1 * 16 + 8, _)).WillOnce(Return(false));

  EXPECT_EQ(identifyOpenType(&reader), fofiIdUnknown);
  EXPECT_EQ(g_identifyCFF_calls, 0);
}

TEST_F(FoFiIdentifyOpenTypeTest_51, ReturnsUnknownWhenOffsetIsNotLessThanIntMax_51) {
  StrictMock<MockReader> reader;

  constexpr int nTables = 1;
  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(DoAll(SetArgPointee<1>(nTables), Return(true)));
  EXPECT_CALL(reader, cmp(12 + 0 * 16, testing::StrEq("CFF "))).WillOnce(Return(true));

  // Provide offset == INT_MAX (should fail offset < INT_MAX)
  EXPECT_CALL(reader, getU32BE(12 + 0 * 16 + 8, _))
      .WillOnce(DoAll(SetArgPointee<1>(static_cast<unsigned int>(INT_MAX)), Return(true)));

  EXPECT_EQ(identifyOpenType(&reader), fofiIdUnknown);
  EXPECT_EQ(g_identifyCFF_calls, 0);
}

TEST_F(FoFiIdentifyOpenTypeTest_51, CallsIdentifyCFFWithOffsetAndMapsCFF8BitToOpenTypeCFF8Bit_51) {
  StrictMock<MockReader> reader;

  constexpr int nTables = 1;
  constexpr unsigned int offset = 1234;

  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(DoAll(SetArgPointee<1>(nTables), Return(true)));
  EXPECT_CALL(reader, cmp(12 + 0 * 16, testing::StrEq("CFF "))).WillOnce(Return(true));
  EXPECT_CALL(reader, getU32BE(12 + 0 * 16 + 8, _))
      .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

  g_identifyCFF_return = fofiIdCFF8Bit;

  EXPECT_EQ(identifyOpenType(&reader), fofiIdOpenTypeCFF8Bit);
  EXPECT_EQ(g_identifyCFF_calls, 1);
  EXPECT_EQ(g_identifyCFF_lastOffset, static_cast<int>(offset));
}

TEST_F(FoFiIdentifyOpenTypeTest_51, CallsIdentifyCFFWithOffsetAndMapsCFFCIDToOpenTypeCFFCID_51) {
  StrictMock<MockReader> reader;

  constexpr int nTables = 4;
  constexpr int idx = 2;
  constexpr unsigned int offset = 77;

  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(DoAll(SetArgPointee<1>(nTables), Return(true)));

  // Not found for i=0,1; found at i=2; should return immediately after handling.
  EXPECT_CALL(reader, cmp(12 + 0 * 16, testing::StrEq("CFF "))).WillOnce(Return(false));
  EXPECT_CALL(reader, cmp(12 + 1 * 16, testing::StrEq("CFF "))).WillOnce(Return(false));
  EXPECT_CALL(reader, cmp(12 + idx * 16, testing::StrEq("CFF "))).WillOnce(Return(true));

  EXPECT_CALL(reader, getU32BE(12 + idx * 16 + 8, _))
      .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

  g_identifyCFF_return = fofiIdCFFCID;

  EXPECT_EQ(identifyOpenType(&reader), fofiIdOpenTypeCFFCID);
  EXPECT_EQ(g_identifyCFF_calls, 1);
  EXPECT_EQ(g_identifyCFF_lastOffset, static_cast<int>(offset));
}

TEST_F(FoFiIdentifyOpenTypeTest_51, ReturnsIdentifyCFFResultUnchangedWhenNotCFF8BitOrCFFCID_51) {
  StrictMock<MockReader> reader;

  constexpr int nTables = 1;
  constexpr unsigned int offset = 5;

  EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(DoAll(SetArgPointee<1>(nTables), Return(true)));
  EXPECT_CALL(reader, cmp(12 + 0 * 16, testing::StrEq("CFF "))).WillOnce(Return(true));
  EXPECT_CALL(reader, getU32BE(12 + 0 * 16 + 8, _))
      .WillOnce(DoAll(SetArgPointee<1>(offset), Return(true)));

  // Pick a value that should not be remapped by identifyOpenType.
  g_identifyCFF_return = fofiIdUnknown;

  EXPECT_EQ(identifyOpenType(&reader), fofiIdUnknown);
  EXPECT_EQ(g_identifyCFF_calls, 1);
  EXPECT_EQ(g_identifyCFF_lastOffset, static_cast<int>(offset));
}