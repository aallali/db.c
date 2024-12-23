/* ************************************************************************** */
/*   Copyright 2024 <Abdellah ALLALI>                                         */
/*                                                                            */
/*   File    : queue.c                                                        */
/*   Project : DB.c                                                           */
/*   License : Apache 2.0 with Commons Clause. See LICENSE file.              */
/*                                                                            */
/*   Created: 2024/12/23 02:51:44 by Abdellah A.                              */
/*   Updated: 2024/12/23 02:58:45 by Abdellah A.                              */
/* ************************************************************************** */

#include <queue.h>

QueueNode *create_queue_node(void *element)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->node = element;
    node->next = NULL;
    return node;
}

Queue *create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    
    return q;
}

void enqueue(Queue *q, void *element)
{
    QueueNode *new_node = create_queue_node(element);

    if (q->front == NULL)
    {
        q->front = q->rear = new_node;
        return;
    }

    q->rear->next = new_node;
    q->rear = q->rear->next;
}

void dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        printf("Queue Underflow\n");
        return;
    }
    QueueNode *tmp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(tmp);
    return;
}
