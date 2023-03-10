#pragma once
#include "globals.h"

#ifndef USER_H
#define USER_H

struct User {
	char name[50];
};


struct User* create_user(char* name);

void draw_user_options();

void draw_user_info();

void WriteUserInfo();

void LoadUserInfo();


#endif