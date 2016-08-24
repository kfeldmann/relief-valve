#!/bin/sh

./test-app.sh 0 | ./rv | ./test-logger.sh 60 65
