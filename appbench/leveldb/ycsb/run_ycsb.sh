#!/bin/bash

src_dir=`readlink -f ../../`
cur_dir=`readlink -f ./`
setup_dir=`readlink -f ../configs`
pmem_dir=/mnt/ram

run_ycsb()
{
    fs=$1
    for run in 1
    do
        #sudo rm -rf $pmem_dir/*
        #sudo taskset -c 0-7 ./run_fs.sh LoadA $fs $run
        #sleep 5
        sudo taskset -c 0-7 ./run_fs.sh RunA $fs $run
        sleep 5
        sudo taskset -c 0-7 ./run_fs.sh RunB $fs $run
        sleep 5
        sudo taskset -c 0-7 ./run_fs.sh RunC $fs $run
        sleep 5
        sudo taskset -c 0-7 ./run_fs.sh RunF $fs $run
        sleep 5
        sudo taskset -c 0-7 ./run_fs.sh RunD $fs $run
        sleep 5
        sudo taskset -c 0-7 ./run_fs.sh LoadE $fs $run
        sleep 5
        sudo taskset -c 0-7 ./run_fs.sh RunE $fs $run
        sleep 5
    done
}

run_ycsb hostcache 

