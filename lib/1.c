#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


static int barspeed = 1000;

void pbarr() {

	int i;
	char * t="#";

	printf("[");


	//for(i=0;i<=100;i++) {
	for(i=0;i<=50;i++) {
		printf("%s", t);
		fflush(stdout);
		usleep(barspeed);
		}

//	printf("]\n");

}

void pbarr2() {

	int i;
	char * t="#";

//	printf("[");


	//for(i=0;i<=100;i++) {
	for(i=0;i<=50;i++) {
		printf("%s", t);
		fflush(stdout);
		usleep(barspeed);
		}

	printf("]\n");

}


char filename[100000];


char split(char *url)  {

	char str[100000];

        strcpy(str, url);

	int init_size = strlen(str);
	char delim[] = "/";

	char *ptr = strtok(str, delim);
	char arr[100000];

	while(ptr != NULL)  {

		(void)strncpy(arr, ptr, sizeof(arr));
		ptr = strtok(NULL, delim);
	}

	strcpy(filename, arr);

}


char redirect[3024];

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


char getfile(char * httpurl, char * path) {


    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    	size_t written = fwrite(ptr, size, nmemb, stream);
    	return written;
    }

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = httpurl;
    char outfilename[FILENAME_MAX];
    strcpy(outfilename, path);

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &url);

	if (url)
	   strcpy(redirect, url);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}



char totalpath[10000000];



int exec(char * download) {

	split(download); 
	char buff[FILENAME_MAX];
        getcwd( buff, FILENAME_MAX );

        strncat(totalpath, buff, 1000); 
        strncat(totalpath, "/", 5); 
        strncat(totalpath, filename, 1000); 

	getfile(download, totalpath);
	size_t arrlen = strlen(redirect);

	pbarr();
	
	if (arrlen != 0) {
		barspeed = 5000; 
		getfile(redirect, totalpath);
		pbarr2();
	}

	else {
		printf("]\n");             
 
	}


}

