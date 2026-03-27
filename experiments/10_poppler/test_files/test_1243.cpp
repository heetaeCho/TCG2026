#include <gtest/gtest.h>

#include "TestProjects/poppler/qt6/src/poppler-private.h"

#include "TestProjects/poppler/Error.h"



namespace {



using namespace Poppler;



class ErrorStringConversionTest_1243 : public ::testing::Test {

protected:

    ErrorStringConversionTest_1243() {}

    virtual ~ErrorStringConversionTest_1243() {}

};



TEST_F(ErrorStringConversionTest_1243, NormalOperation_1243) {

    ::ErrorString input;

    input.text = "Sample error message";

    input.type = static_cast<::ErrorStringType>(1);



    ErrorString result = fromPopplerCore(input);



    EXPECT_EQ(result.data.toStdString(), "Sample error message");

}



TEST_F(ErrorStringConversionTest_1243, EmptyText_1243) {

    ::ErrorString input;

    input.text = "";

    input.type = static_cast<::ErrorStringType>(2);



    ErrorString result = fromPopplerCore(input);



    EXPECT_EQ(result.data.toStdString(), "");

}



TEST_F(ErrorStringConversionTest_1243, LargeText_1243) {

    std::string largeText(1024 * 1024, 'A'); // 1MB of 'A's

    ::ErrorString input;

    input.text = largeText;

    input.type = static_cast<::ErrorStringType>(3);



    ErrorString result = fromPopplerCore(input);



    EXPECT_EQ(result.data.toStdString(), largeText);

}



} // namespace
