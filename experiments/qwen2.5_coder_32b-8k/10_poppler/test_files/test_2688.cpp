#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/pdftocairo.cc"

#include "TestProjects/poppler/goo/GooString.h"



using ::testing::HasSubstr;



// Mock GooString for testing purposes if needed

class MockGooString : public GooString {

public:

    MOCK_METHOD(const std::string &, toStr, (), (const, override));

};



TEST(parseAntialiasOptionTest_2688, ValidOption_ReturnsTrue_2688) {

    // Arrange

    antialias = "valid_option";

    const AntialiasOption antialiasOptions[] = {{"valid_option", 1}, {nullptr, 0}};

    

    // Act

    bool result = parseAntialiasOption();

    

    // Assert

    EXPECT_TRUE(result);

}



TEST(parseAntialiasOptionTest_2688, InvalidOption_ReturnsFalseAndPrintsError_2688) {

    // Arrange

    antialias = "invalid_option";

    const AntialiasOption antialiasOptions[] = {{"valid_option", 1}, {nullptr, 0}};

    

    // Redirect stderr to capture the error message

    std::stringstream buffer;

    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    

    // Act

    bool result = parseAntialiasOption();

    

    // Restore stderr

    std::cerr.rdbuf(old);

    

    // Assert

    EXPECT_FALSE(result);

    EXPECT_THAT(buffer.str(), HasSubstr("Error: Invalid antialias option \"invalid_option\""));

}



TEST(parseAntialiasOptionTest_2688, BoundaryCondition_EmptyString_ReturnsFalseAndPrintsError_2688) {

    // Arrange

    antialias = "";

    const AntialiasOption antialiasOptions[] = {{"valid_option", 1}, {nullptr, 0}};

    

    // Redirect stderr to capture the error message

    std::stringstream buffer;

    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    

    // Act

    bool result = parseAntialiasOption();

    

    // Restore stderr

    std::cerr.rdbuf(old);

    

    // Assert

    EXPECT_FALSE(result);

    EXPECT_THAT(buffer.str(), HasSubstr("Error: Invalid antialias option \"\""));

}



TEST(parseAntialiasOptionTest_2688, BoundaryCondition_Nullptr_ReturnsFalseAndPrintsError_2688) {

    // Arrange

    antialias = nullptr;

    const AntialiasOption antialiasOptions[] = {{"valid_option", 1}, {nullptr, 0}};

    

    // Redirect stderr to capture the error message

    std::stringstream buffer;

    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    

    // Act

    bool result = parseAntialiasOption();

    

    // Restore stderr

    std::cerr.rdbuf(old);

    

    // Assert

    EXPECT_FALSE(result);

    EXPECT_THAT(buffer.str(), HasSubstr("Error: Invalid antialias option \"\""));

}



TEST(parseAntialiasOptionTest_2688, MultipleValidOptions_ReturnsTrueForMatchedOption_2688) {

    // Arrange

    antialias = "option_two";

    const AntialiasOption antialiasOptions[] = {{"option_one", 1}, {"option_two", 2}, {nullptr, 0}};

    

    // Act

    bool result = parseAntialiasOption();

    

    // Assert

    EXPECT_TRUE(result);

}



TEST(parseAntialiasOptionTest_2688, CaseInsensitiveComparison_ReturnsTrueForMatchedOption_2688) {

    // Arrange

    antialias = "VALID_OPTION";

    const AntialiasOption antialiasOptions[] = {{"valid_option", 1}, {nullptr, 0}};

    

    // Act

    bool result = parseAntialiasOption();

    

    // Assert

    EXPECT_TRUE(result);

}
