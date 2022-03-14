#include "../../source/Common/Table.h"
#include <memory>
#include <vector>

struct ShopTable
{
    std::unique_ptr<Table> tab;

    ShopTable()
    {
        tab = std::make_unique<Table>("Shops", "1");
        tab->columns = std::vector<std::string>{"id", "shop", "category", "floor"};
        std::vector<std::string> a{"1", "Rossman", "Beauty", "1"};
        std::vector<std::string> b{"2", "H&M", "Fashion", "1"};
        std::vector<std::string> c{"3", "C&A", "Fashion", "1"};
        std::vector<std::string> d{"4", "NewYorker", "Fashion", "2"};
        std::vector<std::string> e{"5", "Biedronka", "Supermarket", "2"};
        tab->rows.push_back(a);
        tab->rows.push_back(b);
        tab->rows.push_back(c);
        tab->rows.push_back(d);
        tab->rows.push_back(e);
    }
};

struct WorkersTable
{
    std::unique_ptr<Table> tab;

    WorkersTable()
    {
        tab = std::make_unique<Table>("Workers", "1");
        tab->columns = std::vector<std::string>{"worker_id", "work_place", "name", "surname"};
        std::vector<std::string> a{"1", "Rossman", "Adam", "Waters"};
        std::vector<std::string> b{"2", "Rossman", "Joseph", "Eilish" };
        std::vector<std::string> c{"3", "Rossman", "Anna", "Scott" };
        std::vector<std::string> d{"4", "H&M", "Jeronimo", "Kardashian" };
        std::vector<std::string> e{"5", "H&M", "Thomas", "Biden" };
        std::vector<std::string> f{"6", "C&A", "Josh", "Trump" };
        std::vector<std::string> g{"7", "NewYorker", "Rue", "Zendaya"};
        std::vector<std::string> h{"8", "NewYorker", "Blanca", "Wellington" };
        std::vector<std::string> i{"9", "NewYorker", "Jessica" ,"Bread"};
        std::vector<std::string> j{"10", "NewYorker", "Sara", "Priker"};
        std::vector<std::string> k{"10", "NewYorker", "Hannah", "Kowalski"};
        std::vector<std::string> l{"10", "Biedronka", "Joey", "Smith"};
        tab->rows.push_back(a);
        tab->rows.push_back(b);
        tab->rows.push_back(c);
        tab->rows.push_back(d);
        tab->rows.push_back(e);
        tab->rows.push_back(f);
        tab->rows.push_back(g);
        tab->rows.push_back(h);
        tab->rows.push_back(i);
        tab->rows.push_back(j);
        tab->rows.push_back(k);
        tab->rows.push_back(l);
    }
};
