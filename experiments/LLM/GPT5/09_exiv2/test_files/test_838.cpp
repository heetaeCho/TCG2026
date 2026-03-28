// File: test_value_xmptextvalue_write_838.cpp
#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <sstream>
#include <string>

namespace {

class XmpTextValueWriteTest_838 : public ::testing::Test {};

static std::string WriteToString(const Exiv2::XmpTextValue& v) {
  std::ostringstream oss;
  v.write(oss);
  return oss.str();
}

TEST_F(XmpTextValueWriteTest_838, DefaultConstructedWritesEmpty_838) {
  Exiv2::XmpTextValue v;
  EXPECT_EQ("", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, ReadThenWriteEmitsValueOnlyByDefault_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("hello")));
  EXPECT_EQ("hello", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, ArrayTypeAltAddsTypePrefixAndSpaceWhenNonEmpty_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("v")));
  v.setXmpArrayType(Exiv2::XmpValue::xaAlt);

  EXPECT_EQ("type=\"Alt\" v", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, ArrayTypeBagAddsTypePrefixAndSpaceWhenNonEmpty_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("data")));
  v.setXmpArrayType(Exiv2::XmpValue::xaBag);

  EXPECT_EQ("type=\"Bag\" data", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, ArrayTypeSeqAddsTypePrefixAndSpaceWhenNonEmpty_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("x")));
  v.setXmpArrayType(Exiv2::XmpValue::xaSeq);

  EXPECT_EQ("type=\"Seq\" x", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, StructTypeAddsTypePrefixAndSpaceWhenNonEmpty_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("payload")));
  v.setXmpStruct(Exiv2::XmpValue::xsStruct);

  EXPECT_EQ("type=\"Struct\" payload", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, ArrayTypeWithEmptyValueDoesNotInsertTrailingSpace_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("")));
  v.setXmpArrayType(Exiv2::XmpValue::xaAlt);

  // No extra space is expected when the value is empty.
  EXPECT_EQ("type=\"Alt\"", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, StructTypeWithEmptyValueDoesNotInsertTrailingSpace_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("")));
  v.setXmpStruct(Exiv2::XmpValue::xsStruct);

  EXPECT_EQ("type=\"Struct\"", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, ArrayTypeTakesPrecedenceOverStructWhenBothSet_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("z")));
  v.setXmpStruct(Exiv2::XmpValue::xsStruct);
  v.setXmpArrayType(Exiv2::XmpValue::xaBag);

  // Observable behavior: output matches the array-type prefix (not Struct) when both are configured.
  EXPECT_EQ("type=\"Bag\" z", WriteToString(v));
}

TEST_F(XmpTextValueWriteTest_838, WriteReturnsSameStreamReferenceForChaining_838) {
  Exiv2::XmpTextValue v;
  ASSERT_EQ(0, v.read(std::string("chain")));
  v.setXmpArrayType(Exiv2::XmpValue::xaSeq);

  std::ostringstream oss;
  std::ostream& ret = v.write(oss);
  EXPECT_EQ(&oss, &ret);

  // Chaining should keep writing to the same stream.
  ret << "|more";
  EXPECT_EQ("type=\"Seq\" chain|more", oss.str());
}

}  // namespace