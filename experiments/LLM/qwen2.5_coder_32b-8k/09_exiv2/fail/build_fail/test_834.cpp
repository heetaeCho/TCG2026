#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class XmpTextValueTest_834 : public ::testing::Test {

protected:

    XmpTextValue xmpTextValue;

};



TEST_F(XmpTextValueTest_834, ReadValidAltType_834) {

    std::string input = "type=\"Alt\" Some text";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaAlt);

}



TEST_F(XmpTextValueTest_834, ReadValidBagType_834) {

    std::string input = "type=\"Bag\" Some text";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaBag);

}



TEST_F(XmpTextValueTest_834, ReadValidSeqType_834) {

    std::string input = "type=\"Seq\" Some text";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaSeq);

}



TEST_F(XmpTextValueTest_834, ReadValidStructType_834) {

    std::string input = "type=\"Struct\" Some text";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaNone); // Struct does not set xmpArrayType

}



TEST_F(XmpTextValueTest_834, ReadInvalidType_834) {

    std::string input = "type=\"Invalid\" Some text";

    EXPECT_THROW(xmpTextValue.read(input), Exiv2::Error);

}



TEST_F(XmpTextValueTest_834, ReadWithoutType_834) {

    std::string input = "Some text without type";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaNone);

}



TEST_F(XmpTextValueTest_834, ReadEmptyBuffer_834) {

    std::string input = "";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaNone);

}



TEST_F(XmpTextValueTest_834, ReadOnlyTypeNoSpace_834) {

    std::string input = "type=\"Alt\"";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaAlt);

}



TEST_F(XmpTextValueTest_834, ReadOnlyTypeNoQuotes_834) {

    std::string input = "type=Alt";

    EXPECT_EQ(xmpTextValue.read(input), 0);

    EXPECT_EQ(xmpTextValue.xmpArrayType(), XmpArrayType::xaAlt);

}



TEST_F(XmpTextValueTest_834, ReadEmptyTypeWithQuotes_834) {

    std::string input = "type=\"\"";

    EXPECT_THROW(xmpTextValue.read(input), Exiv2::Error);

}
