#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/datasets.hpp"



namespace {



using namespace Exiv2;



class IptcdatumTest : public ::testing::Test {

protected:

    IptcKey key;

    Iptcdatum iptcDatum;



    IptcdatumTest() 

        : key("IPTC.Test.Key"), iptcDatum(key, nullptr) {}

};



TEST_F(IptcdatumTest_665, KeyReturnsCorrectValue_665) {

    EXPECT_EQ(iptcDatum.key(), "IPTC.Test.Key");

}



TEST_F(IptcdatumTest_665, RecordNameBoundaryCondition_665) {

    EXPECT_FALSE(iptcDatum.recordName().empty());

}



TEST_F(IptcdatumTest_665, RecordBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.record(), 0);

}



TEST_F(IptcdatumTest_665, FamilyNameBoundaryCondition_665) {

    EXPECT_FALSE(iptcDatum.familyName() == nullptr);

}



TEST_F(IptcdatumTest_665, GroupNameBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.groupName(), "");

}



TEST_F(IptcdatumTest_665, TagNameBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.tagName(), "");

}



TEST_F(IptcdatumTest_665, TagLabelBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.tagLabel(), "");

}



TEST_F(IptcdatumTest_665, TagDescBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.tagDesc(), "");

}



TEST_F(IptcdatumTest_665, TagBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.tag(), 0);

}



TEST_F(IptcdatumTest_665, TypeIdBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.typeId(), undefined);

}



TEST_F(IptcdatumTest_665, TypeNameBoundaryCondition_665) {

    EXPECT_FALSE(iptcDatum.typeName() == nullptr);

}



TEST_F(IptcdatumTest_665, TypeSizeBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.typeSize(), 0);

}



TEST_F(IptcdatumTest_665, CountBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.count(), 0);

}



TEST_F(IptcdatumTest_665, SizeBoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.size(), 0);

}



TEST_F(IptcdatumTest_665, ToStringBoundaryCondition_665) {

    EXPECT_FALSE(iptcDatum.toString().empty());

}



TEST_F(IptcdatumTest_665, ToInt64BoundaryCondition_665) {

    EXPECT_EQ(iptcDatum.toInt64(0), 0);

}



TEST_F(IptcdatumTest_665, ToFloatBoundaryCondition_665) {

    EXPECT_FLOAT_EQ(iptcDatum.toFloat(0), 0.0f);

}



TEST_F(IptcdatumTest_665, ToRationalBoundaryCondition_665) {

    Rational rational = iptcDatum.toRational(0);

    EXPECT_EQ(rational.first, 0);

    EXPECT_EQ(rational.second, 1);

}



TEST_F(IptcdatumTest_665, GetValueBoundaryCondition_665) {

    EXPECT_FALSE(iptcDatum.getValue() == nullptr);

}



TEST_F(IptcdatumTest_665, ValueBoundaryCondition_665) {

    const Value& value = iptcDatum.value();

    EXPECT_EQ(value.count(), 0);

}



TEST_F(IptcdatumTest_665, CopyBoundaryCondition_665) {

    byte buffer[1];

    ByteOrder byteOrder = littleEndian;

    EXPECT_EQ(iptcDatum.copy(buffer, byteOrder), 0);

}



TEST_F(IptcdatumTest_665, WriteBoundaryCondition_665) {

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    iptcDatum.write(os, pMetadata);

    EXPECT_FALSE(os.str().empty());

}



} // namespace
