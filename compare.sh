#!/bin/bash

# We compare the original file with the two decoded files

diff ./output/original.csv ./output/decoded_3_3_1.csv

diff ./output/original.csv ./output/decoded_3_3_2.csv
