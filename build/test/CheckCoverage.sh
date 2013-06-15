#!/bin/bash

DIRECTORY=./coverage
BUILD_TYPE=Debug
BROWSE=Yes

#make a directory $DIRECTORY if it doesn't exist
if [ ! -d "$DIRECTORY" ]; then
    mkdir -p $DIRECTORY
fi

#clean the old output
rm -rf $DIRECTORY/*

#perform the coverage check
lcov  --capture --directory . --output-file $DIRECTORY/gcov.info

#hacking the gcov info file to eliminate unwanted results (from usr/include, from cxxtest, from stockfish and from the single test runner) 
sed '/SF:\/usr\/.*include/,/end_of_record/d' $DIRECTORY/gcov.info > $DIRECTORY/gcov_parsed.info
sed '/cxxtest/,/end_of_record/d' $DIRECTORY/gcov_parsed.info > $DIRECTORY/gcov.info
sed '/stockfish/,/end_of_record/d' $DIRECTORY/gcov.info > $DIRECTORY/gcov_parsed.info
sed '/single_test_runner/,/end_of_record/d' $DIRECTORY/gcov_parsed.info > $DIRECTORY/gcov.info

#generate html output
genhtml $DIRECTORY/gcov.info --branch-coverage --output-directory $DIRECTORY

#display, if we are running this as an individual test
if [ "$BROWSE" = "Yes" ]; then
    firefox $DIRECTORY/index.html
fi