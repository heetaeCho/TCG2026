#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/emittermanip.h"



using namespace YAML;

using namespace testing;



class EmitterTest_539 : public Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_539, WriteAnchor_NormalOperation_539) {

    _Anchor anchor("test_anchor");

    auto& result = emitter.Write(anchor);

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(&result, &emitter); // Ensure chaining works

}



TEST_F(EmitterTest_539, WriteAnchor_AlreadyHasAnchor_539) {

    _Anchor anchor1("anchor1");

    emitter.Write(anchor1);



    _Anchor anchor2("anchor2");

    auto& result = emitter.Write(anchor2);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(&result, &emitter); // Ensure chaining works

    EXPECT_EQ(emitter.GetLastError(), ErrorMsg::INVALID_ANCHOR);

}



TEST_F(EmitterTest_539, WriteAnchor_EmptyString_539) {

    _Anchor anchor("");

    auto& result = emitter.Write(anchor);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(&result, &emitter); // Ensure chaining works

    EXPECT_EQ(emitter.GetLastError(), ErrorMsg::INVALID_ANCHOR);

}



TEST_F(EmitterTest_539, WriteAnchor_BoundaryCondition_MaxSize_539) {

    std::string max_size_string(1024, 'a'); // Assuming a reasonable max size

    _Anchor anchor(max_size_string);

    auto& result = emitter.Write(anchor);

    EXPECT_TRUE(emitter.good());

    EXPECT_EQ(&result, &emitter); // Ensure chaining works

}



TEST_F(EmitterTest_539, WriteAnchor_ErrorAfterSuccessfulWrite_539) {

    _Anchor valid_anchor("valid");

    emitter.Write(valid_anchor);



    EmitterState* state = emitter.m_pState.get();

    EXPECT_CALL(*state, HasAnchor()).WillOnce(Return(false));

    EXPECT_CALL(*state, SetError(ErrorMsg::INVALID_ANCHOR));



    _Anchor invalid_anchor("");

    auto& result = emitter.Write(invalid_anchor);

    EXPECT_FALSE(emitter.good());

    EXPECT_EQ(&result, &emitter); // Ensure chaining works

    EXPECT_EQ(emitter.GetLastError(), ErrorMsg::INVALID_ANCHOR);

}
