#pragma once

#include "complexities/complexity_analyzer.h"

#include <random>

#include "libds/adt/table.h"



namespace ds::utils
{
    /**
     * @brief Common base for list analyzers.
     */
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void growToSize(Table& structure, size_t size) override;
        int key_;
        int data_;

    private:
        std::default_random_engine rngData_;
        std::default_random_engine rngKey_;
    };

    /**
     * @brief Analyzes complexity of an insertion at the beginning.
     */
    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };

    /**
     * @brief Analyzes complexity of an erasure at the beginning.
     */
    template<class Table>
    class TableFindAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };

    /**
     * @brief Container for all list analyzers.
     */
    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer();
    };

    //----------

    template<class Table>
    TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name),
        rngData_(144),
        rngKey_(144),
        key_(0),
        data_(0)
    {
        ComplexityAnalyzer<Table>::registerBeforeOperation([this](Table& table)
            {
                std::uniform_int_distribution dist(1, 1000000);
                this->key_ = dist(this->rngKey_);
                while (table.contains(this->key_)) {
                    this->key_ = dist(this->rngKey_);
                }
                this->data_ = this->rngData_();
            });
    }

    template <class Table>
    void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
    {
        size_t numberOfElements = size - structure.size();
        for (size_t i = 0; i < numberOfElements; ++i)
        {
            std::uniform_int_distribution dist(1, 1000000);
            int key = dist(this->rngKey_);
            int data = this->rngData_();

            while (structure.contains(key))
            {
                key = dist(this->rngKey_);
            }

            structure.insert(key, data);
        }
    }

    //----------

    template <class Table>
    TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {
    }

    template <class Table>
    void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
    {
        structure.insert(this->key_, this->data_);
    }

    //----------

    template <class Table>
    TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {

    }

    template <class Table>
    void TableFindAnalyzer<Table>::executeOperation(Table& structure)
    {
        int* ptr = nullptr;
        structure.tryFind(this->key_, ptr);
    }

    //----------

    inline TablesAnalyzer::TablesAnalyzer() :
        CompositeAnalyzer("Tables")
    {
        this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::SortedSequenceTable<int, int>>>("SST-insert"));
        this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::SortedSequenceTable<int, int>>>("SST-find"));
    }
}
