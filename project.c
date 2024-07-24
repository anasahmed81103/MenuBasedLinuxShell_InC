#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <sys/time.h>
#include <sys/utsname.h>



char *getHomeDirectory() {
    char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        fprintf(stderr, "Error: HOME environment variable not set.\n");
        exit(1);
    }
    return home_dir;
}


char* getCurrentWorkingDirectory() {
    char* cwd = NULL;
    size_t size = 1024;

    do {
        cwd = (char*)realloc(cwd, size);
        if (cwd == NULL) {
            perror("realloc");
            return NULL;
        }

        if (getcwd(cwd, size) != NULL) {
            return cwd;
        } else {
            if (errno == ERANGE) {
                size *= 2;
            } else {
                perror("getcwd");
                free(cwd);
                return NULL;
            }
        }
    } while (1);
}


void *directmake(void *args){

    char *home_dir = getHomeDirectory();

    char dirname[100];
    printf("Enter the directory name: ");
    scanf("%s", dirname);

    char path[200];
    snprintf(path, sizeof(path), "%s", dirname);

    int status = mkdir(path, S_IRWXU);

    if (status == 0) {
        printf("Directory created successfully.\n");
    } else {
        printf("Error creating directory.\n");
        perror("mkdir");
    }
    pthread_exit(0);

}


void *directrem(void *args){

    char *home_dir = getHomeDirectory();

    char dirname[100];
    printf("Enter the directory name(path): ");
    scanf("%s", dirname);

    char path[200];
    snprintf(path, sizeof(path), "%s", dirname);

    int status = rmdir(path);

    if (status == 0) {
        printf("Directory removed successfully.\n");
    } else {
        printf("Error removing directory.\n");
        perror("rmdir");
    }
    pthread_exit(0);

}


void *removeFile(void *args) {
    char *home_dir = getHomeDirectory();

    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    char path[200];
    snprintf(path, sizeof(path), "%s", filename);

    int status = unlink(path);

    if (status == 0) {
        printf("File removed successfully.\n");
    } else {
        printf("Error removing file.\n");
        perror("unlink");
    }
    pthread_exit(0);
}


void *removeDirWithContents(void *args) {
    char *home_dir = getHomeDirectory();

    char dirname[100];
    printf("Enter the directory name: ");
    scanf("%s", dirname);

    char path[200];
    snprintf(path, sizeof(path), "%s", dirname);

    int status = system(strcat("rm -rf ", path));

    if (status == 0) {
        printf("Directory removed successfully.\n");
    } else {
        printf("Error removing directory.\n");
        perror("system");
    }
    pthread_exit(0);
}


void *copyFile(void *args) {
    char *home_dir = getHomeDirectory();

    char source[100], dest[100];
    printf("Enter the source file name: ");
    scanf("%s", source);
    printf("Enter the destination file name: ");
    scanf("%s", dest);

    char source_path[200], dest_path[200];
    snprintf(source_path, sizeof(source_path), "%s", source);
    snprintf(dest_path, sizeof(dest_path), "%s", dest);

    char command[300];
    snprintf(command, sizeof(command), "cp %s %s", source_path, dest_path);

    int status = system(command);

    if (status == 0) {
        printf("File copied successfully.\n");
    } else {
        printf("Error copying file.\n");
        perror("system");
    }
    pthread_exit(0);
}


void *copyDirWithContents(void *args) {
    char *home_dir = getHomeDirectory();

    char source[100], dest[100];
    printf("Enter the source directory name: ");
    scanf("%s", source);
    printf("Enter the destination directory name: ");
    scanf("%s", dest);

    char source_path[200], dest_path[200];
    snprintf(source_path, sizeof(source_path), "%s",  source);
    snprintf(dest_path, sizeof(dest_path), "%s",  dest);

    char command[300];
    snprintf(command, sizeof(command), "cp -r %s %s", source_path, dest_path);

    int status = system(command);

    if (status == 0) {
        printf("Directory copied successfully.\n");
    } else {
        printf("Error copying directory.\n");
        perror("system");
    }
    pthread_exit(0);
}


void *moveFile(void *args) {
    char *home_dir = getHomeDirectory();

    char source[100], dest[100];
    printf("Enter the source file name: ");
    scanf("%s", source);
    printf("Enter the destination file name: ");
    scanf("%s", dest);

    char source_path[200], dest_path[200];
    snprintf(source_path, sizeof(source_path), "%s",  source);
    snprintf(dest_path, sizeof(dest_path), "%s",  dest);

    char command[300];
    snprintf(command, sizeof(command), "mv %s %s", source_path, dest_path);

    int status = system(command);

    if (status == 0) {
        printf("File moved successfully.\n");
    } else {
        printf("Error moving file.\n");
        perror("system");
    }
    pthread_exit(0);
}


void *moveDirWithContents(void *args) {
    char *home_dir = getHomeDirectory();

    char source[100], dest[100];
    printf("Enter the source directory name: ");
    scanf("%s", source);
    printf("Enter the destination directory name: ");
    scanf("%s", dest);

    char source_path[200], dest_path[200];
    snprintf(source_path, sizeof(source_path), "%s",  source);
    snprintf(dest_path, sizeof(dest_path), "%s",  dest);

    char command[300];
    snprintf(command, sizeof(command), "mv %s %s", source_path, dest_path);

    int status = system(command);

    if (status == 0) {
        printf("Directory moved successfully.\n");
    } else {
        printf("Error moving directory.\n");
        perror("system");
    }
    pthread_exit(0);
}

void *displayFile(void *args) {
    char *home_dir = getHomeDirectory();

    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    char path[200];
    snprintf(path, sizeof(path), "%s",  filename);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        perror("fopen");
        pthread_exit(0);
    }

    char line[256];
    printf("Contents of the file:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
    pthread_exit(0);
}


void *copyFileContent(void *args) {
    char *home_dir = getHomeDirectory();

    char source[100], dest[100];
    printf("Enter the source file name: ");
    scanf("%s", source);
    printf("Enter the destination file name: ");
    scanf("%s", dest);

    char source_path[200], dest_path[200];
    snprintf(source_path, sizeof(source_path), "%s", source);
    snprintf(dest_path, sizeof(dest_path), "%s", dest);

    int source_fd = open(source_path, O_RDONLY);
    if (source_fd == -1) {
        printf("Error opening source file.\n");
        perror("open");
        pthread_exit(0);
    }

    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        printf("Error opening destination file.\n");
        perror("open");
        close(source_fd);
        pthread_exit(0);
    }

    char buffer[1024];
    ssize_t bytes_read, bytes_written;
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            printf("Error writing to destination file.\n");
            perror("write");
            close(source_fd);
            close(dest_fd);
            pthread_exit(0);
        }
    }

    if (bytes_read == -1) {
        printf("Error reading from source file.\n");
        perror("read");
    }

    close(source_fd);
    close(dest_fd);
    printf("File content copied successfully.\n");
    pthread_exit(0);
}


void *copyMultipleFilesToOne(void *args) {
    char *home_dir = getHomeDirectory();

    char source1[100], source2[100], dest[100];
    printf("Enter the first source file name: ");
    scanf("%s", source1);
    printf("Enter the second source file name: ");
    scanf("%s", source2);
    printf("Enter the destination file name: ");
    scanf("%s", dest);

    char source1_path[200], source2_path[200], dest_path[200];
    snprintf(source1_path, sizeof(source1_path), "%s",  source1);
    snprintf(source2_path, sizeof(source2_path), "%s", source2);
    snprintf(dest_path, sizeof(dest_path), "%s",  dest);

    int source1_fd = open(source1_path, O_RDONLY);
    if (source1_fd == -1) {
        printf("Error opening first source file.\n");
        perror("open");
        pthread_exit(0);
    }

    int source2_fd = open(source2_path, O_RDONLY);
    if (source2_fd == -1) {
        printf("Error opening second source file.\n");
        perror("open");
        close(source1_fd);
        pthread_exit(0);
    }

    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        printf("Error opening destination file.\n");
        perror("open");
        close(source1_fd);
        close(source2_fd);
        pthread_exit(0);
    }

    char buffer[1024];
    ssize_t bytes_read, bytes_written;
    while ((bytes_read = read(source1_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            printf("Error writing to destination file.\n");
            perror("write");
            close(source1_fd);
            close(source2_fd);
            close(dest_fd);
            pthread_exit(0);
        }
    }

    if (bytes_read == -1) {
        printf("Error reading from first source file.\n");
        perror("read");
        close(source1_fd);
        close(source2_fd);
        close(dest_fd);
        pthread_exit(0);
    }

    while ((bytes_read = read(source2_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            printf("Error writing to destination file.\n");
            perror("write");
            close(source1_fd);
            close(source2_fd);
            close(dest_fd);
            pthread_exit(0);
        }
    }

    if (bytes_read == -1) {
        printf("Error reading from second source file.\n");
        perror("read");
        close(source1_fd);
        close(source2_fd);
        close(dest_fd);
        pthread_exit(0);
    }

    close(source1_fd);
    close(source2_fd);
    close(dest_fd);
    printf("Files content copied to %s successfully.\n", dest);
    pthread_exit(0);
}



void *displayPublicIP(void *args) {
    system("curl -s ifconfig.me");
    pthread_exit(0);
}



void *displayPrivateIP(void *args) {
    char hostname[1024];
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname");
        pthread_exit(0);
    }

    struct addrinfo hints, *res, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        perror("getaddrinfo");
        pthread_exit(0);
    }

    char ip_address[INET_ADDRSTRLEN];
    for (p = res; p != NULL; p = p->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        if (inet_ntop(AF_INET, &ipv4->sin_addr, ip_address, sizeof(ip_address)) != NULL) {
            printf("Private IP Address: %s\n", ip_address);
            break;
        }
    }

    freeaddrinfo(res);
    pthread_exit(0);
}



void *displayAllNetworkInterfaces(void *args) {
    system("ifconfig -a");
    pthread_exit(0);
}


void *testPing(void *args) {
    struct sockaddr_in serv_addr;
    struct hostent *server;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        pthread_exit(0);
    }

    server = gethostbyname("google.com");
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        pthread_exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(80);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        perror("Error connecting");
        pthread_exit(0);
    }

    printf("Ping successful!\n");

    close(sockfd);
    pthread_exit(0);
}


void *downloadFile(void *args) {
    char url[256];
    printf("Enter the URL of the file to download: ");
    scanf("%255s", url);

    pid_t pid = fork();

    if (pid == 0) {
        execlp("wget", "wget", "-q", url, NULL);
        perror("Error executing wget");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Error forking process");
    } else {
        wait(NULL);
    }

    pthread_exit(0);
}


void *checkDateTime(void *args) {
    time_t now;
    time(&now);
    printf("Current date & time: %s", ctime(&now));
    pthread_exit(0);
}


void *setDateTime(void *args) {
    struct timeval tv;

    // Prompt user for date and time
    int year, month, day, hour, minute, second;
    printf("Enter the date and time (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", &year, &month, &day, &hour, &minute, &second);

    // Convert to seconds since epoch
    struct tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    tv.tv_sec = mktime(&tm);
    tv.tv_usec = 0;

    char cmd[100];
    snprintf(cmd, sizeof(cmd), "sudo date -s '@%ld'", tv.tv_sec);
    if (system(cmd) == -1) {
        perror("Error setting date & time");
        pthread_exit(0);
    }


    printf("Date & time set successfully.\n");

    pthread_exit(0);
}


void *compileCProgram(void *args) {
    char *home_dir = getHomeDirectory();

    char source_file[256];
    printf("Enter the name of the C source file to compile: ");
    scanf("%255s", source_file);

    char source[256];
    snprintf(source, sizeof(source), "%s",  source_file);

    char output_file[256];
    snprintf(output_file, sizeof(output_file), "%s.out", source_file);

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "gcc -o %s %s", output_file, source);
    if (system(cmd) == -1) {
        perror("Error compiling C program");
        pthread_exit(0);
    }

    printf("C program compiled successfully.\n");

    pthread_exit(0);
}


void *compileCppProgram(void *args) {

    char *home_dir = getHomeDirectory();

    char source_file[256];
    printf("Enter the name of the C++ source file to compile: ");
    scanf("%255s", source_file);

    char source[256];
    snprintf(source, sizeof(source), "%s",  source_file);

    char output_file[256];
    snprintf(output_file, sizeof(output_file), "%s.out", source_file);

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "g++ -o %s %s", output_file, source);
    if (system(cmd) == -1) {
        perror("Error compiling C program");
        pthread_exit(0);
    }

    printf("C++ program compiled successfully.\n");

    pthread_exit(0);
}


void *compileAndRunCProgram(void *args) {
    char *home_dir = getHomeDirectory();

    char *curdir = getCurrentWorkingDirectory();

    char source_file[256];
    printf("Enter the name of the C source file to compile and run: ");
    scanf("%255s", source_file);

    char source[256];
    snprintf(source, sizeof(source), "%s",  source_file);

    char output_file[256];
    snprintf(output_file, sizeof(output_file), "%s.out", source_file);

    char cmd_compile[512];
    snprintf(cmd_compile, sizeof(cmd_compile), "gcc -o %s %s", output_file, source);
    if (system(cmd_compile) == -1) {
        perror("\nError compiling C program");
        pthread_exit(0);
    }

    char run[512];
    snprintf(run, sizeof(run), "%s/%s", curdir, output_file);


    pid_t pid = fork();

    if (pid == -1) {
        perror("\nError forking process");
        pthread_exit(0);
    } else if (pid == 0) {
        // Child process
        char *argv[] = {run, NULL};
        if (execvp(argv[0], argv) == -1) {
            perror("\nError running executable");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("\nExecutable finished with exit status: %d\n", WEXITSTATUS(status));
        } else {
            printf("\nExecutable terminated abnormally.\n");
        }
    }

    pthread_exit(0);
}


void *compileAndRunCppProgram(void *args) {
    char *home_dir = getHomeDirectory();

    char *curdir = getCurrentWorkingDirectory();

    char source_file[256];
    printf("Enter the name of the C++ source file to compile and run: ");
    scanf("%255s", source_file);

    char source[256];
    snprintf(source, sizeof(source), "%s",  source_file);

    char output_file[256];
    snprintf(output_file, sizeof(output_file), "%s.out", source_file);

    char cmd_compile[512];
    snprintf(cmd_compile, sizeof(cmd_compile), "g++ -o %s %s", output_file, source);
    if (system(cmd_compile) == -1) {
        perror("\nError compiling C program");
        pthread_exit(0);
    }

    char run[512];
    snprintf(run, sizeof(run), "%s/%s", curdir, output_file);


    pid_t pid = fork();

    if (pid == -1) {
        perror("\nError forking process");
        pthread_exit(0);
    } else if (pid == 0) {
        // Child process
        char *argv[] = {run, NULL};
        if (execvp(argv[0], argv) == -1) {
            perror("\nError running executable");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("\nExecutable finished with exit status: %d\n", WEXITSTATUS(status));
        } else {
            printf("\nExecutable terminated abnormally.\n");
        }
    }

    pthread_exit(0);
}


void *run(void *args) {
    char *home_dir = getHomeDirectory();

    char *curdir = getCurrentWorkingDirectory();

    char executable_file[256];
    printf("Enter the name of the executable file to run: ");
    scanf("%255s", executable_file);

    char executable_path[512];
    snprintf(executable_path, sizeof(executable_path), "%s/%s", curdir, executable_file);

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error forking process");
        pthread_exit(0);
    } else if (pid == 0) {
        // Child process
        char *argv[] = {executable_path, NULL};
        if (execvp(argv[0], argv) == -1) {
            perror("\nError running executable");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("\nExecutable finished with exit status: %d\n", WEXITSTATUS(status));
        } else {
            printf("\nExecutable terminated abnormally.\n");
        }
    }

    pthread_exit(0);
}



void *openfileintext(void *args){

    char *home_dir=getHomeDirectory();

    char openfile[256];
    printf("Enter the name of the file to open: ");
    scanf("%255s", openfile);

    char path[256];
    snprintf(path,sizeof(path),"%s",openfile);

    char cmd[512];
    snprintf(cmd,sizeof(cmd),"xdg-open %s",path);

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error forking process");
        pthread_exit(0);
    } else if (pid == 0) {
        if (system(cmd) == -1) {
            perror("\nError opening text editor");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("\nExecutable finished with exit status: %d\n", WEXITSTATUS(status));
        } else {
            printf("\nExecutable terminated abnormally.\n");
        }
    }


    pthread_exit(0);
}


int changeToHomeDirectory() {
    const char *homeDir = getenv("HOME");

    if (homeDir == NULL) {
        fprintf(stderr, "Error: HOME environment variable not set.\n");
        return -1;
    }

    int result = chdir(homeDir);

    if (result != 0) {
        perror("chdir");
        return -1;
    }

    printf("Current directory changed to: %s\n", homeDir);
    return 0;
}





///////////////////////////////////////////////////////////////////////////////////////////////////






void *cd_back_wrapper(void *arg);
void cd_back();

void *pwd(void *arg) {
    char *home_dir=getHomeDirectory();

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        printf("Error: Unable to get current working directory\n");
    }
    pthread_exit(0);
}


void *ls(void *arg) {
    char *home_dir=getHomeDirectory();
    printf("Files and directories on current path are:\n");
    system("ls");
    pthread_exit(NULL);
}


void *cd(void *arg) {
    char *home_dir=getHomeDirectory();
    char dir[1024]; // Directory path buffer

    printf("Enter directory: ");
    scanf("%s", dir); // Read directory name from user input

    if (chdir(dir) != 0) {
        printf("Error: Unable to change directory to %s\n", dir);
    }
    else{
        char *cur=getCurrentWorkingDirectory();
        printf("current directory changed to: %s\n",cur);
    }

	pthread_exit(0);
}


void *cd_back_wrapper(void *arg) {
    char *home_dir=getHomeDirectory();
    cd_back();
    pthread_exit(0);
}

void cd_back() {
    char *home_dir=getHomeDirectory();
    if (chdir("..") == -1) {
        perror("chdir");
    } else {
        printf("Moved to the previous directory.\n");
        char *cur=getCurrentWorkingDirectory();
        printf("current directory changed to: %s\n",cur);
    }
}


void *touch(void *arg) {
    char *home_dir=getHomeDirectory();
    char filename[1024];

    printf("Enter filename: ");
    scanf("%s", filename); // Read filename from user input

    // Attempt to create the file
    if (creat(filename, 0644) == -1) {
        perror("Error creating file");
    } else {
        printf("File '%s' created successfully.\n", filename);
    }

    pthread_exit(0);
}

void *grep(void *arg) {
    char *home_dir=getHomeDirectory();
    char pattern[1024];
    char filename[1024];

    printf("Enter pattern: ");
    scanf("%s", pattern);

    printf("Enter filename: ");
    scanf("%s", filename);

    char command[4096];
    snprintf(command, sizeof(command), "grep %s %s", pattern, filename);
    system(command);

    pthread_exit(0);
}

void *find(void *arg) {
    char *home_dir=getHomeDirectory();
    char directory[1024];
    char filename[1024];

    printf("Enter directory to search: ");
    scanf("%s", directory);

    printf("Enter filename to search: ");
    scanf("%s", filename);

    char command[4096];
    snprintf(command, sizeof(command), "find %s -name %s", directory, filename);
    system(command);

    pthread_exit(0);
}

void *ps(void *arg) {
    char *home_dir=getHomeDirectory();
    system("ps");
    pthread_exit(0);
}

void *kill_process(void *arg) {
    char *home_dir=getHomeDirectory();
    int pid;
    printf("Enter PID to kill: ");
    scanf("%d", &pid);

    // Attempt to kill the process
    if (kill(pid, SIGKILL) == 0) {
        printf("Process with PID %d has been successfully terminated.\n", pid);
    } else {
        perror("kill");
    }
    pthread_exit(NULL);
}

void *top(void *arg) {
    char *home_dir=getHomeDirectory();
    system("top");
    pthread_exit(0);
}

void *df(void *arg) {
    char *home_dir=getHomeDirectory();
    system("df");
    pthread_exit(0);
}

void *du(void *arg) {
    char *home_dir=getHomeDirectory();
    system("du");
    pthread_exit(0);
}

void *tar_archive(void *arg) {
    char *home_dir=getHomeDirectory();
    char directory[1024];
    char filename[1024];

    printf("Enter directory or file name to archive: ");
    scanf("%s", directory);

    printf("Enter archive filename: ");
    scanf("%s", filename);

    char command[4096];
    snprintf(command, sizeof(command), "tar -cf %s.tar %s", filename, directory);
    system(command);

    printf("Tar archive created successfully!\n");

    pthread_exit(0);
}


void *gzip_compress(void *arg) {
    char *home_dir=getHomeDirectory();
    char filename[1024];

    printf("Enter filename to compress: ");
    scanf("%s", filename);

    char command[4096];
    snprintf(command, sizeof(command), "gzip %s", filename);
    system(command);

    printf("File compressed successfully!\n");

    pthread_exit(0);
}

void *get_system_info(void *arg) {
    char *home_dir=getHomeDirectory();
    struct utsname info;
    if (uname(&info) == -1) {
        perror("uname");
        pthread_exit(NULL);
    }

    printf("System Information:\n");
    printf("  - Operating System: %s\n", info.sysname);
    printf("  - Node Name: %s\n", info.nodename);
    printf("  - Release: %s\n", info.release);
    printf("  - Version: %s\n", info.version);
    printf("  - Machine: %s\n", info.machine);

    pthread_exit(0);
}











int main(){


    printf(" Main Menu \n=============\n\n");
    printf("  1-create new directory\n  2-remove a directory \n  3-remove a file \n");
    printf("  4-remove a directory along with its components\n  5-copy a file\n  6- copy a directory (along with components)\n");
    printf("  7-move a file \n  8-move a directory along with its components \n");
    printf("  9-display a file \n 10-copy a files content to another\n");
    printf(" 11-copy multiple files into one (2) \n");
    printf(" 12-display your ip address(public)\n 13-display your ip-address(private)\n 14-display all network interfaces \n");
    printf(" 15-test ping with google \n 16-download a file from internet\n");
    printf(" 17-check date & time \n 18-set date & time \n 19-compile a c program\n 20-compile a c++ program\n");
    printf(" 21-run an executable file \n 22-compile and run c program\n 23- compile and run a c++ program\n");
    printf(" 24-open a file in text editor \n");
    printf(" 25-Show path for currect directory\n");
    printf(" 26-Show all files and directories at current location\n");
    printf(" 27-Change location to any file or directory located at current location\n");
    printf(" 28-Move to previous directory\n");
    printf(" 29-Create new file\n");
    printf(" 30-Search for a pattern in a file\n");
    printf(" 31-Find a file in a directory\n");
    printf(" 32- View running processes (ps)\n");
    printf(" 33- Kill a process (kill)\n");
    printf(" 34- View system processes (top)\n");
    printf(" 35- View disk space usage (df)\n");
    printf(" 36- View disk usage (du)\n");
    printf(" 37- Create tar\n");
    printf(" 38- Compress files using gzip\n");
    printf(" 39- To print system info\n");
    printf(" 40- Exit\n");

    changeToHomeDirectory();

    while(1){

        printf("choose: ");
        int input;
        scanf("%d",&input);

        switch(input){

            case 1:
                pthread_t p1;
                pthread_create(&p1,NULL,directmake,NULL);
                pthread_join(p1,NULL);
                break;
            case 2:
                pthread_t p2;
                pthread_create(&p2,NULL,directrem,NULL);
                pthread_join(p2,NULL);
                break;
            case 3:
                pthread_t p3;
                pthread_create(&p3, NULL, removeFile, NULL);
                pthread_join(p3, NULL);
                break;
            case 4:
                pthread_t p4;
                pthread_create(&p4, NULL, removeDirWithContents, NULL);
                pthread_join(p4, NULL);
                break;
            case 5:
                pthread_t p5;
                pthread_create(&p5, NULL, copyFile, NULL);
                pthread_join(p5, NULL);
                break;
            case 6:
                pthread_t p6;
                pthread_create(&p6, NULL, copyDirWithContents, NULL);
                pthread_join(p6, NULL);
                break;
            case 7:
                pthread_t p7;
                pthread_create(&p7, NULL, moveFile, NULL);
                pthread_join(p7, NULL);
                break;
            case 8:
                pthread_t p8;
                pthread_create(&p8, NULL, moveDirWithContents, NULL);
                pthread_join(p8, NULL);
                break;
            case 9:
                pthread_t p9;
                pthread_create(&p9, NULL, displayFile, NULL);
                pthread_join(p9, NULL);
                break;
            case 10:
                pthread_t p10;
                pthread_create(&p10, NULL, copyFileContent, NULL);
                pthread_join(p10, NULL);
                break;
            case 11:
                pthread_t p11;
                pthread_create(&p11, NULL, copyMultipleFilesToOne, NULL);
                pthread_join(p11, NULL);
                break;
            case 12:
                pthread_t p12;
                pthread_create(&p12, NULL, displayPublicIP, NULL);
                pthread_join(p12, NULL);
                break;
            case 13:
                pthread_t p13;
                pthread_create(&p13, NULL, displayPrivateIP, NULL);
                pthread_join(p13, NULL);
                break;
            case 14:
                pthread_t p14;
                pthread_create(&p14, NULL, displayAllNetworkInterfaces, NULL);
                pthread_join(p14, NULL);
                break;
            case 15:
                pthread_t p15;
                pthread_create(&p15, NULL, testPing, NULL);
                pthread_join(p15, NULL);
                break;
            case 16:
                pthread_t p16;
                pthread_create(&p16, NULL, downloadFile, NULL);
                pthread_join(p16, NULL);
                break;
            case 17:
                pthread_t p17;
                pthread_create(&p17, NULL, checkDateTime, NULL);
                pthread_join(p17, NULL);
                break;
            case 18:
                pthread_t p18;
                pthread_create(&p18, NULL, setDateTime, NULL);
                pthread_join(p18, NULL);
                break;
            case 19:
                pthread_t p19;
                pthread_create(&p19, NULL, compileCProgram, NULL);
                pthread_join(p19, NULL);
                break;
            case 20:
                pthread_t p20;
                pthread_create(&p20, NULL, compileCppProgram, NULL);
                pthread_join(p20, NULL);
                break;
            case 21:
                pthread_t p21;
                pthread_create(&p21, NULL, run, NULL);
                pthread_join(p21, NULL);
                break;
            case 22:
                pthread_t p22;
                pthread_create(&p22, NULL, compileAndRunCProgram, NULL);
                pthread_join(p22, NULL);
                break;
            case 23:
                pthread_t p23;
                pthread_create(&p23, NULL, compileAndRunCppProgram, NULL);
                pthread_join(p23, NULL);
                break;
            case 24:
                pthread_t p24;
                pthread_create(&p24,NULL,openfileintext,NULL);
                pthread_join(p24,NULL);
                break;
            case 25:
                pthread_t p25;
                pthread_create(&p25,NULL,pwd,NULL);
                pthread_join(p25,NULL);
                break;
            case 26:
                    pthread_t p26;
                    pthread_create(&p26,NULL,ls,NULL);
                    pthread_join(p26,NULL);
                    break;
            case 27:
                    pthread_t p27;
                    pthread_create(&p27,NULL,cd,NULL);
                    pthread_join(p27,NULL);
                    break;
            case 28:
                    pthread_t p28;
                    pthread_create(&p28, NULL, cd_back_wrapper, NULL);
                    pthread_join(p28, NULL);
                    break;
            case 29:
                pthread_t p29;
                pthread_create(&p29, NULL, touch, NULL);
                pthread_join(p29, NULL);
                break;
            case 30:
                pthread_t p30;
                pthread_create(&p30, NULL, grep, NULL);
                pthread_join(p30, NULL);
                break;
            case 31:
                pthread_t p31;
                pthread_create(&p31, NULL, find, NULL);
                pthread_join(p31, NULL);
                break;
            case 32:
                pthread_t p32;
                pthread_create(&p32, NULL, ps, NULL);
                pthread_join(p32, NULL);
                break;
            case 33:
                pthread_t p33;
                pthread_create(&p33, NULL, kill_process, NULL);
                pthread_join(p33, NULL);
                break;
            case 34:
                pthread_t p34;
                pthread_create(&p34, NULL, top, NULL);
                pthread_join(p34, NULL);
                break;
            case 35:
                pthread_t p35;
                pthread_create(&p35, NULL, df, NULL);
                pthread_join(p35, NULL);
                break;
            case 36:
                pthread_t p36;
                pthread_create(&p36, NULL, du, NULL);
                pthread_join(p36, NULL);
                break;
            case 37:
                pthread_t p37;
                pthread_create(&p37, NULL, tar_archive, NULL);
                pthread_join(p37, NULL);
                break;
            case 38:
                pthread_t p38;
                pthread_create(&p38, NULL, gzip_compress, NULL);
                pthread_join(p38, NULL);
                break;
            case 39:
                pthread_t p39;
                pthread_create(&p39, NULL, get_system_info, NULL);
                pthread_join(p39, NULL);
                break;
            case 40:
                exit(0);

            default:
                printf("no such input\n");

        }

    }




}
