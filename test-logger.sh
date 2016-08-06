#!/bin/sh -e


if [ "x$1" != "x" ]; then
    SLEEP=$1
else
    SLEEP=5
fi

if [ "x$2" != "x" ]; then
    INTERVAL=$2
else
    INTERVAL=10
fi

last=`date +%s`

echo "`date -u +%Y-%m-%dT%H:%M:%S%z` test-logger.sh: INFO: ======== STARTUP (pid $$) ========"
while true; do
    read line
    if [ "x$?" != "x0" ]; then
        exit
    fi
    now=`date +%s`
    since=`echo "$now - $last" | bc`
    echo `date -u +%Y-%m-%dT%H:%M:%S%z` LOGGER: $line
    echo `date -u +%Y-%m-%dT%H:%M:%S%z` LOGGER: since = $since, interval = $INTERVAL
    if [ $since -gt $INTERVAL ]; then
        echo `date -u +%Y-%m-%dT%H:%M:%S%z` LOGGER: SLEEPING $SLEEP SECONDS
        sleep $SLEEP
        last=$now
    fi
done

