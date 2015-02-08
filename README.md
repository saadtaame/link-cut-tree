# link-cut-tree
A C++ implementation of link-cut trees. A link-cut tree data structures maintains a forest of nodes subject to the following operations:
* link(x, y): make the tree rooted at x a subtree of y,
* cut(x): remove the edge connecting x to its parent.
The trees can be queried using the following operations:
* root(x): find the root of the tree containing x,
* path(x): compute a function of the nodes on the root-to-x path.
All operations take O(lg n) amortized time. root(x) can be used to test connectivity. In this implementation tha path function computes the depth of a node in its tree.
