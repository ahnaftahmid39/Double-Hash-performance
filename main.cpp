#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#ifdef dataset_size
const int N = dataset_size;
#else
const int N = 10000;
#endif

#ifdef searchset_size
const int S = searchset_size;
#else
const int S = 3000;
#endif

vector<int> primes;

bool is_prime[N * 2];

void sieve(int n = N * 2) {
	memset(is_prime, true, sizeof(is_prime));
	is_prime[1] = false;
	int sqr = sqrt(n);

	for (int i = 2; i <= sqr; i++) {
		if (!is_prime[i]) continue;
		for (int j = 2; i * j <= n; j++) {
			is_prime[i * j] = false;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (is_prime[i]) {
			primes.push_back(i);
		}
	}
}


struct node {
	int val;
	node* left, * right;
	node(int _val, node* _left, node* _right)
		: val(_val), left(_left), right(_right) {
	}
};

struct BinarySearchTree {
	node* root;
	BinarySearchTree() { root = NULL; }
	int size = 0;

	int insert(int x) {
		int t_cnt = 0; // traverse count
		node* newNode = new node(x, NULL, NULL);
		if (root == NULL) {
			root = newNode;
			size++;
			t_cnt++;
			return t_cnt;
		}
		node* k = root;
		while (k != NULL) {
			t_cnt++;
			if (k->val < x) {
				if (k->right == NULL) {
					k->right = newNode;
					size++;
					break;
				}
				k = k->right;
			}
			else {
				if (k->left == NULL) {
					k->left = newNode;
					size++;
					break;
				}
				k = k->left;
			}
		}
		return t_cnt;
	}

	pair<int, bool> search(int x) {
		node* k = root;
		int t_cnt = 0;
		while (k != NULL) {
			t_cnt++;
			if (k->val == x)
				return pair<int, bool>(t_cnt, true);
			else if (k->val < x)
				k = k->right;
			else
				k = k->left;
		}
		return pair<int, bool>(t_cnt, false);
	}
};


struct HashTable {
	int m, m2, size = 0;
	int* T;

	HashTable(int sz) {
		m = sz * 1.2;
		int p_size = primes.size();
		for (int i = 0; p_size; i++) {
			if (primes[i] > m) {
				m = primes[i];
				m2 = primes[i - 1];
				break;
			}
		}
		T = (int*)malloc(sizeof(int) * m);
		for (int i = 0; i < m; i++) {
			T[i] = 0;
		}

		cout << "Hash table m: " << m << endl;
		cout << "Hash table m': " << m2 << endl;
	}

	int h1(int k) {
		return k % m;
	}

	int h2(int k) {
		return 1 + (k % m2);
	}

	int h(int k, int i) {
		return (h1(k) + i * h2(k)) % m;
	}

	int insert(int k) {
		int i = 1;
		while (i <= m) {
			int j = h(k, i);
			if (T[j] == 0) {
				T[j] = k;
				size++;
				return i;
			}
			else {
				i++;
			}
		}
		return -1;
	}

	// returns probe_count, if-found
	pair<int, bool> search(int k) {
		int i = 1;
		while (i <= m) {
			int j = h(k, i);
			if (T[j] == k) {
				return pair<int, bool>(i, true);
			}
			if (T[j] == 0) {
				return pair<int, bool>(i, false);
			}
			i++;
		}
		return pair<int, bool>(i, false);
	}
};

vector<pair<int, int>> probes;
vector<pair<int, int>> traversals;
vector<pair<int, int>> probes_after_iter;
vector<pair<int, int>> traversals_after_iter;
char ins_search_seq[N + S + 5];


void showTabularInfo() {
	cout << "\n\n Probe and Traverse count table for each operation \n\n";
	printf("-");
	for (int j = 0; j < 59; j++) {
		if (j == 9 || j == 27 || j == 43) printf("+");
		else	printf("-");
	}
	puts("-");
	printf("| %-8s| %-16s| %-14s| %-14s|\n", "No.", "Key", "Probe Count", "Traverse count");
	printf("|");
	for (int j = 0; j < 59; j++) {
		if (j == 9 || j == 27 || j == 43) printf("+");
		else	printf("-");
	}
	puts("|");
	for (int i = 0; i < N + S; i++) {
		printf("| %-8d| %-16d| %-14d| %-14d|\n", i + 1, probes[i].first, probes[i].second, traversals[i].second);
		printf("|");
		for (int j = 0; j < 59; j++) {
			if (j == 9 || j == 27 || j == 43) printf("+");
			else	printf("-");
		}
		puts("|");
	}
}


void makeCSVForAllData() {
	fstream fout;
	fout.open("report.csv", ios::out);
	fout << "N," << "Key," << "Operation," << "Probe Count," << "Traverse count" << endl;
	for (int i = 0; i < N + S; i++) {
		string operation = ins_search_seq[i] == 'i' ? "Insert" : "Search";
		fout << i << "," << probes[i].first << "," << operation << "," << probes[i].second << "," << traversals[i].second << endl;
	}
}

void makeCSVForRangeOfData() {
	fstream fout;
	fout.open("report_small.csv", ios::out);
	fout << "N," << "Probe Count," << "Traverse count" << endl;
	for (int i = 0; i < probes_after_iter.size(); i++) {
		fout << probes_after_iter[i].first << "," << probes_after_iter[i].second << "," << traversals_after_iter[i].second << endl;
	}
}

double calcStandardDeviationProbes() {
	long long sum = 0;
	double avg = 0;
	for (int i = 0; i < N; i++) {
		sum += probes[i].second;
	}
	avg = (double)sum / (double)N;
	cout << "Average of probes: " << avg << endl;

	double dsum = 0;
	for (int i = 0; i < N; i++) {
		double dev = probes[i].second - avg;
		dsum += dev * dev;
	}

	double var = dsum / (N - 1);
	double sd = sqrt(var);

	cout << "Standard deviation of probes: " << sd << endl;
	return sd;
}


double calcStandardDeviationTraversals() {
	long long sum = 0;
	double avg = 0.0;
	for (int i = 0; i < N; i++) {
		sum += traversals[i].second;
	}
	avg = (double)sum / (double)N;
	cout << "Average of traversals: " << avg << endl;

	double dsum = 0;
	for (int i = 0; i < N; i++) {
		double dev = traversals[i].second - avg;
		dsum += dev * dev;
	}

	double var = dsum / (N - 1);
	double sd = sqrt(var);

	cout << "Standard deviation of traversals: " << sd << endl;
	return sd;
}

int main() {
	// true random each time
	time_t time;
	srand(time);

	vector<int> keyset;
	vector<int> searchset;
	steady_clock::time_point begin, end;

	// generate primes
	sieve(N * 2);

	// take inputs
	for (int i = 0; i < N; i++) {
		int key;
		scanf("%d", &key);
		keyset.emplace_back(key);
	}

	for (int i = 0; i < S; i++) {
		int key;
		scanf("%d", &key);
		searchset.emplace_back(key);
	}

	BinarySearchTree myPreferredDS = BinarySearchTree();
	HashTable myHashTable = HashTable(N);

	for (int i = 0; i < N; i++) ins_search_seq[i] = 'i';
	for (int i = N; i < N + S; i++) ins_search_seq[i] = 's';

	// randomize the insert-search sequence
	random_shuffle(ins_search_seq, ins_search_seq + N + S);

	/* <<--- Hash functions ---->> */

	begin = steady_clock::now();
	int ki = 0, si = 0;
	int total_probe_count = 0;
	for (int i = 0; i < N + S; i++) {
		// search
		if (ins_search_seq[i] == 's') {
			int p = myHashTable.search(searchset[si]).first;
			total_probe_count += p;
			probes.emplace_back(pair<int, int>(searchset[si], p));
			si++;
		}
		// insert
		else {
			int p = myHashTable.insert(keyset[ki]);
			total_probe_count += p;
			probes.emplace_back(pair<int, int>(keyset[ki], p));
			ki++;
		}
		if (i % 1000 == 0) probes_after_iter.emplace_back(pair<int, int>(i, total_probe_count));
	}
	end = steady_clock::now();
	cout << "Hash function performance measurement: " << duration_cast<microseconds>(end - begin).count() << " us" << endl;
	cout << "Total probe count: " << total_probe_count << endl;

	/* <<---- Binary Search Tree ---->> */

	begin = steady_clock::now();
	ki = 0, si = 0;
	int total_traverse_count = 0;
	for (int i = 0; i < N + S; i++) {
		// search
		if (ins_search_seq[i] == 's') {
			int t = myPreferredDS.search(searchset[si]).first;
			total_traverse_count += t;
			traversals.emplace_back(pair<int, int>(searchset[si], t));
			si++;
		}

		// insert
		else {
			int t = myPreferredDS.insert(keyset[ki]);
			total_traverse_count += t;
			traversals.emplace_back(pair<int, int>(keyset[ki], t));
			ki++;
		}
		if (i % 1000 == 0) traversals_after_iter.emplace_back(pair<int, int>(i, total_traverse_count));
	}
	end = steady_clock::now();
	cout << "Binary Search Tree performance measurement: " << duration_cast<microseconds>(end - begin).count() << " us" << endl;
	cout << "Total traverse count: " << total_traverse_count << endl;

	calcStandardDeviationProbes();
	calcStandardDeviationTraversals();
	showTabularInfo();
	makeCSVForAllData();
	makeCSVForRangeOfData();
}
