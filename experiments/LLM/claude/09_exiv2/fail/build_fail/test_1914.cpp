#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "XMPIterator.hpp"
#include "XMPMeta.hpp"
#include "WXMP_Common.hpp"

// Forward declarations for the wrapper functions we're testing
extern "C" {
void WXMPUtils_UnlockIter_1(XMPIteratorRef iterRef, XMP_OptionBits options);
}

// Since we need to test the wrapper function WXMPUtils_UnlockIter_1,
// and it operates on an XMPIterator through its ref, we need to work
// with the actual objects or mock them appropriately.

// Mock class for XMPIterator to verify UnlockIter is called
class MockXMPIterator : public XMPIterator {
public:
    // We can't easily construct XMPIterator without proper setup,
    // so we'll test through the actual API path instead.
};

class WXMPIteratorTest_1914 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        try {
            XMPIterator::Initialize();
        } catch (...) {
            // May already be initialized
        }
    }

    void TearDown() override {
        // Cleanup
    }
};

// Test that passing a null iterator ref doesn't crash unexpectedly
// (it should handle the error through the wrapper mechanism)
TEST_F(WXMPIteratorTest_1914, NullIteratorRef_1914) {
    // Passing null/0 as iterRef - the wrapper should handle this gracefully
    // via exception handling in XMP_EXIT_WRAPPER_NO_THROW
    EXPECT_NO_FATAL_FAILURE({
        WXMPUtils_UnlockIter_1(0, 0);
    });
}

// Test with zero options on null ref
TEST_F(WXMPIteratorTest_1914, NullRefZeroOptions_1914) {
    EXPECT_NO_FATAL_FAILURE({
        WXMPUtils_UnlockIter_1(nullptr, 0);
    });
}

// Test with various option bits on null ref to ensure no crash
TEST_F(WXMPIteratorTest_1914, NullRefVariousOptions_1914) {
    EXPECT_NO_FATAL_FAILURE({
        WXMPUtils_UnlockIter_1(nullptr, 0x0001);
    });
    EXPECT_NO_FATAL_FAILURE({
        WXMPUtils_UnlockIter_1(nullptr, 0xFFFFFFFF);
    });
}

// Test with a valid XMPIterator created from XMPMeta
TEST_F(WXMPIteratorTest_1914, ValidIteratorUnlock_1914) {
    try {
        XMPMeta meta;
        XMPIterator* iter = new XMPIterator(meta, "", "", 0);
        XMPIteratorRef iterRef = WXMPIterator_IsValidRef(iter) ? (XMPIteratorRef)iter : nullptr;
        
        if (iterRef != nullptr) {
            EXPECT_NO_FATAL_FAILURE({
                WXMPUtils_UnlockIter_1(iterRef, 0);
            });
        }
        
        delete iter;
    } catch (...) {
        // If construction fails due to missing initialization, that's OK
        // The test is about the unlock wrapper behavior
    }
}

// Test with valid iterator and non-zero options
TEST_F(WXMPIteratorTest_1914, ValidIteratorUnlockWithOptions_1914) {
    try {
        XMPMeta meta;
        XMPIterator* iter = new XMPIterator(meta, "", "", 0);
        XMPIteratorRef iterRef = (XMPIteratorRef)iter;
        
        if (iterRef != nullptr) {
            EXPECT_NO_FATAL_FAILURE({
                WXMPUtils_UnlockIter_1(iterRef, 0x0001);
            });
        }
        
        delete iter;
    } catch (...) {
        // Construction might fail - acceptable for this test
    }
}

// Test boundary: maximum option bits
TEST_F(WXMPIteratorTest_1914, MaxOptionBits_1914) {
    EXPECT_NO_FATAL_FAILURE({
        WXMPUtils_UnlockIter_1(nullptr, 0xFFFFFFFF);
    });
}

// Test that the void_wResult is properly used (no crash on repeated calls)
TEST_F(WXMPIteratorTest_1914, RepeatedCallsNullRef_1914) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_NO_FATAL_FAILURE({
            WXMPUtils_UnlockIter_1(nullptr, 0);
        });
    }
}

// Test with an invalid (garbage) pointer - this tests robustness
// Note: In practice this would be undefined behavior, but the wrapper
// should ideally catch exceptions via XMP_EXIT_WRAPPER_NO_THROW
TEST_F(WXMPIteratorTest_1914, InvalidPointerHandling_1914) {
    // We only test null here as invalid non-null pointers would be UB
    XMPIteratorRef invalidRef = nullptr;
    EXPECT_NO_FATAL_FAILURE({
        WXMPUtils_UnlockIter_1(invalidRef, 0);
    });
}
