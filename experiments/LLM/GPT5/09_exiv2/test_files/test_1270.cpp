#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "exiv2/properties.hpp"
#include "exiv2/types.hpp"

namespace Exiv2 {

class XmpPropertyInfoTest : public ::testing::Test {
protected:
    XmpPropertyInfoTest() {
        // Set up common properties for the tests if needed
    }

    virtual ~XmpPropertyInfoTest() = default;

    // Test the operator<< functionality for XmpPropertyInfo
    void testPropertyInfoToStream(const XmpPropertyInfo& propertyInfo, const std::string& expectedOutput) {
        std::ostringstream os;
        os << propertyInfo;
        EXPECT_EQ(os.str(), expectedOutput);
    }
};

TEST_F(XmpPropertyInfoTest, XmpPropertyInfoToStream_Normal_1270) {
    // Prepare XmpPropertyInfo object with typical values
    XmpPropertyInfo propertyInfo;
    propertyInfo.name_ = "TestName";
    propertyInfo.title_ = "TestTitle";
    propertyInfo.xmpValueType_ = "String";
    propertyInfo.typeId_ = 1;  // Some valid TypeId (mock or real value)
    propertyInfo.xmpCategory_ = xmpInternal;
    propertyInfo.desc_ = "Test description";

    // Expected output for the operator<< (simplified for the example)
    std::string expectedOutput = "TestName,TestTitle,String,SomeType,Internal,\"Test description\"\n";

    testPropertyInfoToStream(propertyInfo, expectedOutput);
}

TEST_F(XmpPropertyInfoTest, XmpPropertyInfoToStream_EmptyDescription_1271) {
    // Prepare XmpPropertyInfo object with an empty description
    XmpPropertyInfo propertyInfo;
    propertyInfo.name_ = "TestName";
    propertyInfo.title_ = "TestTitle";
    propertyInfo.xmpValueType_ = "String";
    propertyInfo.typeId_ = 1;  // Some valid TypeId (mock or real value)
    propertyInfo.xmpCategory_ = xmpInternal;
    propertyInfo.desc_ = "";

    // Expected output for the operator<< (with empty description)
    std::string expectedOutput = "TestName,TestTitle,String,SomeType,Internal,\"\"\n";

    testPropertyInfoToStream(propertyInfo, expectedOutput);
}

TEST_F(XmpPropertyInfoTest, XmpPropertyInfoToStream_ExternalCategory_1272) {
    // Prepare XmpPropertyInfo object with external category
    XmpPropertyInfo propertyInfo;
    propertyInfo.name_ = "TestName";
    propertyInfo.title_ = "TestTitle";
    propertyInfo.xmpValueType_ = "String";
    propertyInfo.typeId_ = 1;  // Some valid TypeId (mock or real value)
    propertyInfo.xmpCategory_ = xmpExternal;
    propertyInfo.desc_ = "Test description";

    // Expected output for the operator<< (with external category)
    std::string expectedOutput = "TestName,TestTitle,String,SomeType,External,\"Test description\"\n";

    testPropertyInfoToStream(propertyInfo, expectedOutput);
}

TEST_F(XmpPropertyInfoTest, XmpPropertyInfoEqualityOperator_1273) {
    // Prepare XmpPropertyInfo objects for comparison
    XmpPropertyInfo propertyInfo1;
    propertyInfo1.name_ = "TestName";

    XmpPropertyInfo propertyInfo2;
    propertyInfo2.name_ = "TestName";

    XmpPropertyInfo propertyInfo3;
    propertyInfo3.name_ = "OtherName";

    // Check for equality
    EXPECT_TRUE(propertyInfo1 == "TestName");
    EXPECT_FALSE(propertyInfo1 == "OtherName");
}

} // namespace Exiv2