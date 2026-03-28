#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <string>



// Assuming Value and ExifData are defined somewhere in the codebase.

namespace Exiv2 {

    class Value {

    public:

        std::string toString() const { return value_; }

        void setValue(const std::string& val) { value_ = val; }

    private:

        std::string value_;

    };



    class ExifData {};

}



using namespace Exiv2::Internal;



class PentaxMakerNoteTest : public ::testing::Test {

protected:

    PentaxMakerNote pentaxMakerNote;

};



TEST_F(PentaxMakerNoteTest_189, PrintVersion_ReplacesSpacesWithDots_189) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("Version 1 2");



    std::ostream& result = pentaxMakerNote.printVersion(os, value, nullptr);



    EXPECT_EQ(result.str(), "Version.1.2");

}



TEST_F(PentaxMakerNoteTest_189, PrintVersion_NoSpaces_189) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("Version1.2");



    std::ostream& result = pentaxMakerNote.printVersion(os, value, nullptr);



    EXPECT_EQ(result.str(), "Version1.2");

}



TEST_F(PentaxMakerNoteTest_189, PrintVersion_EmptyString_189) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("");



    std::ostream& result = pentaxMakerNote.printVersion(os, value, nullptr);



    EXPECT_EQ(result.str(), "");

}



TEST_F(PentaxMakerNoteTest_189, PrintVersion_MultipleSpaces_189) {

    std::ostringstream os;

    Exiv2::Value value;

    value.setValue("   Version  1.2   ");



    std::ostream& result = pentaxMakerNote.printVersion(os, value, nullptr);



    EXPECT_EQ(result.str(), "...Version..1.2...");

}
