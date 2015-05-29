#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <utility>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

typedef long long int ll;

typedef class FenwickTree {
public:
	FenwickTree(int n) {
		tree.resize(n + 1);
	}

	/* data: 0-based index, tree: 1-based index
	   Hence we will shift 1 position in update function
	*/
	FenwickTree(std::vector<ll> data) {
		tree.resize(data.size() + 1);

		for (int i = 0; i < data.size(); i++) {
			update(i, data[i]);
		}
	}

	/* query data[n], 0-based index */
	void update(int n, ll val) {
		for (int i = n + 1; i < tree.size(); i += (i & -i)) {
			tree[i] += val;
		}
	}

	/* query data[0] + ... + data[n1], 0-based index */
	ll query(int n) {
		ll val = 0;
		for (int i = n + 1; i > 0; i -= (i & -i)) {
			val += tree[i];
		}
		return val;
	}

	/* query data[n0] + ... + data[n1], 0-based index */
	ll query(int n0, int n1) {
		return query(n1) - query(n0 - 1);
	}

private:
	/* The tree is 1-based index, tree[0] is set to 0 */
	std::vector<ll> tree;

} FenwickTree;

int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::vector<ll> data;

	for (ll i = 0; i < 50; i++) {
		data.push_back(1LL << i);
	}

	FenwickTree tree(data);

	/* Test for Fenwick Tree*/
	for (int i = 0; i < data.size(); i++) {
		ll prefix_sum = std::accumulate(data.begin(), data.begin() + i + 1, 0LL);
		std::cout << "prefix_sum[" << i << "] = " << prefix_sum << ", " << tree.query(i) << std::endl;
		assert(prefix_sum == tree.query(i));

		for (int j = i; j < data.size(); j++) {
			ll sum = std::accumulate(data.begin() + i, data.begin() + j + 1, 0LL);
			std::cout << "prefix_sum[" << i << "..." << j << "] = " << sum << ", " << tree.query(i, j) << std::endl;
			assert(sum == tree.query(i, j));
		}
	}

	std::cout << "Pass All Pair Test." << std::endl;

	return 0;
}