#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct Node make_tree(int *arr, int size) {
  if (size <= 0) {
    exit(1);
  }
  struct Node root = {arr[0], NULL, NULL};

  for (int i = 1; i < size; i++) {
    int current_data = arr[i];
    struct Node *current = &root;
    for (;;) {
      if (current->data > current_data) {
        if (current->left != NULL) {
          current = current->left;
        } else {
          struct Node *n = malloc(sizeof(struct Node));
          n->data = arr[i];
          n->left = NULL;
          n->right = NULL;
          current->left = n;
          break;
        }
      } else if (current->data < current_data) {
        if (current->right != NULL) {
          current = current->right;
        } else {
          struct Node *n = malloc(sizeof(struct Node));
          n->data = arr[i], n->left = NULL;
          n->right = NULL;

          current->right = n;
          break;
        }
      } else {
        break;
      }
    }
  }
  return root;
}

void LPR(struct Node *n) {
  if (n == NULL) {
    return;
  }

  LPR(n->left);
  printf("%d ", n->data);
  LPR(n->right);
}

char *Tree_to_HTML_fn(struct Node *n) {
  if (n == NULL) {
    printf("Skill Issue");
    exit(0);
  }

  // I somehow need to show the tree just like how the nested
  // componets work, Who said that learning HTML can solve this problem
  // Heh
  //
  // Root is 1, left is 0, right is 3, then the string which is going to be
  // saved should be <r> 	<d> 1 </d> 	<l> 		<d> 0 </d>
  // 	</l>
  // 	<r>
  // 		<d> 3 </d>
  // 	</r>
  // </r>
  //
  // Then if I add another node to the left of the right node of the root.
  // <R>
  // 	<d> 1 </d>
  // 	<l>
  // 		<d> 0 </d>
  // 	</l>
  // 	<r>
  // 		<d> 3 </d>
  // 		<l>
  // 			<d> 9 </d>
  // 		</l>
  // 	</r>
  // </R>
  //
  //
  // Now how the hell should I make it. huh

  // I can understand there will some some simple data structure that will be
  // used Since there is nesting, I guess we need to use stack, cause we need to
  // remember previous values too.
  //
  // Okay lets see, if we need stack or not.
  // Lets not deviate from the goal, its to save a tree to a file.
  // So I will need to traverse the tree, in a DFS or BFS mannor.
  // Which matters, cause thats how I will be completing the HTML.
  // I can maintain a pointer which may indicate the location
  // where to write next.
  //
  // Lets choose the DFS way, cause its easy to implement using
  // recursion.

  // who knows, I might have to make Tree_to_HTML function recursive.
  // oh yes, it can be made recursive, and thats something which should be done.

  // First add the current node.
  // check left exists
  // Check right exists.
  // First recursive call to left
  // Then recursive call to right

  char *string = malloc(1000);
  string[0] = '\0';

  char temp[50];
  snprintf(temp, sizeof(temp), "<d>%d</d>", n->data);
  strcat(string, temp);

  int left_exists = 0;
  if (n->left != NULL)
    left_exists = 1;
  int right_exists = 0;
  if (n->right != NULL)
    right_exists = 1;

  char *left_string;
  char *right_string;

  // I know I could have called these function in the about checks only,
  // But I might need to check if left or right exists, so I wrote like this.

  if (!left_exists && !right_exists) {
    // Then I must return the HTML from here
    // Return <d> nnode_data </d>

    int num = n->data;
    snprintf(string, 50, "<d>%d</d>", num);
    return string;
  }
  if (left_exists) {
    left_string = Tree_to_HTML_fn(n->left);
  }

  if (right_exists) {
    right_string = Tree_to_HTML_fn(n->right);
  }

  if (left_exists) {
    // Also from here
    strcat(string, "<l>");
    strcat(string, left_string);
    strcat(string, "</l>");
  }

  if (right_exists) {
    strcat(string, "<r>");
    strcat(string, right_string);
    strcat(string, "</r>");
  }

  return string;
}

char *Tree_to_HTML(struct Node *n) {
  char *body = Tree_to_HTML_fn(n);

  char *result = malloc(2000);
  result[0] = '\0';

  strcat(result, "<R>");
  strcat(result, body);
  strcat(result, "</R>");

  free(body);
  return result;
}

void save_tree_to_file(struct Node *tree, char *file_path) {
  char *html = Tree_to_HTML(tree);
  FILE *f = fopen(file_path, "w");
  if (f == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  fprintf(f, html);
  fclose(f);
}

int main() {
  int arr[] = {54, 65, 2, 43, 54, 78, 76, 89};
  int size = 8;
  struct Node tree = make_tree(arr, size);

  char *string = Tree_to_HTML(&tree);
  printf("%s", string);

  save_tree_to_file(&tree, "binary.tree");
  // Larp();
}
