#!/bin/bash
g++ -o ga *.cpp -I. -lm

rm outfile
./ga berlin52.tsp 500 40000
python3 gagraph.py berlin52 500

#rm outfile
#./ga burma14.tsp 500 24000
#python3 gagraph.py

#rm outfile
#./ga eil51.tsp 500 24000
#python3 gagraph.py

#rm outfile
#./ga eil76.tsp 500 24000
#python3 gagraph.py

#rm outfile
#./ga lin105.tsp 500 24000
#python3 gagraph.py

#./ga lin318.tsp 500 24000
#python3 gagraph.py
