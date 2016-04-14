package main

import (
	"bufio"
	"fmt"
	"os"
)

var stdin *bufio.Reader
var stdout *bufio.Writer

func init() {
	stdin = bufio.NewReader(os.Stdin)
	stdout = bufio.NewWriter(os.Stdout)
}

func power(a, n, mod uint64) uint64 {
	var result uint64 = 1
	for n > 0 {
		if n&1 == 1 {
			result = (result * a) % mod
		}
		n >>= 1
		a = (a * a) % mod
	}
	return result
}

func millerRabinPrimalityTestANumber(a, s, d, n uint64) bool {

	a = power(a, d, n)

	if a == 1 {
		return true
	}

	var i uint64
	for i = 0; i < s; i++ {
		if a == n-1 {
			return true
		}
		a = (a * a) % n
	}

	return false
}

func MillerRabinPrimalityTest(n uint64) bool {

	if n == 2 || n == 3 {
		return true
	} else if n < 2 || (n%2 == 0 && n%3 == 0) {
		return false
	}

	var s, d uint64 = 0, n - 1

	for d&1 == 0 {
		d >>= 1
		s++
	}

	if millerRabinPrimalityTestANumber(3, s, d, n) == false {
		return false
	}

	if n < 1373653 {
		return true
	}

	if millerRabinPrimalityTestANumber(3, s, d, n) == false {
		return false
	}

	if n < 25326001 {
		return true
	}

	if millerRabinPrimalityTestANumber(7, s, d, n) == false {
		return false
	}

	if millerRabinPrimalityTestANumber(11, s, d, n) == false {
		return false
	}

	/* n < 2152302898747*/
	return true

}

func main() {

	var n uint64
	fmt.Fscanf(stdin, "%d\n", &n)
	fmt.Fprintf(stdout, "%t\n", MillerRabinPrimalityTest(n))

	stdout.Flush()
}
