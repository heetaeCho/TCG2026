#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/emittermanip.h"



class EmitterTest_531 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_531, SetLocalIndent_ValidValue_ReturnsReferenceToSelf_531) {

    YAML::_Indent indent(2);

    EXPECT_EQ(&emitter, &emitter.SetLocalIndent(indent));

}



TEST_F(EmitterTest_531, SetLocalIndent_ZeroValue_ReturnsReferenceToSelf_531) {

    YAML::_Indent indent(0);

    EXPECT_EQ(&emitter, &emitter.SetLocalIndent(indent));

}



TEST_F(EmitterTest_531, SetLocalIndent_NegativeValue_ReturnsReferenceToSelf_531) {

    YAML::_Indent indent(-1);

    EXPECT_EQ(&emitter, &emitter.SetLocalIndent(indent));

}



TEST_F(EmitterTest_531, SetLocalIndent_MaxValue_ReturnsReferenceToSelf_531) {

    YAML::_Indent indent(std::numeric_limits<std::size_t>::max());

    EXPECT_EQ(&emitter, &emitter.SetLocalIndent(indent));

}
