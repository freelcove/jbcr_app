#pragma once
#include "globals.h"

#ifndef QUESTIONS_H
#define QUESTIONS_H

#define MAX_LINE_LENGTH 1024
#define MAX_QUESTIONS 1000

typedef struct
{
    int id;
    char question[MAX_LINE_LENGTH];
    char option_1[MAX_LINE_LENGTH];
    char option_2[MAX_LINE_LENGTH];
    char option_3[MAX_LINE_LENGTH];
    char option_4[MAX_LINE_LENGTH];
    char right_answer[MAX_LINE_LENGTH];
    char date[MAX_LINE_LENGTH];
} ObjectiveQuestion;

typedef struct
{
    int id;
    char name[MAX_LINE_LENGTH];
    char definition[MAX_LINE_LENGTH];
} SubjectiveQuestion;

void readObjectiveQuestions(ObjectiveQuestion *questions);

void readSubjectiveQuestions(SubjectiveQuestion *questions);

// db_history.tsv�� �ҷ�����
void readHistory(int *objective_history, int *subjective_history);

// ���� �����丮 ������ db_history.tsv�� ����.
void writeHistory(struct Queue *queue_objective, struct Queue *queue_subjective);

void enqueRandom(struct Queue *queue, int size);

#endif