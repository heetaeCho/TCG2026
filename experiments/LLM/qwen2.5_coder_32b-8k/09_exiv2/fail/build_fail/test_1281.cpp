#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

#include <exiv2/properties.hpp>



using namespace Exiv2;



class XmpdatumTest_1281 : public ::testing::Test {

protected:

    std::unique_ptr<XmpKey> key;

    std::unique_ptr<Value> value;

    std::unique_ptr<Xmpdatum> xmpDatum;



    void SetUp() override {

        key = std::make_unique<XmpKey>("Xmp.dc.creator", "creator");

        value = std::make_unique<StringValue>(std::string("John Doe"));

        xmpDatum = std::make_unique<Xmpdatum>(*key, value.get());

    }

};



TEST_F(XmpdatumTest_1281, GroupName_ReturnsExpectedString_1281) {

    EXPECT_EQ(xmpDatum->groupName(), "dc");

}



TEST_F(XmpdatumTest_1281, GroupName_EmptyKey_ReturnsEmptyString_1281) {

    XmpKey emptyKey("");

    xmpDatum = std::make_unique<Xmpdatum>(emptyKey, value.get());

    EXPECT_EQ(xmpDatum->groupName(), "");

}



TEST_F(XmpdatumTest_1281, GroupName_PrefixOnly_ReturnsEmptyString_1281) {

    XmpKey prefixOnlyKey("Xmp.dc", "");

    xmpDatum = std::make_unique<Xmpdatum>(prefixOnlyKey, value.get());

    EXPECT_EQ(xmpDatum->groupName(), "dc");

}
