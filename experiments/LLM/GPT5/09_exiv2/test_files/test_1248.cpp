#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "properties.hpp"

namespace Exiv2 {

class XmpPropertiesTest : public ::testing::Test {
protected:
    // Setup code if needed
    XmpPropertiesTest() {}
    ~XmpPropertiesTest() override {}
};

TEST_F(XmpPropertiesTest, Ns_ValidPrefix_ReturnsNs_1248) {
    // TEST_ID: 1248
    std::string prefix = "exif";
    
    // Expect ns to be returned for a valid prefix
    std::string expected_ns = "http://ns.exiv2.org/";
    
    EXPECT_EQ(XmpProperties::ns(prefix), expected_ns);
}

TEST_F(XmpPropertiesTest, Ns_InvalidPrefix_ReturnsEmptyString_1249) {
    // TEST_ID: 1249
    std::string prefix = "invalidPrefix";
    
    // Expect an empty string to be returned for an invalid prefix
    EXPECT_EQ(XmpProperties::ns(prefix), "");
}

TEST_F(XmpPropertiesTest, Ns_EmptyPrefix_ThrowsException_1250) {
    // TEST_ID: 1250
    std::string prefix = "";
    
    // Expect an exception to be thrown when an empty prefix is passed
    EXPECT_THROW(XmpProperties::ns(prefix), std::invalid_argument);
}

TEST_F(XmpPropertiesTest, Ns_LookupNsRegistryCalled_1251) {
    // TEST_ID: 1251
    std::string prefix = "dc";
    
    // Mocking the lookupNsRegistryUnsafe method to verify external interaction
    auto mock = std::make_unique<MockXmpProperties>();
    EXPECT_CALL(*mock, lookupNsRegistryUnsafe(::testing::_))
        .Times(1);
    
    mock->ns(prefix);
}

}  // namespace Exiv2