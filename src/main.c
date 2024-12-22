/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : main.c                                                         */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/22 18:14:07 by Abdellah A.                              */
/* ************************************************************************** */

#include "bst.h"
#include "avl.h"
#include "helpers.h"

typedef struct
{
  bool avl;
  bool bst;
} KeyFlags;

KeyFlags check_keys(int argc, char **argv)
{
  KeyFlags flags = {false, false};

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "avl") == 0)
      flags.avl = true;

    if (strcmp(argv[i], "bst") == 0)
      flags.bst = true;
  }
  return flags;
}

int main(int argc, char **argv)
{
  /* clear console */
  printf("\e[1;1H\e[2J");
  printf("*****************************************************************\n");

  KeyFlags flags = check_keys(argc, argv);

  if (argc < 2 || flags.avl)
    avl_main_test();

  if (argc < 2 || flags.bst)
    bst_main_test();

  return 0;
}
