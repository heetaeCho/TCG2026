#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// We need to include the relevant Catch2 headers to access the types
// Since we're working with the partial code, we need to define/include the necessary types

namespace Catch {

enum class Justification { Left, Right };

struct ColumnInfo {
    std::string name;
    int width;
    Justification justification;
    
    bool operator==(const ColumnInfo& other) const {
        return name == other.name && width == other.width && justification == other.justification;
    }
};

class TablePrinter {
private:
    std::ostream& m_os;
    std::vector<ColumnInfo> m_columnInfos;
    int m_currentColumn = -1;
    bool m_isOpen = false;

public:
    TablePrinter(std::ostream& os, std::vector<ColumnInfo> columnInfos)
        : m_os(os), m_columnInfos(std::move(columnInfos)) {}

    auto columnInfos() const -> std::vector<ColumnInfo> const& {
        return m_columnInfos;
    }

    void open() {
        m_isOpen = true;
        m_currentColumn = 0;
    }

    void close() {
        m_isOpen = false;
        m_currentColumn = -1;
    }
};

} // namespace Catch

// Test fixture
class TablePrinterTest_755 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(TablePrinterTest_755, DefaultConstructedWithEmptyColumnInfos_755) {
    std::vector<Catch::ColumnInfo> emptyInfos;
    Catch::TablePrinter printer(oss, emptyInfos);
    
    EXPECT_TRUE(printer.columnInfos().empty());
}

TEST_F(TablePrinterTest_755, ColumnInfosReturnsSameAsProvided_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"Name", 20, Catch::Justification::Left},
        {"Value", 10, Catch::Justification::Right}
    };
    
    Catch::TablePrinter printer(oss, infos);
    
    const auto& result = printer.columnInfos();
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].name, "Name");
    EXPECT_EQ(result[0].width, 20);
    EXPECT_EQ(result[0].justification, Catch::Justification::Left);
    EXPECT_EQ(result[1].name, "Value");
    EXPECT_EQ(result[1].width, 10);
    EXPECT_EQ(result[1].justification, Catch::Justification::Right);
}

TEST_F(TablePrinterTest_755, ColumnInfosReturnsConstReference_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"Col1", 15, Catch::Justification::Left}
    };
    
    Catch::TablePrinter printer(oss, infos);
    
    const auto& ref1 = printer.columnInfos();
    const auto& ref2 = printer.columnInfos();
    
    // Both calls should return reference to the same internal vector
    EXPECT_EQ(&ref1, &ref2);
}

TEST_F(TablePrinterTest_755, SingleColumnInfo_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"SingleCol", 5, Catch::Justification::Right}
    };
    
    Catch::TablePrinter printer(oss, infos);
    
    ASSERT_EQ(printer.columnInfos().size(), 1u);
    EXPECT_EQ(printer.columnInfos()[0].name, "SingleCol");
    EXPECT_EQ(printer.columnInfos()[0].width, 5);
    EXPECT_EQ(printer.columnInfos()[0].justification, Catch::Justification::Right);
}

TEST_F(TablePrinterTest_755, ManyColumnInfos_755) {
    std::vector<Catch::ColumnInfo> infos;
    for (int i = 0; i < 100; ++i) {
        infos.push_back({"Col" + std::to_string(i), i + 1, Catch::Justification::Left});
    }
    
    Catch::TablePrinter printer(oss, infos);
    
    ASSERT_EQ(printer.columnInfos().size(), 100u);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(printer.columnInfos()[i].name, "Col" + std::to_string(i));
        EXPECT_EQ(printer.columnInfos()[i].width, i + 1);
    }
}

TEST_F(TablePrinterTest_755, ColumnInfosPreservedAfterOpen_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"A", 10, Catch::Justification::Left},
        {"B", 20, Catch::Justification::Right}
    };
    
    Catch::TablePrinter printer(oss, infos);
    printer.open();
    
    ASSERT_EQ(printer.columnInfos().size(), 2u);
    EXPECT_EQ(printer.columnInfos()[0].name, "A");
    EXPECT_EQ(printer.columnInfos()[1].name, "B");
}

TEST_F(TablePrinterTest_755, ColumnInfosPreservedAfterClose_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"X", 30, Catch::Justification::Right}
    };
    
    Catch::TablePrinter printer(oss, infos);
    printer.open();
    printer.close();
    
    ASSERT_EQ(printer.columnInfos().size(), 1u);
    EXPECT_EQ(printer.columnInfos()[0].name, "X");
    EXPECT_EQ(printer.columnInfos()[0].width, 30);
}

TEST_F(TablePrinterTest_755, ColumnInfosWithEmptyName_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"", 0, Catch::Justification::Left}
    };
    
    Catch::TablePrinter printer(oss, infos);
    
    ASSERT_EQ(printer.columnInfos().size(), 1u);
    EXPECT_EQ(printer.columnInfos()[0].name, "");
    EXPECT_EQ(printer.columnInfos()[0].width, 0);
}

TEST_F(TablePrinterTest_755, ColumnInfosWithNegativeWidth_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"NegWidth", -5, Catch::Justification::Left}
    };
    
    Catch::TablePrinter printer(oss, infos);
    
    ASSERT_EQ(printer.columnInfos().size(), 1u);
    EXPECT_EQ(printer.columnInfos()[0].width, -5);
}

TEST_F(TablePrinterTest_755, OriginalVectorModificationDoesNotAffectPrinter_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"Original", 10, Catch::Justification::Left}
    };
    
    Catch::TablePrinter printer(oss, infos);
    
    // Modify the original vector after construction
    infos.push_back({"Added", 20, Catch::Justification::Right});
    infos[0].name = "Modified";
    
    // The printer should still have the original data
    ASSERT_EQ(printer.columnInfos().size(), 1u);
    EXPECT_EQ(printer.columnInfos()[0].name, "Original");
}

TEST_F(TablePrinterTest_755, OpenAndCloseDoNotChangeColumnInfos_755) {
    std::vector<Catch::ColumnInfo> infos = {
        {"Col1", 10, Catch::Justification::Left},
        {"Col2", 20, Catch::Justification::Right},
        {"Col3", 30, Catch::Justification::Left}
    };
    
    Catch::TablePrinter printer(oss, infos);
    
    auto before = printer.columnInfos();
    
    printer.open();
    auto duringOpen = printer.columnInfos();
    
    printer.close();
    auto afterClose = printer.columnInfos();
    
    EXPECT_EQ(before, duringOpen);
    EXPECT_EQ(duringOpen, afterClose);
}
