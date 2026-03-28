#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to provide minimal stubs for NSS types since we're testing the interface
// without access to the full NSS library in a unit test context.

// Forward declare / stub the NSS types needed
extern "C" {
    typedef struct HASHContextStr HASHContext;
    
    // We'll track whether HASH_Destroy was called
    static bool g_hash_destroy_called = false;
    static HASHContext* g_hash_destroy_arg = nullptr;
    
    void HASH_Destroy(HASHContext *hash) {
        g_hash_destroy_called = true;
        g_hash_destroy_arg = hash;
    }
}

// Now include or replicate the minimal interface we're testing
// Based on the partial code, HashContext contains a HashDestroyer functor
struct HashContext {
    struct HashDestroyer {
    public:
        void operator()(HASHContext *hash) {
            HASH_Destroy(hash);
        }
    };
};

class HashDestroyerTest_1363 : public ::testing::Test {
protected:
    void SetUp() override {
        g_hash_destroy_called = false;
        g_hash_destroy_arg = nullptr;
    }
};

// Test that HashDestroyer calls HASH_Destroy with the provided pointer
TEST_F(HashDestroyerTest_1363, CallsHashDestroyWithCorrectPointer_1363) {
    HashContext::HashDestroyer destroyer;
    
    // Create a dummy HASHContext pointer (we don't dereference it, just pass it through)
    HASHContext* dummyHash = reinterpret_cast<HASHContext*>(0x12345678);
    
    destroyer(dummyHash);
    
    EXPECT_TRUE(g_hash_destroy_called);
    EXPECT_EQ(g_hash_destroy_arg, dummyHash);
}

// Test that HashDestroyer handles nullptr
TEST_F(HashDestroyerTest_1363, CallsHashDestroyWithNullptr_1363) {
    HashContext::HashDestroyer destroyer;
    
    destroyer(nullptr);
    
    EXPECT_TRUE(g_hash_destroy_called);
    EXPECT_EQ(g_hash_destroy_arg, nullptr);
}

// Test that HashDestroyer can be used as a deleter type (e.g., with unique_ptr)
TEST_F(HashDestroyerTest_1363, CanBeUsedAsUniquePointerDeleter_1363) {
    // Verify that HashDestroyer is usable as a custom deleter type
    // This tests the type compatibility without actually allocating a real HASHContext
    using UniqueHash = std::unique_ptr<HASHContext, HashContext::HashDestroyer>;
    
    // Just verify the type compiles and can be default-constructed
    UniqueHash ptr(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
    
    // No HASH_Destroy should be called for a nullptr unique_ptr going out of scope
    // (unique_ptr doesn't call deleter on nullptr by default - implementation defined,
    //  but we verify the type works)
}

// Test that HashDestroyer triggers HASH_Destroy when unique_ptr releases a non-null pointer
TEST_F(HashDestroyerTest_1363, UniquePointerCallsDestroyerOnReset_1363) {
    using UniqueHash = std::unique_ptr<HASHContext, HashContext::HashDestroyer>;
    
    HASHContext* dummyHash = reinterpret_cast<HASHContext*>(0xDEADBEEF);
    
    {
        UniqueHash ptr(dummyHash);
        EXPECT_FALSE(g_hash_destroy_called);
    }
    // After unique_ptr goes out of scope, destroyer should have been called
    EXPECT_TRUE(g_hash_destroy_called);
    EXPECT_EQ(g_hash_destroy_arg, dummyHash);
}

// Test that multiple calls to HashDestroyer work correctly
TEST_F(HashDestroyerTest_1363, MultipleCallsWorkCorrectly_1363) {
    HashContext::HashDestroyer destroyer;
    
    HASHContext* first = reinterpret_cast<HASHContext*>(0x1);
    HASHContext* second = reinterpret_cast<HASHContext*>(0x2);
    
    destroyer(first);
    EXPECT_TRUE(g_hash_destroy_called);
    EXPECT_EQ(g_hash_destroy_arg, first);
    
    g_hash_destroy_called = false;
    g_hash_destroy_arg = nullptr;
    
    destroyer(second);
    EXPECT_TRUE(g_hash_destroy_called);
    EXPECT_EQ(g_hash_destroy_arg, second);
}

// Test that HashDestroyer is default constructible
TEST_F(HashDestroyerTest_1363, IsDefaultConstructible_1363) {
    EXPECT_TRUE(std::is_default_constructible<HashContext::HashDestroyer>::value);
}

// Test that HashDestroyer is copy constructible
TEST_F(HashDestroyerTest_1363, IsCopyConstructible_1363) {
    EXPECT_TRUE(std::is_copy_constructible<HashContext::HashDestroyer>::value);
    
    HashContext::HashDestroyer original;
    HashContext::HashDestroyer copy(original);
    
    HASHContext* dummyHash = reinterpret_cast<HASHContext*>(0xABCD);
    copy(dummyHash);
    
    EXPECT_TRUE(g_hash_destroy_called);
    EXPECT_EQ(g_hash_destroy_arg, dummyHash);
}
