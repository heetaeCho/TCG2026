#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <string>



namespace Exiv2 {

    namespace Internal {

        class PentaxMakerNote {

        public:

            std::ostream& printResolution(std::ostream& os, const Value& value, const ExifData*) {

                std::string val = value.toString();

                std::replace(val.begin(), val.end(), ' ', 'x');

                os << val;

                return os;

            }

        };

    }

}



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(std::string, toString, (), (const, override));

};



TEST_F(PentaxMakerNoteTest_190, PrintResolution_NormalOperation_190) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("300 200"));



    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;

    std::ostringstream os;



    pentaxMakerNote.printResolution(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "300x200");

}



TEST_F(PentaxMakerNoteTest_190, PrintResolution_EmptyString_190) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return(""));



    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;

    std::ostringstream os;



    pentaxMakerNote.printResolution(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "");

}



TEST_F(PentaxMakerNoteTest_190, PrintResolution_NoSpaces_190) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("300x200"));



    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;

    std::ostringstream os;



    pentaxMakerNote.printResolution(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "300x200");

}



TEST_F(PentaxMakerNoteTest_190, PrintResolution_MultipleSpaces_190) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("  300   200  "));



    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;

    std::ostringstream os;



    pentaxMakerNote.printResolution(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "xxx300xxx200xx");

}



TEST_F(PentaxMakerNoteTest_190, PrintResolution_SpecialCharacters_190) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("300! 200@"));



    Exiv2::Internal::PentaxMakerNote pentaxMakerNote;

    std::ostringstream os;



    pentaxMakerNote.printResolution(os, mockValue, nullptr);



    ASSERT_EQ(os.str(), "300!x200@");

}
