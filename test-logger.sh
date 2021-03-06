#!/bin/sh -e

# Copyright (c) 2016, Kris Feldmann
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#   1. Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
# 
#   2. Redistributions in binary form must reproduce the above
#      copyright notice, this list of conditions and the following
#      disclaimer in the documentation and/or other materials provided
#      with the distribution.
# 
#   3. Neither the name of the copyright holder nor the names of its
#      contributors may be used to endorse or promote products derived
#      from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
# PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
# OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


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

