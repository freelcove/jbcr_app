int match(char* user_answer, char* subjective_questions) {
    int i = 0;
    while (user_answer[i] != '\0' && subjective_questions[i] != '\0') {
        if (user_answer[i] != subjective_questions[i]) {
            return 1;
        }
        i++;
    }
    if (user_answer[i] != '\0' || subjective_questions[i] != '\0') {
        return 1;
    }

    return 0;
}
