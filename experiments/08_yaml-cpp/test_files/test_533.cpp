#include <gtest/gtest.h>

#include "yaml-cpp/emitter.cpp"



namespace YAML {

    TEST_F(GetStringEscapingStyleTest_533, DefaultCase_ReturnsNone_533) {

        EMITTER_MANIP manip = Auto;

        EXPECT_EQ(StringEscaping::None, GetStringEscapingStyle(manip));

    }



    TEST_F(GetStringEscapingStyleTest_533, EscapeNonAscii_ReturnsNonAscii_533) {

        EMITTER_MANIP manip = EscapeNonAscii;

        EXPECT_EQ(StringEscaping::NonAscii, GetStringEscapingStyle(manip));

    }



    TEST_F(GetStringEscapingStyleTest_533, EscapeAsJson_ReturnsJSON_533) {

        EMITTER_MANIP manip = EscapeAsJson;

        EXPECT_EQ(StringEscaping::JSON, GetStringEscapingStyle(manip));

    }



    TEST_F(GetStringEscapingStyleTest_533, InvalidEnumValue_ReturnsNone_533) {

        EMITTER_MANIP manip = static_cast<EMITTER_MANIP>(100); // Assuming 100 is an invalid value

        EXPECT_EQ(StringEscaping::None, GetStringEscapingStyle(manip));

    }

}
