#include "gtest/gtest.h"

#include "../../source/Common/DataBaseTable.h"
#include "../../source/Common/DataBaseTable.cpp"

void getShopTable(Table&tab)
{
    tab.columns = std::vector<std::string>{"id", "shop", "category", "floor"};
    tab.rows.push_back(std::vector<std::string>{"1", "Rossman", "Beauty", "1"});
    tab.rows.push_back({"2", "H&M", "Fashion", "1"});
    tab.rows.push_back({"3", "C&A", "Fashion", "1"});
    tab.rows.push_back({"4", "NewYorker", "Fashion", "2"});
    tab.rows.push_back({"5", "Biedronka", "Supermarket", "2"});
}

TEST(DATA_BASE_TABLE,Hello){
    ASSERT_EQ("Hello","Hello");
}

TEST(DATA_BASE_TABLE,ADD_ROW){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    const int noElementsAfterAddingOneRow=db.getTableDataForReadOnly().rows.size()+1;
    std::vector<std::string> newVector{"6", "Carefour", "Supermarket", "0"};
    db.addRow(std::move(newVector));
    const int noElements=db.getTableDataForReadOnly().rows.size();
    ASSERT_EQ(noElements,noElementsAfterAddingOneRow);
}

TEST(DATA_BASE_TABLE,ADD_ROW_TABLE_EQUALS){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> newVector{"6", "Carefour", "Supermarket", "0"};
    db.addRow(std::move(newVector));
    std::vector<std::string> entities;
    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"1", "Rossman", "Beauty", "1","2", "H&M", "Fashion", "1","3", "C&A", "Fashion", "1","4", "NewYorker", "Fashion", "2","5", "Biedronka", "Supermarket", "2","6", "Carefour", "Supermarket", "0"};
    ASSERT_EQ(expected,entities);
}

TEST(DATA_BASE_TABLE,DELETE_ROW_FULL_ROW_EQUALS_GIVEN){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> toDelete{"1", "Rossman", "Beauty", "1"};
    db.findAndRemoveIfEquals({"id", "shop", "category", "floor"},{"=","=","=","="},toDelete);
    std::vector<std::string>entities;

    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"2", "H&M", "Fashion", "1","3", "C&A", "Fashion", "1","4", "NewYorker", "Fashion", "2","5", "Biedronka", "Supermarket", "2"};
    ASSERT_EQ(expected,entities);
}

TEST(DATA_BASE_TABLE,DELETE_ROW_NOT_FULL_ROW_GIVEN_EQUALS){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> toDelete{"1", "1"};
    db.findAndRemoveIfEquals({"id", "floor"},{"=","="},toDelete);
    std::vector<std::string>entities;

    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"2", "H&M", "Fashion", "1","3", "C&A", "Fashion", "1","4", "NewYorker", "Fashion", "2","5", "Biedronka", "Supermarket", "2"};
    ASSERT_EQ(expected,entities);
}

TEST(DATA_BASE_TABLE,DELETE_ROW_NOT_FULL_ROW_GIVEN_LOWER){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> toDelete{"2"};
    db.findAndRemoveIfEquals({"id"},{">"},toDelete);
    std::vector<std::string>entities;

    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"2", "H&M", "Fashion", "1","3", "C&A", "Fashion", "1","4", "NewYorker", "Fashion", "2","5", "Biedronka", "Supermarket", "2"};
    ASSERT_EQ(expected,entities);
}

TEST(DATA_BASE_TABLE,DELETE_ROW_NOT_FULL_ROW_GIVEN_LOWER_AND_EQUALS){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> toDelete{"Fashion","2"};
    db.findAndRemoveIfEquals({"category","floor"},{"=",">"},toDelete);
    std::vector<std::string>entities;

    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"1", "Rossman", "Beauty", "1", "4", "NewYorker", "Fashion", "2", "5", "Biedronka", "Supermarket", "2" };
    ASSERT_EQ(expected,entities);
}

TEST(DATA_BASE_TABLE,DELETE_ROW_NOT_FULL_ROW_GIVEN_GREATER_AND_EQUALS){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> toDelete{"Fashion","1"};
    db.findAndRemoveIfEquals({"category","floor"},{"=","<"},toDelete);
    std::vector<std::string>entities;

    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"1", "Rossman", "Beauty", "1","2", "H&M", "Fashion", "1","3", "C&A", "Fashion", "1","5", "Biedronka", "Supermarket", "2"};
    ASSERT_EQ(expected,entities);
}

TEST(DATA_BASE_TABLE,UPDATE_ROW_EQUALS_FULL_ROW_GIVEN){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> toUpdate{"1", "Rossman", "Beauty", "1"};
    db.findRowsAndUpdate({"id", "shop", "category", "floor"},{"=","=","=","="},toUpdate,{"xd","xd","xd","xd"});
    std::vector<std::string>entities;

    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"xd","xd","xd","xd","2", "H&M", "Fashion", "1","3", "C&A", "Fashion", "1","4", "NewYorker", "Fashion", "2","5", "Biedronka", "Supermarket", "2"};
    ASSERT_EQ(expected,entities);
}

TEST(DATA_BASE_TABLE,UPDATE_ROW_EQUALS_NOT_FULL_ROW_GIVEN_LOWER){
    Table table("Shops","1");
    getShopTable(table);
    DataBaseTable db (std::move(table));
    std::vector<std::string> toUpdate{"3"};
    db.findRowsAndUpdate({"id"},{">"},toUpdate,{"xd"});
    std::vector<std::string>entities;

    auto tab=db.getTableDataForReadOnly();
    for(const auto& it:tab.rows){
        std::vector<std::string> buffer=it;
        entities.insert(entities.end(),buffer.begin(),buffer.end());
    }
    std::vector<std::string> expected{"xd", "Rossman", "Beauty", "1", "xd", "H&M", "Fashion", "1", "3", "C&A", "Fashion", "1", "4", "NewYorker", "Fashion", "2", "5", "Biedronka", "Supermarket", "2"};
    ASSERT_EQ(expected,entities);
}