#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/goo/gmem.h"



// Since gmalloc_checkoverflow is an inline function that relies on gmalloc,

// we need to ensure that gmalloc behaves as expected.

// We will mock gmalloc using a global mock object.



class MockGMem {

public:

    MOCK_METHOD2(gmalloc, void*(size_t size, bool checkOverflow));

};



MockGMem* g_mockGMem = nullptr;



extern "C" void* gmalloc(size_t size, bool checkOverflow) {

    return g_mockGMem->gmalloc(size, checkOverflow);

}



class GMemTest_10 : public ::testing::Test {

protected:

    void SetUp() override {

        g_mockGMem = new MockGMem();

    }



    void TearDown() override {

        delete g_mockGMem;

        g_mockGMem = nullptr;

    }

};



TEST_F(GMemTest_10, GmallocCheckOverflow_CallsGmallocWithTrue_10) {

    EXPECT_CALL(*g_mockGMem, gmalloc(::testing::_, true))

        .WillOnce(::testing::Return(nullptr));



    void* result = gmalloc_checkoverflow(42);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GMemTest_10, GmallocCheckOverflow_ZeroSize_ReturnsNull_10) {

    EXPECT_CALL(*g_mockGMem, gmalloc(0, true))

        .WillOnce(::testing::Return(nullptr));



    void* result = gmalloc_checkoverflow(0);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GMemTest_10, GmallocCheckOverflow_NonZeroSize_ReturnsNonNull_10) {

    void* expectedPtr = reinterpret_cast<void*>(0x12345678);



    EXPECT_CALL(*g_mockGMem, gmalloc(1024, true))

        .WillOnce(::testing::Return(expectedPtr));



    void* result = gmalloc_checkoverflow(1024);

    EXPECT_EQ(result, expectedPtr);

}



TEST_F(GMemTest_10, GmallocCheckOverflow_LargeSize_ReturnsNonNull_10) {

    void* expectedPtr = reinterpret_cast<void*>(0x87654321);



    EXPECT_CALL(*g_mockGMem, gmalloc(1048576, true))

        .WillOnce(::testing::Return(expectedPtr));



    void* result = gmalloc_checkoverflow(1048576);

    EXPECT_EQ(result, expectedPtr);

}
