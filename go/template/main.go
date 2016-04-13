
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

func main() {



    stdout.Flush()
}