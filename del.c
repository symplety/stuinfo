#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * head = "head.html";
char * foot= "footer.html";



int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  FILE * fd;
  char ch;
  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  fd=fopen("head.html", "r");
  if(fd==NULL){
     fprintf(cgiOut, "Cannot open file,head.html \n");
     return -1;
   }
   ch = fgetc(fd);

   while(ch != EOF){
     fprintf(cgiOut, "%c", ch);
     ch = fgetc(fd);
   }
  fclose(fd);
	char stuId[32] = "\0";
	int status = 0;


	status = cgiFormString("stuId",  stuId, 15);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}


	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);

	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "1", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	sprintf(sql,"delete from  information  where id='%s' and statu=0", stuId);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	fprintf(cgiOut, "delete stu ok!\n");
	mysql_close(db);

	return 0;
}
