cmake_minimum_required(VERSION 3.9)
project(libtask)

set(CMAKE_CXX_STANDARD 11)

add_executable(libtask
        386-ucontext.h
        amd64-ucontext.h
        channel.c
        channel.cc
        context.c
        fd.c
        fd.cc
        httpload.c
        mips-ucontext.h
        net.c
        power-ucontext.h
        primes.c
        print.c
        qlock.c
        rendez.c
        task.c
        task.cc
        task.h
        taskimpl.h
        tcpproxy.c
        testdelay.c
        testdelay1.c)
