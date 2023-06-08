#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H

void initialize_sets(int cap);
void make_set(int x);
int find_set(int x);
void Union(int x, int y);
void destroy_sets();

#endif /* DISJOINT_SETS_H */
