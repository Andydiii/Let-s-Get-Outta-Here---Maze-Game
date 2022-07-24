# Let's Get Outta Here! 
Maze Game in C

Mazes come in two flavours: simply-connected and multiply-connected. A maze is simply-connected if it does not contain loops: there is no way to arrive at a previously visited part of the maze without backtracking, i.e., without walking back a path already traveled. This means that in simply-connected mazes, all walls are connected to the outside wall, whereas multiply-connected mazes can have "islands" of walls inside the maze. Alternatively, any simply-connected maze can be transformed into a tree, whereas multiply-connected mazes can only be transformed into a graph.
****传截图 收藏里教程


Finding the path out of a simply-connected maze is relatively straight forward. A common, intuitive algorithm is the right-hand rule (or wall follower)(https://en.wikipedia.org/wiki/Maze-solving_algorithm#Wall_follower):

While standing on the (S)tart tile, put your right hand onto any wall. Technically, you could also use your left hand (left-hand rule).
Start walking without ever taking your hand off the wall. The direction does not matter. Eventually, you will arrive at the (E)xit.

While this approach is guaranteed to work for simply-connected mazes, it does not always work for multiply-connected ones. If, for example, the wall you put your hand onto is not connected to the outside wall, you might end up in an infinite loop:
******截图
