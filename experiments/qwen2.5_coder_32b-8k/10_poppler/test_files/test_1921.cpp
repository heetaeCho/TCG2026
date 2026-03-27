#include <gtest/gtest.h>

#include "PDFDoc.h"

#include "Outline.h"

#include "XRef.h"

#include "Catalog.h"



// Mock classes for testing purposes

class MockDocument : public PDFDoc {

public:

    MockDocument() {

        // Initialize necessary objects for the test

        xref = new XRef();

        catalog = new Catalog(xref);

        outline = new Outline(catalog->getOutlineDict(), xref);

    }

    

    ~MockDocument() {

        delete outline;

        delete catalog;

        delete xref;

    }



    XRef* getXRef() const override { return xref; }

    Catalog* getCatalog() const override { return catalog; }

    Outline* getOutline() const override { return outline; }



private:

    XRef* xref = nullptr;

    Catalog* catalog = nullptr;

    Outline* outline = nullptr;

};



// Test case for adding an outline item

TEST(OutlineTest, AddOutlineItem) {

    MockDocument doc;

    Outline& outline = *doc.getOutline();

    

    Ref parentRef = {1, 0}; // Assuming a valid reference to the parent outline item

    std::string title = "New Section";

    int destPageNum = 3; 

    std::string objName = "Fit"; // Destination type

    OutlineItem* newItem = new OutlineItem(&title, objName.c_str(), parentRef, destPageNum);

    

    outline.insert(newItem, nullptr); // Insert at the end of the children

    

    EXPECT_EQ(outline.getNumItems(), 1);

    EXPECT_STREQ(outline.getItem(0)->getTitle()->c_str(), title.c_str());

}



// Test case for finding an outline item by title

TEST(OutlineTest, FindOutlineItemByTitle) {

    MockDocument doc;

    Outline& outline = *doc.getOutline();

    

    Ref parentRef = {1, 0}; // Assuming a valid reference to the parent outline item

    std::string title = "Searchable Section";

    int destPageNum = 5; 

    std::string objName = "Fit"; // Destination type

    

    OutlineItem* searchableItem = new OutlineItem(&title, objName.c_str(), parentRef, destPageNum);

    outline.insert(searchableItem, nullptr); // Insert at the end of the children

    

    OutlineItem* foundItem = outline.find(title.c_str());

    

    EXPECT_NE(foundItem, nullptr);

    EXPECT_STREQ(foundItem->getTitle()->c_str(), title.c_str());

}



// Test case for removing an outline item

TEST(OutlineTest, RemoveOutlineItem) {

    MockDocument doc;

    Outline& outline = *doc.getOutline();

    

    Ref parentRef = {1, 0}; // Assuming a valid reference to the parent outline item

    std::string title = "ToRemove";

    int destPageNum = 4; 

    std::string objName = "Fit"; // Destination type

    

    OutlineItem* removableItem = new OutlineItem(&title, objName.c_str(), parentRef, destPageNum);

    outline.insert(removableItem, nullptr); // Insert at the end of the children

    

    outline.remove(removableItem);

    

    EXPECT_EQ(outline.getNumItems(), 0);

}



// Test case for getting number of items in an empty outline

TEST(OutlineTest, GetNumberOfItemsInEmptyOutline) {

    MockDocument doc;

    Outline& outline = *doc.getOutline();

    

    EXPECT_EQ(outline.getNumItems(), 0);

}
