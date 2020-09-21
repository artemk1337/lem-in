# Lem-in

## Quick start

1. Download:
    ```bash
    git clone https://github.com/artemk1337/lem-in.git
    ```
2. Install:
    ```bash
    make
    ```
3. Run:
    ```bash
    ./generator <flag> | ./lem-in
	```
	or  
	```bash
	./generator <flag> | ./lem-in -v
    ```
	or  
	```bash
	./generator <flag> | ./lem-in | python3 visualizer.py
    ```
	Visualizer example:  
	
	![](ezgif.com-video-to-gif.gif)  
	
See `./generator --help` for usage flags.

## Algorithms
1. Bellman–Ford - algorithm that computes shortest paths from a single source vertex to all of the other vertices in a weighted digraph. https://en.wikipedia.org/wiki/Bellman–Ford_algorithm
2. Suurballe - node-disjoint path finding algorithm http://www.macfreek.nl/memory/Disjoint_Path_Finding

## Compatibility ![MAC OS](https://camo.githubusercontent.com/0d10fab705f2a805a305b477cf48a8f53ae36ca9/68747470733a2f2f6d617863646e2e69636f6e73382e636f6d2f416e64726f69645f4c2f504e472f32342f4f7065726174696e675f53797374656d732f6d61635f6f732d32342e706e67) ![Linux](https://camo.githubusercontent.com/2eb8d0628e9c8560af56118cd36345eff22c8dff/68747470733a2f2f6d617863646e2e69636f6e73382e636f6d2f436f6c6f722f504e472f32342f4f7065726174696e675f53797374656d732f6c696e75782d32342e706e67)
Generator works only on Mac OS.    
Programming language: C.
