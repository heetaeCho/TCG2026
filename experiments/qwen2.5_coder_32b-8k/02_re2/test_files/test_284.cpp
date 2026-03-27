#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.cc"



using namespace re2::hooks;



class MockCallback {

public:

    MOCK_METHOD(void, Method, (), ());

};



TEST_F(HookTest_284, LoadReturnsNullptrInitially_284) {

    Hook<MockCallback> hook;

    EXPECT_EQ(hook.Load(), nullptr);

}



TEST_F(HookTest_284, StoreAndLoadWorkTogether_284) {

    Hook<MockCallback> hook;

    MockCallback callback;

    hook.Store(&callback);

    EXPECT_EQ(hook.Load(), &callback);

}



TEST_F(HookTest_284, LoadReturnsUpdatedPointer_284) {

    Hook<MockCallback> hook;

    MockCallback callback1, callback2;

    hook.Store(&callback1);

    EXPECT_EQ(hook.Load(), &callback1);

    hook.Store(&callback2);

    EXPECT_EQ(hook.Load(), &callback2);

}



TEST_F(HookTest_284, StoreNullptrAndLoadReturnsNullptr_284) {

    Hook<MockCallback> hook;

    MockCallback callback;

    hook.Store(&callback);

    hook.Store(nullptr);

    EXPECT_EQ(hook.Load(), nullptr);

}
