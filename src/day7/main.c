#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <assert.h>

#if 1 
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "example.txt"
#endif

#define PART 2

#define FS_CHILDREN_CAP 256
#define FS_NODES_CAP 1024 * 4
#define FS_NODE_NAME_CAP 256

#define LINE_CAP 256

typedef struct Node {
  int fs_size;
  bool is_dir;
  struct Node *parent;

  char name[FS_NODE_NAME_CAP];

  int children_size;
  struct Node *children[FS_CHILDREN_CAP];
} Node;


int nodes_size = 0;
Node nodes[FS_NODES_CAP] = {0};
Node *root;

Node *mkdir(Node *parent, char* name) {
  if (nodes_size >= FS_NODES_CAP) return NULL;

  if (!parent->is_dir) return NULL;
  if (parent->children_size >= FS_CHILDREN_CAP) return NULL;

  Node *new_node = &(nodes[nodes_size++]);
  new_node->fs_size = 0;
  new_node->is_dir = true;
  new_node->parent = parent;
  new_node->children_size = 0;

  memcpy(new_node->name, name, sizeof(new_node->name));


  parent->children[parent->children_size++] = new_node;

  return new_node;
}

Node *touch(Node *parent, char*name, int size) {
  if (nodes_size >= FS_NODES_CAP) return NULL;

  if (!parent->is_dir) return NULL;
  if (parent->children_size >= FS_CHILDREN_CAP) return NULL;

  Node *new_node = &(nodes[nodes_size++]);
  new_node->fs_size = size;
  new_node->is_dir = false;
  new_node->parent = parent;
  new_node->children_size = 0;

  memcpy(new_node->name, name, sizeof(new_node->name));


  parent->children[parent->children_size++] = new_node;

  return new_node;
}

Node *cd(Node *parent, char* name) {
  for (int i = 0; i < parent->children_size; i++) {
    if (strcmp(parent->children[i]->name, name) == 0) return parent->children[i];
  } 

  return NULL;
}

void parse_filesystem(FILE *input) {
  // PARSE FILESYSTEM

  root = &(nodes[nodes_size++]);
  root->is_dir = true;
  memcpy(root->name, "root", sizeof(char) * 4);

  Node *current = root;


  char line[LINE_CAP] = {0};

  while (fgets(line, sizeof(line), input)) {
    char node_name[FS_NODE_NAME_CAP] = {0};
    assert(strlen(line) < sizeof(char) * FS_NODE_NAME_CAP && "Dir name too big");

    if (line[0] == '$') {
      // command
      
      if (strncmp(line, "$ cd", 4) == 0) {
  
        sscanf(line, "$ cd %s\n", node_name);

        if (strcmp(node_name, "..") == 0) {
          if (current->parent) current = current->parent;
          continue;
        } else if (strcmp(node_name, "/") == 0) {
          current = root;
          continue;
        }

        Node *next = cd(current, node_name);
        if (next == NULL) assert(false && "Cannot cd to given directory");

        current = next;

      } else if (strncmp(line, "$ ls", 4) == 0) {
        // list files
      } else {
        assert(false && "Unknown command");
      }

    } else {
      // listing files

      if (strncmp(line, "dir", 3) == 0) {
        // new dir
       
        sscanf(line, "dir %s\n", node_name);
        mkdir(current, node_name);

      } else {
        // new file

        int size = 0;
        sscanf(line, "%d %s\n", &size, node_name);
        touch(current, node_name, size);

      }

    }
    
  }
}

int update_dir_size(Node *node) {
  if (node == NULL) return 0;

  int size = node->fs_size;
  for (int i = 0; i < node->children_size; i++) {
    size += update_dir_size(node->children[i]);
  }
  
  node->fs_size = size;
  return size;
}

void part1(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  parse_filesystem(input);

  update_dir_size(root); 

  int sum = 0;
  for (int i = 0; i < nodes_size; i++) {
    if (!nodes[i].is_dir) continue;
    if (nodes[i].fs_size > 100000) continue;

    sum += nodes[i].fs_size;
  }

  printf("%d", sum);

  fclose(input);
}

#define FS_MAX_SIZE 70000000
#define FS_MIN_SPACE 30000000

void part2(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  parse_filesystem(input);

  int root_size = update_dir_size(root); 

  int unused = FS_MAX_SIZE - root_size;
  int to_be_freed = FS_MIN_SPACE - unused;

  Node *to_be_deleted = root;
  for (int i = 0; i < nodes_size; i++) {
    if (!nodes[i].is_dir) continue;
    if (nodes[i].fs_size < to_be_freed) continue;


    if (nodes[i].fs_size < to_be_deleted->fs_size) {
      to_be_deleted = &(nodes[i]);
    }
  }

  printf("%d", to_be_deleted->fs_size);

  fclose(input);
}


int main(void) {
#if PART == 1
  part1();
#else
  part2();
#endif
}

