#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



using namespace YAML;



class EmitterTest_517 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_517, SetOutputCharset_ReturnsTrueForValidValue_517) {

    EXPECT_TRUE(emitter.SetOutputCharset(EMITTER_MANIP::EscapeUnicode));

}



TEST_F(EmitterTest_517, SetOutputCharset_ReturnsFalseForInvalidValue_517) {

    // Assuming there's an invalid value defined in EMITTER_MANIP

    EXPECT_FALSE(emitter.SetOutputCharset(static_cast<EMITTER_MANIP>(-1)));

}



TEST_F(EmitterTest_517, SetOutputCharset_DoesNotAffectGoodStateOnSuccess_517) {

    emitter.SetOutputCharset(EMITTER_MANIP::EscapeUnicode);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_517, SetOutputCharset_SetsLastErrorOnFailure_517) {

    emitter.SetOutputCharset(static_cast<EMITTER_MANIP>(-1));

    EXPECT_FALSE(emitter.GetLastError().empty());

}



TEST_F(EmitterTest_517, SetOutputCharset_HandlesBoundaryCondition_517) {

    // Assuming there are boundary conditions for EMITTER_MANIP values

    EXPECT_TRUE(emitter.SetOutputCharset(EMITTER_MANIP::EscapeNonAscii));

}



// Additional tests can be added to cover more specific scenarios if needed
