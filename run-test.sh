#!/bin/sh

./test-app.sh 0.01 2>/dev/null | ./rv 2>/dev/null | ./test-logger.sh 3 4 
