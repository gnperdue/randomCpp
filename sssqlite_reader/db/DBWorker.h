#ifndef DBWorker_h
#define DBWorker_h
/*! \file DBWorker.h
*/

#include <sqlite3.h>
#include <vector>

class DBWorker {

    private:
        sqlite3 *data_base;
        bool db_is_available;
        int acquire_resources();
        int release_resources();
        double get_segment_probability(int segment, int run, int subrun,
                int gate, int phys_evt) const;

    public:
        explicit DBWorker();
        ~DBWorker();
        int get_segment_prediction(int run, int subrun,
                int gate, int phys_evt) const;
        std::vector<double> get_segment_probabilities(int run, int subrun,
                int gate, int phys_evt) const;

};

#endif
