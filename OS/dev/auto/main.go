package main

import (
	"fmt"
	"os"
	"os/exec"

	"github.com/fsnotify/fsnotify"
)

// func _test() {
// 	fmt.Println("Started")

// 	// Get the current working directory
// 	dir, err := os.Getwd()
// 	if err != nil {
// 		fmt.Println(err)
// 		os.Exit(1)
// 	}

// 	fmt.Println("Current directory: ", dir)

// 	// Change the current working directory
// 	newpath := "./test"

// 	// create command
// 	cmd := exec.Command("make", "test")
// 	cmd.Dir = newpath

// 	// run command
// 	out, err := cmd.Output()
// 	if err != nil {
// 		fmt.Println(err)
// 		os.Exit(1)
// 	}

// 	fmt.Println(string(out))
// }

// func TestBash() {
// 	cmd := exec.Command("bash", "./here.sh")

// 	out, err := cmd.Output()
// 	fmt.Println(string(out))

// 	if err != nil {
// 		fmt.Println(err)
// 		os.Exit(1)
// 	}
// }

func OnChange() {
	// change to python_run.sh when using codespace
	cmd := exec.Command("bash", "./conda_run.sh")
	out, err := cmd.Output()

	fmt.Println(string(out))

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func main() {

	filename := "./../../src/core/memory.txt"

	// create watcher
	watcher, err := fsnotify.NewWatcher()
	if err != nil {
		fmt.Println("ERROR", err)
	}

	// add file to watcher
	err = watcher.Add(filename)
	if err != nil {
		fmt.Println("ERROR", err)
	}

	// create channel
	done := make(chan bool)
	os.Chdir("../")

	go func() {
		for {
			select {
			case event := <-watcher.Events:
				if event.Op&fsnotify.Write == fsnotify.Write {
					OnChange()
				}
			case err := <-watcher.Errors:
				fmt.Println("ERROR", err)
			}
		}
	}()

	defer watcher.Close()
	<-done
}
