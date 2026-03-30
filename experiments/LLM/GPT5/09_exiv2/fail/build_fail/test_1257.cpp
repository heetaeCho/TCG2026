#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "exiv2/properties.hpp" // Assuming this is the header where XmpProperties is defined

namespace Exiv2 {
    class MockXmpProperties : public XmpProperties {
    public:
        MOCK_METHOD(const XmpPropertyInfo*, propertyList, (const std::string& prefix), (override));
        MOCK_METHOD(std::ostream&, printProperty, (std::ostream& os, const std::string& key, const Value& value), (override));
    };
}

using ::testing::_;
using ::testing::Invoke;

class XmpPropertiesTest : public ::testing::Test {
protected:
    Exiv2::MockXmpProperties mockXmpProperties;
};

TEST_F(XmpPropertiesTest, TestPrintPropertiesWithValidPrefix) {
    const std::string prefix = "validPrefix";
    std::stringstream ss;

    // Mocking the propertyList to return a valid XmpPropertyInfo array when called with a valid prefix.
    XmpPropertyInfo propInfo;
    propInfo.xmpValueType_ = "string";
    propInfo.xmpCategory_ = XmpCategory::String;
    EXPECT_CALL(mockXmpProperties, propertyList(prefix))
        .WillOnce(Invoke([&](const std::string& prefix) -> const XmpPropertyInfo* {
            return &propInfo;
        }));

    // Call printProperties
    mockXmpProperties.printProperties(ss, prefix);

    // Verify that the output stream contains the expected output
    EXPECT_THAT(ss.str(), testing::HasSubstr("string"));
}

TEST_F(XmpPropertiesTest, TestPrintPropertiesWithInvalidPrefix) {
    const std::string prefix = "invalidPrefix";
    std::stringstream ss;

    // Mocking the propertyList to return nullptr when called with an invalid prefix
    EXPECT_CALL(mockXmpProperties, propertyList(prefix))
        .WillOnce(Invoke([&](const std::string& prefix) -> const XmpPropertyInfo* {
            return nullptr;
        }));

    // Call printProperties and ensure no output is generated for an invalid prefix
    mockXmpProperties.printProperties(ss, prefix);
    EXPECT_EQ(ss.str(), "");
}

TEST_F(XmpPropertiesTest, TestPrintProperty) {
    const std::string key = "propertyKey";
    Value value; // Assume Value is a type compatible with printProperty
    std::stringstream ss;

    // Set up the mock to ensure the printProperty method is called with the expected parameters
    EXPECT_CALL(mockXmpProperties, printProperty(_, key, value))
        .WillOnce(Invoke([&](std::ostream& os, const std::string& key, const Value& value) -> std::ostream& {
            os << key << ": " << value; // Mocking the expected output format
            return os;
        }));

    // Call the printProperty function and check the output
    mockXmpProperties.printProperty(ss, key, value);
    EXPECT_EQ(ss.str(), key + ": " + std::to_string(value));
}

TEST_F(XmpPropertiesTest, TestPropertyListReturnsNull) {
    const std::string prefix = "emptyPrefix";
    std::stringstream ss;

    // Mocking propertyList to return nullptr for an empty or invalid prefix
    EXPECT_CALL(mockXmpProperties, propertyList(prefix))
        .WillOnce(Invoke([&](const std::string& prefix) -> const XmpPropertyInfo* {
            return nullptr;
        }));

    // Call printProperties and ensure nothing is printed
    mockXmpProperties.printProperties(ss, prefix);
    EXPECT_EQ(ss.str(), "");
}

TEST_F(XmpPropertiesTest, TestPrintPropertiesBoundary) {
    const std::string prefix = "boundaryPrefix";
    std::stringstream ss;

    // Simulate the behavior for the boundary condition
    XmpPropertyInfo propInfo;
    propInfo.xmpValueType_ = "boundaryString";
    propInfo.xmpCategory_ = XmpCategory::String;

    EXPECT_CALL(mockXmpProperties, propertyList(prefix))
        .WillOnce(Invoke([&](const std::string& prefix) -> const XmpPropertyInfo* {
            return &propInfo;
        }));

    // Call printProperties for the boundary case
    mockXmpProperties.printProperties(ss, prefix);
    EXPECT_THAT(ss.str(), testing::HasSubstr("boundaryString"));
}