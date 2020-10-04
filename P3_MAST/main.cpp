#include <iostream>
#include "node.h"
#include "tree.h"
#include "MAST.h"
using namespace std;

int main()
{
  // freopen("input.txt", "r", stdin);
  int howmany;
  scanf("%d", &howmany);
  tree_t *forest = create_forest(howmany); //tree.h

  for (int i = 0; i < howmany; i++)
    for (int j = i + 1; j < howmany; j++)
      fill_hashtable(forest[j], forest[i]); //mast.h

  for (int i = 0; i < howmany; i++)
    delete_tree(&forest[i]); //tree.h
  delete[] forest;
  return 0;
}