#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <set>

typedef long long int ll;

ll power(ll a, ll n, ll mod)
{
	ll result = 1;
	while (n) {
		if (n & 1) {
			result = (result * a) % mod;
		}
		n >>= 1;
		a = (a * a) % mod;
	}

	return result;
}

/* n - 1 = 2^s * d */
bool miller_rabin_primality_test_a_number(ll a, ll s, ll d, ll n)
{
	while (d % 2 == 0) {
		d /= 2;
		s += 1;
	}

	a = power(a, d, n);

	if (a == 1) {
		return true;
	}

	for (ll i = 0; i < s; i++) {
		if (a == n - 1) {
			return true;
		}
		a = (a*a) % n;
	}

	return false;
}

bool miller_rabin_primality_test(ll n)
{
	ll s = 0, d = n - 1;

	while (d % 2 == 0) {
		d /= 2;
		s += 1;
	}

	std::cout << s << " " << d << std::endl;

	if (miller_rabin_primality_test_a_number(2, s, d, n) == false) {
		return false;
	}

	if (n < 2047) {
		return true;
	}

	if (miller_rabin_primality_test_a_number(3, s, d, n) == false ) {
		return false;
	}

	if (n < 1373653) {
		return true;
	}

	if (miller_rabin_primality_test_a_number(5, s, d, n) == false) {
		return false;
	}

	if (n < 25326001) {
		return true;
	}

	if (miller_rabin_primality_test_a_number(7, s, d, n) == false) {
		return false;
	}

	if (miller_rabin_primality_test_a_number(11, s, d, n) == false) {
		return false;
	}

	/* n < 2152302898747*/
	return true;
}

bool is_prime(ll n)
{
	if (n < 2) {
		return false;
	} if (n == 2 || n == 3) {
		return true;
	} if (n % 2 == 0 || n % 3 == 0) {
		return false;
	}

	return miller_rabin_primality_test(n);
}

int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);

	ll n;
	std::cin >> n;
	std::cout << is_prime(n) << std::endl;
	
	return 0;
}