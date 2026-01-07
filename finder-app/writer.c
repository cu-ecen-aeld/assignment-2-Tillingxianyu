#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syslog.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[])
{
        openlog("aesdwriter", LOG_PID, LOG_USER);

        if (argc < 3)
        {
            syslog(LOG_ERR, "not value %d", argc-1);
            fprintf(stderr, "ERROR:<file> <string>");
            closelog();
            return 1;
        }
        
        const char *writefile = argv[1];
        const char *writestr = argv[2];

        syslog(LOG_DEBUG, "Writing %s to %s",writestr,writefile);
        int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC,0644);
        if (fd == -1)
        {
            syslog(LOG_ERR, "file %s doens't exist : %s", writefile,strerror(errno));
            closelog();
            return 1;
        }

       ssize_t a = write(fd,writestr,strlen(writestr));
       if ( a == -1)
       {
            syslog(LOG_ERR, "could not write file %s : %s",writefile,strerror((errno)));
            close(fd);
            closelog();
            return 1;
        }else if (a != strlen(writestr)) {
            syslog(LOG_ERR, "ERROR%s",writestr);
        }

        close(fd);
        closelog();
        return  0;

        
        }



