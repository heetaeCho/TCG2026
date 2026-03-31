#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Test default construction
TEST(CommentValueTest_132, DefaultConstruction_132) {
  CommentValue cv;
  // Default constructed CommentValue should have empty comment
  std::string comment = cv.comment("");
  EXPECT_TRUE(comment.empty());
}

// Test construction with a string
TEST(CommentValueTest_132, ConstructionWithString_132) {
  CommentValue cv("Hello, World!");
  std::string comment = cv.comment("");
  EXPECT_EQ(comment, "Hello, World!");
}

// Test construction with charset prefix
TEST(CommentValueTest_132, ConstructionWithCharsetPrefix_132) {
  CommentValue cv("charset=\"Ascii\" This is ASCII");
  std::string comment = cv.comment("");
  EXPECT_EQ(comment, "This is ASCII");
}

// Test read from string
TEST(CommentValueTest_132, ReadFromString_132) {
  CommentValue cv;
  int result = cv.read("Test comment");
  EXPECT_EQ(result, 0);
  std::string comment = cv.comment("");
  EXPECT_EQ(comment, "Test comment");
}

// Test read from string with charset
TEST(CommentValueTest_132, ReadFromStringWithCharset_132) {
  CommentValue cv;
  int result = cv.read("charset=\"Ascii\" ASCII comment");
  EXPECT_EQ(result, 0);
  std::string comment = cv.comment("");
  EXPECT_EQ(comment, "ASCII comment");
}

// Test read from byte buffer
TEST(CommentValueTest_132, ReadFromByteBuffer_132) {
  CommentValue cv;
  // UserComment has 8 bytes of charset info followed by the actual comment
  // ASCII charset: "ASCII\0\0\0"
  const char data[] = "ASCII\0\0\0Hello";
  int result = cv.read(reinterpret_cast<const byte*>(data), sizeof(data) - 1, littleEndian);
  EXPECT_EQ(result, 0);
}

// Test copy to buffer
TEST(CommentValueTest_132, CopyToBuffer_132) {
  CommentValue cv("charset=\"Ascii\" Test");
  byte buf[256];
  memset(buf, 0, sizeof(buf));
  size_t copied = cv.copy(buf, littleEndian);
  EXPECT_GT(copied, 0u);
}

// Test write to ostream
TEST(CommentValueTest_132, WriteToOstream_132) {
  CommentValue cv("charset=\"Ascii\" Hello Output");
  std::ostringstream os;
  cv.write(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
  EXPECT_NE(output.find("Hello Output"), std::string::npos);
}

// Test clone
TEST(CommentValueTest_132, Clone_132) {
  CommentValue cv("charset=\"Ascii\" Clone test");
  auto cloned = cv.clone();
  ASSERT_NE(cloned, nullptr);
  std::string original_comment = cv.comment("");
  std::string cloned_comment = cloned->comment("");
  EXPECT_EQ(original_comment, cloned_comment);
}

// Test charsetId for ASCII
TEST(CommentValueTest_132, CharsetIdAscii_132) {
  CommentValue cv("charset=\"Ascii\" ASCII text");
  CommentValue::CharsetId id = cv.charsetId();
  EXPECT_EQ(id, CommentValue::ascii);
}

// Test charsetId for Unicode
TEST(CommentValueTest_132, CharsetIdUnicode_132) {
  CommentValue cv("charset=\"Unicode\" Unicode text");
  CommentValue::CharsetId id = cv.charsetId();
  EXPECT_EQ(id, CommentValue::unicode);
}

// Test charsetId for undefined/default
TEST(CommentValueTest_132, CharsetIdUndefined_132) {
  CommentValue cv("Just a plain comment");
  CommentValue::CharsetId id = cv.charsetId();
  EXPECT_EQ(id, CommentValue::undefined);
}

// Test detectCharset
TEST(CommentValueTest_132, DetectCharsetAscii_132) {
  CommentValue cv("charset=\"Ascii\" Detect me");
  std::string c;
  const char* detected = cv.detectCharset(c);
  ASSERT_NE(detected, nullptr);
}

// Test empty comment
TEST(CommentValueTest_132, EmptyComment_132) {
  CommentValue cv("");
  std::string comment = cv.comment("");
  EXPECT_TRUE(comment.empty());
}

// Test reading empty byte buffer
TEST(CommentValueTest_132, ReadEmptyByteBuffer_132) {
  CommentValue cv;
  int result = cv.read(nullptr, 0, littleEndian);
  // Just ensure it doesn't crash; result may vary
  (void)result;
}

// Test overwriting value with read
TEST(CommentValueTest_132, OverwriteWithRead_132) {
  CommentValue cv("First comment");
  cv.read("Second comment");
  std::string comment = cv.comment("");
  EXPECT_EQ(comment, "Second comment");
}

// Test comment with explicit encoding parameter
TEST(CommentValueTest_132, CommentWithEncoding_132) {
  CommentValue cv("charset=\"Ascii\" Encoded");
  std::string comment = cv.comment("ASCII");
  // The comment function should handle encoding conversion
  EXPECT_FALSE(comment.empty());
}

// Test write to ostream for default charset
TEST(CommentValueTest_132, WriteDefaultCharset_132) {
  CommentValue cv("No charset specified");
  std::ostringstream os;
  cv.write(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// Test charsetId for Jis
TEST(CommentValueTest_132, CharsetIdJis_132) {
  CommentValue cv("charset=\"Jis\" JIS text");
  CommentValue::CharsetId id = cv.charsetId();
  EXPECT_EQ(id, CommentValue::jis);
}

// Test copy returns correct size for ASCII comment
TEST(CommentValueTest_132, CopySizeConsistency_132) {
  CommentValue cv("charset=\"Ascii\" Size test");
  byte buf[256];
  memset(buf, 0, sizeof(buf));
  size_t size = cv.copy(buf, littleEndian);
  // Size should include charset header (8 bytes) + comment length
  EXPECT_GE(size, 8u);
}

// Test clone independence - modifying original doesn't affect clone
TEST(CommentValueTest_132, CloneIndependence_132) {
  CommentValue cv("Original");
  auto cloned = cv.clone();
  cv.read("Modified");
  std::string cloned_comment = cloned->comment("");
  EXPECT_EQ(cloned_comment, "Original");
}

// Test read with byte buffer containing Unicode charset header
TEST(CommentValueTest_132, ReadUnicodeByteBuffer_132) {
  CommentValue cv;
  // Unicode charset header: "UNICODE\0"
  byte data[16];
  memcpy(data, "UNICODE\0", 8);
  // Some UTF-16 data after the header
  data[8] = 'H';
  data[9] = 0;
  data[10] = 'i';
  data[11] = 0;
  int result = cv.read(data, 12, littleEndian);
  EXPECT_EQ(result, 0);
  CommentValue::CharsetId id = cv.charsetId();
  EXPECT_EQ(id, CommentValue::unicode);
}

// Test big endian byte order
TEST(CommentValueTest_132, BigEndianByteOrder_132) {
  CommentValue cv;
  const char data[] = "ASCII\0\0\0BigEndian";
  int result = cv.read(reinterpret_cast<const byte*>(data), sizeof(data) - 1, bigEndian);
  EXPECT_EQ(result, 0);
}

// Test long comment string
TEST(CommentValueTest_132, LongComment_132) {
  std::string longStr(10000, 'A');
  CommentValue cv(longStr);
  std::string comment = cv.comment("");
  EXPECT_EQ(comment, longStr);
}
