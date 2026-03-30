#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;



class MockBoundValueRef : public Detail::BoundValueRefBase {

public:

    MOCK_METHOD(ParserResult, setValue, (const std::string &arg), (override));

};



TEST_F(ExeNameTest_667, SetWithNormalPath_ReturnsMatched_667) {

    ExeName exeName;

    auto result = exeName.set("/path/to/executable");

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(ExeNameTest_667, SetWithFileName_ReturnsMatched_667) {

    ExeName exeName;

    auto result = exeName.set("executable");

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(ExeNameTest_667, SetWithEmptyString_ReturnsMatchedAndDefaultName_667) {

    ExeName exeName;

    auto result = exeName.set("");

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_EQ(exeName.name(), "<executable>");

}



TEST_F(ExeNameTest_667, SetWithTrailingSlash_ReturnsMatchedAndDefaultName_667) {

    ExeName exeName;

    auto result = exeName.set("/path/to/");

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_EQ(exeName.name(), "");

}



TEST_F(ExeNameTest_667, SetWithMultipleSlashes_ReturnsMatchedAndFileName_667) {

    ExeName exeName;

    auto result = exeName.set("/path///to/executable");

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_EQ(exeName.name(), "executable");

}



TEST_F(ExeNameTest_667, SetWithBoundValueRef_ReturnsMatchedAndCallsSetValue_667) {

    std::string ref;

    ExeName exeName(ref);



    auto mockBoundValueRef = std::make_shared<MockBoundValueRef>();

    exeName.m_ref = mockBoundValueRef;



    EXPECT_CALL(*mockBoundValueRef, setValue("executable"))

        .WillOnce(testing::Return(ParserResult::ok()));



    auto result = exeName.set("/path/to/executable");

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(ExeNameTest_667, SetWithBoundValueRefAndEmptyString_ReturnsMatchedAndCallsSetValueWithDefaultName_667) {

    std::string ref;

    ExeName exeName(ref);



    auto mockBoundValueRef = std::make_shared<MockBoundValueRef>();

    exeName.m_ref = mockBoundValueRef;



    EXPECT_CALL(*mockBoundValueRef, setValue("<executable>"))

        .WillOnce(testing::Return(ParserResult::ok()));



    auto result = exeName.set("");

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}
