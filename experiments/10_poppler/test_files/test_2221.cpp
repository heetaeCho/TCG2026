#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "FontInfo.h"



// Mocking FontInfo class for testing purposes

class MockFontInfo : public FontInfo {

public:

    MOCK_METHOD0(getName, const std::optional<std::string>&());

    MOCK_METHOD0(getSubset, bool());

};



TEST_F(PopplerFontsIterTest_2221, GetName_ReturnsFullFontNameWhenNotSubsetted_2221) {

    MockFontInfo mockFontInfo;

    EXPECT_CALL(mockFontInfo, getSubset()).WillRepeatedly(testing::Return(false));

    std::optional<std::string> fullName = "MyFont-Regular";

    EXPECT_CALL(mockFontInfo, getName()).WillOnce(testing::Return(fullName));



    PopplerFontsIter iter;

    iter.items[0] = &mockFontInfo;

    iter.index = 0;



    const char* result = poppler_fonts_iter_get_name(&iter);

    ASSERT_STREQ(result, "MyFont-Regular");

}



TEST_F(PopplerFontsIterTest_2221, GetName_ReturnsTrimmedFontNameWhenSubsetted_2221) {

    MockFontInfo mockFontInfo;

    EXPECT_CALL(mockFontInfo, getSubset()).WillRepeatedly(testing::Return(true));

    std::optional<std::string> fullName = "+MyFont-Regular+Sub";

    EXPECT_CALL(mockFontInfo, getName()).WillOnce(testing::Return(fullName));



    PopplerFontsIter iter;

    iter.items[0] = &mockFontInfo;

    iter.index = 0;



    const char* result = poppler_fonts_iter_get_name(&iter);

    ASSERT_STREQ(result, "MyFont-Regular+Sub");

}



TEST_F(PopplerFontsIterTest_2221, GetName_ReturnsEmptyWhenSubsettedAndNoPlusSign_2221) {

    MockFontInfo mockFontInfo;

    EXPECT_CALL(mockFontInfo, getSubset()).WillRepeatedly(testing::Return(true));

    std::optional<std::string> fullName = "MyFont-Regular";

    EXPECT_CALL(mockFontInfo, getName()).WillOnce(testing::Return(fullName));



    PopplerFontsIter iter;

    iter.items[0] = &mockFontInfo;

    iter.index = 0;



    const char* result = poppler_fonts_iter_get_name(&iter);

    ASSERT_STREQ(result, "");

}



TEST_F(PopplerFontsIterTest_2221, GetName_ReturnsEmptyWhenNoNameAvailable_2221) {

    MockFontInfo mockFontInfo;

    EXPECT_CALL(mockFontInfo, getSubset()).WillRepeatedly(testing::Return(false));

    std::optional<std::string> fullName = "";

    EXPECT_CALL(mockFontInfo, getName()).WillOnce(testing::Return(fullName));



    PopplerFontsIter iter;

    iter.items[0] = &mockFontInfo;

    iter.index = 0;



    const char* result = poppler_fonts_iter_get_name(&iter);

    ASSERT_STREQ(result, "");

}



TEST_F(PopplerFontsIterTest_2221, GetName_ReturnsEmptyWhenNameIsNullptr_2221) {

    MockFontInfo mockFontInfo;

    EXPECT_CALL(mockFontInfo, getSubset()).WillRepeatedly(testing::Return(false));

    std::optional<std::string> fullName = std::nullopt;

    EXPECT_CALL(mockFontInfo, getName()).WillOnce(testing::Return(fullName));



    PopplerFontsIter iter;

    iter.items[0] = &mockFontInfo;

    iter.index = 0;



    const char* result = poppler_fonts_iter_get_name(&iter);

    ASSERT_STREQ(result, "");

}
