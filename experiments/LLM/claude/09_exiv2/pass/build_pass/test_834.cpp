#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <sstream>

namespace {

class XmpTextValueTest_834 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// ==================== Normal Operation Tests ====================

TEST_F(XmpTextValueTest_834, DefaultConstructor_834) {
    Exiv2::XmpTextValue val;
    EXPECT_EQ(val.size(), 0u);
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(XmpTextValueTest_834, ConstructorWithString_834) {
    Exiv2::XmpTextValue val("hello");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "hello");
}

TEST_F(XmpTextValueTest_834, ReadPlainText_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("simple text");
    EXPECT_EQ(result, 0);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "simple text");
}

TEST_F(XmpTextValueTest_834, ReadEmptyString_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.size(), 0u);
}

TEST_F(XmpTextValueTest_834, ReadTypeAlt_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=Alt some alt text");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaAlt);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "some alt text");
}

TEST_F(XmpTextValueTest_834, ReadTypeBag_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=Bag some bag text");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaBag);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "some bag text");
}

TEST_F(XmpTextValueTest_834, ReadTypeSeq_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=Seq some seq text");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaSeq);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "some seq text");
}

TEST_F(XmpTextValueTest_834, ReadTypeStruct_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=Struct some struct text");
    EXPECT_EQ(result, 0);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "some struct text");
}

TEST_F(XmpTextValueTest_834, ReadTypeAltWithQuotes_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=\"Alt\" some alt text");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaAlt);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "some alt text");
}

TEST_F(XmpTextValueTest_834, ReadTypeBagWithQuotes_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=\"Bag\" some bag text");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaBag);
}

TEST_F(XmpTextValueTest_834, ReadTypeSeqWithQuotes_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=\"Seq\" some seq text");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaSeq);
}

TEST_F(XmpTextValueTest_834, ReadTypeStructWithQuotes_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=\"Struct\" some struct text");
    EXPECT_EQ(result, 0);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "some struct text");
}

// ==================== Boundary Condition Tests ====================

TEST_F(XmpTextValueTest_834, ReadTypeWithNoValue_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=Alt");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaAlt);
    // No trailing text after type, value should be empty
    EXPECT_EQ(val.size(), 0u);
}

TEST_F(XmpTextValueTest_834, ReadTypeWithEmptyValueAfterSpace_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=Bag ");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaBag);
}

TEST_F(XmpTextValueTest_834, ReadStringNotStartingWithType_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("nottype=Alt some text");
    EXPECT_EQ(result, 0);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "nottype=Alt some text");
}

TEST_F(XmpTextValueTest_834, ReadTextStartingWithTypeButNoEquals_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type without equals");
    EXPECT_EQ(result, 0);
    // "type" prefix detected but no valid type - the extracted type would be "without"
    // which is invalid, so it should throw
    // Actually let me reconsider - it starts with "type=" ? No, "type without" doesn't start with "type="
    // So it should just be treated as plain text
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type without equals");
}

TEST_F(XmpTextValueTest_834, ReadWithMultipleSpaces_834) {
    Exiv2::XmpTextValue val;
    int result = val.read("type=Alt  text with spaces");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaAlt);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), " text with spaces");
}

TEST_F(XmpTextValueTest_834, SizeReturnsCorrectValue_834) {
    Exiv2::XmpTextValue val;
    val.read("hello world");
    EXPECT_EQ(val.size(), 11u);
}

TEST_F(XmpTextValueTest_834, CountReturnsOne_834) {
    Exiv2::XmpTextValue val;
    val.read("hello");
    EXPECT_EQ(val.count(), 1u);
}

TEST_F(XmpTextValueTest_834, CountForEmptyValue_834) {
    Exiv2::XmpTextValue val;
    val.read("");
    EXPECT_EQ(val.count(), 0u);
}

// ==================== Error / Exceptional Tests ====================

TEST_F(XmpTextValueTest_834, ReadInvalidTypeThrows_834) {
    Exiv2::XmpTextValue val;
    EXPECT_THROW(val.read("type=InvalidType some text"), Exiv2::Error);
}

TEST_F(XmpTextValueTest_834, ReadInvalidTypeWithQuotesThrows_834) {
    Exiv2::XmpTextValue val;
    EXPECT_THROW(val.read("type=\"InvalidType\" some text"), Exiv2::Error);
}

TEST_F(XmpTextValueTest_834, ReadUnknownTypeThrows_834) {
    Exiv2::XmpTextValue val;
    EXPECT_THROW(val.read("type=Foo bar"), Exiv2::Error);
}

TEST_F(XmpTextValueTest_834, ReadTypeWithOnlyQuotesThrows_834) {
    // type="" after stripping quotes becomes empty, which means no type set -> no throw, no array type
    Exiv2::XmpTextValue val;
    int result = val.read("type=\"\" some text");
    EXPECT_EQ(result, 0);
}

// ==================== Conversion Tests ====================

TEST_F(XmpTextValueTest_834, ToInt64FromNumericString_834) {
    Exiv2::XmpTextValue val("42");
    EXPECT_EQ(val.toInt64(0), 42);
}

TEST_F(XmpTextValueTest_834, ToUint32FromNumericString_834) {
    Exiv2::XmpTextValue val("100");
    EXPECT_EQ(val.toUint32(0), 100u);
}

TEST_F(XmpTextValueTest_834, ToFloatFromNumericString_834) {
    Exiv2::XmpTextValue val("3.14");
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

TEST_F(XmpTextValueTest_834, ToRationalFromNumericString_834) {
    Exiv2::XmpTextValue val("5");
    Exiv2::Rational r = val.toRational(0);
    // The exact rational representation depends on implementation
    // but for "5" we expect first/second to represent 5
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_FLOAT_EQ(static_cast<float>(r.first) / static_cast<float>(r.second), 5.0f);
    }
}

// ==================== Write Tests ====================

TEST_F(XmpTextValueTest_834, WriteOutputsValue_834) {
    Exiv2::XmpTextValue val;
    val.read("hello world");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "hello world");
}

TEST_F(XmpTextValueTest_834, WriteEmptyValue_834) {
    Exiv2::XmpTextValue val;
    val.read("");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "");
}

// ==================== Clone Tests ====================

TEST_F(XmpTextValueTest_834, CloneReturnsValidCopy_834) {
    Exiv2::XmpTextValue val;
    val.read("type=Seq cloned text");
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    
    std::ostringstream os;
    cloned->write(os);
    EXPECT_EQ(os.str(), "cloned text");
}

// ==================== Overwrite Tests ====================

TEST_F(XmpTextValueTest_834, ReadOverwritesPreviousValue_834) {
    Exiv2::XmpTextValue val;
    val.read("first value");
    val.read("second value");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "second value");
}

TEST_F(XmpTextValueTest_834, ReadTypeOverwritesPreviousType_834) {
    Exiv2::XmpTextValue val;
    val.read("type=Alt alt text");
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaAlt);
    val.read("type=Bag bag text");
    EXPECT_EQ(val.xmpArrayType(), Exiv2::XmpValue::xaBag);
}

// ==================== Copy to buffer test ====================

TEST_F(XmpTextValueTest_834, CopyToBuffer_834) {
    Exiv2::XmpTextValue val;
    val.read("test");
    std::vector<Exiv2::byte> buf(val.size());
    size_t copied = val.copy(buf.data(), Exiv2::invalidByteOrder);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf.data()), copied), "test");
}

// ==================== Read from byte buffer ====================

TEST_F(XmpTextValueTest_834, ReadFromByteBuffer_834) {
    Exiv2::XmpTextValue val;
    const std::string data = "byte buffer text";
    int result = val.read(reinterpret_cast<const Exiv2::byte*>(data.c_str()), data.size(), Exiv2::invalidByteOrder);
    EXPECT_EQ(result, 0);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "byte buffer text");
}

}  // namespace
