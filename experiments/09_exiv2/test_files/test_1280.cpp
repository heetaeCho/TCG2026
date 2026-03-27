#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpdatumTest_1280 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a sample XmpKey and Value for use in tests

        xmpKey = std::make_unique<XmpKey>("Xmp.dc.title");

        value = std::make_unique<Value>(Value::asciiString, "Sample Title");

        xmpdatum = std::make_unique<Xmpdatum>(*xmpKey, value.get());

    }



    void TearDown() override {

        // Clean up resources

        xmpdatum.reset();

        value.reset();

        xmpKey.reset();

    }



    std::unique_ptr<XmpKey> xmpKey;

    std::unique_ptr<Value> value;

    std::unique_ptr<Xmpdatum> xmpdatum;

};



TEST_F(XmpdatumTest_1280, FamilyName_ReturnsCorrectValue_1280) {

    const char* expectedFamilyName = "Xmp.dc";

    EXPECT_STREQ(xmpdatum->familyName(), expectedFamilyName);

}



TEST_F(XmpdatumTest_1280, FamilyName_ReturnsEmptyStringForNullKey_1280) {

    Xmpdatum nullXmpdatum(XmpKey(""), nullptr);

    EXPECT_STREQ(nullXmpdatum.familyName(), "");

}



// Additional tests can be added to cover other functions and scenarios as needed



```


