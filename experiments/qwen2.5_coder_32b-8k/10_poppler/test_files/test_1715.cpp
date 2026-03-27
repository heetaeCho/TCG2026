#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "StructElement.h"

#include "MarkedContentOutputDev.h"



using namespace testing;



class StructElementTest : public ::testing::Test {

protected:

    Mock<MarkedContentOutputDev> mock_mcdev;

    StrictMock<decltype(mock_mcdev)> mcdev;

    std::unique_ptr<StructElement> struct_element;



    void SetUp() override {

        // Assuming there is a way to create a valid StructElement instance

        // This setup might need adjustments based on actual implementation details

        struct_element = std::make_unique<StructElement>(123, nullptr, nullptr);

    }

};



TEST_F(StructElementTest_1715, GetTextSpans_EmptyWhenNotContent_1715) {

    EXPECT_CALL(mcdev, getTextSpans()).Times(0);  // Ensure getTextSpansInternal is not called

    ON_CALL(*struct_element, isContent()).WillByDefault(Return(false));



    TextSpanArray result = struct_element->getTextSpans();

    EXPECT_TRUE(result.empty());

}



TEST_F(StructElementTest_1715, GetTextSpans_CallsGetTextSpansInternalWhenContent_1715) {

    TextSpanArray expected_spans;

    // Assuming getTextSpans() returns a non-empty array when content is true

    ON_CALL(*struct_element, isContent()).WillByDefault(Return(true));

    EXPECT_CALL(mcdev, getTextSpans()).WillOnce(Return(expected_spans));



    TextSpanArray result = struct_element->getTextSpans();

    EXPECT_EQ(result, expected_spans);

}



TEST_F(StructElementTest_1715, GetTextSpans_ReturnsNonEmptyWhenContentAndHasSpans_1715) {

    TextSpanArray expected_spans;  // Populate with expected spans

    ON_CALL(*struct_element, isContent()).WillByDefault(Return(true));

    EXPECT_CALL(mcdev, getTextSpans()).WillOnce(Return(expected_spans));



    TextSpanArray result = struct_element->getTextSpans();

    EXPECT_FALSE(result.empty());

}



TEST_F(StructElementTest_1715, GetTextSpans_ReturnsEmptyWhenContentButNoSpans_1715) {

    TextSpanArray empty_spans;

    ON_CALL(*struct_element, isContent()).WillByDefault(Return(true));

    EXPECT_CALL(mcdev, getTextSpans()).WillOnce(Return(empty_spans));



    TextSpanArray result = struct_element->getTextSpans();

    EXPECT_TRUE(result.empty());

}
