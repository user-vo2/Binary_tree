#include <stdio.h>
#include <stdlib.h>

struct treenode {
    int data;
    struct treenode *parent, *left, *right;
};

typedef struct treenode treenode;

treenode *find(treenode *root, int data){
    if (root == NULL){
        fprintf(stderr, "Failed to find node because list is empty.");
        return NULL;
    }
    if (root->data == data)
        return root;
    if (root->data > data){
        if (root->left != NULL)
            return find(root->left, data);
        else
            return root;
    }
    if (root->data < data){
        if (root->right != NULL)
            return find(root->right, data);
        else
            return root;
    }
    return NULL;
}

treenode *new_node(treenode *root, int data){
    treenode *node, *node_new = malloc(sizeof(treenode));
    node_new->data = data;
    node_new->left = node_new->right = node_new->parent = NULL;
    if (root == NULL)
        return node_new;
    node = find(root, data);
    if (node->data == data)
        return root;
    if (node->data > data){
        node_new->parent = node;
        node->left = node_new;
    }
    if (node->data < data){
        node_new->parent = node;
        node->right = node_new;
    }
    return root;
}

treenode *tree_minimum(treenode *root)
{
    if (root == NULL){
        fprintf(stderr, "Failed to find node because list is empty.");
        return NULL;
    }
    while (root->left != NULL)
        root = root->left;
    return root;
}

treenode *tree_maximum(treenode *root)
{
    if (root == NULL){
        fprintf(stderr, "Failed to find node because list is empty.");
        return NULL;
    }
    while (root->right != NULL)
        root = root->right;
    return root;
}

treenode *node_follower(treenode *root, int data){
    if (root == NULL){
        fprintf(stderr, "Failed to find node because list is empty.");
        return NULL;
    }
    if (data == tree_maximum(root)->data)
        fprintf(stderr, "Failed to find follower because it is the highest value.");
    treenode *node = find(root, data);
    if (node->right != NULL){
        node = tree_minimum(node->right);
        return node;
    }
    while (node->parent != NULL){
        if (node->parent->left == node)
            return node->parent;
        node = node->parent;
    }
    return NULL;
}

treenode *delete_node(treenode *root, int data)
{
    if (root == NULL){
        fprintf(stderr, "Failed to find node because list is empty.");
        return NULL;
    }
    treenode *node = find(root, data), *x = NULL;
    if (node->left == NULL || node->right == NULL){
        if (node->right != NULL)
            x = node->right;
        if (node->left != NULL)
            x = node->left;
        if (node == root){
            root = x;
            free(node);
            return root;
        }
        if (node->parent->left == node)
            node->parent->left = x;
        else
            node->parent->right = x;
        free(node);
    }
    if (node->left != NULL && node->right != NULL){
        node->data = tree_minimum(node->right)->data;
        node->right = delete_node(node->right, node->data);
    }
    return root;
}

int main()
{
    int n, el, request;
    treenode *root = NULL;
    printf("How many nodes you want to have in a tree?   ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        printf("Print %d value.    ", i + 1);
        scanf("%d", &el);
        root = new_node(root, el);
    }
    printf("Print 0 to stop searching.\nFind the closest value to    ");
    scanf("%d", &request);
    while(request != 0){
        printf("%d\nFind the closest value to    ", find(root, request)->data);
        scanf("%d", &request);
    }
    printf("The lowest value %d.\nThe highest value %d.\n", tree_minimum(root)->data, tree_maximum(root)->data);
    printf("Find follower of   ");
    scanf("%d", &request);
    printf("%d\n", node_follower(root, request)->data);
    printf("Delete node with value   ");
    scanf("%d", &request);
    root = delete_node(root, request);
    printf("%d", root->data);
    return 0;
}
