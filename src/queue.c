/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : queue.c                                                        */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/23 02:51:44 by Abdellah A.                              */
/*   Updated: 2024/12/23 16:36:44 by Abdellah A.                              */
/* ************************************************************************** */

#include <queue.h>

QueueNode *create_queue_node(void *element)
{
    QueueNode *node;

    node = (QueueNode *)malloc(sizeof(QueueNode));
    node->node = element;
    node->next = NULL;

    return node;
}

Queue *create_queue()
{
    Queue *q;

    q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;

    return q;
}

bool queue_is_empty(Queue *q)
{
    return q->front == NULL;
}

int queue_size(Queue *q)
{
    int size;
    QueueNode *tmp;

    size = 0;
    tmp = q->front;

    while (tmp != NULL)
    {
        tmp = tmp->next;
        size += 1;
    }

    return size;
}

void enqueue(Queue *q, void *element)
{
    QueueNode *new_node;
    
    new_node = create_queue_node(element);

    if (queue_is_empty(q) == true)
    {
        q->front = q->rear = new_node;

        return;
    }

    q->rear->next = new_node;
    q->rear = q->rear->next;
}

void *dequeue(Queue *q)
{
    QueueNode *tmp;
    void*element;

    if (queue_is_empty(q) == true)
        return NULL;

    tmp = q->front;
    element = tmp->node;
    q->front = q->front->next;

    if (queue_is_empty(q) == true)
        q->rear = NULL;

    free(tmp);
    return element;
}
