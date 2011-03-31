#include <pthread.h>
#include <signal.h>

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "options.h"
#include "server.h"

sigset_t block_signals()
{
    sigset_t new_mask;
    sigfillset(&new_mask);
    sigset_t old_mask;
    pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);
    return old_mask;
}

void restore_signals(sigset_t mask)
{
    pthread_sigmask(SIG_SETMASK, &mask, 0);
}

void wait_for_signal()
{
    sigset_t wait_mask;
    sigemptyset(&wait_mask);
    sigaddset(&wait_mask, SIGINT);
    sigaddset(&wait_mask, SIGQUIT);
    sigaddset(&wait_mask, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
    int sig = 0;
    sigwait(&wait_mask, &sig);
}

int main(int argc, char* argv[])
{
    // parse options
    addpd::options options(argc, argv);

    // create server
    server s(options.port(), options.multicast());

    // run server in background thread
    sigset_t sigmask = block_signals();
    boost::thread t(boost::bind(&server::run, &s));
    restore_signals(sigmask);

    // wait for signal to terminate
    wait_for_signal();

    // stop the server
    s.stop();
    t.join();

    return 0;
}
