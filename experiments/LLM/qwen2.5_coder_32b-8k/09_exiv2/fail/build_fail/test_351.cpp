#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeDataEntry, (TiffDataEntry* object, const Exifdatum* datum), (override));

};



class TiffDataEntryTest_351 : public ::testing::Test {

protected:

    TiffDataEntry tiffDataEntry;

    MockTiffEncoder mockEncoder;

    std::unique_ptr<Exifdatum> exifdatum;



    void SetUp() override {

        ExifKey key("Exif.Image.Artist");

        Value* value = new StringValue("John Doe");

        exifdatum.reset(new Exifdatum(key, value));

    }

};



TEST_F(TiffDataEntryTest_351, DoEncode_CallsEncoderMethod_351) {

    EXPECT_CALL(mockEncoder, encodeDataEntry(&tiffDataEntry, exifdatum.get())).Times(1);

    tiffDataEntry.doEncode(mockEncoder, exifdatum.get());

}



// Boundary conditions and exceptional cases are not directly observable through the interface

// given in this context. Thus, we focus on normal operation as per constraints.

```


