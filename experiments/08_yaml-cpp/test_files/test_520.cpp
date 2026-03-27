#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_520 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_520, SetNullFormat_Successful_520) {

    EXPECT_TRUE(emitter.SetNullFormat(EMITTER_MANIP::AUTO));

}



TEST_F(EmitterTest_520, SetNullFormat_DefaultValue_ReturnsTrue_520) {

    EXPECT_TRUE(emitter.SetNullFormat(EMITTER_MANIP::DEFAULT));

}



TEST_F(EmitterTest_520, SetNullFormat_UnsupportedValue_ReturnsFalse_520) {

    // Assuming there's an unsupported value for EMITTER_MANIP

    EXPECT_FALSE(emitter.SetNullFormat(static_cast<EMITTER_MANIP>(-1)));

}



TEST_F(EmitterTest_520, SetNullFormat_AfterWrite_DoesNotAffectPreviousData_520) {

    emitter.Write("some data");

    std::size_t initialSize = emitter.size();

    

    EXPECT_TRUE(emitter.SetNullFormat(EMITTER_MANIP::AUTO));

    EXPECT_EQ(initialSize, emitter.size());

}



TEST_F(EmitterTest_520, SetNullFormat_CheckGoodStatus_ReturnsTrue_520) {

    EXPECT_TRUE(emitter.SetNullFormat(EMITTER_MANIP::AUTO));

    EXPECT_TRUE(emitter.good());

}
