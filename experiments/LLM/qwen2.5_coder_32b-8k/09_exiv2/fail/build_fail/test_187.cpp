#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/value.hpp>

#include <Exiv2/exif.hpp>

#include <sstream>



namespace Exiv2 {

    namespace Internal {

        template <size_t N, const TagVocabulary (&array)[N]> 

        std::ostream& printTagVocabularyMulti(std::ostream& os, const Value& value, const ExifData*) {

            static_assert(N > 0, "Passed zero length printTagVocabularyMulti");

            if (value.count() == 0) return os << "(" << value << ")";

            for (size_t i = 0; i < value.count(); i++) {

                if (i != 0) os << ", ";

                auto td = Exiv2::find(array, value.toString(i));

                if (td) {

                    os << _(td->label_);

                } else {

                    os << "(" << value.toString(i) << ")";

                }

            }

            return os;

        }

    }

}



namespace {



// Mock TagVocabulary for testing

const Exiv2::TagVocabulary mockTagVocabulary[] = {

    { "1", N_("Label1") },

    { "2", N_("Label2") },

    { "3", N_("Label3") }

};



using namespace ::testing;



class PrintTagVocabularyMultiTest_187 : public Test {

protected:

    Exiv2::ExifData exifData;

};



TEST_F(PrintTagVocabularyMultiTest_187, EmptyValue_187) {

    std::ostringstream os;

    Exiv2::Value value;

    Exiv2::Internal::printTagVocabularyMulti<3>(os, value, &exifData);

    EXPECT_EQ(os.str(), "(0)");

}



TEST_F(PrintTagVocabularyMultiTest_187, SingleKnownValue_187) {

    std::ostringstream os;

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    value->read("1");

    Exiv2::Internal::printTagVocabularyMulti<3>(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Label1");

    delete value;

}



TEST_F(PrintTagVocabularyMultiTest_187, MultipleKnownValues_187) {

    std::ostringstream os;

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    value->read("1 2");

    Exiv2::Internal::printTagVocabularyMulti<3>(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Label1, Label2");

    delete value;

}



TEST_F(PrintTagVocabularyMultiTest_187, SingleUnknownValue_187) {

    std::ostringstream os;

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    value->read("4");

    Exiv2::Internal::printTagVocabularyMulti<3>(os, *value, &exifData);

    EXPECT_EQ(os.str(), "(4)");

    delete value;

}



TEST_F(PrintTagVocabularyMultiTest_187, MixedKnownUnknownValues_187) {

    std::ostringstream os;

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    value->read("1 4 3");

    Exiv2::Internal::printTagVocabularyMulti<3>(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Label1, (4), Label3");

    delete value;

}



TEST_F(PrintTagVocabularyMultiTest_187, BoundaryConditionSingleChar_187) {

    std::ostringstream os;

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    value->read("3");

    Exiv2::Internal::printTagVocabularyMulti<3>(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Label3");

    delete value;

}



TEST_F(PrintTagVocabularyMultiTest_187, BoundaryConditionMultipleChars_187) {

    std::ostringstream os;

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::asciiString);

    value->read("1 2 3");

    Exiv2::Internal::printTagVocabularyMulti<3>(os, *value, &exifData);

    EXPECT_EQ(os.str(), "Label1, Label2, Label3");

    delete value;

}



} // namespace
