#include <gtest/gtest.h>

#include "XMPIterator.hpp"



class XMPIteratorTest_2100 : public ::testing::Test {

protected:

    IterInfo info;

};



TEST_F(XMPIteratorTest_2100, SetCurrSchema_NormalOperation_2100) {

    XMP_StringPtr schemaName = "http://example.com/schema";

    SetCurrSchema(info, schemaName);

    EXPECT_EQ(info.currSchema, schemaName);

}



TEST_F(XMPIteratorTest_2100, SetCurrSchema_EmptyString_2100) {

    XMP_StringPtr schemaName = "";

    SetCurrSchema(info, schemaName);

    EXPECT_EQ(info.currSchema, "");

}



TEST_F(XMPIteratorTest_2100, SetCurrSchema_NullPointer_2100) {

    XMP_StringPtr schemaName = nullptr;

    SetCurrSchema(info, schemaName);

    EXPECT_EQ(info.currSchema, "");

}
