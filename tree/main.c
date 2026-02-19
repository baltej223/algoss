#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* left;
  struct Node* right;
};

struct Node make_tree(int* arr, int size){
  // treating size to be true 
  if (size <= 0){
    exit(1);
  }
  struct Node root = {arr[0], NULL, NULL};
  
  for (int i = 1; i < size; i++){
    int current_data = arr[i];
    struct Node *current = &root;
    for (;;) {
      if (current->data > current_data){
        if (current->left != NULL){
          current = current->left;
        }
        else{
          struct Node *n = malloc(sizeof(struct Node));
          n->data = arr[i];
          n->left = NULL;
          n->right = NULL;
          current->left = n;
          break;
        }
      }
      else if (current->data < current_data) {
        if (current->right != NULL){
          current = current->right;
        }
        else {
          struct Node *n = malloc(sizeof(struct Node));
          n->data = arr[i],
          n->left = NULL;
          n->right = NULL;

          current->right = n;
          break;
        }
      }
      else {
        break;
      }
    }
  }
  return root;
}

void LPR(struct Node* n) {
  if (n == NULL){
    return;
  }

  LPR(n->left);
  printf("%d ", n->data);
  LPR(n->right);
}

int main(){
  int arr[] = {54, 65, 76, 23, 54, 65, 76, 89};
  int size = 8;
  struct Node tree = make_tree(arr, size);
  LPR(&tree);
}
