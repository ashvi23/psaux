#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <pwd.h>
#include <time.h>
#include <sys/times.h>
int error=0;
//HEADER
char* getUsername(uid_t uid);
char* parseStatus(char* pid, int lineNum);
char* getRSS(char* pid);
char* parseMem( int);
char*getVSZ(char* pid);
char* getState(char* pid);
char* parseCMD(char*pid, int lineNum);
char* getStart(char* pid);

/*char* getStart(char* pid){
	char* path = (char*)malloc(5+16*sizeof(char));
	path[0]='\0';
	strcpy(path, "/proc/");
	strcat(path, pid);
	strcat(path, "/stat");
	FILE* fp = fopen(path, "r");
	if(!fp){ 
		printf("Error\n");
	}
	int lineCounter =0;
	char* start;// = (char*)malloc(strlen(tempLine)+1 * sizeof(char));
	char* buffer = NULL;
	size_t size=0;
	ssize_t lsize ;
	int lineNum = 1;
	while(lsize >=0){
		
		lineCounter++;
		lsize = getline(&buffer, &size, fp);
		//printf("BUFFER: %s\n", buffer);
		if(lineCounter == lineNum){
			//getline();
			//printf();
			free(path);
			fclose(fp);
			int i =0;
			char* token = strtok(buffer, " ");
			for(i=0; i< 22;i++){
				token = strtok(NULL, " ");
			}
			int tok = atoi(token);
			long int time = sysconf(215842741);
			printf("token: %ld\n", time);
			
			
			time_t now;
			time(&now);
			char* cur= (char*) malloc(41* sizeof(char));
			cur[40] = '\0';
			cur = ctime(&now);
			char* mmdd = (char*) malloc(6* sizeof(char));
			mmdd[0] = '\0';
			char* mm= (char*) malloc(3* sizeof(char));
			mm[2] = '\0';
			char* dd= (char*) malloc(3* sizeof(char));
			dd[2] = '\0';
			dd[1] = 'a';
			dd[0] = 'a';
			mm=strtok(cur, " ");
			mm=strtok(NULL, " ");
			dd=strtok(NULL, " ");
			if(dd[1] == 'a'){
				dd[1] = dd[0];
				dd[0] = '0';
			}
			strcat(mmdd,mm );
			strcat(mmdd,dd );
			
			
			return buffer;	
		}
	}
	
	fclose(fp);	
	return "Error";

}*/

char* parseCMD(char* pid, int lineNum){
	//int n = numdigits(atoi(pid));
	
	char* path = (char*)malloc(5+16*sizeof(char));
	
	path[0]='\0';
	strcpy(path, "/proc/");
	strcat(path, pid);
	if(error ==1 ){
	strcat(path, "/comm");}
	else {
	strcat(path, "/cmdline");
	}
	FILE* fp = fopen(path, "r");
	if(!fp){ 
		printf("error\n");
		return "Error";
	}
	
	int lineCounter =0;
	char* line;// = (char*)malloc(strlen(tempLine)+1 * sizeof(char));
	char* buffer = NULL; 
	size_t size=0;
	ssize_t lsize ;
	while(lsize >=0){
		
		lineCounter++;
		lsize = getline(&buffer, &size, fp);
		//printf("BUFFER: %s\n", buffer);
		if(lineCounter == lineNum){
			//getline();
			//printf();
			
			free(path);
			fclose(fp);
			int c=0;
			while(c < lsize){
				//printf("%d:[%c]",buffer[c]);
				if(buffer[c] =='\0'){
				buffer[c] = ' ';} 
				c++;
			}
			return buffer;	
			//break;
		}
	}

	fclose(fp);	
	return;
} 
char* getState(char* pid){
	char* state= (char*) malloc(5* sizeof(char)); 
	// how to get minor code
	char s[20];
	char* line = parseStatus(pid, 3);
	sscanf(line,"%s %s", s, state);
	//printf("LINE: %s\n", line);
	return state;
}
char*getVSZ(char* pid){
	char* vsz = (char*) malloc(15* sizeof(char));
	char vn[15];
	char* line = parseStatus(pid, 14);
	sscanf(line, "%s %s", vn, vsz);
	return vsz;
}
char* parseMem(int lineNum){
	//int n = numdigits(atoi(pid));
	char* path = (char*)malloc(5+16*sizeof(char));
	path[0]='\0';
	strcpy(path, "/proc/");
	//strcat(path, pid);
	strcat(path, "/meminfo");
	FILE* fp = fopen(path, "r");
	if(!fp){ 
 		printf("error\n");
	}
	int lineCounter =0;
	char* line;// = (char*)malloc(strlen(tempLine)+1 * sizeof(char));
	char* buffer = NULL;
	size_t size=0;
	ssize_t lsize ;
	while(lsize >=0){
		
		lineCounter++;
		lsize = getline(&buffer, &size, fp);
		//printf("BUFFER: %s\n", buffer);
		if(lineCounter == lineNum){
			//getline();
			//printf();
			free(path);
			fclose(fp);
			
	
			return buffer;	
			//break;
		}
	}

	
	fclose(fp);	
	return;
} 

char* getRSS(char* pid){
	char* rs= (char*) malloc(15* sizeof(char));
	char r[30];
	char* line = parseStatus(pid, 18);
	sscanf(line, "%s %s", r, rs);
	//printf("LINE: %s\n", line);
	if(rs[0] == 'f'){
		return "Error";
	}
	else{
	return rs;
	}
}
char* parseStatus(char* pid, int lineNum){
	//int n = numdigits(atoi(pid));
	char* path = (char*)malloc(5+16*sizeof(char));
	path[0]='\0';
	strcpy(path, "/proc/");
	strcat(path, pid);
	strcat(path, "/status");
	FILE* fp = fopen(path, "r");
	if(!fp){ 
		printf("Error\n");
	}
	int lineCounter =0;
	char* line;// = (char*)malloc(strlen(tempLine)+1 * sizeof(char));
	char* buffer = NULL;
	size_t size=0;
	ssize_t lsize ;
	while(lsize >=0){
		
		lineCounter++;
		lsize = getline(&buffer, &size, fp);
		//printf("BUFFER: %s\n", buffer);
		if(lineCounter == lineNum){
			//getline();
			//printf();
			free(path);
			fclose(fp);
			return buffer;	
		}
	}
	
	fclose(fp);	
	return "Error";
} 
char* getUsername(uid_t uid){
	struct passwd *p;
	p = getpwuid(uid);
	
	if(p==NULL){
		//printf("%d", uid);
		return "Error";
	}

	char* tempname = p->pw_name;
	if(tempname==NULL){
		return "Error";
	}
	int len = strlen(tempname);
	if(len<=0){
		return "Error";
	}
	char* username = (char*) malloc(len+1*sizeof(char));
	username[len]='\0';
	if(username==NULL){
		return "Error";
	}
	strncpy(username, tempname, len);
	if(username==NULL){
		return "Error";
	}
	//printf("FX username:%s\n", username);
	return username;
}
void processdir(const struct dirent *dir)
{
     //get uid
     char title[40];
     char* uids[200];
     char* line = parseStatus(dir->d_name, 9);
     char* username =NULL;
     char* tempuname;
     //username[99]= '\0';
     sscanf(line,"%s %s", title, uids);
     
     int uid = atoi(uids);
     tempuname = getUsername(uid);
     
     int len = strlen(tempuname);
     username=(char*) malloc(len+1* sizeof(char));
     username[len]='\0';
     strcpy(username, tempuname);
     //printf("RET uids:%s\n", username);
     
     
     //get rss
     char* rss = getRSS(dir->d_name);
     if(rss[0] == 'E'){
      rss= "0";
     error =1;
     }
     //get %mem
     char* buffer = parseMem(1);
	 char* mem= (char*) malloc(15* sizeof(char));
	 sscanf(buffer, "%s %s", title, mem);
	 float memtot;
	 if(error ==1){
	 memtot=0.0;
	
	 }
	 else{
	  memtot = atoi(rss)/atoi(mem);
	 }
	 //printf("pid:%s rss:%s mem: %s memtot:%.1f \n", dir->d_name, rss,mem, memtot);
	 //get vsz
	 char* vz = getVSZ(dir->d_name);
	 if(vz[1]=='/'|| vz[0] == '0'|| error ==1){
	 strcpy(vz, "0");
	 }
	 
	 //printf("PID:%s VZ:%s\n",dir->d_name, vz);
	 
	 //get state
	 char* state = getState(dir->d_name);
	 //printf("PID:%s State:%s\n", dir->d_name, state);

	 char* cmd = parseCMD(dir->d_name, 1);
	 
	 //printf("PID:%s CMD:%s\n", dir->d_name, cmd);
	 int ulen, plen, vzlen, rsslen, statelen, startlen, timelen, cmdlen;
	 ulen = strlen(username);
	 plen = strlen(dir->d_name);
	 vzlen = strlen(vz);
	 rsslen = strlen(rss);
	 cmdlen = strlen(cmd);
	 
	 
	 
     printf("%s\t%s\t0.0\t%.1f\t%s\t%s\t?\t%s\tSTART\tTIME\t%s\n", username, dir->d_name, memtot, vz, rss,state, cmd);
     free(line);
     free(username);
     error=0;
    // char* line = getStart(dir->d_name);
     
     
     //free(rss);
     //free(vz);
     //printf("%s %s\n", dir->d_name, username);
     
}

int filter(const struct dirent *dir)
{
     return !fnmatch("[1-9]*", dir->d_name, 0);// && user == dirinfo.st_uid;
}

int main() 
{
     /* Based on example in "man scandir" */

     struct dirent **namelist;
     int i,n;
	i=0;
     n = scandir("/proc", &namelist, filter, 0);
   
     if (n < 0)
	  perror("Not enough memory.");
     else {
     int i =0;
     printf( "USER\tPID\tCPU\t%MEM\tVSZ\tRSZ\tTTY\tSTAT\tSTART\tTIME\tCOMMAND\n");
	  while(i<n) {
	  	//printf("w:%d\t", i);
	       processdir(namelist[i]);
	       error=0;
	       free(namelist[i]);
	       i++;
	       
	       //break;
	  }
	  free(namelist);
     }
     return 0;
}
/* //gets only user data
     uid_t user;
     struct stat dirinfo;
     int len = strlen(dir->d_name) + 7; 
     char path[len];

     strcpy(path, "/proc/");
     strcat(path, dir->d_name);
     user = getuid();
     if (stat(path, &dirinfo) < 0) {
	  perror("processdir() ==> stat()");
	  exit(EXIT_FAILURE);
     }*/
