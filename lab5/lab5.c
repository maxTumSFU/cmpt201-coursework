#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  struct header *curr = free_list_ptr;
  while (curr != NULL) {
    if (curr->size >= size) // if big enough
    {
      return curr->id;
    } else {
      curr = curr->next;
    }
  }
  // no sufficient block found
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t best_fit_size = UINT64_MAX;
  // TODO: Implement best fit
  struct header *curr = free_list_ptr;
  while (curr != NULL) {
    if (curr->size >= size && curr->size < best_fit_size) {
      best_fit_size = curr->size;
      best_fit_id = curr->id;
    }

    curr = curr->next;
  }

  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // TODO: Implement worst fit
  uint64_t worst_fit_size = 0;
  // TODO: Implement best fit
  struct header *curr = free_list_ptr;
  while (curr != NULL) {
    if (curr->size >= size && curr->size > worst_fit_size) {
      worst_fit_size = curr->size;
      worst_fit_id = curr->id;
    }

    curr = curr->next;
  }

  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algoritm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algoritm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algoritm is: %d\n", worst_fit_id);
  return 0;
}

/*
  inputs: linked list of free blocks | pointer to newly freed block

  check if new block is immediately before one of the other blocks
    (check done by adding size of new block + size of header to new block's pointer and seeing if it
    is 1 away fron each block in the list)
    if yes, swap out new block into linked list and increase its size by size of header + size of
    old block

    if no, continue to next step

  check if new block is immediately after one of the other blocks
  (check done by iterating through list and adding the size of header + size of block for each block
  in the list and seeing if it is 1 away from the new block's pointer)
    if yes, increase size of the other block by size of header + size of new block

    else, continue

  if not immediately before or after, just append new block to the front of the linked list.







 */
