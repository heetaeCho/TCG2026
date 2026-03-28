#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "properties.hpp" // The header file where XmpProperties is defined

namespace Exiv2 {

class MockXmpProperties : public XmpProperties {
public:
    MOCK_METHOD(const XmpNsInfo*, nsInfoUnsafe, (const std::string& prefix), (const, override));
};

}  // namespace Exiv2

// Test fixture for the XmpProperties class
class XmpPropertiesTest : public ::testing::Test {
protected:
    Exiv2::MockXmpProperties mockXmpProperties;
};

// Test for normal operation of nsInfo
TEST_F(XmpPropertiesTest, NsInfo_ReturnsExpectedResult_1255) {
    std::string prefix = "dc";
    Exiv2::XmpNsInfo expectedNsInfo;  // Fill with an appropriate expected value if needed
    EXPECT_CALL(mockXmpProperties, nsInfoUnsafe(prefix))
        .WillOnce(testing::Return(&expectedNsInfo));

    const Exiv2::XmpNsInfo* result = mockXmpProperties.nsInfo(prefix);

    // Check if the result is the expected nsInfo object
    ASSERT_EQ(result, &expectedNsInfo);
}

// Test for boundary condition: Empty prefix
TEST_F(XmpPropertiesTest, NsInfo_EmptyPrefix_1256) {
    std::string emptyPrefix = "";
    Exiv2::XmpNsInfo expectedNsInfo;  // Define expected behavior for empty prefix
    EXPECT_CALL(mockXmpProperties, nsInfoUnsafe(emptyPrefix))
        .WillOnce(testing::Return(&expectedNsInfo));

    const Exiv2::XmpNsInfo* result = mockXmpProperties.nsInfo(emptyPrefix);

    ASSERT_EQ(result, &expectedNsInfo);
}

// Test for boundary condition: Special characters in the prefix
TEST_F(XmpPropertiesTest, NsInfo_SpecialCharacterPrefix_1257) {
    std::string specialPrefix = "dc#123";
    Exiv2::XmpNsInfo expectedNsInfo;  // Define expected behavior for special prefix
    EXPECT_CALL(mockXmpProperties, nsInfoUnsafe(specialPrefix))
        .WillOnce(testing::Return(&expectedNsInfo));

    const Exiv2::XmpNsInfo* result = mockXmpProperties.nsInfo(specialPrefix);

    ASSERT_EQ(result, &expectedNsInfo);
}

// Test for exceptional case: Handling non-existent prefix
TEST_F(XmpPropertiesTest, NsInfo_NonExistentPrefix_1258) {
    std::string nonExistentPrefix = "xyz";
    EXPECT_CALL(mockXmpProperties, nsInfoUnsafe(nonExistentPrefix))
        .WillOnce(testing::Return(nullptr));

    const Exiv2::XmpNsInfo* result = mockXmpProperties.nsInfo(nonExistentPrefix);

    ASSERT_EQ(result, nullptr);  // Expecting null for non-existent prefix
}

}  // namespace Exiv2