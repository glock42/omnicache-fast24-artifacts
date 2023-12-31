
#! /bin/bash
set -x

PARAFS=$OFFLOADBASE
DBPATH=/mnt/ram

declare -a workloadarr=("knn")


# Create output directories
if [ ! -d "$RESULTDIR" ]; then
	mkdir -p $RESULTDIR
fi

CLEAN() {
	rm -rf $DBPATH/*
	sudo killall "db_bench"
	sudo killall "db_bench"
	echo "KILLING Rocksdb db_bench"
}

FlushDisk() {
	sudo sh -c "echo 3 > /proc/sys/vm/drop_caches"
	sudo sh -c "sync"
	sudo sh -c "sync"
	sudo sh -c "echo 3 > /proc/sys/vm/drop_caches"
}

RUN() {
    workload=${workloadarr[($2)]}
    output="$AERESULTDIR/$workload/$1"

    if [ ! -d "$output"  ]; then
        mkdir -p $output
    fi


    export HOST_CACHE_LIMIT_ENV=$((16*1024*1024*1024))
    export DEV_CACHE_LIMIT_ENV=$((4*1024*1024*1024))
    #numactl --physcpubind=0-15,32-47 --membind=0 
    $MICROBENCH/knn//build/knn_hybrid $1  | tee $output/result.txt
    unset HOST_CACHE_LIMIT_ENV
    unset DEV_CACHE_LIMIT_ENV
    sleep 1
}

declare -a typearr=("0")
declare -a threadarr=("16" "32")
#declare -a threadarr=("4")
for size in "${typearr[@]}"
do
    for thrd in "${threadarr[@]}"
    do
        CLEAN
        FlushDisk
        RUN $thrd $size
    done
done
