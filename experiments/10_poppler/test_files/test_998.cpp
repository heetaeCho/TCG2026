#include <gtest/gtest.h>

#include "FontInfo.h"



class FontInfoTest_998 : public ::testing::Test {

protected:

    FontInfo fontInfoWithoutName;

    FontInfo fontInfoWithName;



    FontInfoTest_998() : fontInfoWithoutName(nullptr, nullptr) {

        // Initialize a FontInfo object without a name for testing

    }



    virtual void SetUp() override {

        // Initialize a FontInfo object with a name for testing

        fontInfoWithName = FontInfo(nullptr, nullptr); // Assuming constructor initializes with empty or default values

        const_cast<std::optional<std::string>&>(fontInfoWithName.getName()) = "TestFontName";

    }

};



TEST_F(FontInfoTest_998, GetName_ReturnsEmptyOptional_WhenNameNotSet_998) {

    EXPECT_FALSE(fontInfoWithoutName.getName().has_value());

}



TEST_F(FontInfoTest_998, GetName_ReturnsCorrectName_WhenNameIsSet_998) {

    EXPECT_TRUE(fontInfoWithName.getName().has_value());

    EXPECT_EQ(*fontInfoWithName.getName(), "TestFontName");

}



// Additional tests for other observable behaviors can be added here following the same pattern
