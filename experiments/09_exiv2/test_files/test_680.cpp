#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;



class IptcdatumTest_680 : public ::testing::Test {

protected:

    IptcdatumTest_680() 

        : key(IptcKey("Iptc.Envelope.ModelVersion")), value(new StringValue) {}



    ~IptcdatumTest_680() override = default;



    void SetUp() override {

        value->setValue("Example");

        iptcdatum = Iptcdatum(key, value.get());

    }



    void TearDown() override {

        // Clean up if necessary

    }



    IptcKey key;

    std::unique_ptr<StringValue> value;

    Iptcdatum iptcdatum;

};



TEST_F(IptcdatumTest_680, ToStringDefault_680) {

    EXPECT_EQ(iptcdatum.toString(), "Example");

}



TEST_F(IptcdatumTest_680, ToStringWithN_680) {

    EXPECT_EQ(iptcdatum.toString(5), "Examp");

}



TEST_F(IptcdatumTest_680, ToStringBoundary_680) {

    EXPECT_EQ(iptcdatum.toString(0), "");

    EXPECT_EQ(iptcdatum.toString(10), "Example");

}



TEST_F(IptcdatumTest_680, ToStringLongString_680) {

    iptcdatum.setValue("ThisIsALongerExampleStringForTestingPurposes");

    EXPECT_EQ(iptcdatum.toString(20), "ThisIsALongerExamp");

}



TEST_F(IptcdatumTest_680, ToStringEmptyValue_680) {

    value->setValue("");

    iptcdatum = Iptcdatum(key, value.get());

    EXPECT_EQ(iptcdatum.toString(), "");

}



TEST_F(IptcdatumTest_680, ToStringNullValue_680) {

    iptcdatum.setValue(nullptr);

    EXPECT_EQ(iptcdatum.toString(), "");

}
