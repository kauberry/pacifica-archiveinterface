#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *id2dirandfilename(int id)
{

	
	char * s;
	char * d = "";
	char * ff = "";
	char * f;
	char * stemp;
	char * dtemp;
	char subStemp[3];
	size_t sz;
	sz = snprintf(NULL, 0, "%x", id);
	s = (char *)malloc(sz + 1);
	snprintf(s, sz+1, "%x", id);

	//need to get the len of s before looping
	while (strlen(s) > 2 )
	{
		//get the last two characters of the s string to set to d
		sz = (strlen(s) -2); //starting point for the last two characters of s
		memcpy(subStemp, &s[sz],2);
		subStemp[2] = '\0';


		//copy d into a temp variable so that we can reuse the values
		sz = snprintf(NULL, 0, "%s", d);
		dtemp = (char *)malloc(sz + 1);
		strcpy(dtemp,d);
		//need to free d if it has size
		if(strlen(d) >0)
		{
			free(d);
		}


		//set d
		sz = snprintf(NULL, 0, "%s/%s", dtemp,subStemp);
		d = (char *)malloc(sz + 1);
		snprintf(d, sz+1, "%s/%s", dtemp,subStemp);
		free(dtemp);


		//copy s to a temp
		stemp = (char *)malloc(strlen(s) + 1); //create a temp string to hold the value;
		strcpy(stemp,s);
		free(s);

		//substring out s
		s = (char *)malloc(strlen(stemp) - 1); //subtract 1 here because we want 2 substring off 2, but still need to add 1 for string termination
		strncpy(s, stemp, (strlen(stemp) -2));
		free(stemp);

		
	}

	if ( strcmp( d, "" ) == 0 )
	{
		//set d
		d = "/";

		//set f
		sz = snprintf(NULL, 0, "file.%s", s);
		f = (char *)malloc(sz + 1);
		snprintf(f, sz+1, "file.%s", s);

		//set ff
		sz = snprintf(NULL, 0, "/%s", f);
		ff = (char *)malloc(sz + 1);
		snprintf(ff, sz+1, "/%s", f);

		//free up the memory for f and d (not ff since we need to return it)
		free(f);

	}
	else
	{
		sz = snprintf(NULL, 0, "%x", id);
		f = (char *)malloc(sz + 1);
		snprintf(f, sz+1, "%x", id);

		//set ff
		sz = snprintf(NULL, 0, "%s/%s", d,f);
		ff = (char *)malloc(sz + 1);
		snprintf(ff, sz+1, "%s/%s", d,f);

		//free up the memory for f and d (not ff since we need to return it)
		free(f);
		free(d);
	}

  	free(s);

	return ff;
}

char *id2filename(int id)
{
	char * filename = id2dirandfilename(id);
	return filename;
}

int checkisdigit(char* arg)
{
	int length = strlen(arg);
	int i = 0;
	int tmp;
	for(i=0; i < length; i++)
	{
		tmp = arg[i];
		if(!isdigit(tmp))
		{
			return 0;
		}
	}

}

int main(int argc, char * argv[])
{
	if (argc > 1) //make sure that an id was passed in
	{
		if( checkisdigit(argv[1]))
		{
			char * arg = argv[1];
			int id = atoi(arg);
			char * filename = id2filename(id);
			printf("%s\n",filename);
		}
		else
		{
			printf("No valid integer passed in\n");
		}
	}
	else
	{
		printf("Incorrect Number of Arguments passed in, missing Id\n");
	}
	return 0;
}