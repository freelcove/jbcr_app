#include "utilities.h"

// ���� �ð� �ҷ��ͼ� ���ڿ��� return
char *get_current_time()
{
	time_t now;
	struct tm *timeinfo;
	static char str_time[20];

	time(&now);
	timeinfo = localtime(&now);

	strftime(str_time, sizeof(str_time), "%Y-%m-%d %H%M%S", timeinfo);
	return str_time;
}

void WriteUserInfo()
{
	FILE *file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_user_info.tsv", "w");
	if (file == NULL)
	{
		printf("Failed to open file.\n");
		return;
	}

	fprintf(file, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
			interval_failed_questions, font_size,
			color_mode, best_streak_objective, current_streak_objective, best_streak_subjective, current_streak_subjective,
			total_tried_objective, total_right_objective,
			total_tried_subjective, total_right_subjective);

	fclose(file);
}

void loadUserInfo()
{
	FILE *file;
	char line[MAX_LINE_LENGTH];

	file = fopen("db/db_user_info.tsv", "r");
	if (file == NULL)
	{
		return;
	}

	fgets(line, MAX_LINE_LENGTH, file);

	sscanf(line, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
		   &interval_failed_questions, &font_size,
		   &color_mode, &best_streak_objective, &current_streak_objective, &best_streak_subjective, &current_streak_subjective,
		   &total_tried_objective, &total_right_objective,
		   &total_tried_subjective, &total_right_subjective);

	fclose(file);
}

void resetUserInfo()
{
	best_streak_objective = 0;
	current_streak_objective = 0;
	best_streak_subjective = 0;
	current_streak_subjective = 0;
	total_tried_objective = 0;
	total_right_objective = 0;

	total_tried_subjective = 0;
	total_right_subjective = 0;
}
