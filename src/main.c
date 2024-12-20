/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : main.c                                                         */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/13 13:37:42 by Abdellah A.                              */
/*   Updated: 2024/12/21 00:03:15 by Abdellah A.                              */
/* ************************************************************************** */

#include "bst.h"
#include "avl.h"
#include "helpers.h"

int main()
{
  /* clear console */
  printf("\e[1;1H\e[2J");
  printf("*****************************************************************\n");
  /*
    UnComment the main func collection you want to run
  */
  // bst_main_test();
  avl_main_test();

  return 0;
}
