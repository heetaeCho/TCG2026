#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMP_Core_Impl.cpp"

#include "XMP_Const.h"



// Mock class for XMP_Mutex to simulate its behavior

class MockXMP_Mutex {

public:

    MOCK_METHOD(int, unlock, (), ());

};



TEST_F(MockXMP_MutexTest_1883, NormalOperation_UnlockSuccess_1883) {

    MockXMP_Mutex mockMutex;

    EXPECT_CALL(mockMutex, unlock()).WillOnce(testing::Return(0));



    XMP_ExitCriticalRegion(mockMutex);

}



TEST_F(MockXMP_MutexTest_1883, ExceptionalCase_UnlockFailure_1883) {

    MockXMP_Mutex mockMutex;

    EXPECT_CALL(mockMutex, unlock()).WillOnce(testing::Return(1));

    

    EXPECT_THROW(XMP_ExitCriticalRegion(mockMutex), XMP_Error);

}



TEST_F(MockXMP_MutexTest_1883, BoundaryCondition_UnlockMultipleTimesSuccess_1883) {

    MockXMP_Mutex mockMutex;

    EXPECT_CALL(mockMutex, unlock()).WillRepeatedly(testing::Return(0));



    for (int i = 0; i < 5; ++i) {

        XMP_ExitCriticalRegion(mockMutex);

    }

}



TEST_F(MockXMP_MutexTest_1883, BoundaryCondition_UnlockMultipleTimesFailure_1883) {

    MockXMP_Mutex mockMutex;

    EXPECT_CALL(mockMutex, unlock()).WillOnce(testing::Return(0))

                                    .WillOnce(testing::Return(1));



    XMP_ExitCriticalRegion(mockMutex);

    EXPECT_THROW(XMP_ExitCriticalRegion(mockMutex), XMP_Error);

}
