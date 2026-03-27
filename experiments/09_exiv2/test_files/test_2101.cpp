#include <gtest/gtest.h>

#include "XMPIterator.hpp"



using namespace XMP_NAMESPACE;



class XMPIteratorTest_2101 : public ::testing::Test {

protected:

    IterInfo info;

    XMP_VarString schemaName;



    void SetUp() override {

        schemaName = "http://example.com/schema";

    }

};



TEST_F(XMPIteratorTest_2101, SetCurrSchema_SetsCorrectSchema_2101) {

    SetCurrSchema(info, schemaName);

    EXPECT_EQ(info.currSchema, schemaName);

}



TEST_F(XMPIteratorTest_2101, SetCurrSchema_EmptySchemaName_2101) {

    XMP_VarString emptySchema;

    SetCurrSchema(info, emptySchema);

    EXPECT_TRUE(info.currSchema.empty());

}



TEST_F(XMPIteratorTest_2101, SetCurrSchema_LongSchemaName_2101) {

    XMP_VarString longSchema("http://this.is.a.very.long.schema.name/that/should/still/work/correctly");

    SetCurrSchema(info, longSchema);

    EXPECT_EQ(info.currSchema, longSchema);

}
