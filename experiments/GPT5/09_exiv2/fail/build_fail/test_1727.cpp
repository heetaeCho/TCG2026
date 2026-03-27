#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "sigmamnn_int.hpp" // Include the header file of SigmaMakerNote class

namespace Exiv2 {
    namespace Internal {
        class SigmaMakerNoteTest : public testing::Test {
        protected:
            SigmaMakerNote sigmaMakerNote;
        };
        
        // TEST_ID: 1727
        TEST_F(SigmaMakerNoteTest, Print0x0009_HandlesAverage_1727) {
            std::ostringstream os;
            Value value("Average");
            ExifData* exifData = nullptr;
            
            // Test when value is "Average"
            sigmaMakerNote.print0x0009(os, value, exifData);
            
            // Verify the output stream content
            EXPECT_EQ(os.str(), "Average");
        }
        
        // TEST_ID: 1728
        TEST_F(SigmaMakerNoteTest, Print0x0009_HandlesCenter_1728) {
            std::ostringstream os;
            Value value("Center");
            ExifData* exifData = nullptr;
            
            // Test when value is "Center"
            sigmaMakerNote.print0x0009(os, value, exifData);
            
            // Verify the output stream content
            EXPECT_EQ(os.str(), "Center");
        }
        
        // TEST_ID: 1729
        TEST_F(SigmaMakerNoteTest, Print0x0009_Handles8Segment_1729) {
            std::ostringstream os;
            Value value("8-Segment");
            ExifData* exifData = nullptr;
            
            // Test when value is "8-Segment"
            sigmaMakerNote.print0x0009(os, value, exifData);
            
            // Verify the output stream content
            EXPECT_EQ(os.str(), "8-Segment");
        }
        
        // TEST_ID: 1730
        TEST_F(SigmaMakerNoteTest, Print0x0009_HandlesDefaultCase_1730) {
            std::ostringstream os;
            Value value("Unknown");
            ExifData* exifData = nullptr;
            
            // Test when value doesn't match any specific case
            sigmaMakerNote.print0x0009(os, value, exifData);
            
            // Verify the output stream content
            EXPECT_EQ(os.str(), "(Unknown)");
        }
    }
}