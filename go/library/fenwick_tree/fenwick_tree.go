
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

type FenwickTree struct {
    tree []int 
}

func NewFenwickTree(size int) (*FenwickTree) {
     return &FenwickTree{tree: make([]int, size + 1)}   
}

func (tree *FenwickTree) Update(position, value int) {
    for i := position + 1; i < len(tree.tree); i += (i & -i) {
        tree.tree[i] += value
    }
}

func (tree *FenwickTree) Query(start, end int) int {
    var result int
    
    for i := end + 1; i > 0 ; i -= (i & -i) {
        result += tree.tree[i]
    }

    for i := start; i > 0 ; i -= (i & -i) {
        result -= tree.tree[i]
    }
    
    return result
}

func main() {

    n := 0
    
    fmt.Fscanf(stdin, "%d", &n)
    
    data := make([]int, n)
    tree := NewFenwickTree(n)
    
    for i := 0; i < n; i++ {
        data[i] = i << uint(i)
        tree.Update(i, data[i])
    }
        
    for i := 0; i < n; i++ {
        for j := i; j < n; j++ {
            v1 := tree.Query(i, j)
            v2 := 0
            for k := i; k <= j; k++ {
                v2 += data[k]
            }
            
            if v1 != v2 {
                fmt.Fprintf(stdout, "%d %d %d %d\n", i, j, v1, v2)
            }
        }
    }

    stdout.Flush()
}