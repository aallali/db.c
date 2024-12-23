/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : queue.h                                                        */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/23 02:52:18 by Abdellah A.                              */
/*   Updated: 2024/12/23 03:01:22 by Abdellah A.                              */
/* ************************************************************************** */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueNode
{
    void *node;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *create_queue();

QueueNode *create_queue_node(void *element);

void enqueue(Queue *q, void *element);

void dequeue(Queue *q);
int queue_size(Queue *q);

bool queue_is_empty(Queue *q);

#endif // QUEUE_H
