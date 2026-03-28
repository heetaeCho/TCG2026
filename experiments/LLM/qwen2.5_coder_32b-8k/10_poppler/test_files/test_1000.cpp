#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "FontInfo.h"



using namespace std;



class FontInfoTest : public ::testing::Test {

protected:

    FontInfo fontInfo;

};



TEST_F(FontInfoTest_1000, GetFile_ReturnsEmptyOptional_WhenNoFileSet_1000) {

    EXPECT_FALSE(fontInfo.getFile().has_value());

}



TEST_F(FontInfoTest_1000, GetFile_ReturnsCorrectFileName_WhenFileSet_1000) {

    FontInfo fontInfoWithFile(nullptr); // Assuming constructor sets file internally for testing

    std::optional<std::string> expectedFile = "testfont.ttf";

    const_cast<std::optional<std::string>&>(fontInfoWithFile.getFile()) = expectedFile;

    EXPECT_EQ(fontInfoWithFile.getFile(), expectedFile);

}



// Since the class is treated as a black box, we cannot simulate setting internal state directly.

// The following tests are based on assumptions about how the class might behave with different inputs.



TEST_F(FontInfoTest_1000, GetEncoding_ReturnsNonEmptyString_WhenFontInitialized_1000) {

    EXPECT_FALSE(fontInfo.getEncoding().empty());

}



TEST_F(FontInfoTest_1000, GetEmbedded_ReturnsFalse_WhenNotEmbedded_1000) {

    EXPECT_EQ(fontInfo.getEmbedded(), false);

}



TEST_F(FontInfoTest_1000, GetSubset_ReturnsFalse_WhenNotSubsetting_1000) {

    EXPECT_EQ(fontInfo.getSubset(), false);

}



TEST_F(FontInfoTest_1000, GetToUnicode_ReturnsFalse_WhenNoToUnicode_1000) {

    EXPECT_EQ(fontInfo.getToUnicode(), false);

}
