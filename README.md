# Double Hashing Performance Evaluation

To run this project simply run this command in terminal:
```
make
```

To change the dataset size or search key set size simpley go to makefile and edit them.
Example:
```
DATASET_SIZE=5000
SEARCHSET_SIZE=2000
```

I don't have `make` installed, what to do? Run these commands:
```
rm -f bin/* dataset.txt result.txt
mkdir -p bin
g++ -D dataset_size=10000 -D searchset_size=3000 -o bin/dataset dataset.cpp
g++ -D dataset_size=10000 -D searchset_size=3000 -o bin/main main.cpp
bin/dataset > dataset.txt && bin/main < dataset.txt > result.txt
```

Performance results will be stored in `result.txt` file. To view the dataset go to `dataset.txt` file.

`test.cpp` file is for testing if my hash functions are actually working or not. Also I compared `BST`, `STL set`, `Double Hashing` altogether. It turns out Double Hashing > BST > STL set in terms of performance.