#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ostream>
#include <string>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>

namespace Exiv2 {
    
    // Mock class for testing purposes
    class MockPrintFct {
    public:
        MOCK_METHOD(std::ostream&, operator(), (std::ostream& os, const Value& value, const void* extra), ());
    };

    // Test fixture for XmpProperties
    class XmpPropertiesTest_1258 : public ::testing::Test {
    protected:
        // Mocked PrintFct for testing
        MockPrintFct mockPrintFct;

        // Test subject
        XmpProperties xmpProperties;

        // Helper to simulate the behavior of 'find' function within 'printProperty'
        void setupMockBehavior(bool shouldFind) {
            if (shouldFind) {
                EXPECT_CALL(mockPrintFct, operator()(testing::_, testing::_, testing::_))
                    .WillOnce(testing::ReturnRef(std::cout));
            }
        }
    };

    // Test normal operation
    TEST_F(XmpPropertiesTest_1258, PrintProperty_NormalOperation_1258) {
        std::ostream os(nullptr);
        const std::string key = "Xmp.exif.FocalLength";
        Value value(TypeId::kInt32);
        
        // Setup mock behavior (simulate that the function will find and print correctly)
        setupMockBehavior(true);
        
        // Call the method to test
        std::ostream& result = xmpProperties.printProperty(os, key, value);
        
        // Verify the result, ensuring it interacts correctly with the mock PrintFct
        ASSERT_EQ(&result, &os);
    }

    // Test boundary conditions
    TEST_F(XmpPropertiesTest_1258, PrintProperty_BoundaryCondition_1258) {
        std::ostream os(nullptr);
        const std::string key = "Xmp.exif.FocalLength";
        Value value(TypeId::kInt32);
        
        // Test with an empty key
        std::string emptyKey = "";
        std::ostream& result = xmpProperties.printProperty(os, emptyKey, value);
        
        // Verify that printProperty still returns a valid ostream reference
        ASSERT_EQ(&result, &os);
    }

    // Test error case: invalid key not found in xmpPrintInfo
    TEST_F(XmpPropertiesTest_1258, PrintProperty_InvalidKey_1258) {
        std::ostream os(nullptr);
        const std::string key = "Invalid.Key.NotFound";
        Value value(TypeId::kInt32);

        // Expect no interaction with the mock as the key is not found
        setupMockBehavior(false);

        // Call the method to test
        std::ostream& result = xmpProperties.printProperty(os, key, value);
        
        // Verify the result
        ASSERT_EQ(&result, &os);
    }

    // Test external interactions (mocking the `find` and `printFct`)
    TEST_F(XmpPropertiesTest_1258, PrintProperty_MockedFind_1258) {
        std::ostream os(nullptr);
        const std::string key = "Xmp.exif.FocalLength";
        Value value(TypeId::kInt32);
        
        // Setup mock behavior
        setupMockBehavior(true);

        // Call printProperty and verify mock interaction
        std::ostream& result = xmpProperties.printProperty(os, key, value);
        ASSERT_EQ(&result, &os);
    }
}