#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Ошибка при вызове fork
        perror("Ошибка fork");
        return 1;
    } else if (pid == 0) {
        // Дочерний процесс: запуск sequential_min_max с аргументами командной строки
        printf("Запуск sequential_min_max в дочернем процессе\n");

        // Замена процесса на sequential_min_max с передачей всех аргументов командной строки
        char *args[] = {"./sequential_min_max", "8745", "55", NULL};
        if (execvp(args[0], args) == -1) {
            perror("exec failed");
            exit(1);
        }
        // Если execv вернулся, значит произошла ошибка
        perror("Ошибка execv");
        exit(1);
    } else {
        // Родительский процесс: ожидание завершения дочернего процесса
        int status;
        waitpid(pid, &status, 0); // Ожидание завершения дочернего процесса

        if (WIFEXITED(status)) {
            printf("Дочерний процесс завершился с кодом %d\n", WEXITSTATUS(status));
        } else {
            printf("Дочерний процесс завершился с ошибкой\n");
        }
    }

    return 0;
}
