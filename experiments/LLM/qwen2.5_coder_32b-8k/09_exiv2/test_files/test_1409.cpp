#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TagsIntTest_1409 : public ::testing::Test {

protected:

    ExifData metadata_;

    Value value_{TypeId::asciiString};

};



TEST_F(TagsIntTest_1409, PrintValidTagDetails_1409) {

    std::ostringstream os;

    print0xa300(os, value_, &metadata_);

    EXPECT_TRUE(os.str().find("Film scanner") != std::string::npos ||

                os.str().find("Reflexion print scanner") != std::string::npos ||

                os.str().find("Digital still camera") != std::string::npos);

}



TEST_F(TagsIntTest_1409, PrintInvalidTagDetails_1409) {

    TagDetails invalidTag = {4, "Unknown"};

    Exiv2::Internal::exifFileSource[0] = invalidTag;

    std::ostringstream os;

    print0xa300(os, value_, &metadata_);

    EXPECT_EQ(os.str(), "");

}



TEST_F(TagsIntTest_1409, EmptyMetadata_1409) {

    metadata_.clear();

    std::ostringstream os;

    print0xa300(os, value_, &metadata_);

    EXPECT_TRUE(os.str().empty());

}



TEST_F(TagsIntTest_1409, MetadataWithNoExifData_1409) {

    ExifData emptyMetadata;

    std::ostringstream os;

    print0xa300(os, value_, &emptyMetadata);

    EXPECT_TRUE(os.str().empty());

}

```


