#include<bits/stdc++.h>
using namespace std;

void print_random_numbers() {
	for (int i = 0; i < 10; i++) {
		int r = rand();
		cout << r << endl;
	}
}

#ifdef dataset_size
const int dsize = dataset_size;
#else
int dsize = 10000;
#endif

#ifdef searchset_size
const int ssize = searchset_size;
#else
const int ssize = 3000;
#endif

int main() {
	time_t time;
	srand(time);

	set<int> dataset_sorted;
	vector<int> dataset;

	while (dataset_sorted.size() < dsize) {
		int r = rand();
		pair<set<int>::iterator, bool> pr = dataset_sorted.insert(r);
		if (pr.second == true) {
			dataset.push_back(r);
		}

	}
	for (vector<int>::iterator it = dataset.begin(); it != dataset.end(); ++it) {
		printf("%d\n", *it);
	}

	// cout << "\n\nSearch set: \n\n";

	random_shuffle(dataset.begin(), dataset.end());
	vector<int> searchset;
	int di = 0, dcnt = 0;
	while (searchset.size() < ssize) {
		int r2 = rand() % 100;
		bool dset = false;
		if (r2 < 30) {
			while (true) {
				int r = rand();
				if (dataset_sorted.find(r) == dataset_sorted.end()) {
					searchset.emplace_back(r);
					break;
				}
			}
		}
		else {
			dset = true;
			dcnt++;
			searchset.emplace_back(dataset[di++]);
		}
		int r1 = rand() % 100;
		if (r1 < 20 && searchset.size() < ssize) {
			int d = searchset[searchset.size() - 1];
			if (dset) dcnt++;
			searchset.emplace_back(d);
		}
	}

	// int rcnt = 0; // repeatition count
	// for (vector<int>::iterator it = searchset.begin(); it != searchset.end(); ++it) {
		// if (*it == *(it + 1)) {
		// 	rcnt++;
		// }
	// }

	random_shuffle(searchset.begin(), searchset.end());
	for (vector<int>::iterator it = searchset.begin(); it != searchset.end(); ++it) {
		printf("%d\n", *it);
	}

	cout << "Search set contains " << dcnt << " elements from dataset" << endl;
	// cout << "repeat count: " << rcnt << endl;
}