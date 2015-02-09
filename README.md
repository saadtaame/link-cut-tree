# link-cut-tree
A C++ implementation of link-cut trees. A link-cut tree data structure maintains a forest of nodes subject to the following operations:
* __link(x, y)__: make the tree rooted at x a subtree of y,
* __cut(x)__: remove the edge connecting x to its parent.

The trees can be queried using the following operations:
* __root(x)__: find the root of the tree containing x,
* __path(x)__: compute a function of the nodes on the root-to-x path.

All operations take O(lg n) amortized time. root(x) can be used to test connectivity. In this implementation the path function computes the depth of a node in its tree. Dynamic lowest ancestor queries can be answered by using the function lca(x, y).

Interface:

For all 0 <= x, y < n,

* **LinkCut tree(n);** /* new link-cut tree with n nodes */
* **tree.link(x, y);** /* link x and y */
* **tree.cut(x);** /* cut x */
* **tree.root(x);** /* root of tree containing x */
* **tree.depth(x);** /* depth of x in its tree */
* **tree.lca(x, y);** /* lowest common ancestor of x and y */
