

#include "ucode.c"
char cwd[256];
	char * t1 = "xwrxwrxwr-------";
	char * t2 = "----------------";


is_DIR(u16 mode){
if((mode & 0xF000)== 0x4000){
			return 1;
		}
		return 0;
}
is_REG(u16 mode){
	if((mode & 0xF000)==0x8000){
			return 1;
		}
		return 0;
}
is_LINK(u16 mode){
	if((mode & 0xF000)== 0xA000){
			return 1;
		}
		return 0;
}


void ls_file(char * file)
{
	int i=0;
	STAT s;
	
	stat(file, &s);

	//checks for correct mode
	if(is_REG(s.st_mode)){
		printf("-");
	}
	else if(is_DIR(s.st_mode)){
		printf("d");

	}
		
	else if(is_LINK(s.st_mode)){
		printf("l");

	}

		//prints relevent data
	printf("%d %d %d %d %s\n ", s.st_nlink, s.st_gid, s.st_uid, s.st_size,file);

		
      //shows link file
	if(is_LINK(s.st_mode))
	{
		prints(" -> ");
		char link[256];
		readlink(file, link);
		prints(link);
	}
}

void ls_dir(char * dname)
{
	int dir;
	char *cp;
	char buf[MAX],temp[256];

	DIR *dp;
printf("directory: %s\n",dname);
	//opens the directory
	dir = open(dname, O_RDONLY);
	//reads 1024 to buffer
	read(dir, buf, MAX);
	//sets cp to buf
	cp = buf;
	//convert buf to a directory
	dp = (DIR*) buf;
	while(cp < 1024 + buf)
	{
		strncpy(temp, dp->name, dp->name_len);
		temp[dp->name_len] = '\0';
		ls_file(temp);
		cp += dp->rec_len;
		dp = (DIR*)cp;
	}
}

int main(int argc, char * argv[])
{

	printf("\n---------------------------------\n");
	printf("Paul Dibble's ls\n");
	printf("---------------------------------\n");
	getcwd(cwd);
	
	//no filepath givin
	if(argc < 2)
	{
		ls_dir(cwd);
	}

	else
	{
		STAT s;
		stat(argv[1], &s);
		if(is_DIR(s.st_mode))
			ls_dir(argv[1]);
		else
			ls_file(argv[1]);
	}

	return 0;
}
