#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <string>

// Forward declaration of the function under test
namespace Exiv2 {
bool isQTimeType(BasicIo& iIo, bool advance);
}

// Mock class for BasicIo
class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool isWriteable), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(size_t, tell, (), (const, override));
  MOCK_METHOD(size_t, size, (), (const, override));
  MOCK_METHOD(bool, isopen, (), (const, override));
  MOCK_METHOD(int, error, (), (const, override));
  MOCK_METHOD(bool, eof, (), (const, override));
  MOCK_METHOD(const std::string&, path, (), (const, override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class IsQTimeTypeTest_662 : public ::testing::Test {
 protected:
  MockBasicIo mockIo;
  std::string dummyPath = "test";
};

// Helper to set up a successful read with specific 12-byte data
// Bytes 0-3: size (ignored by the function logic, just needs to be there)
// Bytes 4-7: tag (e.g., "ftyp", "moov", etc.)
// Bytes 8-11: file type (e.g., "isom", "mp42", etc.)
static void setupRead(MockBasicIo& mockIo, const char data[12], size_t readReturn = 12) {
  ON_CALL(mockIo, read(testing::_, testing::_))
      .WillByDefault([data, readReturn](Exiv2::byte* buf, size_t rcount) -> size_t {
        size_t toCopy = std::min(rcount, readReturn);
        std::memcpy(buf, data, toCopy);
        return toCopy;
      });
  ON_CALL(mockIo, error()).WillByDefault(testing::Return(0));
  ON_CALL(mockIo, eof()).WillByDefault(testing::Return(false));
}

// Test: Valid ftyp + isom should return true
TEST_F(IsQTimeTypeTest_662, ValidFtypIsom_662) {
  // 4 bytes size + "ftyp" + "isom"
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'f', 't', 'y', 'p', 'i', 's', 'o', 'm'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: Valid ftyp + mp42 should return true
TEST_F(IsQTimeTypeTest_662, ValidFtypMp42_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'f', 't', 'y', 'p', 'm', 'p', '4', '2'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, false);
  EXPECT_TRUE(result);
}

// Test: Valid moov tag but no matching file type at bytes 8-11 should return false
TEST_F(IsQTimeTypeTest_662, ValidTagButInvalidFileType_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'm', 'o', 'o', 'v', 'X', 'X', 'X', 'X'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1).WillOnce(testing::Return(0));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: Invalid tag (not in qTimeTags list) should return false
TEST_F(IsQTimeTypeTest_662, InvalidTag_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'X', 'X', 'X', 'X', 'i', 's', 'o', 'm'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1).WillOnce(testing::Return(0));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: IO error on read should return false
TEST_F(IsQTimeTypeTest_662, IoErrorOnRead_662) {
  EXPECT_CALL(mockIo, read(testing::_, 12)).WillOnce([](Exiv2::byte* buf, size_t) -> size_t {
    return 0;
  });
  EXPECT_CALL(mockIo, error()).WillRepeatedly(testing::Return(1));
  EXPECT_CALL(mockIo, eof()).WillRepeatedly(testing::Return(false));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: EOF on read should return false
TEST_F(IsQTimeTypeTest_662, EofOnRead_662) {
  EXPECT_CALL(mockIo, read(testing::_, 12)).WillOnce([](Exiv2::byte* buf, size_t) -> size_t {
    return 0;
  });
  EXPECT_CALL(mockIo, error()).WillRepeatedly(testing::Return(0));
  EXPECT_CALL(mockIo, eof()).WillRepeatedly(testing::Return(true));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: advance=false with valid data should seek back to beginning
TEST_F(IsQTimeTypeTest_662, AdvanceFalseSeeksBack_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'f', 't', 'y', 'p', 'i', 's', 'o', 'm'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1).WillOnce(testing::Return(0));

  bool result = Exiv2::isQTimeType(mockIo, false);
  EXPECT_TRUE(result);
}

// Test: advance=true with valid data should NOT seek back
TEST_F(IsQTimeTypeTest_662, AdvanceTrueDoesNotSeekBack_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'f', 't', 'y', 'p', 'i', 's', 'o', 'm'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, seek(testing::_, testing::_)).Times(0);

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "free" tag with valid file type
TEST_F(IsQTimeTypeTest_662, FreeTagWithValidFileType_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'f', 'r', 'e', 'e', 'q', 't', ' ', ' '};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "mdat" tag with valid file type "3gp4"
TEST_F(IsQTimeTypeTest_662, MdatTagWith3gp4_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'm', 'd', 'a', 't', '3', 'g', 'p', '4'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "skip" tag with valid file type "M4A "
TEST_F(IsQTimeTypeTest_662, SkipTagWithM4A_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 's', 'k', 'i', 'p', 'M', '4', 'A', ' '};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "wide" tag with valid file type "CAEP"
TEST_F(IsQTimeTypeTest_662, WideTagWithCAEP_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'w', 'i', 'd', 'e', 'C', 'A', 'E', 'P'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "uuid" tag with valid file type "pana"
TEST_F(IsQTimeTypeTest_662, UuidTagWithPana_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'u', 'u', 'i', 'd', 'p', 'a', 'n', 'a'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "PICT" tag with valid file type "NIKO"
TEST_F(IsQTimeTypeTest_662, PICTTagWithNIKO_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'P', 'I', 'C', 'T', 'N', 'I', 'K', 'O'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "pict" tag (lowercase) with valid file type
TEST_F(IsQTimeTypeTest_662, PictLowercaseTagValid_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'p', 'i', 'c', 't', 'i', 's', 'o', 'm'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "pnot" tag with valid file type
TEST_F(IsQTimeTypeTest_662, PnotTagValid_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'p', 'n', 'o', 't', 'm', 'p', '4', '1'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "junk" tag with valid file type
TEST_F(IsQTimeTypeTest_662, JunkTagValid_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'j', 'u', 'n', 'k', 'a', 'v', 'c', '1'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: ftyp tag with unrecognized file type should return false and seek back
TEST_F(IsQTimeTypeTest_662, FtypTagUnrecognizedFileType_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'f', 't', 'y', 'p', 'Z', 'Z', 'Z', 'Z'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1).WillOnce(testing::Return(0));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: advance=true with non-matched result should still seek back
TEST_F(IsQTimeTypeTest_662, AdvanceTrueNotMatchedSeeksBack_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'A', 'B', 'C', 'D', 'i', 's', 'o', 'm'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1).WillOnce(testing::Return(0));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: All zeroes in data should return false
TEST_F(IsQTimeTypeTest_662, AllZeroesReturnFalse_662) {
  char data[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1).WillOnce(testing::Return(0));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: "ftyp" with "qt  " (Apple QuickTime) file type
TEST_F(IsQTimeTypeTest_662, FtypWithAppleQuickTime_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x14, 'f', 't', 'y', 'p', 'q', 't', ' ', ' '};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: Both error and eof true should return false
TEST_F(IsQTimeTypeTest_662, BothErrorAndEof_662) {
  EXPECT_CALL(mockIo, read(testing::_, 12)).WillOnce([](Exiv2::byte*, size_t) -> size_t {
    return 0;
  });
  EXPECT_CALL(mockIo, error()).WillRepeatedly(testing::Return(1));
  EXPECT_CALL(mockIo, eof()).WillRepeatedly(testing::Return(true));

  bool result = Exiv2::isQTimeType(mockIo, false);
  EXPECT_FALSE(result);
}

// Test: "ftyp" tag with "3g2a" file type (3GPP2)
TEST_F(IsQTimeTypeTest_662, FtypWith3g2a_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'f', 't', 'y', 'p', '3', 'g', '2', 'a'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: "moov" tag with "niko" file type (Nikon)
TEST_F(IsQTimeTypeTest_662, MoovTagWithNiko_662) {
  char data[12] = {0x00, 0x00, 0x00, 0x0C, 'm', 'o', 'o', 'v', 'n', 'i', 'k', 'o'};
  setupRead(mockIo, data);

  EXPECT_CALL(mockIo, read(testing::_, 12)).Times(1);
  EXPECT_CALL(mockIo, error()).Times(testing::AtLeast(1));
  EXPECT_CALL(mockIo, eof()).Times(testing::AtLeast(1));

  bool result = Exiv2::isQTimeType(mockIo, true);
  EXPECT_TRUE(result);
}
