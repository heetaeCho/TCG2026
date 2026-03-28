#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_522 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_522, SetSeqFormat_ReturnsTrueForValidValue_522) {

    EMITTER_MANIP validValue = Flow; // Assuming Flow is a valid EMITTER_MANIP value

    EXPECT_TRUE(emitter.SetSeqFormat(validValue));

}



TEST_F(EmitterTest_522, SetSeqFormat_ReturnsFalseForInvalidValue_522) {

    EMITTER_MANIP invalidValue = static_cast<EMITTER_MANIP>(-1); // Assuming -1 is an invalid EMITTER_MANIP value

    EXPECT_FALSE(emitter.SetSeqFormat(invalidValue));

}



TEST_F(EmitterTest_522, SetSeqFormat_DoesNotThrowExceptionForValidValue_522) {

    EMITTER_MANIP validValue = Flow; // Assuming Flow is a valid EMITTER_MANIP value

    EXPECT_NO_THROW(emitter.SetSeqFormat(validValue));

}



TEST_F(EmitterTest_522, SetSeqFormat_DoesNotModifyGoodStateOnSuccess_522) {

    EMITTER_MANIP validValue = Flow; // Assuming Flow is a valid EMITTER_MANIP value

    emitter.SetSeqFormat(validValue);

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_522, SetSeqFormat_ModifiesLastErrorOnFailure_522) {

    EMITTER_MANIP invalidValue = static_cast<EMITTER_MANIP>(-1); // Assuming -1 is an invalid EMITTER_MANIP value

    emitter.SetSeqFormat(invalidValue);

    EXPECT_FALSE(emitter.GetLastError().empty());

}
