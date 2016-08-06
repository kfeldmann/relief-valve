#!/bin/sh

if [ "x$1" != "x" ]; then
    SLEEP=$1
else
    SLEEP=1
fi

echo "`date -u +%Y-%m-%dT%H:%M:%S%z` test-app.sh: INFO: ======== STARTUP (pid $$) ========"
while true; do
    echo `date -u +%Y-%m-%dT%H:%M:%S%z` test-app.sh: HEARTBEAT
    echo `date -u +%Y-%m-%dT%H:%M:%S%z`test-app.sh: sleep time = $SLEEP seconds
    sleep $SLEEP
    #t=`echo $t + 2 | bc`
done

