#include "implementation.h"

#include <stdio.h>

#include "../log/core.h"

typedef int Item;

#define ITEM_SIZE sizeof(Item)

/* Casts properly top item from stack. */
#define stack_peek(stack) *(Item *)stack_peek(stack)

/* To print current status of the stack. */
#define stack_print(stack) \
  if (stack_size(stack)) \
    printf("Stack data size: %zu | Stack size: %zu | Data: %d\n", \
           stack->data_size, stack->size, stack_peek(stack)); \
  else \
    printf("Stack data size: %zu | Stack size: %zu | Data: Empty\n", \
           stack->data_size, stack->size);

int main (void)
{
  struct Stack *stack = stack_initialise(ITEM_SIZE);

  if (!stack_is_empty(stack)) {
    log_error("stack_is_empty() failed.")
  } else {
    log_success("stack_is_empty() successed.");
  }

  if (stack_size(stack)) {
    log_error("stack_size() failed.")
  } else {
    log_success("stack_size() successed.");
  }

  {
    Item a = 500;
    stack_push(stack, &a);
  }
  {
    Item a = 1000;
    stack_push(stack, &a);
  }

  stack_print(stack);
  stack_pop(stack);
  stack_print(stack);
  stack_pop(stack);
  stack_print(stack);

  Item *a = malloc(ITEM_SIZE);
  *a = 500;
  stack_emplace(stack, a);

  stack_print(stack);

  stack_pop(stack);

  stack_print(stack);

  free(stack);
}
