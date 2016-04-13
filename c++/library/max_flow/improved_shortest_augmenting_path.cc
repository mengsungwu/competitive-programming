#include <iostream>
#include <algorithm>
#include <climits>
#include <numeric>
#include <utility>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

typedef long long int ll;


std::vector< std::vector<ll> > capacity;
std::vector< std::vector<ll> > residual;
std::vector<ll> h;

ll dfs(ll node, ll flow, ll source, ll sink)
{
	if (node == sink) {
		return flow;
	}

	for (ll i = 0; i < capacity.size(); i++) {
		if (residual[node][i] > 0 && h[node] == h[i] + 1) {
			ll df = dfs(i, std::min(flow, residual[node][i]), source, sink);

			if (df) {
				residual[node][i] -= df;
				residual[i][node] += df;
				return df;
			}
		}
	}

	/* no admissible edge */
	h[node]++;
	return 0;
}

ll max_flow(ll source, ll sink)
{
	/* Initial residual graph */
	residual.resize(capacity.size());
	for (ll i = 0; i < residual.size(); i++) {
		residual[i].resize(capacity[i].size());
		for (ll j = 0; j < residual[i].size(); j++) {
			residual[i][j] = capacity[i][j];
		}
	}

	/* Initial h label */
	h.resize(capacity.size());
	std::fill(h.begin(), h.end(), 0);

	ll flow = 0;
	while (h[source] < capacity.size()) {
		flow += dfs(source, LONG_MAX, source, sink);
	}
	return flow;
}

int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);

	ll n, m;
	std::cin >> n >> m;

	capacity.resize(2 * n + 2);
	for (ll i = 0; i < capacity.size(); i++) {
		capacity[i].resize(2 * n + 2);
	}

	ll original_solider = 0;
	for (ll i = 1; i <= n; i++) {
		std::cin >> capacity[0][i];
		capacity[i][i + n] = LONG_MAX;
		original_solider += capacity[0][i];;
	}

	ll soldier = 0;
	for (ll i = 1; i <= n; i++) {
		std::cin >> capacity[i + n][2 * n + 1];
		soldier += capacity[i + n][2 * n + 1];
	}

	for (ll i = 0; i < m; i++) {
		ll p, q;
		std::cin >> p >> q;
		capacity[p][q + n] = LONG_MAX;
		capacity[q][p + n] = LONG_MAX;
	}

	if (original_solider == soldier && soldier == max_flow(0, 2 * n + 1)) {
		std::cout << "YES" << std::endl;
		for (ll i = 1; i <= n; i++) {
			for (ll j = 1; j <= n; j++) {
				if (capacity[i][j + n] - residual[i][j + n] > 0) {
					std::cout << capacity[i][j + n] - residual[i][j + n] << " ";
				} else {
					std::cout << 0 << " ";
				}
			}
			std::cout << std::endl;
		}

	} else {
		std::cout << "NO" << std::endl;
	}
	
	return 0;
}