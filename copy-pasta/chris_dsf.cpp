struct DSF_Tree
{
  DSF_Tree* parent = this;
  int id;
  //custom data to insert
};

DSF_Tree* find(DSF_Tree* tree)
{
  if(tree->parent != tree)
    tree->parent = find(tree->parent);
  return tree->parent;
}

void unioon(DSF_Tree* first, DSF_Tree* second)
{
  auto root1 = find(first);
  auto root2 = find(second);
  if(root1->id != root2->id)
    root1->parent = root2;
}

DSF_Tree* makeSet(int id)
{
  auto tree = new DSF_Tree;
  tree->parent = tree;
  tree->id = id;
  return tree;
}
