#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

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

	void insert(int x) {
		node* newNode = new node(x, NULL, NULL);
		if (root == NULL) {
			root = newNode;
			size++;
			return;
		}
		node* k = root;
		while (k != NULL) {
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
	}

	void remove(int x) {
		node* k = search(x);
		if (k != NULL) remove(k);
	}

	void remove(node* k) {
		if (!k->left && !k->right) {
			node* x = parent(k);
			if (x->left == k) x->left = NULL;
			else x->right = NULL;

		}
		else if (!k->left) {
			node* x = parent(k);
			if (x->right == k) x->right = k->right;
			else x->left = k->right;

		}
		else if (!k->right) {
			node* x = parent(k);
			if (x->right == k) x->right = k->left;
			x->left = k->left;

		}
		else {
			node* s = k->left;
			while (s->right) s = s->right;
			remove(s);
			k->val = s->val;
		}
	}

	node* search(int x) {
		node* k = root;
		while (k != NULL) {
			if (k->val == x)
				return k;
			else if (k->val < x)
				k = k->right;
			else
				k = k->left;
		}
		return NULL;
	}

	node* parent(node* x) {
		node* k = root;
		node* par = NULL;
		while (k != NULL) {
			if (k->val == x->val)
				return par;
			else if (k->val < x->val) {
				par = k;
				k = k->right;
			}
			else {
				par = k;
				k = k->left;
			}
		}
		return par;
	}

	node* lower_bound(int x) {
		node* k = root, * ans = NULL;
		while (k != NULL) {
			if (k->val <= x) {
				ans = k;
				k = k->right;
			}
			else {
				k = k->left;
			}
		}
		return ans;
	}
	node* upper_bound(int x) {
		node* k = root, * ans = NULL;
		while (k != NULL) {
			if (k->val <= x) {
				k = k->right;
			}
			else {
				ans = k;
				k = k->left;
			}
		}
		return ans;
	}

	void inorder(node* k) {
		if (k == NULL) return;
		inorder(k->left);
		printf("%d ", k->val);
		inorder(k->right);
	}

	void preorder(node* k) {
		if (k == NULL) return;
		printf("%d ", k->val);
		preorder(k->left);
		preorder(k->right);
	}

	void postorder(node* k) {
		if (k == NULL) return;
		postorder(k->left);
		postorder(k->right);
		printf("%d ", k->val);
	}

	void print_inorder() {
		printf("Printing in inorder\n");
		inorder(root);
		puts("");
	}

	void print_preorder() {
		printf("Printing in preorder\n");
		preorder(root);
		puts("");
	}

	void print_postorder() {
		printf("Printing in postorder\n");
		postorder(root);
		puts("");
	}
};



#ifdef dataset_size
const int N = dataset_size;
#else
const int N = 10000;
#endif

#ifdef searchset_size
const int S = searchset_size;
#else
const int S = 10000;
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
		int i = 0;
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

	pair<int, bool> search(int k) {
		int i = 0;
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
int main() {
	vector<int> dataset;
	vector<int> searchset;
	steady_clock::time_point begin, end;

	sieve();

	for (int i = 0; i < N; i++) {
		int key;
		scanf("%d", &key);
		dataset.emplace_back(key);
	}

	for (int i = 0; i < S; i++) {
		int key;
		scanf("%d", &key);
		searchset.emplace_back(key);
	}

	BinarySearchTree myPreferredDS = BinarySearchTree();
	HashTable myHashTable = HashTable(N);
	set<int> myStlDS;

	cout << "\n<<--- Insertion ---->>\n" << endl;

	random_shuffle(dataset.begin(), dataset.end());
	begin = steady_clock::now();
	for (int i = 0; i < N; i++) {
		myStlDS.insert(dataset[i]);
	}
	end = steady_clock::now();
	cout << "STL Set insertion time: " << duration_cast<microseconds>(end - begin).count() << " us" << endl;

	random_shuffle(dataset.begin(), dataset.end());
	begin = steady_clock::now();
	for (int i = 0; i < N; i++) {
		myPreferredDS.insert(dataset[i]);
	}
	end = steady_clock::now();
	cout << "BST insertion time: " << chrono::duration_cast<microseconds>(end - begin).count() << " us" << endl;

	random_shuffle(dataset.begin(), dataset.end());
	begin = steady_clock::now();
	for (int i = 0; i < N; i++) {
		myHashTable.insert(dataset[i]);
	}
	end = steady_clock::now();
	cout << "Hashtable insertion time: " << duration_cast<microseconds>(end - begin).count() << " us" << endl;


	cout << "\n<<--- Searching ---->>\n" << endl;
	int found_cnt = 0;
	begin = steady_clock::now();
	for (int i = 0; i < S; i++) {
		node* res = myPreferredDS.search(searchset[i]);
		if (res != NULL) found_cnt++;
	}
	end = steady_clock::now();
	cout << "BST searching time: " << duration_cast<microseconds>(end - begin).count() << " us" << ", found count: " << found_cnt << endl;

	begin = steady_clock::now();
	found_cnt = 0;
	set<int>::iterator si;
	for (int i = 0; i < S; i++) {
		si = myStlDS.find(searchset[i]);
		if (si != myStlDS.end()) {
			found_cnt++;
		}
	}
	end = steady_clock::now();
	cout << "STL set searching time: " << duration_cast<microseconds>(end - begin).count() << " us" << ", found count: " << found_cnt << endl;

	begin = steady_clock::now();
	int probe_cnt = 0;
	found_cnt = 0;
	for (int i = 0; i < S; i++) {
		pair<int, bool> sresult = myHashTable.search(searchset[i]);
		probe_cnt += sresult.first;
		if (sresult.second) found_cnt++;
	}
	end = steady_clock::now();
	cout << "Hashtable searching time: " << duration_cast<microseconds>(end - begin).count() << " us" << ", found count: " << found_cnt << endl << "\nTotal probe count: " << probe_cnt << endl;
}