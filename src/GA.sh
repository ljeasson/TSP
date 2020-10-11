#!/bin/bash
rm outfile
g++ -o ga *.cpp -I. -lm
./ga berlin52.tsp 500
python3 gagraph.py
