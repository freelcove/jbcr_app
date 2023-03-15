#include "globals.h"

int main()
{

	// 전역 변수 Initialization
	initGlobals();

	loadUserInfo();

	// 콘솔창 Initialization.
	initScreen();

	// db를 저장할 questions[] 선언
	ObjectiveQuestion *objective_questions = malloc(sizeof(ObjectiveQuestion) * MAX_QUESTIONS);
	SubjectiveQuestion *subjective_questions = malloc(sizeof(SubjectiveQuestion) * MAX_QUESTIONS);

	// tsv 파일에서 데이터 불러와서 questions[] 배열에 저장
	readObjectiveQuestions(objective_questions);
	readSubjectiveQuestions(subjective_questions);

	// 히스토리를 저장할 queue 생성
	struct Queue *queue_objective = create_queue();
	struct Queue *queue_subjective = create_queue();

	readHistory(queue_objective, queue_subjective);

	// 만약 프로그램 첫 실행이라면 히스토리를 새로 채워 넣음.
	// enqueueRandom()로 db에 적힌 순서와 달리 랜덤하게 넣음.
	if (queue_objective->front == NULL)
	{
		enqueueRandom(queue_objective, num_objective_questions);
	}

	if (queue_subjective->front == NULL)
	{
		enqueueRandom(queue_subjective, num_subjective_questions);
	}

	const char *main_menu_items[] = {"1. 객관식 문제",
									 "2. 주관식 풀기",
									 "3. 기록",
									 "4. 옵션",
									 "5. 종료"};
	int num_main_menu_items = sizeof(main_menu_items) / sizeof(main_menu_items[0]);
	5;

	// 메인메뉴 = 5
	// 객관식 = 0
	// 주관식 = 1
	// 사용자 = 2
	// 옵션	= 3
	// 종료 = 4

	while (1)
	{
		clearScreen();
		switch (current_mode)
		{

			// current_mode = 메인메뉴
		case 5:

			drawTitle();
			drawMenu(num_main_menu_items, main_menu_items, 28, 16);
			controlMainMenu(processUserInput(num_main_menu_items));
			break;

			// current_mode = 객관식 문제
		case 0:
			all_process_objective(objective_questions, queue_objective);
			break;

			// current_mode = 주관식 문제
		case 1: {
			int solved_questions = 0;
			while (1) {
				int id = queue_subjective->front->key;

				faltcount = 0;
				check_subjective = 1;
				print_change_row(&subjective_questions[id].definition);
				printf("\n");
				printf("\t     정답을 입력하세요 : ");

				fgets(user_answer, sizeof(user_answer), stdin);
				user_answer[strcspn(user_answer, "\n")] = 0;

				if (check_subjective_correction(subjective_questions, id, queue_subjective)) {
					char error_message[100];
					sprintf(error_message, "%s은(는) 오답입니다.", user_answer);
					printf("\n\t     %s\n",error_message);

					printf("\t     정답은 ");
					SetConsoleTextAttribute(console, select_color(-1));
					printf("%s", subjective_questions[id].name);
					SetConsoleTextAttribute(console, color_mode_preset[color_mode % 4]);
					printf(" 입니다.\n");
					faltcount++;
					insert_after_x(queue_subjective, queue_subjective->front->key, interval_failed_questions);
					dequeue(queue_subjective);
				}

				clearInputBuffer();
				solved_questions++;
				printf("\t     다음 문제로 넘어가시려면 엔터를 누르세요.\n");
				printf("\t     종료를 원하시면 Esc를 누르세요.\n");
				current_menu = 0;
				int swit = 0;
				while (1) {
					if (kbhit()) {
						char input = getch();
						if (input == 'x' || input == 27) {
							swit = 1;
						}
						break;
					}
				}

				if (swit == 1) {
					exit_menu(solved_questions);
					check_subjective = 0;
					current_mode = 5;
					current_menu = 0;
					break;
				}

				clearScreen();
			}
		}
			  break;

			// current_mode = 기록
		case 2:
			drawTitle();
			char info0[50];
			sprintf(info0, "Best Streak: %d", best_streak);

			char info1[50];
			int objective_percentage = (total_tried_objective == 0) ? 0 : (double)total_right_objective / total_tried_objective * 100;
			sprintf(info1, "객관식 푼 문제 수: %d | 정답률: %d%%", total_tried_objective, objective_percentage);

			char info2[50];
			int subjective_percentage = (total_tried_subjective == 0) ? 0 : (double)total_right_subjective / total_tried_subjective * 100;
			sprintf(info2, "주관식 푼 문제 수: %d | 정답률: %d%%", total_tried_subjective, subjective_percentage);

			char *info_items[] = {info0, info1, info2, "기록 초기화", "뒤로 가기"};
			int num_info_items = sizeof(info_items) / sizeof(info_items[0]);

			drawMenu(num_info_items, info_items, 22, 16);
			controlInfo(processUserInput(num_info_items));
			break;
			drawTitle();

			// current_mode = 옵션
		case 3:
			drawTitle();
			char option0[50];
			sprintf(option0, "틀린 문제 재학습 주기: %02d", interval_failed_questions);

			char option1[20];
			sprintf(option1, "화면 크기: %d", font_size);

			char option2[20];
			sprintf(option2, "테마: %d", color_mode);

			char *option_items[] = {option0,
									option1,
									option2,
									"디폴트 값으로 옵션 초기화",
									"뒤로 가기"};
			int num_option_items = sizeof(option_items) / sizeof(option_items[0]);

			drawMenu(num_option_items, option_items, 25, 16);
			controlOptions(processUserInput(num_option_items));
			break;

			// current_mode = 종료
		case 4:
			printf("프로그램 종료");

			// db_history.tsv에 history를 저장
			writeHistory(queue_objective, queue_subjective);

			WriteUserInfo();

			// 동적할당한 메모리 해제
			free(objective_questions);
			free(subjective_questions);

			return 0;
		default:
			break;
		}
	}
	return 0;
}
