#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>

// Minimal reproduction of the class under test based on the provided partial code
namespace Poppler {

class DocumentData {
public:
    bool xrefReconstructed = false;
    std::function<void(void)> xrefReconstructedCallback;

    void notifyXRefReconstructed()
    {
        if (!xrefReconstructed) {
            xrefReconstructed = true;
        }
        if (xrefReconstructedCallback) {
            xrefReconstructedCallback();
        }
    }
};

} // namespace Poppler

// Test fixture
class DocumentDataTest_1289 : public ::testing::Test {
protected:
    Poppler::DocumentData docData;

    void SetUp() override
    {
        docData.xrefReconstructed = false;
        docData.xrefReconstructedCallback = nullptr;
    }
};

// Test that xrefReconstructed is set to true after calling notifyXRefReconstructed
TEST_F(DocumentDataTest_1289, NotifyXRefReconstructedSetsFlag_1289)
{
    EXPECT_FALSE(docData.xrefReconstructed);
    docData.notifyXRefReconstructed();
    EXPECT_TRUE(docData.xrefReconstructed);
}

// Test that the callback is invoked when set
TEST_F(DocumentDataTest_1289, NotifyXRefReconstructedInvokesCallback_1289)
{
    bool callbackInvoked = false;
    docData.xrefReconstructedCallback = [&callbackInvoked]() { callbackInvoked = true; };

    docData.notifyXRefReconstructed();

    EXPECT_TRUE(callbackInvoked);
}

// Test that calling notifyXRefReconstructed without a callback does not crash
TEST_F(DocumentDataTest_1289, NotifyXRefReconstructedWithoutCallbackDoesNotCrash_1289)
{
    docData.xrefReconstructedCallback = nullptr;
    EXPECT_NO_THROW(docData.notifyXRefReconstructed());
    EXPECT_TRUE(docData.xrefReconstructed);
}

// Test that calling notifyXRefReconstructed multiple times keeps the flag true
TEST_F(DocumentDataTest_1289, NotifyXRefReconstructedMultipleCallsKeepsFlagTrue_1289)
{
    docData.notifyXRefReconstructed();
    EXPECT_TRUE(docData.xrefReconstructed);

    docData.notifyXRefReconstructed();
    EXPECT_TRUE(docData.xrefReconstructed);
}

// Test that the callback is invoked on every call to notifyXRefReconstructed
TEST_F(DocumentDataTest_1289, NotifyXRefReconstructedCallbackInvokedEveryTime_1289)
{
    int callCount = 0;
    docData.xrefReconstructedCallback = [&callCount]() { callCount++; };

    docData.notifyXRefReconstructed();
    docData.notifyXRefReconstructed();
    docData.notifyXRefReconstructed();

    EXPECT_EQ(callCount, 3);
}

// Test that the flag transitions from false to true only on first call
TEST_F(DocumentDataTest_1289, FlagTransitionsOnlyOnce_1289)
{
    int flagSetCount = 0;
    // We observe the flag before and after each call
    EXPECT_FALSE(docData.xrefReconstructed);

    docData.notifyXRefReconstructed();
    EXPECT_TRUE(docData.xrefReconstructed);

    // Flag is already true, calling again should not change it
    bool flagBefore = docData.xrefReconstructed;
    docData.notifyXRefReconstructed();
    bool flagAfter = docData.xrefReconstructed;

    EXPECT_EQ(flagBefore, flagAfter);
    EXPECT_TRUE(flagAfter);
}

// Test that xrefReconstructed is already true before calling notify
TEST_F(DocumentDataTest_1289, NotifyWhenFlagAlreadyTrue_1289)
{
    docData.xrefReconstructed = true;
    bool callbackInvoked = false;
    docData.xrefReconstructedCallback = [&callbackInvoked]() { callbackInvoked = true; };

    docData.notifyXRefReconstructed();

    // Flag should still be true
    EXPECT_TRUE(docData.xrefReconstructed);
    // Callback should still be invoked
    EXPECT_TRUE(callbackInvoked);
}

// Test with a callback that modifies the flag
TEST_F(DocumentDataTest_1289, CallbackCanObserveFlagState_1289)
{
    bool flagDuringCallback = false;
    docData.xrefReconstructedCallback = [this, &flagDuringCallback]() {
        flagDuringCallback = docData.xrefReconstructed;
    };

    docData.notifyXRefReconstructed();

    // The flag should have been set before the callback is called (based on code order)
    EXPECT_TRUE(flagDuringCallback);
}

// Test replacing callback between calls
TEST_F(DocumentDataTest_1289, ReplacingCallbackBetweenCalls_1289)
{
    int firstCallbackCount = 0;
    int secondCallbackCount = 0;

    docData.xrefReconstructedCallback = [&firstCallbackCount]() { firstCallbackCount++; };
    docData.notifyXRefReconstructed();

    docData.xrefReconstructedCallback = [&secondCallbackCount]() { secondCallbackCount++; };
    docData.notifyXRefReconstructed();

    EXPECT_EQ(firstCallbackCount, 1);
    EXPECT_EQ(secondCallbackCount, 1);
}

// Test removing callback after setting it
TEST_F(DocumentDataTest_1289, RemovingCallbackAfterSetting_1289)
{
    int callbackCount = 0;
    docData.xrefReconstructedCallback = [&callbackCount]() { callbackCount++; };
    docData.notifyXRefReconstructed();
    EXPECT_EQ(callbackCount, 1);

    docData.xrefReconstructedCallback = nullptr;
    EXPECT_NO_THROW(docData.notifyXRefReconstructed());
    EXPECT_EQ(callbackCount, 1);  // Should not have been called again
}

// Test default state of the object
TEST_F(DocumentDataTest_1289, DefaultState_1289)
{
    Poppler::DocumentData freshData;
    EXPECT_FALSE(freshData.xrefReconstructed);
    EXPECT_FALSE(static_cast<bool>(freshData.xrefReconstructedCallback));
}
