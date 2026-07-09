#ifndef TEMPORAL_BTREE_H
#define TEMPORAL_BTREE_H

typedef struct LogKey LogKey;
typedef struct BTreeNode BTreeNode;

BTreeNode* init_btree_node();
void insert_temporal_key(BTreeNode* root, long long epoch, int chunk_id);
int scan_time_window(BTreeNode* root, long long target_epoch);

#endif
