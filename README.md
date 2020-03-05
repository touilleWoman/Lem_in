# lem-in

School 42 team project, I'm in charge of the algorithme part.

The purpose of this project is to find paths from start room to end room and to move ants by these paths with the least amount of steps.


**Usage**

```
make
./lem-in < ressources/bigmap
```

I use Breadth-first search (BFS) algorithm and Edmonds-Karp algorithme with adaptation.

>the Edmonds–Karp algorithm is an implementation of the Ford–Fulkerson method for computing 
>the maximum flow in a flow network. 

It is demanded that we can have maximum one ant in each room. So the max-flow of all edges are 1. However Edmonds-Karp algorithme doesn't take node flow in consideration. When two paths are crossed, the ants will walk over each other. To avoid this, I have a node_flow counter, if node_flow == 2, I will consider this round of BFS as invalid, and add this path in to forbidden pathlist.
