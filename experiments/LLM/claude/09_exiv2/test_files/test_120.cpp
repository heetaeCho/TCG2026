#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <string>

// Forward declaration of the function under test
namespace Exiv2 {
std::string readStringTag(const BasicIo::UniquePtr& io, size_t length);
}

// We need a concrete implementation of BasicIo for testing.
// Using MemIo which is a standard Exiv2 in-memory IO class.
#include <exiv2/basicio.hpp>

class ReadStringTagTest_120 : public ::testing::Test {
protected:
  std::unique_ptr<Exiv2::BasicIo> createMemIo(const std::string& data) {
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    return io;
  }

  std::unique_ptr<Exiv2::BasicIo> createMemIoFromBytes(const Exiv2::byte* data, size_t size) {
    auto io = std::make_unique<Exiv2::MemIo>(data, size);
    return io;
  }
};

// Test reading a normal string
TEST_F(ReadStringTagTest_120, ReadsNormalString_120) {
  std::string content = "Hello, World!";
  auto io = createMemIo(content);
  io->open();

  std::string result = Exiv2::readStringTag(io, 5);
  EXPECT_EQ(result, "Hello");
}

// Test reading the entire content
TEST_F(ReadStringTagTest_120, ReadsEntireContent_120) {
  std::string content = "TestData";
  auto io = createMemIo(content);
  io->open();

  std::string result = Exiv2::readStringTag(io, content.size());
  EXPECT_EQ(result, "TestData");
}

// Test reading zero-length string
TEST_F(ReadStringTagTest_120, ReadsZeroLengthString_120) {
  std::string content = "SomeData";
  auto io = createMemIo(content);
  io->open();

  std::string result = Exiv2::readStringTag(io, 0);
  EXPECT_EQ(result, "");
}

// Test reading a single character
TEST_F(ReadStringTagTest_120, ReadsSingleCharacter_120) {
  std::string content = "A";
  auto io = createMemIo(content);
  io->open();

  std::string result = Exiv2::readStringTag(io, 1);
  EXPECT_EQ(result, "A");
}

// Test that reading more than available data throws an exception
TEST_F(ReadStringTagTest_120, ThrowsWhenLengthExceedsAvailable_120) {
  std::string content = "Short";
  auto io = createMemIo(content);
  io->open();

  EXPECT_THROW(Exiv2::readStringTag(io, content.size() + 10), Exiv2::Error);
}

// Test reading after seeking partway through
TEST_F(ReadStringTagTest_120, ReadsFromCurrentPosition_120) {
  std::string content = "HelloWorld";
  auto io = createMemIo(content);
  io->open();
  io->seek(5, Exiv2::BasicIo::beg);

  std::string result = Exiv2::readStringTag(io, 5);
  EXPECT_EQ(result, "World");
}

// Test that the IO position advances after reading
TEST_F(ReadStringTagTest_120, AdvancesIOPosition_120) {
  std::string content = "ABCDEFGHIJ";
  auto io = createMemIo(content);
  io->open();

  Exiv2::readStringTag(io, 5);
  EXPECT_EQ(io->tell(), 5u);
}

// Test reading string with null bytes - should be truncated at null
TEST_F(ReadStringTagTest_120, HandlesNullBytesInData_120) {
  const Exiv2::byte data[] = {'H', 'e', 'l', '\0', 'o'};
  auto io = createMemIoFromBytes(data, sizeof(data));
  io->open();

  std::string result = Exiv2::readStringTag(io, 5);
  // toString typically stops at null, and substr(0, length) limits it
  // The result should be "Hel" since toString stops at null byte
  EXPECT_EQ(result, "Hel");
}

// Test reading when position is at the end - length > 0 should throw
TEST_F(ReadStringTagTest_120, ThrowsWhenAtEndOfStream_120) {
  std::string content = "Data";
  auto io = createMemIo(content);
  io->open();
  io->seek(0, Exiv2::BasicIo::end);

  EXPECT_THROW(Exiv2::readStringTag(io, 1), Exiv2::Error);
}

// Test reading exactly all remaining bytes from current position
TEST_F(ReadStringTagTest_120, ReadsExactlyRemainingBytes_120) {
  std::string content = "0123456789";
  auto io = createMemIo(content);
  io->open();
  io->seek(7, Exiv2::BasicIo::beg);

  std::string result = Exiv2::readStringTag(io, 3);
  EXPECT_EQ(result, "789");
}

// Test reading with spaces and special characters
TEST_F(ReadStringTagTest_120, ReadsSpecialCharacters_120) {
  std::string content = "Hello World!\n\tTest";
  auto io = createMemIo(content);
  io->open();

  std::string result = Exiv2::readStringTag(io, 12);
  EXPECT_EQ(result, "Hello World!");
}

// Test multiple consecutive reads
TEST_F(ReadStringTagTest_120, MultipleConsecutiveReads_120) {
  std::string content = "AABBCCDD";
  auto io = createMemIo(content);
  io->open();

  std::string result1 = Exiv2::readStringTag(io, 2);
  EXPECT_EQ(result1, "AA");

  std::string result2 = Exiv2::readStringTag(io, 2);
  EXPECT_EQ(result2, "BB");

  std::string result3 = Exiv2::readStringTag(io, 2);
  EXPECT_EQ(result3, "CC");

  std::string result4 = Exiv2::readStringTag(io, 2);
  EXPECT_EQ(result4, "DD");
}

// Test that requesting exactly one more byte than available throws
TEST_F(ReadStringTagTest_120, ThrowsWhenRequestingOneMoreThanAvailable_120) {
  std::string content = "ABC";
  auto io = createMemIo(content);
  io->open();

  EXPECT_THROW(Exiv2::readStringTag(io, 4), Exiv2::Error);
}

// Test reading binary-like data (non-printable characters, but no null)
TEST_F(ReadStringTagTest_120, ReadsBinaryNonNullData_120) {
  const Exiv2::byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  auto io = createMemIoFromBytes(data, sizeof(data));
  io->open();

  std::string result = Exiv2::readStringTag(io, 5);
  EXPECT_EQ(result.size(), 5u);
}

// Test that reading at position 0 on empty IO with length 0 works
TEST_F(ReadStringTagTest_120, EmptyIOZeroLength_120) {
  std::string content = "";
  auto io = createMemIo(content);
  io->open();

  std::string result = Exiv2::readStringTag(io, 0);
  EXPECT_EQ(result, "");
}

// Test that reading from empty IO with non-zero length throws
TEST_F(ReadStringTagTest_120, EmptyIONonZeroLengthThrows_120) {
  std::string content = "";
  auto io = createMemIo(content);
  io->open();

  EXPECT_THROW(Exiv2::readStringTag(io, 1), Exiv2::Error);
}
