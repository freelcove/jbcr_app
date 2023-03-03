#pragma once
#ifndef QUESTIONS_H
#define QUESTIONS_H

#define MAX_LINE_LENGTH 1024
#define MAX_QUESTIONS 100

typedef struct {
    int id;
    char question[MAX_LINE_LENGTH];
    char option_1[MAX_LINE_LENGTH];
    char option_2[MAX_LINE_LENGTH];
    char option_3[MAX_LINE_LENGTH];
    char option_4[MAX_LINE_LENGTH];
    char right_answer[MAX_LINE_LENGTH];
    char date[MAX_LINE_LENGTH];
} Question;

void read_questions(Question* questions, int* num_questions);

#endif