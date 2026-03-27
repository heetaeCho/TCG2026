#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "WXMPMeta.hpp"

#include "XMP_Const.h"



using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



// Mock class for XMP_TextOutputProc

class MockTextOutputProc {

public:

    MOCK_METHOD2(Invoke, void(void*, const char*));

};



// Wrapper function to use the mock object as a callback

void MockOutputRoutine(void* refCon, const char* text) {

    static_cast<MockTextOutputProc*>(refCon)->Invoke(refCon, text);

}



class WXMPMetaTest_1995 : public ::testing::Test {

protected:

    WXMP_Result wResult;

};



TEST_F(WXMPMetaTest_1995, ValidOutProc_1995) {

    MockTextOutputProc mockOutput;

    EXPECT_CALL(mockOutput, Invoke(_, _));



    WXMPMeta_DumpNamespaces_1(MockOutputRoutine, &mockOutput, &wResult);



    ASSERT_EQ(wResult.int32Result, 0);

}



TEST_F(WXMPMetaTest_1995, NullOutProc_1995) {

    WXMPMeta_DumpNamespaces_1(nullptr, nullptr, &wResult);



    EXPECT_EQ(wResult.int32Result, kXMPErr_BadParam);

}
