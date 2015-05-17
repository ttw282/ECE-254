/**
 * @file os/lab0/ls/ls_fname.c
 * @brief: OS lab0: simple ls command to list file names of a directory 
 * @date: 2012/09/16
 */

/* This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>          // printf() needs this, man 3 printf
#include <stdlib.h>         // exit() needs this, man 3 exit
#include <pwd.h>            // getpwuid()
#include <grp.h>            // getgrgid()
#include <time.h>           // ctime()
#include <string.h>         // strlen()

#define STRLEN1 128
#define STRLEN2 64



int 
main() 
{
	DIR *p_dir;
	p_dir = opendir(".");
	struct dirent *p_dirent;
	
	char str[] = "---";
	int size = 0;
	struct stat buf;
	char time = "";

	while ((p_dirent = readdir(p_dir)) != NULL) {
		char *str_path = p_dirent->d_name;	// relative path name!
		lstat(str_path, &buf);
		mode_t mode = buf.st_mode;

		off_t off = buf.st_size;
		
		const time_t atime = buf.st_atime;
		const time_t mtime = buf.st_mtime;
		const time_t ctime1 = buf.st_ctime;	

		if (str_path == NULL) {
			printf("Null pointer found!"); 
			exit(2);
		} else {

			str[0] = (mode & S_IRUSR) ? 'r' : '-';
			str[1] = (mode & S_IWUSR) ? 'w' : '-';
			str[2] = (mode & S_IXUSR) ? 'x' : '-';	
			str[3] = (mode & S_IRGRP) ? 'r' : '-';
			str[4] = (mode & S_IWGRP) ? 'w' : '-';
			str[5] = (mode & S_IXGRP) ? 'x' : '-';
			str[6] = (mode & S_IROTH) ? 'r' : '-';
			str[7] = (mode & S_IWOTH) ? 'w' : '-';
			str[8] = (mode & S_IXOTH) ? 'x' : '-';
			
			size = off;
					
			/* assume no sticky bit set */ 
			printf("%s %d %d %d %s %s %s %s\n", str, buf.st_uid, buf.st_gid, size, strtok(ctime(&atime), "\n"), strtok(ctime(&mtime), "\n"), strtok(ctime(&ctime1), "\n"), str_path);
		}
	}
	
	

	return 0;
}
