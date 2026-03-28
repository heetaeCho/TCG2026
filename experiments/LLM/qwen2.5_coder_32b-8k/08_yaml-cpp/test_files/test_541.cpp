#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/ostream_wrapper.h"

#include "yaml-cpp/emittermanip.h"



class EmitterTest_541 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_541, WriteComment_NormalOperation_541) {

    std::ostringstream stream;

    YAML::Emitter e(stream);

    YAML::_Comment comment("This is a comment");



    e.Write(comment);



    EXPECT_EQ("# This is a comment\n", stream.str());

}



TEST_F(EmitterTest_541, WriteComment_EmptyContent_541) {

    std::ostringstream stream;

    YAML::Emitter e(stream);

    YAML::_Comment comment("");



    e.Write(comment);



    EXPECT_EQ("# \n", stream.str());

}



TEST_F(EmitterTest_541, WriteComment_AtStartOfLine_541) {

    std::ostringstream stream;

    YAML::Emitter e(stream);

    YAML::_Comment comment("Starting line comment");



    e.Write(comment);



    EXPECT_EQ("# Starting line comment\n", stream.str());

}



TEST_F(EmitterTest_541, WriteComment_NotAtStartOfLine_541) {

    std::ostringstream stream;

    YAML::Emitter e(stream);

    e.Write("Some text");

    YAML::_Comment comment("Inline comment");



    e.Write(comment);



    EXPECT_EQ("Some text # Inline comment\n", stream.str());

}



TEST_F(EmitterTest_541, WriteComment_MultipleComments_541) {

    std::ostringstream stream;

    YAML::Emitter e(stream);

    YAML::_Comment comment1("First comment");

    YAML::_Comment comment2("Second comment");



    e.Write(comment1);

    e.Write(comment2);



    EXPECT_EQ("# First comment\n# Second comment\n", stream.str());

}



TEST_F(EmitterTest_541, WriteComment_BadEmitterState_541) {

    std::ostringstream stream;

    YAML::Emitter e(stream);

    YAML::_Comment comment("This should not be written");

    e.SetLocalIndent(YAML::_Indent(0, 0)); // This might set a bad state depending on implementation



    e.Write(comment);



    EXPECT_EQ("", stream.str());

}
