#include <gtest/gtest.h>
#include <exiv2/types.hpp>

namespace {

class TypeInfoTest_1112 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== typeName tests ====================

TEST_F(TypeInfoTest_1112, TypeName_InvalidTypeId_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::invalidTypeId);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Invalid", name);
}

TEST_F(TypeInfoTest_1112, TypeName_UnsignedByte_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedByte);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Byte", name);
}

TEST_F(TypeInfoTest_1112, TypeName_AsciiString_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::asciiString);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Ascii", name);
}

TEST_F(TypeInfoTest_1112, TypeName_UnsignedShort_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedShort);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Short", name);
}

TEST_F(TypeInfoTest_1112, TypeName_UnsignedLong_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedLong);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Long", name);
}

TEST_F(TypeInfoTest_1112, TypeName_UnsignedRational_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedRational);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Rational", name);
}

TEST_F(TypeInfoTest_1112, TypeName_SignedByte_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedByte);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SByte", name);
}

TEST_F(TypeInfoTest_1112, TypeName_Undefined_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::undefined);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Undefined", name);
}

TEST_F(TypeInfoTest_1112, TypeName_SignedShort_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedShort);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SShort", name);
}

TEST_F(TypeInfoTest_1112, TypeName_SignedLong_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedLong);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SLong", name);
}

TEST_F(TypeInfoTest_1112, TypeName_SignedRational_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::signedRational);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("SRational", name);
}

TEST_F(TypeInfoTest_1112, TypeName_TiffFloat_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffFloat);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Float", name);
}

TEST_F(TypeInfoTest_1112, TypeName_TiffDouble_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffDouble);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Double", name);
}

TEST_F(TypeInfoTest_1112, TypeName_TiffIfd_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::tiffIfd);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Ifd", name);
}

TEST_F(TypeInfoTest_1112, TypeName_String_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::string);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("String", name);
}

TEST_F(TypeInfoTest_1112, TypeName_Date_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::date);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Date", name);
}

TEST_F(TypeInfoTest_1112, TypeName_Time_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::time);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Time", name);
}

TEST_F(TypeInfoTest_1112, TypeName_Comment_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::comment);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Comment", name);
}

TEST_F(TypeInfoTest_1112, TypeName_Directory_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::directory);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("Directory", name);
}

TEST_F(TypeInfoTest_1112, TypeName_XmpText_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpText);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpText", name);
}

TEST_F(TypeInfoTest_1112, TypeName_XmpAlt_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpAlt);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpAlt", name);
}

TEST_F(TypeInfoTest_1112, TypeName_XmpBag_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpBag);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpBag", name);
}

TEST_F(TypeInfoTest_1112, TypeName_XmpSeq_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::xmpSeq);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("XmpSeq", name);
}

TEST_F(TypeInfoTest_1112, TypeName_LangAlt_1112) {
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::langAlt);
    ASSERT_NE(nullptr, name);
    EXPECT_STREQ("LangAlt", name);
}

TEST_F(TypeInfoTest_1112, TypeName_UnknownTypeId_ReturnsNull_1112) {
    const char* name = Exiv2::TypeInfo::typeName(static_cast<Exiv2::TypeId>(9999));
    EXPECT_EQ(nullptr, name);
}

TEST_F(TypeInfoTest_1112, TypeName_NegativeTypeId_ReturnsNull_1112) {
    const char* name = Exiv2::TypeInfo::typeName(static_cast<Exiv2::TypeId>(-1));
    EXPECT_EQ(nullptr, name);
}

// ==================== typeId tests ====================

TEST_F(TypeInfoTest_1112, TypeId_FromInvalid_1112) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("Invalid"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromByte_1112) {
    EXPECT_EQ(Exiv2::unsignedByte, Exiv2::TypeInfo::typeId("Byte"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromAscii_1112) {
    EXPECT_EQ(Exiv2::asciiString, Exiv2::TypeInfo::typeId("Ascii"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromShort_1112) {
    EXPECT_EQ(Exiv2::unsignedShort, Exiv2::TypeInfo::typeId("Short"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromLong_1112) {
    EXPECT_EQ(Exiv2::unsignedLong, Exiv2::TypeInfo::typeId("Long"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromRational_1112) {
    EXPECT_EQ(Exiv2::unsignedRational, Exiv2::TypeInfo::typeId("Rational"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromSByte_1112) {
    EXPECT_EQ(Exiv2::signedByte, Exiv2::TypeInfo::typeId("SByte"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromUndefined_1112) {
    EXPECT_EQ(Exiv2::undefined, Exiv2::TypeInfo::typeId("Undefined"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromSShort_1112) {
    EXPECT_EQ(Exiv2::signedShort, Exiv2::TypeInfo::typeId("SShort"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromSLong_1112) {
    EXPECT_EQ(Exiv2::signedLong, Exiv2::TypeInfo::typeId("SLong"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromSRational_1112) {
    EXPECT_EQ(Exiv2::signedRational, Exiv2::TypeInfo::typeId("SRational"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromFloat_1112) {
    EXPECT_EQ(Exiv2::tiffFloat, Exiv2::TypeInfo::typeId("Float"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromDouble_1112) {
    EXPECT_EQ(Exiv2::tiffDouble, Exiv2::TypeInfo::typeId("Double"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromIfd_1112) {
    EXPECT_EQ(Exiv2::tiffIfd, Exiv2::TypeInfo::typeId("Ifd"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromString_1112) {
    EXPECT_EQ(Exiv2::string, Exiv2::TypeInfo::typeId("String"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromDate_1112) {
    EXPECT_EQ(Exiv2::date, Exiv2::TypeInfo::typeId("Date"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromTime_1112) {
    EXPECT_EQ(Exiv2::time, Exiv2::TypeInfo::typeId("Time"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromComment_1112) {
    EXPECT_EQ(Exiv2::comment, Exiv2::TypeInfo::typeId("Comment"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromDirectory_1112) {
    EXPECT_EQ(Exiv2::directory, Exiv2::TypeInfo::typeId("Directory"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromXmpText_1112) {
    EXPECT_EQ(Exiv2::xmpText, Exiv2::TypeInfo::typeId("XmpText"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromXmpAlt_1112) {
    EXPECT_EQ(Exiv2::xmpAlt, Exiv2::TypeInfo::typeId("XmpAlt"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromXmpBag_1112) {
    EXPECT_EQ(Exiv2::xmpBag, Exiv2::TypeInfo::typeId("XmpBag"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromXmpSeq_1112) {
    EXPECT_EQ(Exiv2::xmpSeq, Exiv2::TypeInfo::typeId("XmpSeq"));
}

TEST_F(TypeInfoTest_1112, TypeId_FromLangAlt_1112) {
    EXPECT_EQ(Exiv2::langAlt, Exiv2::TypeInfo::typeId("LangAlt"));
}

TEST_F(TypeInfoTest_1112, TypeId_UnknownName_ReturnsInvalidTypeId_1112) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("NonExistentType"));
}

TEST_F(TypeInfoTest_1112, TypeId_EmptyString_ReturnsInvalidTypeId_1112) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId(""));
}

TEST_F(TypeInfoTest_1112, TypeId_CaseSensitive_1112) {
    // "byte" is not "Byte", should not match
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("byte"));
}

TEST_F(TypeInfoTest_1112, TypeId_CaseSensitive_Uppercase_1112) {
    EXPECT_EQ(Exiv2::invalidTypeId, Exiv2::TypeInfo::typeId("BYTE"));
}

// ==================== typeSize tests ====================

TEST_F(TypeInfoTest_1112, TypeSize_InvalidTypeId_1112) {
    EXPECT_EQ(0u, Exiv2::TypeInfo::typeSize(Exiv2::invalidTypeId));
}

TEST_F(TypeInfoTest_1112, TypeSize_UnsignedByte_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedByte));
}

TEST_F(TypeInfoTest_1112, TypeSize_AsciiString_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::asciiString));
}

TEST_F(TypeInfoTest_1112, TypeSize_UnsignedShort_1112) {
    EXPECT_EQ(2u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedShort));
}

TEST_F(TypeInfoTest_1112, TypeSize_UnsignedLong_1112) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedLong));
}

TEST_F(TypeInfoTest_1112, TypeSize_UnsignedRational_1112) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::unsignedRational));
}

TEST_F(TypeInfoTest_1112, TypeSize_SignedByte_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::signedByte));
}

TEST_F(TypeInfoTest_1112, TypeSize_Undefined_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::undefined));
}

TEST_F(TypeInfoTest_1112, TypeSize_SignedShort_1112) {
    EXPECT_EQ(2u, Exiv2::TypeInfo::typeSize(Exiv2::signedShort));
}

TEST_F(TypeInfoTest_1112, TypeSize_SignedLong_1112) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::signedLong));
}

TEST_F(TypeInfoTest_1112, TypeSize_SignedRational_1112) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::signedRational));
}

TEST_F(TypeInfoTest_1112, TypeSize_TiffFloat_1112) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::tiffFloat));
}

TEST_F(TypeInfoTest_1112, TypeSize_TiffDouble_1112) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::tiffDouble));
}

TEST_F(TypeInfoTest_1112, TypeSize_TiffIfd_1112) {
    EXPECT_EQ(4u, Exiv2::TypeInfo::typeSize(Exiv2::tiffIfd));
}

TEST_F(TypeInfoTest_1112, TypeSize_String_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::string));
}

TEST_F(TypeInfoTest_1112, TypeSize_Date_1112) {
    EXPECT_EQ(8u, Exiv2::TypeInfo::typeSize(Exiv2::date));
}

TEST_F(TypeInfoTest_1112, TypeSize_Time_1112) {
    EXPECT_EQ(11u, Exiv2::TypeInfo::typeSize(Exiv2::time));
}

TEST_F(TypeInfoTest_1112, TypeSize_Comment_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::comment));
}

TEST_F(TypeInfoTest_1112, TypeSize_Directory_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::directory));
}

TEST_F(TypeInfoTest_1112, TypeSize_XmpText_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpText));
}

TEST_F(TypeInfoTest_1112, TypeSize_XmpAlt_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpAlt));
}

TEST_F(TypeInfoTest_1112, TypeSize_XmpBag_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpBag));
}

TEST_F(TypeInfoTest_1112, TypeSize_XmpSeq_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::xmpSeq));
}

TEST_F(TypeInfoTest_1112, TypeSize_LangAlt_1112) {
    EXPECT_EQ(1u, Exiv2::TypeInfo::typeSize(Exiv2::langAlt));
}

TEST_F(TypeInfoTest_1112, TypeSize_UnknownTypeId_ReturnsZero_1112) {
    EXPECT_EQ(0u, Exiv2::TypeInfo::typeSize(static_cast<Exiv2::TypeId>(9999)));
}

// ==================== Round-trip tests ====================

TEST_F(TypeInfoTest_1112, RoundTrip_TypeNameToTypeId_1112) {
    // For each known type, converting name->id->name should yield the same name
    const char* name = Exiv2::TypeInfo::typeName(Exiv2::unsignedByte);
    ASSERT_NE(nullptr, name);
    Exiv2::TypeId id = Exiv2::TypeInfo::typeId(name);
    EXPECT_EQ(Exiv2::unsignedByte, id);
}

TEST_F(TypeInfoTest_1112, RoundTrip_AllTypes_1112) {
    Exiv2::TypeId allTypes[] = {
        Exiv2::invalidTypeId, Exiv2::unsignedByte, Exiv2::asciiString,
        Exiv2::unsignedShort, Exiv2::unsignedLong, Exiv2::unsignedRational,
        Exiv2::signedByte, Exiv2::undefined, Exiv2::signedShort,
        Exiv2::signedLong, Exiv2::signedRational, Exiv2::tiffFloat,
        Exiv2::tiffDouble, Exiv2::tiffIfd, Exiv2::string,
        Exiv2::date, Exiv2::time, Exiv2::comment,
        Exiv2::directory, Exiv2::xmpText, Exiv2::xmpAlt,
        Exiv2::xmpBag, Exiv2::xmpSeq, Exiv2::langAlt
    };

    for (auto typeId : allTypes) {
        const char* name = Exiv2::TypeInfo::typeName(typeId);
        ASSERT_NE(nullptr, name) << "typeName returned nullptr for typeId=" << typeId;
        Exiv2::TypeId resolvedId = Exiv2::TypeInfo::typeId(name);
        EXPECT_EQ(typeId, resolvedId) << "Round-trip failed for typeId=" << typeId << " name=" << name;
    }
}

}  // namespace
