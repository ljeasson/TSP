#!/bin/bash
rm outfile
g++ -o ga *.cpp -I. -lm

./ga berlin52.tsp 500 24000
python3 gagraph.py

./ga burma14.tsp 500 24000
python3 gagraph.py

./ga eil51.tsp 500 24000
python3 gagraph.py

./ga eil76.tsp 500 24000
python3 gagraph.py

#./ga lin105.tsp 500 24000
#python3 gagraph.py

#./ga lin318.tsp 500 24000
#python3 gagraph.py
