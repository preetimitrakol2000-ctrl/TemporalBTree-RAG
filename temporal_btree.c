#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 3

typedef struct {
    long long timestamp_epoch;
    int data_chunk_id;
} LogKey;

typedef struct BTreeNode {
    LogKey keys[MAX_KEYS];
    struct BTreeNode* children[MAX_KEYS + 1];
    int num_keys;
    int is_leaf;
} BTreeNode;

#ifdef _WIN32
    __declspec(dllexport) BTreeNode* init_btree_node();
    __declspec(dllexport) void insert_temporal_key(BTreeNode* root, long long epoch, int chunk_id);
    __declspec(dllexport) int scan_time_window(BTreeNode* root, long long target_epoch);
#endif

BTreeNode* init_btree_node() {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->num_keys = 0;
    node->is_leaf = 1;
    for (int i = 0; i <= MAX_KEYS; i++) node->children[i] = NULL;
    return node;
}

void insert_temporal_key(BTreeNode* root, long long epoch, int chunk_id) {
    if (root->num_keys < MAX_KEYS) {
        int i = root->num_keys - 1;
        while (i >= 0 && root->keys[i].timestamp_epoch > epoch) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1].timestamp_epoch = epoch;
        root->keys[i + 1].data_chunk_id = chunk_id;
        root->num_keys++;
    }
}

int scan_time_window(BTreeNode* root, long long target_epoch) {
    int i = 0;
    while (i < root->num_keys && target_epoch > root->keys[i].timestamp_epoch) {
        i++;
    }
    if (i < root->num_keys && target_epoch == root->keys[i].timestamp_epoch) {
        return root->keys[i].data_chunk_id;
    }
    if (root->is_leaf) return -1;
    return scan_time_window(root->children[i], target_epoch);
}
