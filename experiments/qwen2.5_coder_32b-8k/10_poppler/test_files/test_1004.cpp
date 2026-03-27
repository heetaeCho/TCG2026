#include <gtest/gtest.h>

#include "FontInfo.h"



class FontInfoTest : public ::testing::Test {

protected:

    std::optional<std::string> name = "SampleName";

    std::optional<std::string> substituteName = "SubstituteName";

    std::optional<std::string> file = "SampleFile.ttf";

    std::string encoding = "UTF-8";

    bool emb = true;

    bool subset = false; // This will be toggled in tests

    bool hasToUnicode = true;

    Ref fontRef {1, 0};

    Ref embRef {2, 0};



    FontInfo* fontInfo;



    void SetUp() override {

        // Mock GfxFont and XRef objects for the constructor if needed.

        // Since we are treating this as a black box, we assume these are correctly initialized elsewhere.

        fontInfo = new FontInfo(nullptr, nullptr); // Assuming a default constructor or valid mock objects can be passed

    }



    void TearDown() override {

        delete fontInfo;

    }

};



TEST_F(FontInfoTest_1004, GetSubset_ReturnsTrue_1004) {

    fontInfo->subset = true;  // Directly setting subset to test the return value

    EXPECT_TRUE(fontInfo->getSubset());

}



TEST_F(FontInfoTest_1004, GetSubset_ReturnsFalse_1004) {

    fontInfo->subset = false; // Directly setting subset to test the return value

    EXPECT_FALSE(fontInfo->getSubset());

}



// Additional tests can be added based on other public methods and their expected behaviors.

```


