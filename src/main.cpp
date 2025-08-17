/**
 * BranchDB – An in-memory key-value database
 * with TTL, disk persistence.
 *
 * © 2025 KHAMITKAR SAI CHANDAN
 * Licensed under the Apache License, Version 2.0.
 * You may obtain a copy at:
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * You must retain this header in any redistribution or modification.
 */

#include <branchdb/db/database.h>
#include <branchdb/persistent_connect/persistent_connect.h>
#include <csignal>
#include <thread>
#include <boost/asio.hpp>

using namespace std;
using namespace chrono;

void handleSigint(int signal)
{
    cout << endl << "Data stored to DISK successfully, Status:[OK]" << endl;
}

int main()
{
    branchdb::Database db;
    signal(SIGINT, handleSigint);
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1981));

    cout << "TCP server started, listening at port: 1981" << endl;

    // Open to listen from clients
    while(true){
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        thread(persistent_connect::handle_client, move(socket), ref(db)).detach();
    }
    return 0;
}