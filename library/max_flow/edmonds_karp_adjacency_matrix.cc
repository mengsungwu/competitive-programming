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
std::vector<ll> path;

bool BFS(ll source, ll sink)
{
	std::queue<ll> queue;
	std::vector<ll> distance(residual.size(), -1);

	path.clear();
	path.resize(residual.size());
	distance[source] = 0;
	queue.push(source);


	while (!queue.empty()) {
		ll x = queue.front();
		queue.pop();

		for (ll i = 0; i < residual[x].size(); i++) {
			if (residual[x][i] > 0 && distance[i] == -1) {
				distance[i] = distance[x] + 1;
				path[i] = x;
				if (i == sink) {
					return true;
				}
				queue.push(i);
			}
		}
	}
	return false;
}

ll flow(ll source, ll sink)
{
	ll df = LLONG_MAX;
	ll y = sink;
	while (y != source) {
		ll x = path[y];
		df = std::min(df, residual[x][y]);
		y = x;
	}

	y = sink;
	while (y != source) {
		ll x = path[y];
		residual[x][y] -= df;
		residual[y][x] += df;
		y = x;
	}

	return df;
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

	ll total = 0;
	std::vector<ll> path;
	while (BFS(source, sink)) {
		total += flow(source, sink);
	}

	return total;
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
		capacity[i][i + n] = LLONG_MAX;
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
		capacity[p][q + n] = LLONG_MAX;
		capacity[q][p + n] = LLONG_MAX;
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