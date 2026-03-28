#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Dict.h"
#include "Annot.h"

// Mock class for Dict to be used in testing
class MockDict : public Dict {
public:
    MOCK_METHOD(Object, lookup, (std::string_view key, int recursion), (const, override));
};

// Test suite for the parseAnnotExternalData function
class AnnotTest_2017 : public ::testing::Test {
protected:
    void SetUp() override {
        // Any necessary setup
    }

    void TearDown() override {
        // Any necessary cleanup
    }
};

// TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkup3D_WhenSubtypeIsMarkup3D_2017)
TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkup3D_WhenSubtypeIsMarkup3D_2017) {
    // Arrange
    MockDict dict;
    Object obj1 = Object("Subtype");
    EXPECT_CALL(dict, lookup("Subtype", 0)).WillOnce(testing::Return(obj1));
    
    // Setup the mock to return "Markup3D"
    obj1 = Object("Markup3D");
    
    // Act
    AnnotExternalDataType result = parseAnnotExternalData(&dict);
    
    // Assert
    EXPECT_EQ(result, annotExternalDataMarkup3D);
}

// TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkupUnknown_WhenSubtypeIsUnknown_2017)
TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkupUnknown_WhenSubtypeIsUnknown_2017) {
    // Arrange
    MockDict dict;
    Object obj1 = Object("Subtype");
    EXPECT_CALL(dict, lookup("Subtype", 0)).WillOnce(testing::Return(obj1));
    
    // Setup the mock to return a value other than "Markup3D"
    obj1 = Object("UnknownType");
    
    // Act
    AnnotExternalDataType result = parseAnnotExternalData(&dict);
    
    // Assert
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkupUnknown_WhenNoSubtype_2017)
TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkupUnknown_WhenNoSubtype_2017) {
    // Arrange
    MockDict dict;
    Object obj1 = Object();
    
    // Simulate the lookup returning no value for the "Subtype" key
    EXPECT_CALL(dict, lookup("Subtype", 0)).WillOnce(testing::Return(obj1));
    
    // Act
    AnnotExternalDataType result = parseAnnotExternalData(&dict);
    
    // Assert
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkupUnknown_WhenInvalidSubtype_2017)
TEST_F(AnnotTest_2017, parseAnnotExternalData_ReturnsMarkupUnknown_WhenInvalidSubtype_2017) {
    // Arrange
    MockDict dict;
    Object obj1 = Object("Subtype");
    EXPECT_CALL(dict, lookup("Subtype", 0)).WillOnce(testing::Return(obj1));
    
    // Setup the mock to return an invalid subtype
    obj1 = Object("InvalidSubtype");
    
    // Act
    AnnotExternalDataType result = parseAnnotExternalData(&dict);
    
    // Assert
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}

// TEST_F(AnnotTest_2017, parseAnnotExternalData_HandlesNullInput_2017)
TEST_F(AnnotTest_2017, parseAnnotExternalData_HandlesNullInput_2017) {
    // Act
    AnnotExternalDataType result = parseAnnotExternalData(nullptr);
    
    // Assert
    EXPECT_EQ(result, annotExternalDataMarkupUnknown);
}