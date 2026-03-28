#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declaration and include necessary headers
// Based on the partial code, ExpatAdapter is created via XMP_NewExpatAdapter()

// We need to include the relevant headers for ExpatAdapter
// These are typical includes based on the exiv2/xmpsdk structure
#include "ExpatAdapter.hpp"

// If the above header doesn't exist, try alternatives
// #include "XMP_Environment.h"
// #include "source/ExpatAdapter.hpp"

class ExpatAdapterTest_2090 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that XMP_NewExpatAdapter returns a non-null pointer
TEST_F(ExpatAdapterTest_2090, NewExpatAdapterReturnsNonNull_2090) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter();
    ASSERT_NE(adapter, nullptr);
    delete adapter;
}

// Test that multiple calls to XMP_NewExpatAdapter return different instances
TEST_F(ExpatAdapterTest_2090, NewExpatAdapterReturnsDifferentInstances_2090) {
    ExpatAdapter* adapter1 = XMP_NewExpatAdapter();
    ExpatAdapter* adapter2 = XMP_NewExpatAdapter();
    ASSERT_NE(adapter1, nullptr);
    ASSERT_NE(adapter2, nullptr);
    EXPECT_NE(adapter1, adapter2);
    delete adapter1;
    delete adapter2;
}

// Test that the created ExpatAdapter can be safely deleted
TEST_F(ExpatAdapterTest_2090, NewExpatAdapterCanBeDeleted_2090) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter();
    ASSERT_NE(adapter, nullptr);
    // Should not crash or throw
    EXPECT_NO_THROW(delete adapter);
}

// Test creating and destroying many adapters (stress/boundary test)
TEST_F(ExpatAdapterTest_2090, MultipleAdaptersCreatedAndDestroyed_2090) {
    const int count = 100;
    std::vector<ExpatAdapter*> adapters;
    adapters.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        ExpatAdapter* adapter = XMP_NewExpatAdapter();
        ASSERT_NE(adapter, nullptr) << "Failed at iteration " << i;
        adapters.push_back(adapter);
    }
    
    for (auto* adapter : adapters) {
        delete adapter;
    }
}

// Test that the adapter object is a valid ExpatAdapter type
TEST_F(ExpatAdapterTest_2090, NewExpatAdapterReturnsCorrectType_2090) {
    ExpatAdapter* adapter = XMP_NewExpatAdapter();
    ASSERT_NE(adapter, nullptr);
    
    // Verify it's a valid ExpatAdapter by checking the pointer is valid
    // (dynamic_cast would work if there's a virtual destructor / polymorphism)
    ExpatAdapter* casted = dynamic_cast<ExpatAdapter*>(adapter);
    EXPECT_NE(casted, nullptr);
    
    delete adapter;
}
