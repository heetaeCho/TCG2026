#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpKeyTest_1265 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed

    }



    void TearDown() override {

        // Cleanup can be done here if needed

    }

};



TEST_F(XmpKeyTest_1265, TagLabel_ReturnsTagNameIfPropertyTitleIsNull_1265) {

    XmpKey key("prefix", "property");

    EXPECT_CALL(*key.p_, tagName()).WillOnce(::testing::Return("defaultTag"));

    const char* expected = "defaultTag";

    EXPECT_STREQ(key.tagLabel().c_str(), expected);

}



TEST_F(XmpKeyTest_1265, TagLabel_ReturnsPropertyTitleIfNotNull_1265) {

    XmpKey key("prefix", "property");

    EXPECT_CALL(*key.p_, tagName()).WillOnce(::testing::Return("defaultTag"));

    const char* expected = "actualTitle";

    EXPECT_CALL(XmpProperties::propertyTitle(key)).WillOnce(::testing::Return(expected));

    EXPECT_STREQ(key.tagLabel().c_str(), expected);

}



TEST_F(XmpKeyTest_1265, TagLabel_HandlesEmptyPrefixAndProperty_1265) {

    XmpKey key("", "");

    EXPECT_CALL(*key.p_, tagName()).WillOnce(::testing::Return("defaultTag"));

    const char* expected = "defaultTag";

    EXPECT_STREQ(key.tagLabel().c_str(), expected);

}



TEST_F(XmpKeyTest_1265, TagLabel_HandlesOnlyPrefix_1265) {

    XmpKey key("prefix", "");

    EXPECT_CALL(*key.p_, tagName()).WillOnce(::testing::Return("defaultTag"));

    const char* expected = "defaultTag";

    EXPECT_STREQ(key.tagLabel().c_str(), expected);

}



TEST_F(XmpKeyTest_1265, TagLabel_HandlesOnlyProperty_1265) {

    XmpKey key("", "property");

    EXPECT_CALL(*key.p_, tagName()).WillOnce(::testing::Return("defaultTag"));

    const char* expected = "defaultTag";

    EXPECT_STREQ(key.tagLabel().c_str(), expected);

}

```


