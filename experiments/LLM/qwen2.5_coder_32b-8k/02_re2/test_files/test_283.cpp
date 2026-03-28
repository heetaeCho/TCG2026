#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.cc"  // Adjust the path as necessary



using namespace re2::hooks;



class HookTest_283 : public ::testing::Test {

protected:

    using TestHook = Hook<void(*)()>;



    void SetUp() override {

        hook.Store(nullptr);

    }



    TestHook hook;

};



TEST_F(HookTest_283, StoreAndLoadNullPointer_283) {

    EXPECT_EQ(hook.Load(), nullptr);

}



TEST_F(HookTest_283, StoreNonNullPointer_LoadReturnsSamePointer_283) {

    void (*testCallback)() = [](){};

    hook.Store(testCallback);

    EXPECT_EQ(hook.Load(), testCallback);

}



TEST_F(HookTest_283, StoreMultipleTimes_LastStoredPointerIsLoaded_283) {

    void (*firstCallback)() = [](){};

    void (*secondCallback)() = [](){};



    hook.Store(firstCallback);

    hook.Store(secondCallback);



    EXPECT_EQ(hook.Load(), secondCallback);

}



TEST_F(HookTest_283, StoreAndLoadWithDifferentTypes_283) {

    using IntHook = Hook<int(*)()>;

    IntHook intHook;



    int (*intCallback)() = [](){ return 42; };

    intHook.Store(intCallback);



    EXPECT_EQ(intHook.Load(), intCallback);

}
