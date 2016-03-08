#ifndef DBWorker_cxx
#define DBWorker_cxx
/*! \file DBWorker.cpp
*/

#include "DBWorker.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>

//----------------------------------------------------------------------------
DBWorker::DBWorker():
    data_base(NULL),
    db_is_available(false)
{
    int rc = this->acquire_resources();
    if (0 != rc) {
        std::cerr << "db open error code: " << rc << std::endl;
    }
}

//----------------------------------------------------------------------------
DBWorker::~DBWorker()
{
    int rc = this->release_resources();
    if (0 != rc) {
        std::cerr << "db open error code: " << rc << std::endl;
    }
}

//----------------------------------------------------------------------------
int DBWorker::acquire_resources()
{
    // const char * db_file_name = "file:prediction1457237432.db?nolock=1";
    const char * db_file_name = "/afs/fnal.gov/files/home/room1/perdue/prediction1457237432.db";
    char * vfs_name = NULL;
    int rc = 0;
    int flags = SQLITE_OPEN_READONLY;
    // int flags = SQLITE_OPEN_READONLY|SQLITE_OPEN_URI;
    // int flags = SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE;

    sqlite3_initialize();
    rc = sqlite3_open_v2(db_file_name, &data_base, flags, vfs_name);
    if (SQLITE_OK == rc) {
        db_is_available = true;
    }
    else {
        sqlite3_close(data_base);
    }

    return rc;
}

//----------------------------------------------------------------------------
int DBWorker::release_resources()
{
    int rc = sqlite3_close(data_base);
    rc = sqlite3_shutdown();
    db_is_available = false;

    return rc;
}

//----------------------------------------------------------------------------
int DBWorker::get_segment_prediction(int run, int subrun,
        int gate, int phys_evt) const
{
    if (!db_is_available) return SQLITE_ERROR;

    int segment = -1;
    sqlite3_stmt *stmt = NULL;
    int idx = -1;
    const char * sqlstr =
        "SELECT segment FROM zsegment_prediction WHERE \
        run = :run AND \
        subrun = :subrun AND \
        gate = :gate AND \
        phys_evt = :phys_evt;";

    int rc = sqlite3_prepare_v2(data_base, sqlstr, -1, &stmt, NULL);
    if (SQLITE_OK != rc) {
        std::cerr << "db statement prepare error code = "
            << rc << std::endl;
        return rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":run");
    rc = sqlite3_bind_int(stmt, idx, run);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for run failed with rc = "
            << rc << std::endl;
        return rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":subrun");
    rc = sqlite3_bind_int(stmt, idx, subrun);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for subrun failed with rc = "
            << rc << std::endl;
        return rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":gate");
    rc = sqlite3_bind_int(stmt, idx, gate);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for gate failed with rc = "
            << rc << std::endl;
        return rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":phys_evt");
    rc = sqlite3_bind_int(stmt, idx, phys_evt);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for phys_evt failed with rc = " 
            << rc << std::endl;
        return rc;
    }

    rc = sqlite3_step(stmt);
    if ((SQLITE_DONE != rc ) && (SQLITE_ROW != rc )) {
        std::cerr << "sqlite3_step AddRunDataToDB failed with rc = "
            << rc << std::endl;
        return rc;
    }
    segment = sqlite3_column_int(stmt, 0);

    sqlite3_reset(stmt); // reset probably unnecessary since we done anyway
    sqlite3_clear_bindings(stmt);

    sqlite3_finalize(stmt);
    stmt = NULL;

    return segment;
}

//----------------------------------------------------------------------------
double DBWorker::get_segment_probability(int segment, int run, int subrun,
        int gate, int phys_evt) const
{
    if (!db_is_available) return (double)SQLITE_ERROR;

    sqlite3_stmt *stmt = NULL;
    int idx = -1;
    std::stringstream ss;
    char sqlstr[300];
    ss << "SELECT prob" << std::setfill('0') << std::setw(2) << segment <<
        " FROM zsegment_prediction WHERE " <<
        " run = :run AND " <<
        " subrun = :subrun AND " <<
        " gate = :gate AND " <<
        " phys_evt = :phys_evt;";
    const std::string& tmp = ss.str();
    sprintf(sqlstr, tmp.c_str());
    double probability = -1.0;

    int rc = sqlite3_prepare_v2(data_base, sqlstr, -1, &stmt, NULL);
    if (SQLITE_OK != rc) {
        std::cerr << "db statement prepare error code = "
            << rc << std::endl;
        return (double)rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":run");
    rc = sqlite3_bind_int(stmt, idx, run);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for run failed with rc = "
            << rc << std::endl;
        return (double)rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":subrun");
    rc = sqlite3_bind_int(stmt, idx, subrun);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for subrun failed with rc = "
            << rc << std::endl;
        return (double)rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":gate");
    rc = sqlite3_bind_int(stmt, idx, gate);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for gate failed with rc = "
            << rc << std::endl;
        return (double)rc;
    }

    idx = sqlite3_bind_parameter_index(stmt, ":phys_evt");
    rc = sqlite3_bind_int(stmt, idx, phys_evt);
    if (SQLITE_OK != rc) {
        std::cerr << "sqlite3_bind for phys_evt failed with rc = " 
            << rc << std::endl;
        return (double)rc;
    }

    rc = sqlite3_step(stmt);
    if ((SQLITE_DONE != rc ) && (SQLITE_ROW != rc )) {
        std::cerr << "sqlite3_step AddRunDataToDB failed with rc = "
            << rc << std::endl;
        return (double)rc;
    }
    probability = sqlite3_column_double(stmt, 0);

    sqlite3_reset(stmt); // reset probably unnecessary since we done anyway
    sqlite3_clear_bindings(stmt);

    sqlite3_finalize(stmt);
    stmt = NULL;

    return probability;
}


//----------------------------------------------------------------------------
std::vector<double> DBWorker::get_segment_probabilities(int run, int subrun, 
        int gate, int phys_evt) const
{
    std::vector<double> probs;
    for (int i = 0; i < 11; ++i) {
        probs.push_back(this->get_segment_probability(i, run, subrun,
                    gate, phys_evt));
    }
    return probs;
}

#endif
