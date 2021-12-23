package main

import (
	"fmt"
)

func main() {
	fmt.Println("Hello World !")
	//数组   var a[100] int
	//Init
	var balance = [5]float32{1000, 2, 3.4, 7, 50}
	//balance := [5]float32{1000 , 2 , 3.4 , 7 , 50}
	var i int

	for i = 0; i < 5; i++ {
		//balance[i] = i + 100
		fmt.Println(balance[i])
	}

}
