#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <mutex>

// Mock the Exiv2::XmpProperties class
namespace Exiv2 {
    class XmpProperties {
    public:
        virtual ~XmpProperties() = default;

        virtual void unregisterNs(const std::string& ns) {
            auto scoped_write_lock = std::scoped_lock(mutex_);
            unregisterNsUnsafe(ns);
        }

        // Mocked dependencies
        virtual void unregisterNsUnsafe(const std::string& ns) = 0;
    };
}

class XmpPropertiesMock : public Exiv2::XmpProperties {
public:
    MOCK_METHOD(void, unregisterNsUnsafe, (const std::string& ns), (override));
};

class XmpPropertiesTest : public ::testing::Test {
protected:
    XmpPropertiesMock mockXmpProperties;
};

// Test case for normal operation (testing that unregisterNs calls unregisterNsUnsafe)
TEST_F(XmpPropertiesTest, UnregisterNs_NormalOperation_1245) {
    std::string ns = "http://example.com/ns";
    
    // Expect unregisterNsUnsafe to be called with the given namespace
    EXPECT_CALL(mockXmpProperties, unregisterNsUnsafe(ns))
        .Times(1);
    
    // Call unregisterNs which should internally call unregisterNsUnsafe
    mockXmpProperties.unregisterNs(ns);
}

// Test case for boundary conditions (testing with an empty namespace)
TEST_F(XmpPropertiesTest, UnregisterNs_EmptyNamespace_1246) {
    std::string ns = "";
    
    // Expect unregisterNsUnsafe to be called with an empty string
    EXPECT_CALL(mockXmpProperties, unregisterNsUnsafe(ns))
        .Times(1);
    
    // Call unregisterNs with empty namespace
    mockXmpProperties.unregisterNs(ns);
}

// Test case for error/exception case (testing with a non-existing namespace, the function doesn't throw in this case, but we can verify interactions)
TEST_F(XmpPropertiesTest, UnregisterNs_NonExistingNamespace_1247) {
    std::string ns = "http://nonexistent.com/ns";
    
    // Expect unregisterNsUnsafe to be called with the non-existing namespace
    EXPECT_CALL(mockXmpProperties, unregisterNsUnsafe(ns))
        .Times(1);
    
    // Call unregisterNs with a non-existing namespace
    mockXmpProperties.unregisterNs(ns);
}